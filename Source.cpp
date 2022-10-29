// Source.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <conio.h>
#include <string.h>
#include <locale.h>

// Объявление глобальных переменных
struct PRODUKT
{
	char name[50];
	char naz[10];
	int kol;
	float cena;
};
PRODUKT st[50];
int numrec=0;

// Объявление функций
int  ShowMenu();
void AddItem();
void EditItem();
void DeleteItem();
void PrintPRODUKT(int numrec);
void LoadTxtFile();
void LoadBinFile();
void SaveTxtFile();
void SaveBinFile();
void SaveReport();
int  GetIndex();
void SortList();

int _tmain(int argc, _TCHAR* argv[])
{
	int nMenu;

	setlocale(LC_CTYPE,"Russian");
	do
	{
		nMenu=ShowMenu();
		switch(nMenu)
		{
		case 1:
			  {
				  AddItem();
				  break;
			  }
		case 2:
			  {
				  EditItem();
				  break;
			  }
		case 3:
			  {
				  DeleteItem();
				  break;
			  }
		case 4:
			  {
				  SortList();
				  if(numrec==0)
				  {
					  printf("\nБаза данных пуста...\n");
					  break;
				  }
				  printf("\n");
				  printf("+----+--------------+--------------------+----------------+--------+\n");
				  printf("| №  |    Автор     |      Название      | Кол-во страниц |  Цена  |\n");
	              printf("+----+--------------+--------------------+----------------+--------+\n");
				  for(int i=0;i<numrec;++i)
				  {
					  PrintPRODUKT(i);
				  }
				  printf("+----+--------------+--------------------+----------------+--------+\n");
				  break;
			  }
		case 5:
			  {
				  LoadTxtFile();
				  break;
			  }
		case 6:
			  {
				  LoadBinFile();
				  break;
			  }
		case 7:
			  {
				  SaveTxtFile();
				  break;
			  }
		case 8:
			  {
				  SaveBinFile();
				  break;
			  }
		case 9:
			  {
				  SaveReport();
				  break;
			  }
		default: printf("\nНеправильный пункт меню...\n");
		}
	}while(nMenu!=0);
	return 0;
}

// Функция вывода меню на экран
int ShowMenu()
{
	int choice;

	printf("\n===============================================================================\n");
	printf("1 - Добавить запись\n");
	printf("2 - Изменить запись\n");
	printf("3 - Удалить  запись\n");
	printf("4 - Показать весь список\n");
	printf("5 - Загрузить текстовый файл\n");
	printf("6 - Загрузить двойчный файл\n");
	printf("7 - Сохранить текстовый файл\n");
	printf("8 - Сохранить двоичный файл\n");
	printf("9 - Сохранить отчет\n");
	printf("0 - Выход\n");
	printf("Количество записей в базе: %d\n",numrec);
	printf("Ваш выбор: ");
	scanf("%d",&choice);
	return choice;
}

// Функция ввода данных о продукте
void AddItem()
{
	flushall();
	printf("Автор : ");
	gets(st[numrec].name); 
	printf("Название   : ");
	gets(st[numrec].naz);
	printf("Кол-во страниц: ");
	scanf("%d",&st[numrec].kol);
	printf("Цена: ");
	scanf("%f",&st[numrec].cena);
	++numrec;
}

// Функция изменения записи
void EditItem()
{
	int index;

	index=GetIndex();
	if(index==-1)
		return;
	printf("Сейчас эта запись содержит следующие данные:\n");
	printf("\n");
	printf("+----+--------------+--------------------+----------------+--------+\n");
	printf("| №  |    Автор     |      Название      | Кол-во страниц |  Цена  |\n");
	printf("+----+--------------+--------------------+----------------+--------+\n");
	PrintPRODUKT(index);
	printf("+----+--------------+--------------------+----------------+--------+\n");
	printf("\nВведите новые данные:\n");
	flushall();
	printf("Автор : ");
	gets(st[index].name); 
	printf("Название   : ");
	gets(st[index].naz);
	printf("Кол-во страниц: ");
	scanf("%d",&st[index].kol);
	printf("Цена: ");
	scanf("%f",&st[index].cena);
	printf("\nДанные изменены.\n");
}

// Функция удаления записи
void DeleteItem()
{
	int index;

	index=GetIndex();
	if(index==-1)
		return;
	for(int i=index;i<numrec-1;++i)
		st[i]=st[i+1];
	--numrec;
}

// Функция вывода на экран информации об одном продукте
void PrintPRODUKT(int i)
{
	printf("| %-2d | %-12s | %-18s | %-14d | %-6.1f |\n",i+1,st[i].name,st[i].naz,st[i].kol,st[i].cena);
}

// Функция чтения БД из текстового файла
void LoadTxtFile()
{
	FILE *fp;

	fp=fopen("db.txt","r");
	if(fp==NULL)
	{
		printf("\nОшибка открытия файла...\n");
		return;
	}
	fscanf(fp,"%d\n",&numrec);
	for(int i=0;i<numrec;++i)
	{
		fgets(st[i].name,50,fp);
		st[i].name[strlen(st[i].name)-1]='\0';
		fgets(st[i].naz,10,fp);
		st[i].naz[strlen(st[i].naz)-1]='\0';
		fscanf(fp,"%d",&st[i].kol);
		fscanf(fp,"%f\n",&st[i].cena);
	}
	printf("\nФайл прочитан.\n");
	fclose(fp);
}

// Функция чтения БД из двоичного (бинарного) файла
void LoadBinFile()
{
	FILE *fp;

	fp=fopen("db.bin","r");
	if(fp==NULL)
	{
		printf("\nОшибка открытия файла...\n");
		return;
	}
	fread(&numrec,sizeof(int),1,fp);
	for(int i=0;i<numrec;++i)
	{
		fread(&st[i],sizeof(PRODUKT),1,fp);
	}
	printf("\nФайл прочитан.\n");
	fclose(fp);
}

// Функция сохранения БД в текстовый файл
void SaveTxtFile()
{
	FILE *fp;

	fp=fopen("db.txt","w");
	if(fp==NULL)
	{
		printf("\nОшибка открытия файла...\n");
		return;
	}
	fprintf(fp,"%d\n",numrec);
	for(int i=0;i<numrec;++i)
	{
		fprintf(fp,"%s\n",st[i].name);
		fprintf(fp,"%s\n",st[i].naz);
		fprintf(fp,"%d\n",st[i].kol);
		fprintf(fp,"%f\n",st[i].cena);
	}
	printf("\nФайл сохранен.\n");
	fclose(fp);
}

// Функция сохранения БД в двоичный (бинарный) файл
void SaveBinFile()
{
	FILE *fp;

	fp=fopen("db.bin","w");
	if(fp==NULL)
	{
		printf("\nОшибка открытия файла...\n");
		return;
	}
	fwrite(&numrec,sizeof(int),1,fp);
	for(int i=0;i<numrec;++i)
	{
		fwrite(&st[i],sizeof(PRODUKT),1,fp);
	}
	printf("\nФайл сохранен.\n");
	fclose(fp);
}

// Функция сохранения БД в файл-отчет
void SaveReport()
{
	FILE *fp;

	fp=fopen("report.txt","w");
	if(fp==NULL)
	{
		printf("\nОшибка открытия файла...\n");
		return;
	}
	fprintf(fp,"==================================== ОТЧЕТ ====================================\n");
	fprintf(fp,"+----+--------------+--------------------+----------------+--------+\n");
	fprintf(fp,"| №  |    Автор     |      Название      | Кол-во страниц |  Цена  |\n");
	fprintf(fp,"+----+--------------+--------------------+----------------+--------+\n");
	for(int i=0;i<numrec;++i)
	{
		fprintf(fp,"| %-2d | %-30s | %-11s | %-12d | %-8.1f |\n",i+1,st[i].name,st[i].naz,st[i].kol,st[i].cena);
	}
	fprintf(fp,"+----+--------------+--------------------+----------------+--------+\n");
	printf("\nОтчет сохранен.\n");
	fclose(fp);
}

// Функция запроса номера записи
int GetIndex()
{
	int index;

	if(numrec==0)
	{
		printf("\nБаза данных пуста...\n");
		return -1;
	}
	printf("\nВведите номер записи (1..%d): ",numrec);
	scanf("%d",&index);
	if(index<1 || index>numrec)
	{
		printf("\nНет записи с таким номером...\n");
		return -1;
	}
	return index-1;
}

// Функция сортировки записей по полю Наименование
void SortList()
{
	PRODUKT temp;
	int sortOk;

	do
	{
		sortOk=1;
		for(int i=0;i<numrec-1;++i)
		{
			if(strcmp(st[i].name,st[i+1].name)>0)
			{
				temp=st[i];
				st[i]=st[i+1];
				st[i+1]=temp;
				sortOk=0;
			}
		}
	}while(sortOk==0);
}