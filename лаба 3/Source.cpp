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
	char inf[100];											// �������� ����������
	int prior;
	struct node* next;										// ������ �� ��������� ����� �� ��������� 
};


int main()
{
	setlocale(LC_ALL, "Russian");

	int N;
	printf("������� ������ ������: ");
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		add_to_list_pr();									// ������� � ����������� (1)
		//add_to_list_queue();								// ������� (2)
		//add_to_list();										// ���� (3)
	}

	review();

	for (int i = 0; i < N; i++)
	{
		printf("�������� ���������� ��������\n");
		//if (i % 3 == 0)
		//{
		//	add_to_list_pr();									// ������� � ����������� (1)
		//	add_to_list_queue();								// ������� (2)
		//	add_to_list();										// ���� (3)
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
	if (head == NULL)										// ���� ������ ���, �� ������������� ������ ������
	{
		head = p;
		last = p;
	}
	else 													// ���� ������ ��� ����, �� ��������� � �����
	{
		last->next = p;
		last = p;
	}
}

void add_to_list_pr(void)
{
	struct node* p = NULL;
	p = add_elem();
	if (head == NULL)										// ���� ������ ���, �� ������������� ������ ������
	{
		head = p;
		last = p;
	}
	else 													// ���� ������ ��� ����, �� ��������� �� ����������
	{
		if (head->prior < p->prior)							// ��������� � ������ (�.� ������ � ������� ����������� ����� �������� � ������� �����������)
		{
			p->next = head;
			head = p;
		}
		else
		{
			struct node* struc = head;
			while (struc)
			{
				if (struc->next == NULL)					// ��������� � �����
				{
					struc->next = p;
					p->next = NULL;
					last = p;
					break;
				}
				else if (struc->next->prior < p->prior)		// ��������� � ��������
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
	if (head == NULL)										// ���� ������ ���, �� ������������� ������ ������
	{
		head = p;
		last = p;
	}
	else													// ���� ������ ��� ����, �� ��������� � ������
	{
		p->next = head;
		head = p;
	}
}

void del_from_list(void)
{
	struct node* struc = head;
	if (struc->next == NULL)								// ������� ������������ �������
	{
		free(struc);
		head = NULL;
		last = NULL;
		return;
	}
	while (struc)
	{
		if (struc->next == last)							// ������� ��������� �������
		{
			free(struc->next);
			struc->next = NULL;
			last = struc;
			break;
		}
		struc = struc->next;
	}

}

struct node* add_elem(void)									// ������� ����� �������
{
	struct node* p = NULL;
	char s[100];
	int pr;

	p = (node*)malloc(sizeof(struct node));					// �������� ������ ��� ����� ������� ������
	if (p == NULL)											// ���� ������ �� ����������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	printf("������� �������� �������: \n");					// ������ ��������
	scanf("%s", s);
	strcpy(p->inf, s);

	printf("������� ��������� �������: \n");				// ������ ���������
	scanf("%d", &pr);
	p->prior = pr;

	p->next = NULL;
	return p;												// ���������� ��������� �� ��������� ������� (��� ��� �������, � ����� ����� ������)
}

void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("������ ����\n");
	}
	while (struc)
	{
		printf("��� - %s, " "��������� - %d", struc->inf, struc->prior);
		struc = struc->next;
		printf("\n");
	}
}

void free_list(void)
{
	struct node* struc = head, * p;
	while (struc)
	{
		p = struc->next;									// p ��������� �� ��������� 
		free(struc);										// ����������� �������
		struc = p;											// struc ��������� �� p, �.� �� ���������
	}
}
