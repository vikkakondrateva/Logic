#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

int main() {

	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int size;
	int** arr;

	printf("Введите размер матрицы смежности: ");
	scanf("%d", &size);
	printf("\n");

	arr = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++) {
		arr[i] = (int*)malloc(sizeof(int) * size);
	}

	int count_smez = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				arr[i][j] = 0;
			}

			else if (i > j) {
				arr[i][j] = arr[j][i];
				if (arr[i][j] == 1) {
					//count_smez++;
				}
			}

			else {
				arr[i][j] = rand() % 2;
				if (arr[i][j] == 1) {
					count_smez++;
				}
			}
		}
	}
	//count_smez = count_smez / 2;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%7d", arr[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("Количество рёбер (размер) графа через матрицу смежности: %d\n", count_smez);
	printf("\n");

	int g = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] == 1) {
				g++;
			}
		}

		if (g == 0) {
			printf("Вершина %d - изолирована\n", i + 1);
		}
		if (g == 1) {
			printf("Вершина %d - концевая\n", i + 1);
		}
		if (g == size - 1) {
			printf("Вершина %d - доминирующая\n", i + 1);
		}

		g = 0;
	}
	printf("\n=========================================================================================\n");

	//задание 2*
	printf("Матрица инцидентности:\n\n");
	int** arr1;
	arr1 = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++) {
		arr1[i] = (int*)malloc(sizeof(int) * count_smez);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < count_smez; j++) {
			arr1[i][j] = 0;
		}
	}

	int d = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			if ((arr[i][j] == 1) and (i < j)) {
				arr1[i][d] = 1;
				arr1[j][d] = 1;
				d++;
			}
		}
	}

	int count_in = 0;							//==count_smez

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < count_smez; j++) {
			printf("%7d", arr1[i][j]);
			if (j + 1 > count_in) {	//размер графа = количеству столбцов матрицы инцидентности
				count_in = j + 1;		//на 2 делить не надо
			}
			//if (arr1[i][j] == 1) {		//размер графа = количество единиц деленное на 2
			//	count_in++;
			//}
		}
		printf("\n");
	}
	//count_in = count_in / 2;

	printf("\n");
	printf("Количество рёбер (размер) графа через матрицу инцидентности: %d\n", count_in);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < count_smez; j++) {
			if (arr1[i][j] == 1) {
				g++;
			}
		}

		if (g == 0) {
			printf("Вершина %d - изолирована\n", i + 1);
		}
		if (g == 1) {
			printf("Вершина %d - концевая\n", i + 1);
		}
		if (g == size - 1) {
			printf("Вершина %d - доминирующая\n", i + 1);
		}

		g = 0;
	}



	for (int i = 0; i < size; ++i) free(arr1[i]);
	free(arr1);
	for (int i = 0; i < size; ++i) free(arr[i]);
	free(arr);

	return 0;
}
