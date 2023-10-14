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

			else {
				arr[i][j] = rand() % 2;
				count_smez += arr[i][j];
			}

		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%7d", arr[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("Количество рёбер (размер) графа через матрицу смежности: %d\n", count_smez);
	printf("\n");


	//задание 2*
	printf("Матрица инцидентности:\n\n");
	int** arr2;
	arr2 = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++) {
		arr2[i] = (int*)malloc(sizeof(int) * count_smez);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < count_smez; j++) {
			arr2[i][j] = 0;
		}
	}

	int d = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < count_smez; j++) {

			if (arr[i][j] == 1) {
				arr2[i][d] = -1;
				arr2[j][d] = 1;
				d++;
			}
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < count_smez; j++) {
			printf("%7d", arr2[i][j]);
		}
		printf("\n");
	}


	for (int i = 0; i < size; ++i) free(arr2[i]);
	free(arr2);
	for (int i = 0; i < size; ++i) free(arr[i]);
	free(arr);
}