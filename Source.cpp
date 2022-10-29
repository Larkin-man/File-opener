//---------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h> //для getch
#include<math.h>
#include<string.h>
#pragma hdrstop

#include <tchar.h>
//---------------------------------------------------------------------------

struct Node     //Двусвязный список
{
	wchar_t name[80];  //wchar_t
	wchar_t  symb;
   int  num2;
   double  num3;
   Node *pNext;
   Node *pPrev;
};

Node *Record;       //Новый список
int nRecord;     //Количество списков

//Node *CreateItem (int id, const wchar_t *name, float mark);
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
bool ModifyBinary();
//-------------------------------------------------------------------
#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
int nMenu = 0;
   printf ( "1.string 2.wchar_t 3.int 4.double.\n");

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
				printf ( "File saved.");
			break;
		case 7:
			if (saveAsText())
				printf ( "File saved.");
			break;
		case 6:
			if (loadFromBinary())
				printf ( "File loaded. %d",nRecord);
			break;
		case 8:
			if (loadFromText())
				printf ( "File loaded. %d",nRecord);
			break;
		case 9:
			if (ModifyBinary())
				printf ( "Report saved.");
			break;
		case -5:
			if (ModifyBinary())
				printf ("Succes modify binary.");
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
//-------------------------------------------------------------------
//-------------------------------------------------------------------
Node *CreateItem (const wchar_t *name, wchar_t  symb, int  num2 ,double  num3)
{                //Функция создает новый элемент
	Node *pItem = new Node;
	wcsncpy(pItem->name, name, 80);   //   wcscpy strncpy
	pItem->symb = symb;
	pItem->num2 = num2;
	pItem->num3 = num3;
	pItem->pNext = NULL;
   pItem->pPrev = NULL;
   return pItem;
}
//-------------------------------------------------------------------
Node *InsertAfter (Node *parent, Node *Item)
{                 //Функция связывает два элемента
   if (parent != NULL)
   {
      //Item->pNext=parent->pNext;
      parent->pNext = Item;
      Item->pPrev = parent;
   }
   return Item;
}
//-------------------------------------------------------------------
Node *getTail (Node *head)
{             //Функция поиска последного элемента ы списке
   if(head == NULL)
      return NULL;
   Node *Item = head;
   while(Item->pNext != NULL)
      Item = Item->pNext;
   return Item;
}
//-------------------------------------------------------------------
Node *PushBack (Node *head, Node *Item)
{              //Функция вставляет элемент в конец списка
   Node *tail = getTail(head);
   return InsertAfter (tail, Item);
}
//-------------------------------------------------------------------
void PrintNode (Node *Item)
{              //Функция печатает один элемент на экране
   printf("%s ",Item->name);
   printf("%c ",Item->symb);
   printf("%d ",Item->num2);
   printf("%f \n",Item->num3);
}
//-------------------------------------------------------------------
void PrintList (Node *head)
{              //Функция печатает весь список на экране
   if (  nRecord == 0 )
   {
      printf("List is empty.\n");
      return;
   }
   Node *Item = head;
   printf("Record:\n");
   while(Item != NULL)
   {
      PrintNode(Item);
      Item = Item->pNext;
   }
}
//-------------------------------------------------------------------
void DeleteList (Node *Item)
{               //Функция удаляет список
   if (Item->pNext != NULL)
   {
      DeleteList (Item->pNext);
   }
   delete Item;
}
//-------------------------------------------------------------------
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
//-------------------------------------------------------------------
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
	printf ( "-5. Modify Binary		\n");
	//printf ( "---------	\n");
	printf ( "0. Exit	\n");
	printf ( "\n>:");

	int choise = 0;
	//cin >> choise;
   scanf ("%d",&choise);
	return choise;
}
//-------------------------------------------------------------------
void addItem()     //Функция добавляет элемент в список
{
   printf ( "Please type a new value: ");
	wchar_t name[80];
	wchar_t symb;
	int num2;
   double num3;
   nRecord++;
   scanf("%s %c %d %le",&name,&symb,&num2,&num3);
   Node *Item = PushBack(Record,CreateItem(name,symb,num2,num3));
   if(Record == NULL)
      Record=Item;
}
//-------------------------------------------------------------------
void deleteItem()    //Функция удаляет выбраный элемент
{
   Node *Item = Record;
   int nIdx = getIndex();
	for (int i=0; i<nIdx; i++)
		Item=Item->pNext;

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
//-------------------------------------------------------------------
int getIndex()    //Функция возвращает индекс элемента
{
	if (Record == NULL)
	{
		printf ( "Record is empty \n");
		return -1;
	}
	int nIdx = -1;
	printf ( "Please enter an item's index to delete from array 1.. %d >:",nRecord);
	//cin >> nIdx;
   scanf("%d",&nIdx);

	if (nIdx < 1 || nIdx > nRecord)
	{
		printf ( "Error: index is out of bound.");
		return -1;
   }
	return nIdx - 1;
}
//-------------------------------------------------------------------
void modifyItem()    //Функция изменяет элемент
{
   int nIdx = getIndex();
   if (nIdx == -1)
   {
      return;
   }

   //cout ( "You are going to replace value " << Record->name << " at position " << nIdx + 1 << "." \n");
   printf ( "You are going to replace value %d at position %d \n",Record->name,nIdx + 1);
   printf ( "Please type a new value: ");
   Node *Item = Record;
   for (int i=0;i<nIdx;i++)
      Item = Item->pNext;
   scanf("%s %c %d %le",&Item->name,
                       &Item->symb,
                       &Item->num2,
                       &Item->num3);
}
//-------------------------------------------------------------------
bool saveAsBinary()    //Функция сохраняет список в бинарный файл
{
	/*r  Open for reading only.
w  Create for writing. .
a  Append; open for writing at end-of-file or create for writing if the file does not exist.
r+  Open an existing file for update (reading and writing).
w+  Create a new file for update (reading and writing).
a+  Open for append; open (or create if the file does not exist) for update at the end of the file.

To specify that a given file is being opened or created in text mode append a t to the mode string (rt w+t and so on); similarly to specify binary mode append a b to the mode string (wb a+b and so on).
	*/

	//FILE *fp = fopen ("lab14.bin", "w"); //К СИМВОЛЫУ 10 добавиться ЕЩЕ БАЙТ, СИВОЛ 13 не записывается!!!!
	FILE *fp = fopen ("lab14.bin", "wb");

	if (!fp)
	{
		printf ( "Cannot create binary file");
		return false;
	}
	fwrite(&nRecord, sizeof(int), 1, fp);
   for (int i = 0; i < nRecord; ++i)
	{
      int len = wcslen(Record->name);    // strlen
      fwrite(&len, sizeof(int), 1, fp);
      fwrite(Record->name, 1, len, fp);
		fwrite(&Record->symb, sizeof(wchar_t), 1, fp);
      fwrite(&Record->num2, sizeof(int), 1, fp);
      fwrite(&Record->num3, sizeof(double), 1, fp);
      //fwrite(&Record->pNext, sizeof(*Node), 1, fp);  Указатели сохранять не нужно
      //fwrite(&Record->pPrev, sizeof(*Node), 1, fp);  Имхо проще создать новые
      Record=Record->pNext;
	}

	fclose(fp);
	return true;
}
//-------------------------------------------------------------------
bool loadFromBinary()    //Функция загружает список из бинарного файла
{
   FILE *fp = fopen ("lab14.bin", "rb");

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
		wchar_t name[80];
		wchar_t symb;
      int num2;
      double num3;
      int len = 0;
      fread(&len, sizeof(int), 1, fp);
		fread(name, sizeof(wchar_t), len, fp);
		name[len]=L'\0';
		fread(&symb, sizeof(wchar_t), 1, fp);
      fread(&num2, sizeof(int), 1, fp);
      fread(&num3, sizeof(double), 1, fp);
      //fread(&Record,sizeof(Record), 1, fp);
      Node *Item = PushBack(Record,CreateItem(name,symb,num2,num3));
      if(Record == NULL)
      Record=Item;
	}

	fclose(fp);
	return true;
 }
//-------------------------------------------------------------------
bool saveAsText()   //Функция сохраняет список в текстовый файл
{
	FILE *fp = fopen ("lab14.txt", "wt"); //
	if (!fp)
	{
		printf ( "Cannot create text file");
		return false;
	}

	fprintf(fp, "%d\n", nRecord);
	for (int i = 0; i < nRecord; ++i)
	{
       fprintf(fp, "%s ", Record->name);
       fprintf(fp, "%c ", Record->symb);
       fprintf(fp, "%d ", Record->num2);
       fprintf(fp, "%lf\n", Record->num3);
       Record = Record->pNext;
	} //while (Record->pNext != NULL);
	fclose(fp);
	return true;
}
//-------------------------------------------------------------------
bool loadFromText()     //Функция загружает список из текстового файла
{
	FILE *fp = fopen ("lab14.txt", "rt");
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

	fscanf(fp, "%d\n", &nRecord);
	for (int i = 0; i < nRecord; ++i)
	{
		wchar_t name[80];
      wchar_t symb;
      int num2;
      double num3;
      fscanf(fp, "%s ", &name);
      fscanf(fp, "%c ", &symb);
      fscanf(fp, "%d ", &num2);
      fscanf(fp, "%lf\n", &num3);
      Node *Item = PushBack(Record, CreateItem(name,symb,num2,num3));
      if(Record == NULL)
        Record=Item;
        //Record=Record->pNext;
	}
	fclose(fp);
	return true;
 }
//-------------------------------------------------------------------
bool saveReport()   //Функция сохраняет отсчет
{
	FILE *fp;
	fp=fopen("report.txt","wt");
	if (fp == NULL)
	{
		printf("\nОшибка открытия файла...\n");
		return false;
	}
	fprintf(fp, "This is a report example for %d items\n", nRecord);
	fprintf(fp,"+----+--------------+--------+---------------------------+-----------------------------------+\n");
	fprintf(fp,"| №  | Наименование | Милота | Максимальный рост в холке |  Средняя продолжительность жизни  |\n");
	fprintf(fp,"+----+--------------+--------+---------------------------+-----------------------------------+\n");
	for(int i=0; i<nRecord; ++i)
	{
		fprintf(fp,"| %d  | %s  | %c  | %d  | %f  |\n",
		//fprintf(fp,"| %-2d | %-20s | %-c | %-20d | %-20f |\n",  ТАК НЕ ПАШЕТ
			i+1, Record->name, Record->symb, Record->num2, Record->num3);
		Record=Record->pNext; //ЗАПИСЫВАЕТ КАЛЯКУМАЛЯКУ
	}
	fprintf(fp,"+----+--------------+--------+---------------------------+-----------------------------------+\n");
	fclose(fp);
   return true;

}
//-------------------------------------------------------------------
bool ModifyBinary()
{
	FILE *fp = fopen ("BIN.bin", "r+b");
	if (!fp)
		{  printf ("Cannot open binary file");		return false;	}
	if (Record)
	{
		delete [] Record;
		Record = NULL;
	}
	int mas[8];
	//int WR = 55;
	//long rew = ;
	fread(&mas[0], sizeof(int), 1, fp);
	fread(&mas[1], sizeof(int), 1, fp);
	fread(&mas[2], sizeof(int), 1, fp);
	fseek(fp, -(4), SEEK_CUR);
	//fflush(fp);
	int flush = mas[2]*2;
	fwrite(&flush, sizeof(int), 1, fp);
	//fflush(fp); //без этойхренине заптшется Нет запишется
	fseek(fp, 0, SEEK_CUR);   //..безэтойхрени не  сработанет чтение и не щапишется
	fread(&mas[3], sizeof(int), 1, fp);
	fread(&mas[4], sizeof(int), 1, fp);
	fread(&mas[5], sizeof(int), 1, fp);
	fread(&mas[6], sizeof(int), 1, fp);
	//fread(&mas[7], sizeof(int), 1, fp);
	for (int i = 0; i < 8; ++i)
		printf("[%d] = %d\n",i, mas[i]);
	/*
	fread(&nRecord, sizeof(int), 1, fp);
	for (int i = 0; i < nRecord; ++i)
	{
      char name[80];
      char symb;
      int num2;
      double num3;
      int len = 0;
      fread(&len, sizeof(int), 1, fp);
      fread(name, sizeof(char), len, fp);
      name[len]='\0';
      fread(&symb, sizeof(char), 1, fp);
		fread(&num2, sizeof(int), 1, fp);
      fread(&num3, sizeof(double), 1, fp);
      //fread(&Record,sizeof(Record), 1, fp);
      Node *Item = PushBack(Record,CreateItem(name,symb,num2,num3));
      if(Record == NULL)
      Record=Item;
	}            */

	fclose(fp);
	return true;
}
//-------------------------------------------------------------------
