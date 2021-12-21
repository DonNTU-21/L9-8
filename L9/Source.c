#define _CRT_SECURE_NO_WARNINGS
#define LINE "============================================================"
#define Culture struct Culture 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>


void FileCreate();
void AnalyzeFileContent();
void DisplayFileContent(char name[13]);
int ValidateINT();

Culture
{
	char name[60];
	int area[2];
};

FILE* file;
Culture e;
int years[] = { 1960, 1967 };




int main()
{
	setlocale(LC_ALL, "");
	system("chcp 1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
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

			printf("\n\t\OverThousandArea.dat: \n");
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
void AnalyzeFileContent()
{
#pragma region Variables
	int maxArea = 0;
	char maxAreaCulture[50];

	unsigned char c1, c2;

	int len, 
		i, 
		j = 0, 
		t, 
		tempName[30];
#pragma endregion

	Culture sorted[30];

	FILE* MaxArea,
		* OverThousandArea,
		* Sorted;

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

	fseek(file, 0, SEEK_END);
	len = ftell(file);
	i = 0;

	strcpy(maxAreaCulture, "a");

	while (i < len)
	{
		fseek(file, i, SEEK_SET);
		fread(&e.name, sizeof(e.name), 1, file);
		fread(&e.area[0], sizeof(int), 1, file);
		fread(&e.area[1], sizeof(int), 1, file);

		// Max. Культура '60
		if (maxArea < e.area[0])						
		{
			strcpy(maxAreaCulture, e.name);
			maxArea = e.area[0];
		}	
		// Культуры более 1000 га.
		if (e.area[1] > 1000)							
		{
			fwrite(e.name, sizeof(e.name), 1, OverThousandArea);
			fwrite(&e.area[0], sizeof(int), 1, OverThousandArea);
			fwrite(&e.area[1], sizeof(int), 1, OverThousandArea);
		}

		if (e.area[0] < 1300)
		{
			strcpy(sorted[j].name, e.name);
			sorted[j].area[0] = e.area[0];
			sorted[j].area[1] = e.area[1];
			j++;
		}

		i += sizeof(e.name) + 2 * sizeof(int);
	}

	for (int k = 0; k < j; k++)
	{
		for (int u = j-1; u > k; u--)
		{
			c1 = sorted[u - 1].name[0];
			c2 = sorted[u].name[0];
			
			//printf("%c < %c", c1, c2);

			if (c1 < c2)
			{
				//printf(" - true");
				strcpy(tempName, sorted[u - 1].name);
				strcpy(sorted[u - 1].name, sorted[u].name);
				strcpy(sorted[u].name, tempName);
				for (int v = 0; v < 2; v++)
				{
					t = sorted[u - 1].area[v];
					sorted[u - 1].area[v] = sorted[u].area[v];
					sorted[u].area[v] = t;
				}
			}
			//printf("\n");
		}
	}

	fwrite(maxAreaCulture, sizeof(maxAreaCulture), 1, MaxArea);
	fwrite(&maxArea, sizeof(int), 1, MaxArea);

	for (int i = 0; i < j; i++)
	{
		fwrite(&sorted[i].name, sizeof(sorted[i].name), 1, Sorted);
		fwrite(&sorted[i].area[0], sizeof(int), 1, Sorted);
		fwrite(&sorted[i].area[1], sizeof(int), 1, Sorted);
	}
	
	fclose(file);
	fclose(MaxArea);
	fclose(OverThousandArea);
	fclose(Sorted);
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