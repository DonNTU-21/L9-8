#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

void FileCreate();
void DisplayFileContent();
void ReverseAlphabetSort();
int GetMaxCulture();
int GetCultures();
int ValidateINT();

FILE* file;
int N = 0;
int years[] = { 1960, 1967 };

struct Culture
{
	char name[60];
	int area[2];
} e;



int main()
{
	setlocale(LC_ALL, "");
	system("chcp 1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice = 0;

	while (1)
	{		
		printf("Что нужно сделать с файлом?\n");
		printf("1 - Создать файл\n");
		printf("2 - Вывод содержимого\n");
		printf("3 - Узнать культуру и её максимальную площадь в 1960г.\n");
		printf("4 - Узнать культуры площадь которых превысила 1000 т. га в 1967г.\n");
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
		case 2: DisplayFileContent("res.dat");
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
		gets(e.name);
		if (strcmp(e.name, "") != 0)
		{
			N++;
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
		fread(&e.area[0], sizeof(int), 1, file);
		fread(&e.area[1], sizeof(int), 1, file);
		printf("%s %d %d\n", e.name, e.area[0], e.area[1]);
		i += sizeof(e.name)+2*sizeof(int);
	}
	fclose(file);
}
void ReverseAlphabetSort()
{
	struct Culture sorted[30];
	FILE* sortedFile;
	unsigned char c1, c2;
	char temp[30];
	int tempInt;
	int limit = 1300;
	int len, i, j, k, u, v;

	if ((file = fopen("res.dat", "r"))				== NULL || 
		(sortedFile = fopen("sorted.dat", "wb+"))	== NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}

	fseek(file, 0, SEEK_END);

	len = ftell(file);
	i = 0;
	j = 0;

	while (i < len)
	{
		printf("i = %d\n", i);
		fseek(file, i, SEEK_SET);
		fread(&sorted[j].name, sizeof(e.name), 1, file);
		fread(&sorted[j].area[0], sizeof(int), 1, file);
		fread(&sorted[j].area[1], sizeof(int), 1, file);
		j++;
		i += sizeof(e.name) + 2 * sizeof(int);
	}

	/*for (k = 0; k < j; k++)
	{
		printf("sorted[%d] = { %s, %d, %d }\n", k, sorted[k].name, sorted[k].area[0], sorted[k].area[1]);
	}*/

	printf("j = %d\n", j);
	for (k = 0; k < j; k++)
	{
		for (u = j-1; u >= k; u--)
		{
			c1 = sorted[u - 1].name[0];
			c2 = sorted[u].name[0];
			if (c1 > c2)
			{
				strcpy(temp, sorted[u - 1].name);
				strcpy(sorted[u - 1].name, sorted[u].name);
				strcpy(sorted[u].name, temp);
				for (v = 0; v < 2; v++)
				{
					tempInt = sorted[u - 1].area[v];
					sorted[u - 1].area[v] = sorted[u].area[v];
					sorted[u].area[v] = tempInt;
				}
			}
		}
	}
	for (i = 0; i < j; i++)
	{
		fwrite(&sorted[i].name, sizeof(sorted[i].name), 1, sortedFile);
		fwrite(&sorted[i].area[0], sizeof(int), 1, sortedFile);
		fwrite(&sorted[i].area[1], sizeof(int), 1, sortedFile);
	}

	fclose(file);
	fclose(sortedFile);
	DisplayFileContent("sorted.dat");
}
int GetMaxCulture() // Макс. площадь в 1960г.
{
	int maxArea = 0;
	char maxAreaCulture[50];
	int len, i;
	if ((file = fopen("res.dat", "r")) == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	i = 0;

	while (i < len)
	{
		fseek(file, i, SEEK_SET);
		fread(&e.name, sizeof(e.name), 1, file);
		fread(&e.area[0], sizeof(int), 1, file);
		if (i == 0)
		{
			strcpy(maxAreaCulture, e.name);
			maxArea = e.area[0];
		}
		else if (e.area[0] > maxArea)
		{
			strcpy(maxAreaCulture, e.name);
			maxArea = e.area[0];
		}
		fread(&e.area[1], sizeof(int), 1, file);	
		i += sizeof(e.name) + 2 * sizeof(int);
		//printf("\n e.area = %d, maxArea = %d", e.area[0], maxArea);
	}
	printf("Max Area is equal to %d in %s ", maxArea, maxAreaCulture);
	fclose(file);
	return 0;
}
int GetCultures()
{
	int currentArea = 0;
	int limit = 1000;
	char currentCulture[50];
	int len, i;
	if ((file = fopen("res.dat", "r")) == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(-1);
	}
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	i = 0;

	while (i < len)
	{
		fseek(file, i, SEEK_SET);
		fread(&e.name, sizeof(e.name), 1, file);
		fread(&e.area[0], sizeof(int), 1, file);
		fread(&e.area[1], sizeof(int), 1, file);
		if (e.area[1] > limit)
		{
			strcpy(currentCulture, e.name);
			currentArea = e.area[1];
			printf("В %d году производство СелХоз продукции %s превысило %d(%d)\n", years[1], currentCulture, limit, currentArea);

		}
		i += sizeof(e.name) + 2 * sizeof(int);
	}
	fclose(file);
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