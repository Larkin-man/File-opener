// Source.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <string.h>
#include <locale.h>

// Объявление глобальных переменных

class KOR
{public:

	

	char Name[50];
	char Nazv[10];
	int kol;
	float cena;
	KOR *next;


	void AddItem();
	void LoadTxtFile();
	void SaveTxtFile();
	void removeAt();
	void DeleteList(KOR*);
	int GetIndex();
	void SortList();
	void EditItem();
	KOR* CreateItem(const char* Name, const char* Nazv, int kol, float cena);
	KOR* GetTail(KOR*);
	KOR* push_back(KOR*, KOR*);
	
	
};
KOR *head=NULL;
int numrec=0;

// Объявление функций
int ShowMenu();
void PrintKor(KOR*, int);

// Главная функция
int _tmain(int argc, _TCHAR* argv[])
{
	int nMenu,i;
	KOR *st;
	KOR a;

	setlocale(LC_CTYPE,"Russian");
	do
	{
		nMenu=ShowMenu();
		switch(nMenu)
		{
		case 1:
			  {
				  a.AddItem();
				  break;
			  }
		case 2:
			  {
				  a.EditItem();
				  break;
			  }
		case 3:
			  {
				  a.removeAt();
				  break;
			  }
		case 4:
			  {if(!head)
				  {
					  printf("\nБаза данных пуста...\n");
					  break;
				  }
				  a.SortList();
				  
				  printf("\n");
				  printf("+----+--------------+--------------------+----------------+--------+\n");
				  printf("| №  |    Автор     |      Название      | Кол-во страниц |  Цена  |\n");
	              printf("+----+--------------+--------------------+----------------+--------+\n");
				  st = head;
				  i=1;
				  while(st)
				  {
					  PrintKor(st,i++);
					  st=st->next;
				  }
				  printf("+----+--------------+--------------------+----------------+--------+\n");
				  break;
			  }
		case 5:
			  {
				  if(head)
				  {
					  a.DeleteList(head);
					  head=NULL;
					  numrec=0;
				  }
				  a.LoadTxtFile();
				  break;
			  }
		case 6:
			  {
				  a.SaveTxtFile();
				  break;
			  }
		case 7:
			  {
				  if(!head)
				  {
					  printf("\nБаза данных и так пуста!\n"); 
					  break;
				  }
				  a.DeleteList(head);
				  head=NULL;
				  numrec=0;
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

	printf("\n====================================================================\n");
	printf("1 - Добавить запись\n");
	printf("2 - Изменить запись\n");
	printf("3 - Удалить  запись\n");
	printf("4 - Показать весь список\n");
	printf("5 - Загрузить текстовый файл\n");
	printf("6 - Сохранить текстовый файл\n");
	printf("7 - Удалить список\n");
	printf("0 - Выход\n");
	printf("Количество записей в базе: %d\n",numrec);
	printf("Ваш выбор: ");
	scanf("%d",&choice);
	return choice;
}

// Функция ввода данных о студенте
void KOR :: AddItem()
{
	char Name[50];
	char Nomer[10];
	int mest;
	float cena;
	KOR *st, *tail,a;

	flushall();			
	printf("Автор          : ");
	gets(Name); 
	printf("Название       : ");
	gets(Nazv);
	printf("Кол-во страниц : ");
	scanf("%d",&kol);
	printf("Цена           : ");
	scanf("%f",&cena);

	tail = GetTail(head);
	st=a.push_back(tail, a.CreateItem(Name, Nazv, kol, cena));
	if (!head)
		head = st;
	++numrec;
}

// Функция изменения записи
void KOR :: EditItem()
{
	int index;
	KOR *st,a;

	index=a.GetIndex();
	if(index==-1)
		return;
	st=head;
	for(int i=1;i<index;++i)
		st=st->next;
	printf("Сейчас эта запись содержит следующие данные:\n");
	printf("\n");
	printf("+----+--------------+--------------------+----------------+--------+\n");
	printf("| №  |    Автор     |      Название      | Кол-во страниц |  Цена  |\n");
	printf("+----+--------------+--------------------+----------------+--------+\n");
	PrintKor(st, index);
	printf("+----+--------------+--------------------+----------------+--------+\n");
	printf("\nВведите новые данные:\n");
	flushall();
	printf("Автор : ");
	gets(st->Name); 
	printf("Название : ");
	gets(st->Nazv);
	printf("Кол-во страниц: ");
	scanf("%d",&st->kol);
	printf("Цена: ");
	scanf("%f",&st->cena);
	printf("\nДанные изменены.\n");
}

// Функция удаления записи
void KOR :: removeAt()
{
	int index;
	KOR *st,a;

	index=a.GetIndex();
	if(index==-1)
		return;
	if(index==1)
	{
		head=head->next;
		--numrec;
		return;
	}
	st=head;
	for(int i=1;i<index-1;++i)
		st=st->next;
	st->next=st->next->next;
	--numrec;
}

// НОВАЯ Функция создает новый элемент (пока вне списка)
KOR* KOR :: CreateItem(const char* Name, const char* Nazv, int kol, float cena)
{
	KOR *st = new KOR;
	strcpy(st->Name, Name);
	strcpy(st->Nazv, Nazv);
	st->kol=kol;
	st->cena=cena;
	st->next=NULL;
	return st;
}

// НОВАЯ Функция находит последний элемент списка
KOR* KOR :: GetTail(KOR* st)
{
	while(st && st->next)
		st=st->next;
	return st;
}

// Функция добавляет созданный элемент в конец списка
KOR* KOR :: push_back(KOR *parent, KOR *st)
{
	if (parent) 
	{
		st->next = parent->next;
		parent->next = st;
	}
	return st;
}

// Функция печатает указанный элемент списка
void PrintKor(KOR *st, int i)
{
	printf("| %-2d | %-12s | %-18s | %-14d | %-6.1f |\n",i,st->Name,st->Nazv,st->kol,st->cena);
}

// Функция чтения БД из текстового файла
void KOR :: LoadTxtFile()
{
	FILE *fp;
	char Name[50];
	char Nazv[10];
	int kol;
	float cena;
	KOR *st, *tail,a;

	fp=fopen("db.txt","r");
	if(fp==NULL)
	{
		printf("\nОшибка открытия файла...\n");
		return;
	}
	// здесь надо удалить список, если он существует
	fscanf(fp,"%d\n",&numrec);
	for(int i=0;i<numrec;++i)
	{
		fgets(Name,50,fp);
		Name[strlen(Name)-1]='\0';
		fgets(Nazv,10,fp);
		Nazv[strlen(Nazv)-1]='\0';
		fscanf(fp,"%d\n",&kol);
		fscanf(fp,"%f\n",&cena);
		tail = a.GetTail(head);
		st=a.push_back(tail, a.CreateItem(Name, Nazv, kol, cena));
		if (!head)
			head = st;
	}
	printf("\nФайл прочитан.\n");
	fclose(fp);
}

// Функция сохранения БД в текстовый файл
void KOR :: SaveTxtFile()
{
	FILE *fp;
	KOR *st;

	if(!head)
	{
		printf("\nБаза данных пуста...\n");
		return;
	}
	fp=fopen("db.txt","w");
	if(fp==NULL)
	{
		printf("\nОшибка открытия файла...\n");
		return;
	}
	fprintf(fp,"%d\n",numrec);
	st=head;
	while(st)
	{
		fprintf(fp,"%s\n",st->Name);
		fprintf(fp,"%s\n",st->Nazv);
		fprintf(fp,"%d\n",st->kol);
		fprintf(fp,"%f\n",st->cena);
		st=st->next;
	}
	printf("\nФайл сохранен.\n");
	fclose(fp);
}

// НОВАЯ Функция удаляет весь список
void KOR :: DeleteList(KOR *head)
{
	KOR *st,a;
	st=head;
	if (st->next)				//Пока есть еще элементы
		a.DeleteList(st->next);	//удалить их
	delete st;					//удалить текущий элемент
}

// Функция запроса номера записи
int KOR :: GetIndex()
{
	int index;

	if(!head)
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
	return index;
}
void KOR :: SortList()
{
	KOR *st, *stnext, temp;
	
	int sortOk;
	do
	{
		sortOk=1;
		st=head;
		stnext=head->next;
		while(stnext)
		{
			if(strcmp(st->Name,stnext->Name)>0)
				{

					strcpy (temp.Name,st->Name);
					strcpy (temp.Nazv,st->Nazv);
					temp.kol=st->kol;
					temp.cena=st->cena;

					strcpy (st->Name,stnext->Name);
					strcpy (st->Nazv,stnext->Nazv);
					st->kol=stnext->kol;
					st->cena=stnext->cena;

					strcpy (stnext->Name,temp.Name);
					strcpy (stnext->Nazv,temp.Nazv);
					stnext->kol=temp.kol;
					stnext->cena=temp.cena;

						sortOk=0;
				}
			st=st->next;
			stnext=stnext->next;
		}
	
	}while(sortOk==0);
}

