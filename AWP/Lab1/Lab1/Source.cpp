
#include <Windows.h>
#include <iostream>
#include <sysinfoapi.h>
#include <time.h>
#include <xmmintrin.h>

using namespace std;

const int N = 64;

void loop(float* res_ms, float const_value, float* string_ms, int Kd16)
{
	for (int i = 0; i < 16*Kd16; i++){
		res_ms[i] += const_value * string_ms[i];
	}
}

void auto_vectorize(float ****left, float ****right, float ****res, unsigned K)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				for (int a = 0; a < K; a++)
					for (int c = 0; c < K; c++)
						loop(res[i][j][a], left[i][k][a][c], right[k][j][c], K >> 4);
}
void my_vectorize(float**** left, float**** right, float**** res, unsigned K)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				for (int a = 0; a < K; a++)
					for (int c = 0; c < K; c++) {
						__m128 const_value = _mm_set1_ps(left[i][k][a][c]);
						for (int b = 0; b < K; b += 4) {
							__m128 string_value = _mm_load_ps(&right[k][j][c][b]);
							__m128 res_value = _mm_load_ps(&res[i][j][a][b]);
							res_value = _mm_add_ps(res_value, _mm_mul_ps(string_value, const_value));
							_mm_store_ps(&res[i][j][a][b], res_value);
						}
					}
}

void init_matrix(float**** &matrix, int n, int k, bool is_rand)
{
	srand(time(0));
	matrix = (float****)_aligned_malloc(n * sizeof(float***), 16);
	if (!matrix) throw exception();
	for (int i = 0; i < n; i++) {
		matrix[i] = (float***)_aligned_malloc(n * sizeof(float**), 16);
		if (!(matrix[i])) throw exception();
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (float**)_aligned_malloc(k * sizeof(float*), 16);
			if (!(matrix[i][j])) throw exception();
			for (int a = 0; a < k; a++) {
				matrix[i][j][a] = (float*)_aligned_malloc(k * sizeof(float), 16);
				if (!(matrix[i][j][a])) throw exception();
				for (int b = 0; b < k; b++)
					matrix[i][j][a][b] = is_rand?(double)(rand() / 100):0;
			}
		}
	}
}

int main()
{
	while (1) {
		unsigned int K;
		cout << "input contains matrix size: ";
		cin >> K;
		if (K % 16) return 1;
		float**** matrix[3];
		for (int i = 0; i < 3; i++)
			init_matrix(matrix[i], N, K, i != 2);
		DWORD start = GetTickCount64();
		auto_vectorize(matrix[0], matrix[1], matrix[2], K);
		DWORD duration = GetTickCount64() - start;
		cout << "auto_vec: " << duration << " ticks" << endl;
		start = GetTickCount64();
		my_vectorize(matrix[0], matrix[1], matrix[2], K);
		duration = GetTickCount64() - start;
		cout << "my_vec: " << duration << " ticks" << endl;
	}
	system("pause > NUL");
	return 0;
}
///линия памяти кратна 64 