//*****КУРСОВАЯ РАБОТА ПО ДИСЦИПЛИНЕ*****//
//*****"ТЕХНОЛОГИЯ ПРОГРАММИРОВАНИЯ"*****//
//********Апонасенко А.В. КИ08-04********//

#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

struct Node     //Двусвязный список
{
   char name[80];
   int  num1;
   int  num2;
   int  num3;
   Node *pNext;
   Node *pPrev;
};

Node *Record;       //Новый список
int nRecord;     //Количество списков

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
				printf ( "File saved.");
			}
			break;
		case 7:
			if (saveAsText())
			{
				printf ( "File saved.");
			}
			break;
		case 6:
			if (loadFromBinary())
			{
				printf ( "File loaded.");
			}
			break;
		case 8:
			if (loadFromText())
			{
				printf ( "File loaded.");
			}
			break;
		case 9:
			if (saveReport())
			{
				printf ( "Report saved.");
			}
			break;
		default:
			printf ( "Wrong menu item! \n");
		}
	}

	if (Record != NULL)
	{
		delete [] Record;
	}
        
	//getch(); //return 0;
}

Node *CreateItem (const char *name, int  num1, int  num2 ,int  num3)
{                //Функция создает новый элемент
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
{                 //Функция связывает два элемента
   if (parent != NULL)
   {
      //Item->pNext=parent->pNext;
      parent->pNext=Item;
      Item->pPrev=parent;
   }
   return Item;
}

Node *getTail (Node *head)
{             //Функция поиска последного элемента ы списке
   if(head == NULL)
      return NULL;
   Node *Item=head;
   while(Item->pNext != NULL)
      Item = Item->pNext;
   return Item;
}

Node *PushBack (Node *head, Node *Item)
{              //Функция вставляет элемент в конец списка
   Node *tail = getTail(head);
   return InsertAfter (tail, Item);
}

void PrintNode (Node *Item)
{              //Функция печатает один элемент на экране
   printf("%s ",Item->name);
   printf("%d ",Item->num1);
   printf("%d ",Item->num2);
   printf("%d \n",Item->num3);
}

void PrintList (Node *head)
{              //Функция печатает весь список на экране
   Node *Item = head;
   printf("Record:\n");
   while(Item != NULL)
   {
      PrintNode(Item);
      Item = Item->pNext;
   }
}                              

void DeleteList (Node *Item)
{               //Функция удаляет список
   if (Item->pNext != NULL)
   {
      DeleteList (Item->pNext);
   }
   delete Item;
}

Node *RemoveNode (Node *prev, Node *Item)
{                //Функция удаляет элементы списка расположеные перед Item
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

int showMenu()    //Функция показывает меню
{
	printf ( "\n1. Add	\n");
	printf ( "2. Delete  \n");
	printf ( "3. Modify	\n");
	printf ( "4. Print	\n");
	printf ( "5. Save into Binary	\n");
	printf ( "6. Load from Binary	\n");
	printf ( "7. Save to Text		\n");
	printf ( "8. Load from Text		\n");
        printf ( "9. Save Report		\n");
	//printf ( "---------	\n");
	printf ( "0. Exit	\n");
	printf ( "\n?>");

	int choise = 0;
	//cin >> choise;
     scanf ("%d",&choise);

	return choise;
}

void addItem()     //Функция добавляет элемент в список
{
   printf ( "Please type a new value: ");
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

void deleteItem()    //Функция удаляет выбраный элемент
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

int getIndex()    //Функция возвращает индекс элемента
{
	if (Record == NULL)
	{
		printf ( "Record is empty \n");
		return -1;
	}
	int nIdx = -1;
	printf ( "Please enter an item's index to delete from array 1.. %d ",nRecord);
	//cin >> nIdx;
     scanf("%d",&nIdx);

	if (nIdx < 1 || nIdx > nRecord)
	{
		printf ( "Error: index is out of bound.");
		return -1;
	}

	return nIdx - 1;

}
void modifyItem()    //Функция изменяет элемент
{
   int nIdx = getIndex();
   if (nIdx == -1)
   {
   return;
   }

   //printf ( "You are going to replace value " << Record->name << " at position " << nIdx + 1 << "." \n");
   printf ( "You are going to replace value %d at position %d \n",Record->name,nIdx + 1);
   printf ( "Please type a new value: ");
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

k,bool saveAsBinary()    //Функция сохраняет список в бинарный файл
{
   FILE *fp = fopen ("lab14.bin", "w");

	if (!fp)
	m;jjj{
		printf ( "Cannot create binary file");
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
         //fwrite(&Record->pNext, sizeof(*Node), 1, fp);  Указатели сохранять не нужно
         //fwrite(&Record->pPrev, sizeof(*Node), 1, fp);  Имхо проще создать новые
           Record=Record->pNext;
	}

	fclose(fp);
	return true;
}

bool loadFromBinary()    //Функция загружает список из бинарного файла
{
   FILE *fp = fopen ("lab14.bin", "r");

	if (!fp)
	{
		printf ( "Cannot open binary file");
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
bool saveAsText()   //Функция сохраняет список в текстовый файл
{                                     
   FILE *fp = fopen ("lab14.txt", "w");

	if (!fp)
	{
		printf ( "Cannot create text file");
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

bool loadFromText()     //Функция загружает список из текстового файла
{
   FILE *fp = fopen ("lab14.txt", "r");

	if (!fp)
	{
		printf ( "Cannot open text file");
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

bool saveReport()   //Функция сохраняет отсчет
{
	FILE *fp;
	fp=fopen("report.txt","w");
	if(fp==NULL)
	{
		printf("\nОшибка открытия файла...\n");
		return false;
	}
	fprintf(fp, "This is a report example for %d items\n", nRecord);
	fprintf(fp,"+----+--------------+--------------------------+---------------------------+-----------------------------------+\n");
	fprintf(fp,"| №  | Наименование | Минимальный рост в холке | Максимальный рост в холке |  Средняя продолжительность жизни  |\n");
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
