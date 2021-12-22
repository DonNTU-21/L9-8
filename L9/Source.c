#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define LINE "============================================================"
#define Culture struct Culture 

void FileCreate();
void AnalyzeFileContent();
void DisplayFileContent(char name[13]);
void Sort(FILE*);
int ValidateINT();

Culture
{
	char name[60];
	int area[2];
};

FILE* file;
Culture e;
int years[] = { 1960, 1967 };
int N;

int main()
{
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	system("color F0");
	int choice = 0;

	while (1)
	{
		printf("%s\nЧто нужно сделать с файлом?\n", LINE);
		printf("1 - Создать файл\n");
		printf("2 - Вывод содержимого\n");
		printf("0 - Выход\n");
		printf("Ваш выбор: ");
		choice = ValidateINT();
		printf("\n\n");
		while (choice > 3 || choice < 0)
		{
			printf("Ошибка, такой категории нет. Повторите попытку!\n");
			printf("Ваш выбор: ");
			choice = ValidateINT();
		}
		switch (choice)
		{
		case 1:	FileCreate();
			break;
		case 2:
			AnalyzeFileContent();
			printf("\t\tres.dat: \n");
			DisplayFileContent("res.dat");

			printf("\n\t\tMaxArea.dat: \n");
			DisplayFileContent("MaxArea.dat");

			printf("\n\t\tOverThousandArea.dat: \n");
			DisplayFileContent("OverThousandArea.dat");

			printf("\n\t\tSorted.dat: \n");
			DisplayFileContent("Sorted.dat");
			break;
		case 0:
			system("pause");
			return 0;
		}
		printf("%s\n\n", LINE);
	}
}

void FileCreate()
{
	file = fopen("res.dat", "wb+");
	if (file == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}
	strcpy(e.name, "a");

	while (strcmp(e.name, "") != 0)
	{
		printf("\nНаименование селхоз продукции: ");
		//N++;
		gets(e.name);
		if (strcmp(e.name, "") != 0)
		{
			fwrite(&e.name, sizeof(e.name), 1, file);
			for (int i = 0; i < 2; i++)
			{
				printf("Производство в %d: ", years[i]);
				e.area[i] = ValidateINT();
				fflush(stdin);
				fwrite(&e.area[i], sizeof(e.area[i]), 1, file);
			}
		}
	}
	printf("Данные записаны в файл res.dat\n\n\n");
	fclose(file);

}
void DisplayFileContent(char name[13])
{
	if ((file = fopen(name, "r")) == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
		system("pause");
	}
	int len,
		i;
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	i = 0;
	while (i < len)
	{
		fseek(file, i, SEEK_SET);
		fread(&e, sizeof(Culture), 1, file);
		printf("%s %d %d\n", e.name, e.area[0], e.area[1]);
		i += sizeof(Culture);
	}
	fclose(file);
}
void AnalyzeFileContent()
{

#pragma region Variables
	char tempName[30];

	unsigned char c1, c2;

	int len,
		i,
		lenSorted,
		v,
		j = 0,
		t;

#pragma endregion

	Culture sorted[30];
	Culture max;
	Culture x;

	FILE* MaxArea,
		* OverThousandArea,
		* Sorted;

#pragma region Files
	if ((file = fopen("res.dat", "r")) == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}
	if ((MaxArea = fopen("MaxArea.dat", "wb+")) == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}
	if ((OverThousandArea = fopen("OverThousandArea.dat", "wb+")) == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}
	if ((Sorted = fopen("Sorted.dat", "wb+")) == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}
#pragma endregion

	fseek(file, 0, SEEK_END);
	len = ftell(file);
	lenSorted = ftell(Sorted);
	i = 0;
	v = 0;


	while (i < len)
	{

		fseek(file, i, SEEK_SET);
		fread(&e, sizeof(Culture), 1, file);

		// Max. Культура '60
		if (max.area[0] < e.area[0])
		{

			strcpy(max.name, e.name);
			max.area[0] = e.area[0];
			max.area[1] = e.area[1];
		}
		// Культуры более 1000 га.
		if (e.area[1] > 1000)
		{
			fwrite(&e, sizeof(Culture), 1, OverThousandArea);
		}

		if (e.area[0] < 1300)
		{
			fwrite(&e, sizeof(Culture), 1, Sorted);
		}
		N++;
		i += sizeof(Culture);
	}

	fwrite(&max, sizeof(max), 1, MaxArea);
	Sort(Sorted);

	fclose(file);
	fclose(MaxArea);
	fclose(OverThousandArea);
	fclose(Sorted);
}
void Sort(FILE* sort)
{
	int i = 0,
		j = 0,
		pos;

	Culture a, b;

	fseek(sort, 0, SEEK_SET);

	while (i < (sizeof(Culture))*(N))
	{
		fseek(sort, i, SEEK_SET);
		fread(&a, sizeof(Culture), 1, sort);

		j = i + sizeof(Culture);

		while (j < (sizeof(Culture)*(N-1)))
		{
			fseek(sort, j, SEEK_SET);
			fread(&b, sizeof(Culture), 1, sort);

			if (strcmp(a.name, b.name) < 0)
			{
				printf("%s < %s\n", a.name, b.name);

				pos = i;
				fseek(sort, pos, SEEK_SET);
				fwrite(&b, sizeof(Culture), 1, sort);

				pos = j;
				fseek(sort, pos, SEEK_SET);
				fwrite(&a, sizeof(Culture), 1, sort);
				strcpy(a.name, b.name);
			}
			j += sizeof(Culture);
		}
		i += sizeof(Culture);
	}
}

int ValidateINT()
{
	char data[10];
	gets(data);
	while (!isdigit(data[0]))
	{
		fflush(stdin);
		printf("\nНеверный ввод! Повторите попытку: ");
		gets(data);
	}
	return atoi(data);
}

