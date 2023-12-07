#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <iostream> 
#include <queue>
using namespace std;
queue <int> Q;

int size1;
int** arr1;
int* dist;

struct Node
{
	int n;			//Номер вершины (0..N-1)
	Node* next;
};

Node* LA;			//Массив структур - списков смежности [N]

Node* make_LA()
{
	Node* la, * p;
	la = (Node*)malloc(sizeof(Node) * size1);

	for (int i = 0; i < size1; i++)
	{
		la[i].n = i;
		la[i].next = NULL;
		p = &la[i];

		for (int j = 0; j < size1; j++)
		{
			if (arr1[i][j] == 1)
			{
				p->next = (Node*)malloc(sizeof(Node));
				p = p->next;
				p->n = j;
				p->next = NULL;
			}
		}
	}
	return la;
}


void print_LA()
{
	Node* p;
	for (int i = 0; i < size1; i++)
	{
		p = &LA[i];
		while (p != NULL)
		{
			printf("%d > ", p->n);
			p = p->next;
		}
		printf("\n");
	}
}

void first_list(int l)					// l - вершина, с которой начинаем обход
{
	Node* p;
	p = &LA[l];

	dist[l] = 0;
	Q.push(l);
	while (!Q.empty())
	{
		l = Q.front();
		Q.pop();
		p = &LA[l];
	
		while (p->next != NULL)
		{
			if (dist[p->next->n] != -1)
			{
				p = p->next;
			}
			else
			{
				dist[p->next->n] = dist[l] + 1;
				p = p->next;
				Q.push(p->n);
			}
		}
	}
}

void second_list(int l, int count)
{
	Node* p;
	p = &LA[l];
	dist[l] = count;

	while (p->next != NULL)
	{
		if (dist[p->next->n] == 0)
		{
			dist[p->next->n] = 1;
			l = p->next->n;
			count++;
			second_list(l, count);
			count--;
		}
		p = p->next;
	}
}
void create_matrix() {

	for (int i = 0; i < size1; i++) {
		for (int j = i; j < size1; j++) {
			if (i == j) {					//главная диагональ == 0
				arr1[i][j] = 0;
			}

			else {							//ниже главной диагонали отразить то, что выше
				arr1[i][j] = rand() % 2;
				arr1[j][i] = arr1[i][j];
			}
		}
	}
}


void print_matrix() {
	printf("     ");
	for (int i = 0; i < size1; i++) {
		printf("%4d ", i);
	}
	printf("\n");
	printf("-----------------------------------------------------------\n");

	for (int i = 0; i < size1; i++) {
		printf("%4d|", i);
		for (int j = 0; j < size1; j++) {
			printf("%4d ", arr1[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void BFSD(int v)
{
	Q.push(v);
	dist[v] = 0;
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		for (int i = 0; i < size1; i++) {
			if ((arr1[v][i] == 1) && (dist[i] == -1)) {
				Q.push(i);
				dist[i] = dist[v] + 1;
			}
		}
	}
}

void DFS1(int v, int count) {
	dist[v] = count;
	for (int i = 0; i < size1; i++) {
		if ((arr1[v][i] == 1) && (dist[i] == -1)) {
			count++;
			DFS1(i, count);
			count--;
		}
	}
}


int main() {

	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	printf("Задание 1.1\n");
	printf("Введите размер матрицы смежности M1: ");
	scanf("%d", &size1);
	printf("\n");

	dist = (int*)malloc(sizeof(int) * size1);

	arr1 = (int**)malloc(sizeof(int*) * size1);
	for (int i = 0; i < size1; i++) {
		arr1[i] = (int*)malloc(sizeof(int) * size1);
	}

	clock_t start, end;
	double time1, time2;

	printf("Матрица M1:\n");
	create_matrix();
	print_matrix();				

	int a;
	printf("=======================================================================\n\n");
	printf("Задание 1.2 (обход в ширину через queue)\n");
	printf("Введите вершину (от 0 до %d) для начала обхода: ", size1 - 1);
	scanf("%d", &a);


	printf("\n");
	
	for (int i = 0; i < size1; i++) {
		dist[i] = -1;
	}

	start = clock();
	BFSD(a);
	end = clock();
	time1 = (double)(end - start) / CLOCKS_PER_SEC;
	

	for (int i = 0; i < size1; i++) {
		printf("Расстояние от %d вершины до %d вершины = %d\n", a, i, dist[i]);
	}

	for (int i = 0; i < size1; i++) {
		dist[i] = -1;
	}

	printf("\n");

	printf("=======================================================================\n\n");
	printf("Задание 1.3 (обход в ширину через списки)\n");
	printf("Список смежности S1:\n");
	LA = make_LA();
	print_LA();   
	printf("\n");

	first_list(a);

	for (int i = 0; i < size1; i++) {
		printf("Расстояние от %d вершины до %d вершины = %d\n", a, i, dist[i]);
	}
	printf("\n");

	for (int i = 0; i < size1; i++) {
		dist[i] = -1;
	}

	printf("=======================================================================\n\n");
	printf("Задание 2.1 (обход в глубину)\n");

	int c = 0;

	start = clock();
	DFS1(a, c);
	end = clock();
	time2 = (double)(end - start) / CLOCKS_PER_SEC;
	

	for (int i = 0; i < size1; i++) {
		printf("Расстояние от %d вершины до %d вершины = %d\n", a, i, dist[i]);
	}

	printf("=======================================================================\n\n");
	printf("Задание 2.2 (обход в глубину через списки)\n");

	c = 0;
	second_list(a, c);

	for (int i = 0; i < size1; i++) {
		printf("Расстояние от %d вершины до %d вершины = %d\n", a, i, dist[i]);
	}

	printf("\n");
	printf("=======================================================================\n\n");
	printf("Задание 2.3 (Оценка времени)\n");
	printf("Время работы алгоритма поиска расстояний на основе обхода в ширину: %lf\n", time1);
	printf("Время работы алгоритма поиска расстояний на основе обхода в глубину: %lf\n", time2);

	for (int i = 0; i < size1; ++i) free(arr1[i]);
	free(arr1);

	free(dist);

	_getch();
	return 0;
}