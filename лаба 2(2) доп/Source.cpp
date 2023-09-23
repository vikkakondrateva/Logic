#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>


void calc(int* a, int n);
void shell(int* items, int count);
void output(int* items, int count);
void qs(int* items, int left, int right);
int compare(const void* x1, const void* x2);

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	int N;
	printf("������� ������ �������: ");
	scanf("%d", &N);

	int y = N;

	for (int l = 0; l < 5; l++) {
		N = y / (5 - l);
		printf("������ ������� = %d\n", N);
		printf("-----------------------------------------------------\n");

		int* A = (int*)malloc(sizeof(int) * N);

		//��������� ����� �������� ������� �
		for (int i = 0; i < N; i++)
		{
			A[i] = rand() % 200 - 100;
			//printf("%d ", A[i]);
			//printf("\n");
		}
		printf("\n");
		printf("��� ������� �� ��������� �����\n");
		printf("\n");
		calc(A, N);
		printf("\n");
		printf("\n");

		//�� �����������
		for (int i = 0; i < N; i++)
		{
			A[i] = i * 2 - N;
		}
		//output(A, N);
		printf("��� ������������ ������������������\n");
		printf("\n");
		calc(A, N);
		printf("\n");
		printf("\n");

		//�� ��������
		for (int i = 0; i < N; i++)
		{
			A[i] = -(i * 2 - N);
		}
		//output(A, N);
		printf("��� ��������� ������������������\n");
		printf("\n");
		calc(A, N);
		printf("\n");
		printf("\n");

		//�������� �������, �������� ����������
		for (int i = 0; i < N; i++)
		{
			A[i] = abs(i * 2 - N);
		}
		//output(A, N);
		printf("��� ��������� ������������������\n");
		printf("\n\n");
		calc(A, N);

		free(A);
		printf("=====================================================\n");
	}
	return 0;
}

void calc(int* a, int n)
{
	clock_t start, end;
	double time;

	int* B = (int*)malloc(sizeof(int) * n);

	memcpy(B, a, sizeof(int) * n);
	start = clock();
	shell(B, n);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("�op������� �����:%lf\n", time);

	memcpy(B, a, sizeof(int) * n);
	start = clock();
	qs(B, 0, n - 1);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("������� ����������:%lf\n", time);

	memcpy(B, a, sizeof(int) * n);
	start = clock();
	qsort(B, n, sizeof(int), compare);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("qsort:%lf\n", time);

	free(B);
}

void output(int* items, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("%d ", items[i]);
	}
	printf("\n");
}

void shell(int* items, int count)
{
	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	for (k = 0; k < 5; k++)
	{
		gap = a[k];
		for (i = gap; i < count; ++i)
		{
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

void qs(int* items, int left, int right) //����� �������: qs(items, 0, count-1);
{
	int i, j;
	int x, y;

	i = left; j = right;

	/* ����� ���������� */
	x = items[(left + right) / 2];

	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;

		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) qs(items, left, j);
	if (i < right) qs(items, i, right);
}

int compare(const void* x1, const void* x2)   // ������� ��������� ��������� �������
{
	return (*(int*)x1 - *(int*)x2);              // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}