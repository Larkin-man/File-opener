// Source.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <conio.h>
#include <string.h>
#include <locale.h>

// ���������� ���������� ����������
struct PRODUKT
{
	char name[50];
	char naz[10];
	int kol;
	float cena;
};
PRODUKT st[50];
int numrec=0;

// ���������� �������
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
					  printf("\n���� ������ �����...\n");
					  break;
				  }
				  printf("\n");
				  printf("+----+--------------+--------------------+----------------+--------+\n");
				  printf("| �  |    �����     |      ��������      | ���-�� ������� |  ����  |\n");
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
		default: printf("\n������������ ����� ����...\n");
		}
	}while(nMenu!=0);
	return 0;
}

// ������� ������ ���� �� �����
int ShowMenu()
{
	int choice;

	printf("\n===============================================================================\n");
	printf("1 - �������� ������\n");
	printf("2 - �������� ������\n");
	printf("3 - �������  ������\n");
	printf("4 - �������� ���� ������\n");
	printf("5 - ��������� ��������� ����\n");
	printf("6 - ��������� �������� ����\n");
	printf("7 - ��������� ��������� ����\n");
	printf("8 - ��������� �������� ����\n");
	printf("9 - ��������� �����\n");
	printf("0 - �����\n");
	printf("���������� ������� � ����: %d\n",numrec);
	printf("��� �����: ");
	scanf("%d",&choice);
	return choice;
}

// ������� ����� ������ � ��������
void AddItem()
{
	flushall();
	printf("����� : ");
	gets(st[numrec].name); 
	printf("��������   : ");
	gets(st[numrec].naz);
	printf("���-�� �������: ");
	scanf("%d",&st[numrec].kol);
	printf("����: ");
	scanf("%f",&st[numrec].cena);
	++numrec;
}

// ������� ��������� ������
void EditItem()
{
	int index;

	index=GetIndex();
	if(index==-1)
		return;
	printf("������ ��� ������ �������� ��������� ������:\n");
	printf("\n");
	printf("+----+--------------+--------------------+----------------+--------+\n");
	printf("| �  |    �����     |      ��������      | ���-�� ������� |  ����  |\n");
	printf("+----+--------------+--------------------+----------------+--------+\n");
	PrintPRODUKT(index);
	printf("+----+--------------+--------------------+----------------+--------+\n");
	printf("\n������� ����� ������:\n");
	flushall();
	printf("����� : ");
	gets(st[index].name); 
	printf("��������   : ");
	gets(st[index].naz);
	printf("���-�� �������: ");
	scanf("%d",&st[index].kol);
	printf("����: ");
	scanf("%f",&st[index].cena);
	printf("\n������ ��������.\n");
}

// ������� �������� ������
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

// ������� ������ �� ����� ���������� �� ����� ��������
void PrintPRODUKT(int i)
{
	printf("| %-2d | %-12s | %-18s | %-14d | %-6.1f |\n",i+1,st[i].name,st[i].naz,st[i].kol,st[i].cena);
}

// ������� ������ �� �� ���������� �����
void LoadTxtFile()
{
	FILE *fp;

	fp=fopen("db.txt","r");
	if(fp==NULL)
	{
		printf("\n������ �������� �����...\n");
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
	printf("\n���� ��������.\n");
	fclose(fp);
}

// ������� ������ �� �� ��������� (���������) �����
void LoadBinFile()
{
	FILE *fp;

	fp=fopen("db.bin","r");
	if(fp==NULL)
	{
		printf("\n������ �������� �����...\n");
		return;
	}
	fread(&numrec,sizeof(int),1,fp);
	for(int i=0;i<numrec;++i)
	{
		fread(&st[i],sizeof(PRODUKT),1,fp);
	}
	printf("\n���� ��������.\n");
	fclose(fp);
}

// ������� ���������� �� � ��������� ����
void SaveTxtFile()
{
	FILE *fp;

	fp=fopen("db.txt","w");
	if(fp==NULL)
	{
		printf("\n������ �������� �����...\n");
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
	printf("\n���� ��������.\n");
	fclose(fp);
}

// ������� ���������� �� � �������� (��������) ����
void SaveBinFile()
{
	FILE *fp;

	fp=fopen("db.bin","w");
	if(fp==NULL)
	{
		printf("\n������ �������� �����...\n");
		return;
	}
	fwrite(&numrec,sizeof(int),1,fp);
	for(int i=0;i<numrec;++i)
	{
		fwrite(&st[i],sizeof(PRODUKT),1,fp);
	}
	printf("\n���� ��������.\n");
	fclose(fp);
}

// ������� ���������� �� � ����-�����
void SaveReport()
{
	FILE *fp;

	fp=fopen("report.txt","w");
	if(fp==NULL)
	{
		printf("\n������ �������� �����...\n");
		return;
	}
	fprintf(fp,"==================================== ����� ====================================\n");
	fprintf(fp,"+----+--------------+--------------------+----------------+--------+\n");
	fprintf(fp,"| �  |    �����     |      ��������      | ���-�� ������� |  ����  |\n");
	fprintf(fp,"+----+--------------+--------------------+----------------+--------+\n");
	for(int i=0;i<numrec;++i)
	{
		fprintf(fp,"| %-2d | %-30s | %-11s | %-12d | %-8.1f |\n",i+1,st[i].name,st[i].naz,st[i].kol,st[i].cena);
	}
	fprintf(fp,"+----+--------------+--------------------+----------------+--------+\n");
	printf("\n����� ��������.\n");
	fclose(fp);
}

// ������� ������� ������ ������
int GetIndex()
{
	int index;

	if(numrec==0)
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
	return index-1;
}

// ������� ���������� ������� �� ���� ������������
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