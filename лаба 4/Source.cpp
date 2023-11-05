#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//struct Node* root;
int C;
int R;
int A;

void FindTree(struct Node* root, int data);
struct Node* CreateTree(struct Node* root, struct Node* r, int data);
void print_tree(struct Node* r, int l);
void level(int data);

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
};

int main()
{
	setlocale(LC_ALL, "");
	int D;

	struct Node* root;
	root = NULL;

	printf("-1 - окончание построения дерева\n\n");
	while (1)
	{
		printf("Введите число: ");
		scanf("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			break;
		}
		else
		{
			C = 0; R = 0;
			//FindTree(root, D);							// функцию для исключения добавления одинаковых символов
			if (C == 0)
			{
				root = CreateTree(root, root, D);
			}
			else
			{
				printf("Введите другое число\n");
			}
		}
		print_tree(root, 0);
	}

	printf("-1 - окончание поиска\n");
	while (1)
	{
		printf("Введите искомое число: ");
		scanf("%d", &D);
		if (D == -1)
		{
			printf("Поиск окончен\n\n");
			break;
		}
		else
		{
			C = 0; R = 0; A = 0;
			FindTree(root, D);

			printf("Число вхождений = %d\n", C);
			printf("Сложность поиска = %d\n\n", R);
		}
	}

	return 0;
}

void FindTree(struct Node* root, int data)
{
	R++;
	if (root == NULL)
	{
		return;
	}

	if (data == root->data)
	{
		C++;
		level(data);
		//A = R - 1;
	}

	if (data < root->data)
		FindTree(root->left, data);
	else
		FindTree(root->right, data);
}

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	//printf("(%lld %lld %d)\n", root, r, data);

	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(1);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data < root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data < r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	printf("%d-", l);
	for (int i = 0; i < l; i++)
	{
		printf("  ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

void level(int data)
{
	A = R - 1;
	printf("Уровень числа %d = %d\n", data, A);
}