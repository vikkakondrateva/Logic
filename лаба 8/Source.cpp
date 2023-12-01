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

int k;
int size1, h;
int** arr1;
int* vis;

void print_vis();

void add_to_list_queue(int s);
void del_from_list();
struct Node* add_elem(int s);

struct Node* head = NULL, * last = NULL;


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

	vis[l] = 1;
	printf("%5d", l);
	Q.push(l);

	while (!Q.empty())
	{
		l = Q.front();
		Q.pop();
		p = &LA[l];
		
		while (p->next != NULL)
		{
			if (vis[p->next->n] == 1)
			{
				p = p->next;
			}
			else
			{
				vis[p->next->n] = 1;
				p = p->next;

				l = p->n;
				Q.push(l);
				printf("%5d", l);
			}
		}
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


void print_vis() {
	printf("\nМассив vis:\n");
	for (int i = 0; i < size1; i++) {
		printf("%7d", vis[i]);
	}
	printf("\n\n");
}

void BFS1(int s) {
	vis[s] = 1;
	printf("%5d", s);
	Q.push(s);
	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		for (int i = 0; i < size1; i++) {
			if ((arr1[s][i] == 1) && (vis[i] == 0)) {
				printf("%5d", i);
				vis[i] = 1;
				Q.push(i);
			}
		}
	}
}


void BFS2(int s) {				//s - с этой вершины начинаем
	vis[s] = 1;
	printf("%5d", s);
	add_to_list_queue(s);
	while (head != 0) {
		s = last->n;
		del_from_list();
		for (int i = 0; i < size1; i++) {
			if ((arr1[s][i] == 1) && (vis[i] == 0)) {
				printf("%5d", i);
				vis[i] = 1;
				add_to_list_queue(i);
			}
		}
	}
}


void clean_vis() {
	for (int i = 0; i < size1; i++) {
		vis[i] = 0;
	}
}


void add_to_list_queue(int s)
{
	Node* p = NULL;
	p = add_elem(s);
	if (head == NULL)										// если очереди нет, то устанавливаем голову очереди
	{
		head = p;
		last = p;
	}
	else													// если очередь уже есть, то вставляем в начало
	{
		p->next = head;
		head = p;
	}
}


struct Node* add_elem(int s)									// Создаем новый элемент
{
	Node* p = NULL;


	p = (Node*)malloc(sizeof(struct Node));					// выделяем память под новый элемент списка
	if (p == NULL)											// если память не выделилась
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	p->n = s;

	p->next = NULL;
	return p;												// возвращаем указатель на созданный элемент (где его создали, в каком месте памяти)
}


void del_from_list()
{
	Node* struc = head;
	if (struc->next == NULL)								// удаляем единственный элемент
	{
		free(struc);
		head = NULL;
		last = NULL;
		return;
	}
	while (struc)
	{
		if (struc->next == last)							// удаляем последний элемент
		{
			free(struc->next);
			struc->next = NULL;
			last = struc;
			break;
		}
		struc = struc->next;
	}
}


int main() {

	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	printf("Задание 1\n");
	printf("Введите размер матрицы смежности M1: ");
	scanf("%d", &size1);
	printf("\n");

	vis = (int*)malloc(sizeof(int) * size1);

	arr1 = (int**)malloc(sizeof(int*) * size1);
	for (int i = 0; i < size1; i++) {
		arr1[i] = (int*)malloc(sizeof(int) * size1);
	}

	printf("Матрица M1:\n");
	create_matrix();
	print_matrix();

	clean_vis();
	printf("=======================================================================\n\n");
	printf("Задание 2\n");
	printf("Введите вершину (от 0 до %d) для начала обхода: ", size1 - 1);
	scanf("%d", &h);

	int l = h;

	k = h;
	printf("\n");
	printf("я был в вершинах:");

	clock_t start, end;
	double time;

	start = clock();
	BFS1(h);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\n");
	//printf("Время работы стандартной queue:%lf\n", time);

	clean_vis();

	printf("\n");

	printf("=======================================================================\n\n");
	printf("Задание 3\n");
	printf("Список смежности S1:\n");
	LA = make_LA();
	print_LA();
	printf("\n");

	printf("я был в вершинах:");
	first_list(l);
	printf("\n");

	printf("=======================================================================\n\n");
	printf("Задание 4\n");

	clean_vis();
	printf("я был в вершинах:");

	int s = h;

	start = clock();
	BFS2(s);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\n");
	//printf("Время работы нашей queue:%lf\n", time);

	for (int i = 0; i < size1; ++i) free(arr1[i]);
	free(arr1);
	free(vis);

	_getch();
	return 0;
}
