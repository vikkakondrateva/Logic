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

	for (int i = 0; i < si; i++) {									   //������� ����� �������
		m[i] = i + 1;
	}

	fprintf(F, "  ");														   //����� ����� �������
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

	for (int i = 0; i < si; i++) {                                        //���� ��� ������ �������
		fprintf(F, "%d|", m[i]);												//����� ������� �������
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
		printf("����:\n");
		printf("1 - ����������������� ���� (������ ����)\n");
		printf("2 - ����������������� ���� (��������� ��������)\n");
		printf("3 - ��������������� ���� (������ ����)\n");
		printf("4 - ��������������� ���� (��������� ��������)\n");

		printf("ecs - �����\n");
		menu = _getch();
	

		switch (menu) {
		case '1':
			system("cls");
			printf("������� ������ ���������� �������:");
			scanf("%d", &size);
			printf("\n");

			arr1 = (int*)malloc(sizeof(int) * size);

			arr = (int**)malloc(sizeof(int*) * size);
			for (int i = 0; i < size; i++) {
				arr[i] = (int*)malloc(sizeof(int) * size);
			}

			int chi;

			for (int i = 0; i < size; i++) {                                       //���� ��� ������� �������
				for (int j = 0; j < size; j++) {
					if (i == j) {												   //���� ������� ���������
						arr[i][j] = 0;
					}
					if (i < j) {												   //���� ���� ������� ���������
						int a1 = i + 1, a2 = j + 1;
						printf("������� ����� ���� %d -> %d ������ 1000\n(���� �� ������, ����� ���� �� ���� - ������� 10000): ", a1, a2);
						scanf("%d", &chi);
						printf("\n");
						while ((chi < 1) || (chi >= 1000)) {
							if (chi == 10000) {
								break;
							}
							printf("���� ����� �� ������ � �������� �� 1 �� 999\n\n");
							printf("������� ����� ���� %d -> %d ������ 1000\n(���� �� ������, ����� ���� �� ���� - ������� 10000): ", a1, a2);
							scanf("%d", &chi);
							printf("\n");
						}
						arr[i][j] = chi;
					}
					if (i > j) {												   //���� ���� ������� ���������
						arr[i][j] = arr[j][i];
					}
				}
			}
			printf("\n");
			f = fopen("�����.txt", "a");
			fprintf(f, "������ ��� ������������������ �����:\n");
			printf("������ ��� ������������������ �����:\n");
			shapka(size, arr, arr1, f);

			alg(size, arr);

			fprintf(f, "���������� ��������� ������:\n");
			printf("���������� ��������� ������:\n");
			shapka(size, arr, arr1, f);
			fprintf(f, "\n\n\n");
			fclose(f);
			printf("������ ��� ������������������ ����� � ���������� ��� ���� ��������� ������: '�����.txt'\n\n");

			system("pause");
			for(int i = 0; i < size; ++i) free(arr[i]);
			free(arr);
			free(arr1);
			break;
		}


		switch (menu) {
		case '2':
			system("cls");
			printf("������� ������ ���������� �������:");
			scanf("%d", &size);
			printf("\n");

			arr1 = (int*)malloc(sizeof(int) * size);

			arr = (int**)malloc(sizeof(int*) * size);
			for (int i = 0; i < size; i++) {
				arr[i] = (int*)malloc(sizeof(int) * size);
			}

			for (int i = 0; i < size; i++) {                                       //���� ��� ������� �������
				for (int j = 0; j < size; j++) {
					if (i == j) {												   //���� ������� ���������
						arr[i][j] = 0;
					}
					if (i < j) {												   //���� ���� ������� ���������
						arr[i][j] = rand() % 120 + 1;
						if (arr[i][j] >= 100){
							arr[i][j] = 10000;
						}
					}
					if (i > j) {												   //���� ���� ������� ���������
						arr[i][j] = arr[j][i];
					}
				}
			}
			printf("\n");

			f = fopen("�����.txt", "a");
			fprintf(f, "������ ��� ������������������ �����:\n");
			printf("������ ��� ������������������ �����:\n");
			shapka(size, arr, arr1, f);

			alg(size, arr);

			fprintf(f, "���������� ��������� ������:\n");
			printf("���������� ��������� ������:\n");
			shapka(size, arr, arr1, f);
			fprintf(f, "\n\n\n");
			fclose(f);
			printf("������ ��� ������������������ ����� � ���������� ��� ���� ��������� ������: '�����.txt'\n");

			system("pause");
			for (int i = 0; i < size; ++i) free(arr[i]);
			free(arr);
			free(arr1);
			break;
		}


		switch (menu) {
		case '3':
			system("cls");
			printf("������� ������ ���������� �������:");
			scanf("%d", &size);
			printf("\n");

			arr1 = (int*)malloc(sizeof(int) * size);

			arr = (int**)malloc(sizeof(int*) * size);
			for (int i = 0; i < size; i++) {
				arr[i] = (int*)malloc(sizeof(int) * size);
			}

			int chi;

			for (int i = 0; i < size; i++) {                                       //���� ��� ������� �������
				for (int j = 0; j < size; j++) {
					if (i == j) {												   //���� ������� ���������
						arr[i][j] = 0;
					}
					else{
						int a1 = i + 1, a2 = j + 1;
						printf("������� ����� ���� %d -> %d ������ 1000\n(���� �� ������, ����� ���� �� ���� - ������� 10000): ", a1, a2);
						scanf("%d", &chi);
						printf("\n");
						while ((chi < 1) || (chi >= 1000)) {
							printf("���� ����� �� ������ � �������� �� 1 �� 999\n\n");
							if (chi == 10000) {
								break;
							}
							printf("������� ����� ���� %d -> %d ������ 1000\n(���� �� ������, ����� ���� �� ���� - ������� 10000): ", a1, a2);
							scanf("%d", &chi);
							printf("\n");
						}
						arr[i][j] = chi;	
					}
				}
			}
			printf("\n");

			f = fopen("�����.txt", "a");
			fprintf(f, "������ ��� ���������������� �����:\n");
			printf("������ ��� ���������������� �����:\n");
			shapka(size, arr, arr1, f);

			alg(size, arr);

			fprintf(f, "���������� ��������� ������:\n");
			printf("���������� ��������� ������:\n");
			shapka(size, arr, arr1, f);
			fprintf(f, "\n\n\n");
			fclose(f);
			printf("������ ��� ���������������� ����� � ���������� ��� ���� ��������� ������: '�����.txt'\n");

			system("pause");
			for (int i = 0; i < size; ++i) free(arr[i]);
			free(arr);
			free(arr1);
			break;
		}


		switch (menu) {
		case '4':
			system("cls");
			printf("������� ������ ���������� �������:");
			scanf("%d", &size);
			printf("\n");

			arr1 = (int*)malloc(sizeof(int) * size);

			arr = (int**)malloc(sizeof(int*) * size);
			for (int i = 0; i < size; i++) {
				arr[i] = (int*)malloc(sizeof(int) * size);
			}


			for (int i = 0; i < size; i++) {                                       //���� ��� ������� �������
				for (int j = 0; j < size; j++) {
					if (i == j) {												   //���� ������� ���������
						arr[i][j] = 0;
					}
					else{												   //���� ���� ������� ���������
						arr[i][j] = rand() % 120 + 1;
						if (arr[i][j] >= 100) {
							arr[i][j] = 10000;
						}
					}
				}
			}
			printf("\n");

			f = fopen("�����.txt", "a");
			fprintf(f, "������ ��� ���������������� �����:\n");
			printf("������ ��� ���������������� �����:\n");
			shapka(size, arr, arr1, f);

			alg(size, arr);

			fprintf(f, "���������� ��������� ������:\n");
			printf("���������� ��������� ������:\n");
			shapka(size, arr, arr1, f);
			fprintf(f, "\n\n\n");
			fclose(f);
			printf("������ ��� ���������������� ����� � ���������� ��� ���� ��������� ������: '�����.txt'\n");

			system("pause");
			for (int i = 0; i < size; ++i) free(arr[i]);
			free(arr);
			free(arr1);
			break;
		}
	
	} while (menu != 27);
}