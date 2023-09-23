#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

int main(void)
{
	setlocale(LC_ALL, "Russian");
	int N;
	printf("Введите размер массива: ");
	scanf("%d", &N);
	int y = N;

	for (int l = 0; l < 5; l++) {

		N = y / (5 - l);

		int** a = (int**)malloc(sizeof(int*) * N);
		for (int i = 0; i < N; i++) a[i] = (int*)malloc(sizeof(int) * N);

		int** b = (int**)malloc(sizeof(int*) * N);
		for (int i = 0; i < N; i++) b[i] = (int*)malloc(sizeof(int) * N);

		int** c = (int**)malloc(sizeof(int*) * N);
		for (int i = 0; i < N; i++) c[i] = (int*)malloc(sizeof(int) * N);



		int i = 0, j = 0, r, elem_c;

		srand(time(NULL)); // инициализируем параметры генератора случайных чисел
		while (i < N)
		{
			while (j < N)
			{
				a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
				j++;
			}
			i++;
		}
		srand(time(NULL)); // инициализируем параметры генератора случайных чисел
		i = 0; j = 0;
		while (i < N)
		{
			while (j < N)
			{
				b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
				j++;
			}
			i++;
		}


		clock_t start = clock();

		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				elem_c = 0;
				for (r = 0; r < N; r++)
				{
					elem_c = elem_c + a[i][r] * b[r][j];
					c[i][j] = elem_c;

				}
			}
			//printf("%d%% ", i*100/N);
		}

		clock_t end = clock();

		double time = (double)(end - start) / CLOCKS_PER_SEC;
		printf("Время выполнения для %d: %lf\n", N, time);

		for (int i = 0; i < N; ++i) free(a[i]);
		free(a);
		for (int i = 0; i < N; ++i) free(b[i]);
		free(b);
		for (int i = 0; i < N; ++i) free(c[i]);
		free(c);
	}

	
	return(0);
}
