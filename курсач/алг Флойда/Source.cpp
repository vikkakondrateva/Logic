#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>



void alg(int si, int** a) {

	for (int k = 0; k < si; k++) {
		for (int i = 0; i < si; i++) {
			for (int j = 0; j < si; j++) {
				if (a[i][j] > a[i][k] + a[k][j]) {
					a[i][j] = a[i][k] + a[k][j];
				}
			}
		}
	}

}



void shapka(int si, int** a, int* m, FILE* F) {

	//printf("%d", si);

	for (int i = 0; i < si; i++) {									   //задание шапки таблицы
		m[i] = i + 1;
	}

	fprintf(F, "  ");														   //вывод шапки таблицы
	printf("  ");
	for (int i = 0; i < si; i++) {
		fprintf(F, "%7d", m[i]);
		printf("%7d", m[i]);
	}
	fprintf(F, "\n");
	printf("\n");

	for (int i = 0; i < si * 7 + 6; i++) {
		fprintf(F, "-");
		printf("-");
	}
	fprintf(F, "\n");
	printf("\n");

	for (int i = 0; i < si; i++) {                                        //цикл для вывода массива
		fprintf(F, "%d|", m[i]);												//вывод первого столбца
		printf("%d|", m[i]);
		for (int j = 0; j < si; j++) {
			if (a[i][j] >= 10000) {
				fprintf(F, "      -");
				printf("      -");
			}
			else {
				fprintf(F, "%7d", a[i][j]);
				printf("%7d", a[i][j]);
			}
		}
		fprintf(F, "\n");
		printf("\n");
	}
	fprintf(F, "\n\n");
	printf("\n\n");
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	FILE* f;
	char menu;
	int size;
	int** arr;
	int* arr1;
	

	do {
		system("cls");
		printf("МЕНЮ:\n");
		printf("1 - Неориентированный граф (ручной ввод)\n");
		printf("2 - Неориентированный граф (случайные значения)\n");
		printf("3 - Ориентированный граф (ручной ввод)\n");
		printf("4 - Ориентированный граф (случайные значения)\n");

		printf("ecs - выход\n");
		menu = _getch();
	

		switch (menu) {
		case '1':
			system("cls");
			printf("Введите размер квадратной матрицы:");
			scanf("%d", &size);
			printf("\n");

			arr1 = (int*)malloc(sizeof(int) * size);

			arr = (int**)malloc(sizeof(int*) * size);
			for (int i = 0; i < size; i++) {
				arr[i] = (int*)malloc(sizeof(int) * size);
			}

			int chi;

			for (int i = 0; i < size; i++) {                                       //цикл для задания массива
				for (int j = 0; j < size; j++) {
					if (i == j) {												   //если главная диагональ
						arr[i][j] = 0;
					}
					if (i < j) {												   //если выше главной диагонали
						int a1 = i + 1, a2 = j + 1;
						printf("Введите длину пути %d -> %d меньше 1000\n(Если вы хотите, чтобы пути не было - введите 10000): ", a1, a2);
						scanf("%d", &chi);
						printf("\n");
						while ((chi < 1) || (chi >= 1000)) {
							if (chi == 10000) {
								break;
							}
							printf("Ваше число не входит в диапазон от 1 до 999\n\n");
							printf("Введите длину пути %d -> %d меньше 1000\n(Если вы хотите, чтобы пути не было - введите 10000): ", a1, a2);
							scanf("%d", &chi);
							printf("\n");
						}
						arr[i][j] = chi;
					}
					if (i > j) {												   //если ниже главной диагонали
						arr[i][j] = arr[j][i];
					}
				}
			}
			printf("\n");
			f = fopen("графы.txt", "a");
			fprintf(f, "Массив для неориентированного графа:\n");
			printf("Массив для неориентированного графа:\n");
			shapka(size, arr, arr1, f);

			alg(size, arr);

			fprintf(f, "Реализация алгоритма Флойда:\n");
			printf("Реализация алгоритма Флойда:\n");
			shapka(size, arr, arr1, f);
			fprintf(f, "\n\n\n");
			fclose(f);
			printf("Массив для неориентированного графа и применение для него алгоритма Флойда: 'графы.txt'\n\n");

			system("pause");
			for(int i = 0; i < size; ++i) free(arr[i]);
			free(arr);
			free(arr1);
			break;
		}


		switch (menu) {
		case '2':
			system("cls");
			printf("Введите размер квадратной матрицы:");
			scanf("%d", &size);
			printf("\n");

			arr1 = (int*)malloc(sizeof(int) * size);

			arr = (int**)malloc(sizeof(int*) * size);
			for (int i = 0; i < size; i++) {
				arr[i] = (int*)malloc(sizeof(int) * size);
			}

			for (int i = 0; i < size; i++) {                                       //цикл для задания массива
				for (int j = 0; j < size; j++) {
					if (i == j) {												   //если главная диагональ
						arr[i][j] = 0;
					}
					if (i < j) {												   //если выше главной диагонали
						arr[i][j] = rand() % 120 + 1;
						if (arr[i][j] >= 100){
							arr[i][j] = 10000;
						}
					}
					if (i > j) {												   //если ниже главной диагонали
						arr[i][j] = arr[j][i];
					}
				}
			}
			printf("\n");

			f = fopen("графы.txt", "a");
			fprintf(f, "Массив для неориентированного графа:\n");
			printf("Массив для неориентированного графа:\n");
			shapka(size, arr, arr1, f);

			alg(size, arr);

			fprintf(f, "Реализация алгоритма Флойда:\n");
			printf("Реализация алгоритма Флойда:\n");
			shapka(size, arr, arr1, f);
			fprintf(f, "\n\n\n");
			fclose(f);
			printf("Массив для неориентированного графа и применение для него алгоритма Флойда: 'графы.txt'\n");

			system("pause");
			for (int i = 0; i < size; ++i) free(arr[i]);
			free(arr);
			free(arr1);
			break;
		}


		switch (menu) {
		case '3':
			system("cls");
			printf("Введите размер квадратной матрицы:");
			scanf("%d", &size);
			printf("\n");

			arr1 = (int*)malloc(sizeof(int) * size);

			arr = (int**)malloc(sizeof(int*) * size);
			for (int i = 0; i < size; i++) {
				arr[i] = (int*)malloc(sizeof(int) * size);
			}

			int chi;

			for (int i = 0; i < size; i++) {                                       //цикл для задания массива
				for (int j = 0; j < size; j++) {
					if (i == j) {												   //если главная диагональ
						arr[i][j] = 0;
					}
					else{
						int a1 = i + 1, a2 = j + 1;
						printf("Введите длину пути %d -> %d меньше 1000\n(Если вы хотите, чтобы пути не было - введите 10000): ", a1, a2);
						scanf("%d", &chi);
						printf("\n");
						while ((chi < 1) || (chi >= 1000)) {
							printf("Ваше число не входит в диапазон от 1 до 999\n\n");
							if (chi == 10000) {
								break;
							}
							printf("Введите длину пути %d -> %d меньше 1000\n(Если вы хотите, чтобы пути не было - введите 10000): ", a1, a2);
							scanf("%d", &chi);
							printf("\n");
						}
						arr[i][j] = chi;	
					}
				}
			}
			printf("\n");

			f = fopen("графы.txt", "a");
			fprintf(f, "Массив для ориентированного графа:\n");
			printf("Массив для ориентированного графа:\n");
			shapka(size, arr, arr1, f);

			alg(size, arr);

			fprintf(f, "Реализация алгоритма Флойда:\n");
			printf("Реализация алгоритма Флойда:\n");
			shapka(size, arr, arr1, f);
			fprintf(f, "\n\n\n");
			fclose(f);
			printf("Массив для ориентированного графа и применение для него алгоритма Флойда: 'графы.txt'\n");

			system("pause");
			for (int i = 0; i < size; ++i) free(arr[i]);
			free(arr);
			free(arr1);
			break;
		}


		switch (menu) {
		case '4':
			system("cls");
			printf("Введите размер квадратной матрицы:");
			scanf("%d", &size);
			printf("\n");

			arr1 = (int*)malloc(sizeof(int) * size);

			arr = (int**)malloc(sizeof(int*) * size);
			for (int i = 0; i < size; i++) {
				arr[i] = (int*)malloc(sizeof(int) * size);
			}


			for (int i = 0; i < size; i++) {                                       //цикл для задания массива
				for (int j = 0; j < size; j++) {
					if (i == j) {												   //если главная диагональ
						arr[i][j] = 0;
					}
					else{												   //если выше главной диагонали
						arr[i][j] = rand() % 120 + 1;
						if (arr[i][j] >= 100) {
							arr[i][j] = 10000;
						}
					}
				}
			}
			printf("\n");

			f = fopen("графы.txt", "a");
			fprintf(f, "Массив для ориентированного графа:\n");
			printf("Массив для ориентированного графа:\n");
			shapka(size, arr, arr1, f);

			alg(size, arr);

			fprintf(f, "Реализация алгоритма Флойда:\n");
			printf("Реализация алгоритма Флойда:\n");
			shapka(size, arr, arr1, f);
			fprintf(f, "\n\n\n");
			fclose(f);
			printf("Массив для ориентированного графа и применение для него алгоритма Флойда: 'графы.txt'\n");

			system("pause");
			for (int i = 0; i < size; ++i) free(arr[i]);
			free(arr);
			free(arr1);
			break;
		}
	
	} while (menu != 27);
}