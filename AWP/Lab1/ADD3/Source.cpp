
#include <Windows.h>
#include <iostream>
#include <sysinfoapi.h>
#include <time.h>
#include <xmmintrin.h>

using namespace std;

const int N = 1024;
const int CACHE_LINE_LENGTH = 64;

void without_optimiztion(float** left, float** right, float** res)
{
	for (int i = 0; i < N; i++)
		for (int k = 0; k < N; k++)
			for (int j = 0; j < N; j++) {
				res[i][j] += left[i][k] * right[k][j];
			}
}

void with_optimiztion(float** left, float** right, float** res)
{
	for (int x = 0; x < N; x += CACHE_LINE_LENGTH)
		for (int y = 0; y < N; y += CACHE_LINE_LENGTH)
			for (int a = 0; a < N; a += CACHE_LINE_LENGTH)
				for (int i = x; i < CACHE_LINE_LENGTH + x; i++)
					for (int j = y; j < CACHE_LINE_LENGTH + y; j++)
						for (int k = a; k < CACHE_LINE_LENGTH+a; k++){
							res[i][j] += left[i][k] * right[k][j];
						}
}

void init_matrix(float**& matrix, int n, bool is_rand)
{
	srand(time(0));
	matrix = (float**)_aligned_malloc(n * sizeof(float*), CACHE_LINE_LENGTH);
	if (!matrix) throw exception();
	for (int i = 0; i < n; i++) {
		matrix[i] = (float*)_aligned_malloc(n * sizeof(float), CACHE_LINE_LENGTH);
		if (!(matrix[i])) throw exception();
		for (int j = 0; j < n; j++)
		matrix[i][j] = is_rand ? ((double)rand() / 100) : 0;
	}
}

void clear_matrix(float** matrix)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			matrix[i][j] = 0;
}

int main()
{
	float** matrix[3];
	for (int i = 0; i < 3; i++)
		init_matrix(matrix[i], N, i != 2);
	DWORD start = GetTickCount64();
	without_optimiztion(matrix[0], matrix[1], matrix[2]);
	DWORD duration = GetTickCount64() - start;
	cout << "not optimized: " << duration << " ticks" << endl << matrix[2][0][0] << endl;
	start = GetTickCount64();
	clear_matrix(matrix[2]);
	with_optimiztion(matrix[0], matrix[1], matrix[2]);
	duration = GetTickCount64() - start;
	cout << "optimaze: " << duration << " ticks" << endl << matrix[2][0][0] << endl;
	system("pause > NUL");
	return 0;
}