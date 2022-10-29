// Source.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <string.h>
#include <locale.h>

// ���������� ���������� ����������

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

// ���������� �������
int ShowMenu();
void PrintKor(KOR*, int);

// ������� �������
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
					  printf("\n���� ������ �����...\n");
					  break;
				  }
				  a.SortList();
				  
				  printf("\n");
				  printf("+----+--------------+--------------------+----------------+--------+\n");
				  printf("| �  |    �����     |      ��������      | ���-�� ������� |  ����  |\n");
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
					  printf("\n���� ������ � ��� �����!\n"); 
					  break;
				  }
				  a.DeleteList(head);
				  head=NULL;
				  numrec=0;
				  break;
			  }
		default: printf("\n������������ ����� ����...\n");
		}
	}while(nMenu!=0);
	return 0;
}

// ������� ������ ���� �� �����
int ShowMenu()
{
	int choice;

	printf("\n====================================================================\n");
	printf("1 - �������� ������\n");
	printf("2 - �������� ������\n");
	printf("3 - �������  ������\n");
	printf("4 - �������� ���� ������\n");
	printf("5 - ��������� ��������� ����\n");
	printf("6 - ��������� ��������� ����\n");
	printf("7 - ������� ������\n");
	printf("0 - �����\n");
	printf("���������� ������� � ����: %d\n",numrec);
	printf("��� �����: ");
	scanf("%d",&choice);
	return choice;
}

// ������� ����� ������ � ��������
void KOR :: AddItem()
{
	char Name[50];
	char Nomer[10];
	int mest;
	float cena;
	KOR *st, *tail,a;

	flushall();			
	printf("�����          : ");
	gets(Name); 
	printf("��������       : ");
	gets(Nazv);
	printf("���-�� ������� : ");
	scanf("%d",&kol);
	printf("����           : ");
	scanf("%f",&cena);

	tail = GetTail(head);
	st=a.push_back(tail, a.CreateItem(Name, Nazv, kol, cena));
	if (!head)
		head = st;
	++numrec;
}

// ������� ��������� ������
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
	printf("������ ��� ������ �������� ��������� ������:\n");
	printf("\n");
	printf("+----+--------------+--------------------+----------------+--------+\n");
	printf("| �  |    �����     |      ��������      | ���-�� ������� |  ����  |\n");
	printf("+----+--------------+--------------------+----------------+--------+\n");
	PrintKor(st, index);
	printf("+----+--------------+--------------------+----------------+--------+\n");
	printf("\n������� ����� ������:\n");
	flushall();
	printf("����� : ");
	gets(st->Name); 
	printf("�������� : ");
	gets(st->Nazv);
	printf("���-�� �������: ");
	scanf("%d",&st->kol);
	printf("����: ");
	scanf("%f",&st->cena);
	printf("\n������ ��������.\n");
}

// ������� �������� ������
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

// ����� ������� ������� ����� ������� (���� ��� ������)
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

// ����� ������� ������� ��������� ������� ������
KOR* KOR :: GetTail(KOR* st)
{
	while(st && st->next)
		st=st->next;
	return st;
}

// ������� ��������� ��������� ������� � ����� ������
KOR* KOR :: push_back(KOR *parent, KOR *st)
{
	if (parent) 
	{
		st->next = parent->next;
		parent->next = st;
	}
	return st;
}

// ������� �������� ��������� ������� ������
void PrintKor(KOR *st, int i)
{
	printf("| %-2d | %-12s | %-18s | %-14d | %-6.1f |\n",i,st->Name,st->Nazv,st->kol,st->cena);
}

// ������� ������ �� �� ���������� �����
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
		printf("\n������ �������� �����...\n");
		return;
	}
	// ����� ���� ������� ������, ���� �� ����������
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
	printf("\n���� ��������.\n");
	fclose(fp);
}

// ������� ���������� �� � ��������� ����
void KOR :: SaveTxtFile()
{
	FILE *fp;
	KOR *st;

	if(!head)
	{
		printf("\n���� ������ �����...\n");
		return;
	}
	fp=fopen("db.txt","w");
	if(fp==NULL)
	{
		printf("\n������ �������� �����...\n");
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
	printf("\n���� ��������.\n");
	fclose(fp);
}

// ����� ������� ������� ���� ������
void KOR :: DeleteList(KOR *head)
{
	KOR *st,a;
	st=head;
	if (st->next)				//���� ���� ��� ��������
		a.DeleteList(st->next);	//������� ��
	delete st;					//������� ������� �������
}

// ������� ������� ������ ������
int KOR :: GetIndex()
{
	int index;

	if(!head)
	{
		printf("\n���� ������ �����...\n");
		return -1;
	}
	printf("\n������� ����� ������ (1..%d): ",numrec);
	scanf("%d",&index);
	if(index<1 || index>numrec)
	{
		printf("\n��� ������ � ����� �������...\n");
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

