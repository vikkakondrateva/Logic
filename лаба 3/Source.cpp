#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

void add_to_list(void);
void add_to_list_pr(void);
void add_to_list_queue(void);
void del_from_list(void);
struct node* add_elem(void);
void review(void);
void free_list(void);

struct node* head = NULL, * last = NULL;

struct node
{
	char inf[100];											// полезная информация
	int prior;
	struct node* next;										// ссылка на следующую такую же структуру 
};


int main()
{
	setlocale(LC_ALL, "Russian");

	int N;
	printf("Введите размер списка: ");
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		add_to_list_pr();									// очередь с приоритетом (1)
		//add_to_list_queue();								// очередь (2)
		//add_to_list();										// стек (3)
	}

	review();

	for (int i = 0; i < N; i++)
	{
		printf("Удаление последнего элемента\n");
		//if (i % 3 == 0)
		//{
		//	add_to_list_pr();									// очередь с приоритетом (1)
		//	add_to_list_queue();								// очередь (2)
		//	add_to_list();										// стек (3)
		//}
		del_from_list();
		review();
	}

	free_list();

	return 0;
}

void add_to_list(void)
{
	struct node* p = NULL;
	p = add_elem();
	if (head == NULL)										// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else 													// если список уже есть, то вставляем в конец
	{
		last->next = p;
		last = p;
	}
}

void add_to_list_pr(void)
{
	struct node* p = NULL;
	p = add_elem();
	if (head == NULL)										// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else 													// если список уже есть, то вставляем по приоритету
	{
		if (head->prior < p->prior)							// вставляем в начало (т.е объект с большим приоритетом перед объектом с меньшим приоритетом)
		{
			p->next = head;
			head = p;
		}
		else
		{
			struct node* struc = head;
			while (struc)
			{
				if (struc->next == NULL)					// вставляем в конец
				{
					struc->next = p;
					p->next = NULL;
					last = p;
					break;
				}
				else if (struc->next->prior < p->prior)		// вставляем в середину
				{
					p->next = struc->next;
					struc->next = p;
					break;
				}
				struc = struc->next;
			}
		}
	}
}

void add_to_list_queue(void)
{
	struct node* p = NULL;
	p = add_elem();
	if (head == NULL)										// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else													// если список уже есть, то вставляем в начало
	{
		p->next = head;
		head = p;
	}
}

void del_from_list(void)
{
	struct node* struc = head;
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

struct node* add_elem(void)									// Создаем новый элемент
{
	struct node* p = NULL;
	char s[100];
	int pr;

	p = (node*)malloc(sizeof(struct node));					// выделяем память под новый элемент списка
	if (p == NULL)											// если память не выделилась
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");					// вводим название
	scanf("%s", s);
	strcpy(p->inf, s);

	printf("Введите приоритет объекта: \n");				// вводим приоритет
	scanf("%d", &pr);
	p->prior = pr;

	p->next = NULL;
	return p;												// возвращаем указатель на созданный элемент (где его создали, в каком месте памяти)
}

void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, " "Приоритет - %d", struc->inf, struc->prior);
		struc = struc->next;
		printf("\n");
	}
}

void free_list(void)
{
	struct node* struc = head, * p;
	while (struc)
	{
		p = struc->next;									// p указывает на следующий 
		free(struc);										// освобождаем текущий
		struc = p;											// struc переходит на p, т.е на следующий
	}
}
