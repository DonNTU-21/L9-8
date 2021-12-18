#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include "Validating.h"

void FileCreate();
void DisplayFileContent();
void ReverseAlphabetSort();
int GetMaxCulture();
int GetCultures();
int ValidateINT();

FILE* file;
int N = 0;
int years[] = { 1960, 1967 };

struct Row
{
	char name[60];
	int area[];
} e;



int main()
{
	setlocale(LC_ALL, "");
	system("chcp 1251");
	int choice = 0;

	while (1)
	{		
		printf("Что нужно сделать с файлом?\n");
		printf("1 - Создать файл\n");
		printf("2 - Вывод содержимого\n");
		printf("3 - Узнать культуру и её максимальную площадь в 1960г.\n");
		printf("4 - Узнать культуры площадь которых превысила 1000 т. га\n");
		printf("5 - Упорядочить в обратном порядке название культур, чья площадь в 1960г. не превысила 1300га.\n");
		printf("0 - Выход\n");
		printf("Ваш выбор: ");
		choice = ValidateINT();
		printf("\n\n");
		while (choice > 5 || choice < 0)
		{
			printf("Ошибка, такой категории нет. Повторите попытку!\n");
			printf("Ваш выбор: ");
			choice = ValidateINT();
		}
		switch (choice)
		{
		case 1:	FileCreate();
			break;
		case 2: DisplayFileContent();
			break;
		case 3: GetMaxCulture();
			break;
		case 4: GetCultures();
			break;
		case 5: ReverseAlphabetSort();
			break;
		case 0: return 0;
		}
		printf("\n\n");
	}
}

void FileCreate()
{
	file = fopen("res.dat", "w");
	if (file == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}
	strcpy(e.name, "a");

	while (strcmp(e.name, "") != 0)
	{
		printf("\nНаименование селхоз продукции: ");
		gets(e.name);
		if (strcmp(e.name, "") != 0)
		{
			N++;
			fwrite(&e.name, sizeof(e.name), 1, file);
			for (int i = 0; i < 2; i++)
			{
				printf("Производство в %d: ", years[i]);
				e.area[i] = ValidateINT();
				fwrite(&e.area[i], sizeof(e.area[i])+1, 1, file);
			}
		}	
	}
	printf("Данные записаны в файл res.dat\n\n\n");
	fclose(file);

}
void DisplayFileContent()
{
	if ((file = fopen("res.dat", "r+")) == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}
	int len,
		i;

	fseek(file, 0, SEEK_END);
	len = ftell(file);
	i = 0;
	while(i<len)
	{
		fseek(file, i, SEEK_SET);
		fread(&e.name, sizeof(e.name), 1, file);
		fread(&e.area[0], sizeof(e.area[0])+1, 1, file);
		fread(&e.area[1], sizeof(e.area[1]) + 1, 1, file);
		fseek(file, ftell(file), SEEK_SET);
		printf("%s %d %d\n", e.name, e.area[0], e.area[1]);
		i += sizeof(e)+1;
	}
	fclose(file);
}

void ReverseAlphabetSort()
{
}

int GetMaxCulture()
{
	return 0;
}

int GetCultures()
{
	return 0;
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