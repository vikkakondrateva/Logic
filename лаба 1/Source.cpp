#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>




void numb1() {                //1 ������� ����� ������������ � ����������� ���������� �������
	
	printf("No 1\n");
	int max, min, i;
	int sub = 0;
	int arr1[] = { -1, 0, 1, 2, 3 };
	max = arr1[0];
	min = arr1[0];
	printf("������ arr1 = { -1, 0, 1, 2, 3}\n");
	for (i = 0; i < 5; i++) {
		if (arr1[i] > max) {                                       //����� ���� ��������
			max = arr1[i];
		}
		if (arr1[i] < min) {                                       //����� ��� ��������
			min = arr1[i];
		}
	}
	sub = max - min;
	printf("�������� = %d\n\n", sub);
}





void numb2() {              //2 ������������� ������� ���������� �������
	
	printf("No 2\n");
	int arr2[5];
	int i;
	printf("������ ��������� �����:\n");
	for (i = 0; i < 5; i++) {                                      //������� ������� ��������� �����
		arr2[i] = rand() % 100 - rand() % 100;
		printf("%d ", arr2[i]);
	}
	printf("\n\n");
}





void numb3() {           //3 �������� ������� ������������� �������, ��������� � ����������
	
	printf("No 3\n");
	int* arr3;
	int n, i;

	printf("������� n (����� ��������� �������):\n");
	scanf("%d", &n);

	printf("n = %d\n", n);
	arr3 = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {                                      //���� �������
		printf("������� ������� �������:");
		scanf("%d", &arr3[i]);
	}

	for (i = 0; i < n; i++) {                                      //����� �������
		printf("%d   ", arr3[i]);
	}

	printf("\n\n");

	free(arr3);
}





void numb4() {          //4 ����� �������� � ������ ������� (��� ������) ���������� �������
	
	printf("No 4\n");
	int* arr4;
	int h, k;
	int i, j;

	printf("������� k (����� ����� �������):\n");
	scanf("%d", &k);
	printf("������� h (����� �������� �������):\n");
	scanf("%d", &h);

	printf("k = %d\n", k);
	printf("h = %d\n", h);
	arr4 = (int*)malloc(h * k * sizeof(int));

	for (j = 0; j < k; j++) {                                       //���� ��� ������� �������
		for (i = 0; i < h; i++) {
			*(arr4 + j * h + i) = (rand() % 100) - (rand() % 100);
			/*printf("������� ������� �������[%d][%d]:", j, i);     //��� �������� � ����������
			scanf("%d", *(arr4 + j * h + i));*/
		}
	}

	for (j = 0; j < k; j++) {                                        //���� ��� ������ �������
		for (i = 0; i < h; i++) {
			printf("%7d", *(arr4 + j * h + i));
		}
		printf("\n");
	}

	printf("\n");

	int sum;

	for (j = 0; j < k; j++) {                                //j - stroki
		sum = 0;
		for (i = 0; i < h; i++) {
			sum = sum + *(arr4 + j * h + i);
		}
		printf("����� ������ No %d = %d\n", j, sum);
	}
	printf("\n");

	for (i = 0; i < h; i++) {                                //i - stolbci
		sum = 0;
		for (j = 0; j < k; j++) {
			sum = sum + *(arr4 + j * h + i);
		}
		printf("����� ������� No %d = %d\n", j, sum);
	}
	printf("\n");

	free(arr4);

}



void numb5() {                 //����� ����� �������� student ��������� �  ��������� ����������� (��������, ������ � �.�.).

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);                         //_IONBF	����� �� ������������, ���������� �� buffer ��� size.
	int i;                                                    
															  //���� mode����������� �������� _IONBF, ����� ��������������, 
														 	  //� ��� ��������� size� buffer������������
	struct student
	{
		char famil[20];
		char name[20], facult[20];
		int zachetka;
	}	stud[3];

	int t = 3;

	for (i = 0; i < t; i++)
	{
		printf("������� ������� ��������\n");
		scanf("%20s", stud[i].famil);

	}
	printf("\n");


	for (i = 0; i < t; i++)
	{
		printf("������� ��� �������� %s\n", stud[i].famil);
		scanf("%20s", stud[i].name);
	}
	printf("\n");


	for (i = 0; i < t; i++)
	{
		printf("������� �������� ���������� �������� %s %s\n", stud[i].famil, stud[i].name);
		scanf("%20s", stud[i].facult);
	}
	printf("\n");


	for (i = 0; i < t; i++)
	{
		printf("������� ����� �������� ������ �������� %s %s\n", stud[i].famil, stud[i].name);
		scanf("%d", &stud[i].zachetka);
	}
	printf("\n");


	/*for (i = 0; i < t; i++)
	{
		printf("C������ %s %s ��������� �� ���������� %s, ����� �������� ������ %d \n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].zachetka);
	}
	printf("\n");*/

	char fami[20], nam[20];
	printf("��� ������ �������� ������� �������: ");
	scanf("%s", &fami);
	printf("������� ���: ");
	scanf("%s", &nam);
	printf("\n");

	for (i = 0; i < t; i++) {
		if ((strcmp(stud[i].famil, fami) == 0) && (strcmp(stud[i].name, nam) == 0)) {
			printf("C������ %s %s ��������� �� ���������� %s, ����� �������� ������ %d \n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].zachetka);
		}
	}


}




	int main() {
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	numb1();
	numb2();
	numb3();
	numb4();
	numb5();
	
	system("pause");
}