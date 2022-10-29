//*****�������� ������ �� ����������*****//
//*****"���������� ����������������"*****//
//********���������� �.�. ��08-04********//

#include <iostream>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

using namespace std; 

struct Node     //���������� ������
{
   char name[80];
   int  num1;
   int  num2;
   int  num3;
   Node *pNext;
   Node *pPrev;
};

Node *Record = NULL; //����� ������
int nRecord = 0;     //���������� �������

Node *CreateItem (int id, const char *name, float mark);
Node *InsertAfter (Node *parent, Node *Item);
Node *getTail (Node *head);
Node *PushBack (Node *head, Node *Item); 
void PrintNode (Node *Item);
void PrintList (Node *head);
void DeleteList (Node *Item);
Node *RemoveNode (Node *prev, Node *Item);

int showMenu();
void addItem();
void deleteItem();
void modifyItem();

bool saveAsBinary();
bool loadFromBinary();
bool saveAsText();
bool loadFromText(); 
int getIndex();
bool saveReport();

void main()   //int _tmain(int argc, _TCHAR* argv[])
{
	int nMenu = 0;                   

	while ((nMenu = showMenu()) != 0)
	{
		switch (nMenu)
		{
		case 1:
			addItem();
			break;
		case 2:
			deleteItem();
			break;
		case 3:
			modifyItem();
			break;
		case 4:
			PrintList (Record);
			break;
		case 5:
			if (saveAsBinary())
			{
				cout << "File saved.";
			}
			break;
		case 7:
			if (saveAsText())
			{
				cout << "File saved.";
			}
			break;
		case 6:
			if (loadFromBinary())
			{
				cout << "File loaded.";
			}
			break;
		case 8:
			if (loadFromText())
			{
				cout << "File loaded.";
			}
			break;
		case 9:
			if (saveReport())
			{
				cout << "Report saved.";
			}
			break;
		default:
			cout << "Wrong menu item!" <<endl;
		}
	}

	if (Record != NULL)
	{
		delete [] Record;
	}
        
	//getch(); //return 0;
}

Node *CreateItem (const char *name, int  num1, int  num2 ,int  num3)
{                //������� ������� ����� �������
   Node *pItem = new Node;
   strncpy(pItem->name,name,80);
   pItem->num1=num1;
   pItem->num2=num2;
   pItem->num3=num3;
   pItem->pNext=NULL;
   pItem->pPrev=NULL;
   return pItem;
}

Node *InsertAfter (Node *parent, Node *Item)
{                 //������� ��������� ��� ��������
   if (parent != NULL)
   {
      //Item->pNext=parent->pNext;
      parent->pNext=Item;
      Item->pPrev=parent;
   }
   return Item;
}

Node *getTail (Node *head)
{             //������� ������ ���������� �������� � ������
   if(head == NULL)
      return NULL;
   Node *Item=head;
   while(Item->pNext != NULL)
      Item = Item->pNext;
   return Item;
}

Node *PushBack (Node *head, Node *Item)
{              //������� ��������� ������� � ����� ������
   Node *tail = getTail(head);
   return InsertAfter (tail, Item);
}

void PrintNode (Node *Item)
{              //������� �������� ���� ������� �� ������
   printf("%s ",Item->name);
   printf("%d ",Item->num1);
   printf("%d ",Item->num2);
   printf("%d \n",Item->num3);
}

void PrintList (Node *head)
{              //������� �������� ���� ������ �� ������
   Node *Item = head;
   printf("Record:\n");
   while(Item != NULL)
   {
      PrintNode(Item);
      Item = Item->pNext;
   }
}                              

void DeleteList (Node *Item)
{               //������� ������� ������
   if (Item->pNext != NULL)
   {
      DeleteList (Item->pNext);
   }
   delete Item;
}

Node *RemoveNode (Node *prev, Node *Item)
{                //������� ������� �������� ������ ������������ ����� Item
   if (prev == Item)
   {
      return Item;
   }
   while (prev != NULL && prev->pNext != Item)
   {
      prev = prev->pNext;
   }
   if (prev != NULL)
   {
      prev->pNext=Item->pNext;
   }
   return Item;
}

int showMenu()    //������� ���������� ����
{
	cout << "\n1. Add"	<< endl;
	cout << "2. Delete"	<< endl;
	cout << "3. Modify"	<< endl;
	cout << "4. Print"	<< endl;
	cout << "5. Save into Binary"	<< endl;
	cout << "6. Load from Binary"	<< endl;
	cout << "7. Save to Text"		<< endl;
	cout << "8. Load from Text"		<< endl;
        cout << "9. Save Report"		<< endl;
	//cout << "---------"	<< endl;
	cout << "0. Exit"	<< endl;
	cout << "\n?>";

	int choise = 0;
	cin >> choise;

	return choise;
}

void addItem()     //������� ��������� ������� � ������
{
   cout << "Please type a new value: ";
   char name[80];
   int num1;
   int num2;
   int num3;
   nRecord++;
   scanf("%s %d %d %d",&name,&num1,&num2,&num3);
   Node *Item = PushBack(Record,CreateItem(name,num1,num2,num3));
   if(Record == NULL)
      Record=Item;

}

void deleteItem()    //������� ������� �������� �������
{
   Node *Item = Record;
   int nIdx = getIndex();
   for (int i=0;i<nIdx;i++)
      {
      Item=Item->pNext;
      }
   
   if (Item->pNext == NULL)
       Item->pPrev->pNext=NULL;
   else
   if (Item->pPrev == NULL)
       {
       Record=Record->pNext;
       Item->pNext->pPrev=NULL;
       }
   else
   InsertAfter(Item->pPrev,Item->pNext);
   nRecord--;

}

int getIndex()    //������� ���������� ������ ��������
{
	if (Record == NULL)
	{
		cout << "Record is empty" << endl;
		return -1;
	}
	int nIdx = -1;
	cout << "Please enter an item's index to delete from array (1.." << nRecord << "):";
	cin >> nIdx;

	if (nIdx < 1 || nIdx > nRecord)
	{
		cout << "Error: index is out of bound.";
		return -1;
	}

	return nIdx - 1;

}
void modifyItem()    //������� �������� �������
{
   int nIdx = getIndex();
   if (nIdx == -1)
   {
   return;
   }

   cout << "You are going to replace value " << Record->name << " at position " << nIdx + 1 << "." << endl;
   cout << "Please type a new value: ";
   Node *Item = Record;
   for (int i=0;i<nIdx;i++)
      {
      Item=Item->pNext;
      }
   scanf("%s %d %d %d",&Item->name,
                       &Item->num1,
                       &Item->num2,
                       &Item->num3);
}

bool saveAsBinary()    //������� ��������� ������ � �������� ����
{
   FILE *fp = fopen ("lab14.bin", "w");

	if (!fp)
	{
		cout << "Cannot create binary file";
		return false;
	}  
	fwrite(&nRecord, sizeof(int), 1, fp);
        for (int i = 0; i < nRecord; ++i)
	{
           int len = strlen(Record->name);
           fwrite(&len, sizeof(int), 1, fp);
           fwrite(Record->name, 1, len, fp);  
           fwrite(&Record->num1, sizeof(int), 1, fp);
           fwrite(&Record->num2, sizeof(int), 1, fp);
           fwrite(&Record->num3, sizeof(int), 1, fp);
         //fwrite(&Record->pNext, sizeof(*Node), 1, fp);  ��������� ��������� �� �����
         //fwrite(&Record->pPrev, sizeof(*Node), 1, fp);  ���� ����� ������� �����
           Record=Record->pNext;
	}

	fclose(fp);
	return true;
}

bool loadFromBinary()    //������� ��������� ������ �� ��������� �����
{
   FILE *fp = fopen ("lab14.bin", "r");

	if (!fp)
	{
		cout << "Cannot open binary file";
		return false;
	}

	if (Record)
	{
		delete [] Record;
		Record = NULL;
	}

	fread(&nRecord, sizeof(int), 1, fp);
	for (int i = 0; i < nRecord; ++i)
	{
           char name[80];
           int num1;
           int num2;
           int num3; 
           int len = 0;
           fread(&len, sizeof(int), 1, fp);
           fread(name, sizeof(char), len, fp);
           name[len]='\0'; 
           fread(&num1, sizeof(int), 1, fp);
           fread(&num2, sizeof(int), 1, fp);
           fread(&num3, sizeof(int), 1, fp);
           //fread(&Record,sizeof(Record), 1, fp);
           Node *Item = PushBack(Record,CreateItem(name,num1,num2,num3));
           if(Record == NULL)
           Record=Item;  
	}

	fclose(fp);
	return true;
 }
bool saveAsText()   //������� ��������� ������ � ��������� ����
{                                     
   FILE *fp = fopen ("lab14.txt", "w");

	if (!fp)
	{
		cout << "Cannot create text file";
		return false;
	}
        //Node *Item = Record;

	fprintf(fp, "%d ", nRecord);
	for (int i = 0; i < nRecord; ++i)
	{
                fprintf(fp, "%s ", Record->name);
		fprintf(fp, "%d ", Record->num1);
                fprintf(fp, "%d ", Record->num2);
                fprintf(fp, "%d ", Record->num3);
              //fprintf(fp, "%p ", Record->pNext);
              //fprintf(fp, "%p ", Record->pPrev);
                Record=Record->pNext;
	} //while (Record->pNext != NULL);
	fclose(fp);

	return true;
}

bool loadFromText()     //������� ��������� ������ �� ���������� �����
{
   FILE *fp = fopen ("lab14.txt", "r");

	if (!fp)
	{
		cout << "Cannot open text file";
		return false;
	}

	if (Record)
	{
		delete [] Record;
		Record = NULL;
	}

	fscanf(fp, "%d", &nRecord);

                                            
	for (int i = 0; i < nRecord; ++i)
	{
           char name[80];
           int num1;
           int num2;
           int num3;
           fscanf(fp, "%s", &name);
           fscanf(fp, "%d", &num1);
           fscanf(fp, "%d", &num2);
           fscanf(fp, "%d", &num3);
         //fscanf(fp, "%d", &pNext);
         //fscanf(fp, "%d", &pPrev);
           Node *Item = PushBack(Record,CreateItem(name,num1,num2,num3));
           if(Record == NULL)
              Record=Item;
              //Record=Record->pNext;
	}  
	fclose(fp);
	return true;
 }

bool saveReport()   //������� ��������� ������
{
	FILE *fp;
	fp=fopen("report.txt","w");
	if(fp==NULL)
	{
		printf("\n������ �������� �����...\n");
		return false;
	}
	fprintf(fp, "This is a report example for %d items\n", nRecord);
	fprintf(fp,"+----+--------------+--------------------------+---------------------------+-----------------------------------+\n");
	fprintf(fp,"| �  | ������������ | ����������� ���� � ����� | ������������ ���� � ����� |  ������� ����������������� �����  |\n");
	fprintf(fp,"+----+--------------+--------------------------+---------------------------+-----------------------------------+\n");
	for(int i=0;i<nRecord;++i)
	{
		fprintf(fp,"| %-3d | %-20s | %-20d | %-20d | %-20d |\n",i+1,Record->name,Record->num1,Record->num2,Record->num3);
                Record=Record->pNext;
	}
	fprintf(fp,"+----+--------------+--------------------------+---------------------------+-----------------------------------+\n");
	fclose(fp);
        return true;

}


