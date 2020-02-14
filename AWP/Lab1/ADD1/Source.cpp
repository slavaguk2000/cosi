
#include <Windows.h>
#include <iostream>
#include <sysinfoapi.h>
#include <time.h>
#include <xmmintrin.h>

using namespace std;

const int N = 64;
const int K = 4;

void loop(float* res_ms, float const_value, float* string_ms)
{
	for (int i = 0; i < K; i++) {
		res_ms[i] += const_value * string_ms[i];
	}
}

void auto_vectorize(float**** left, float**** right, float**** res)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				for (int a = 0; a < K; a++)
					for (int c = 0; c < K; c++)
						loop(res[i][j][a], left[i][k][a][c], right[k][j][c]);
}
void my_vectorize(float**** left, float**** right, float**** res)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int a = 0; a < K; a++){
				__m128 res_value = _mm_load_ps(res[i][j][a]);
				
				__m128 const_value = _mm_set1_ps(*left[i][0][a]);
				__m128 string_value = _mm_load_ps(*right[0][j]);
				res_value = _mm_add_ps(res_value, _mm_mul_ps(string_value, const_value));

				const_value = _mm_set1_ps(*left[i][1][a]);
				string_value = _mm_load_ps(*right[1][j]);
				res_value = _mm_add_ps(res_value, _mm_mul_ps(string_value, const_value));

				const_value = _mm_set1_ps(*left[i][2][a]);
				string_value = _mm_load_ps(*right[2][j]);
				res_value = _mm_add_ps(res_value, _mm_mul_ps(string_value, const_value));

				const_value = _mm_set1_ps(*left[i][3][a]);
				string_value = _mm_load_ps(*right[3][j]);
				res_value = _mm_add_ps(res_value, _mm_mul_ps(string_value, const_value));

				_mm_store_ps(res[i][j][a], res_value);

				__m128 res_value1 = _mm_load_ps(res[i][j][a]);

				__m128 const_value1 = _mm_set1_ps(*(left[i][0][a] + 1));
				__m128 string_value1 = _mm_load_ps(*(right[0][j] + 1));
				res_value1 = _mm_add_ps(res_value1, _mm_mul_ps(string_value1, const_value1));
				const_value1 = _mm_set1_ps(*(left[i][1][a] + 1));
				string_value1 = _mm_load_ps(*(right[1][j] + 1));
				res_value1 = _mm_add_ps(res_value1, _mm_mul_ps(string_value1, const_value1));
				const_value1 = _mm_set1_ps(*(left[i][2][a] + 1));
				string_value1 = _mm_load_ps(*(right[2][j] + 1));
				res_value1 = _mm_add_ps(res_value1, _mm_mul_ps(string_value1, const_value1));
				const_value1 = _mm_set1_ps(*(left[i][3][a] + 1));
				string_value1 = _mm_load_ps(*(right[3][j] + 1));
				res_value1 = _mm_add_ps(res_value1, _mm_mul_ps(string_value1, const_value1));

				_mm_store_ps(res[i][j][a], res_value1);

				__m128 res_value2 = _mm_load_ps(res[i][j][a]);

				__m128 const_value2 = _mm_set1_ps(*(left[i][0][a] + 2));
				__m128 string_value2 = _mm_load_ps(*(right[0][j] + 2));
				res_value2 = _mm_add_ps(res_value2, _mm_mul_ps(string_value2, const_value2));
				const_value2 = _mm_set1_ps(*(left[i][1][a] + 2));
				string_value2 = _mm_load_ps(*(right[1][j] + 2));
				res_value2 = _mm_add_ps(res_value2, _mm_mul_ps(string_value2, const_value2));
				const_value2 = _mm_set1_ps(*(left[i][2][a] + 2));
				string_value2 = _mm_load_ps(*(right[2][j] + 2));
				res_value2 = _mm_add_ps(res_value2, _mm_mul_ps(string_value2, const_value2));
				const_value2 = _mm_set1_ps(*(left[i][3][a] + 2));
				string_value2 = _mm_load_ps(*(right[3][j] + 2));
				res_value2 = _mm_add_ps(res_value2, _mm_mul_ps(string_value2, const_value2));

				_mm_store_ps(res[i][j][a], res_value2);

				__m128 res_value3 = _mm_load_ps(res[i][j][a]);

				__m128 const_value3 = _mm_set1_ps(*(left[i][0][a] + 3));
				__m128 string_value3 = _mm_load_ps(*(right[0][j] + 3));
				res_value3 = _mm_add_ps(res_value3, _mm_mul_ps(string_value3, const_value3));
				const_value3 = _mm_set1_ps(*(left[i][1][a] + 3));
				string_value3 = _mm_load_ps(*(right[1][j] + 3));
				res_value3 = _mm_add_ps(res_value3, _mm_mul_ps(string_value3, const_value3));
				const_value3 = _mm_set1_ps(*(left[i][2][a] + 3));
				string_value3 = _mm_load_ps(*(right[2][j] + 3));
				res_value3 = _mm_add_ps(res_value3, _mm_mul_ps(string_value3, const_value3));
				const_value3 = _mm_set1_ps(*(left[i][3][a] + 3));
				string_value3 = _mm_load_ps(*(right[3][j] + 3));
				res_value3 = _mm_add_ps(res_value3, _mm_mul_ps(string_value3, const_value3));

				_mm_store_ps(res[i][j][a], res_value3);
			}
}

void init_matrix(float****& matrix, int n, int k, bool is_rand)
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
					matrix[i][j][a][b] = is_rand ? (double)(rand() / 100) : 0;
			}
		}
	}
}

int main()
{
	float**** matrix[3];
	for (int i = 0; i < 3; i++)
		init_matrix(matrix[i], N, K, i != 2);
	DWORD start = GetTickCount64();
	auto_vectorize(matrix[0], matrix[1], matrix[2]);
	DWORD duration = GetTickCount64() - start;
	cout << "auto_vec: " << duration << " ticks" << endl;
	start = GetTickCount64();
	my_vectorize(matrix[0], matrix[1], matrix[2]);
	duration = GetTickCount64() - start;
	cout << "my_vec: " << duration << " ticks" << endl;
	system("pause > NUL");
	return 0;
}
///линия памяти кратна 64 