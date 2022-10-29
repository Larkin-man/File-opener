//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

int numA; // количество элементов в списке A
int numB; // количество элементов в списке B

void vis() // управление видимостью и доступностью некоторых компонентов
{
Form1->StringGrid3->Visible=(numA>0)&(numB>0);
Form1->Image1->Visible=(numA>0)&(numB>0);
Form1->Image2->Visible=(numA>0)&(numB>0);
Form1->SpeedButton2->Enabled=(numA>0);
Form1->SpeedButton3->Enabled=(numA>0);
Form1->SpeedButton9->Enabled=(numA>0)&(numB>0);
Form1->SpeedButton5->Enabled=(numB>0);
Form1->SpeedButton8->Enabled=(numB>0);
Form1->SpeedButton10->Enabled=(numA>0)&(numB>0);
Form1->SpeedButton7->Enabled=(numA>0)&(numB>0);
Form1->StringGrid1->Visible=numA;
Form1->StringGrid2->Visible=numB;
Form1->StringGrid3->ColCount=numA;
Form1->StringGrid3->RowCount=numB;
}

struct port { // структура для хранения информации об аэропортах
            char city[20]; // город
            };

struct ElementA // описание элемента списка A
{
port data; // данные
ElementA *prev; // указатель на предыдущий элемент
ElementA *next; // указатель на следующий элемент
};

ElementA *beginA; // указатель на начало списка
ElementA *endA; // указатель на конец списка

void InitA() // инициализация списка
{
beginA=NULL;
endA=NULL;
numA=0;
}

void AddA(port data) // добавление в конец списка
{
ElementA *q = new ElementA; // создаем новый элемент
q->data=data; // переносим в него данные
q->next=NULL; // следующего элемента нет
q->prev=endA;  // предыдущий - конец списка
if(numA==0) // если список пуст, то
 endA=beginA=q; // начало равно концу и равно
  else       // единственному элементу
   {
   endA->next=q; // новый элемент
   endA=q;      // является последним
   }
numA++; // увеличение количества элементов на 1
}

void PrintListA() // вывод всего списка на экран
{
if (numA)
 {
 int i=1;
 Form1->StringGrid1->RowCount=numA+1;
 ElementA *temp; // временная переменная
 temp=beginA;
 for(i=1;i<=numA;i++) // выводим все элементы
  {
  Form1->StringGrid1->Cells[0][i]=temp->data.city;
  temp=temp->next;
  }
 }
vis();
}

void DeleteAllA() // удаление всего списка
{
int i;
ElementA *temp, // временная переменная
 	 *temp1; // временная переменная
temp=beginA;
for(i=0;i<numA;i++) // удаляем весь список
 {
 temp1=temp->next;
 delete temp;
 temp=temp1;
 }
beginA=NULL;
endA=NULL;
numA=0;
}

void SortA(char a) // сортировка списка методом "пузырьковой" сортировки
{
if (numA) // если список не пустой
 {
 int i,j; // счётчики для циклов
 ElementA *temp; // временная переменная
 port h;
 Form1->StringGrid3->ColCount++;
 for(j=0;j<numA-1;j++) // несколько проходов
  {
  temp=beginA;
  for(i=1;i<numA-j;i++) // один проход по всему списку
   {
   if (a==1&&strcmp(temp->data.city,temp->next->data.city)>0|| // по городу и по возрастанию
       a==2&&strcmp(temp->data.city,temp->next->data.city)<0) // по городу и по убыванию
       {
       h=temp->data;
       temp->data=temp->next->data;
       temp->next->data=h;
       Form1->StringGrid3->Cols[Form1->StringGrid3->ColCount-1]->Text=Form1->StringGrid3->Cols[i-1]->Text;
       Form1->StringGrid3->Cols[i-1]->Text=Form1->StringGrid3->Cols[i]->Text;
       Form1->StringGrid3->Cols[i]->Text=Form1->StringGrid3->Cols[Form1->StringGrid3->ColCount-1]->Text;
       }
   temp=temp->next;
   }
  }
 Form1->StringGrid3->ColCount--;
 }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct trip { // структура для хранения информации о рейсах
            char timestart[6]; // время вылета
            char timestop[6]; // время прилёта
            char type[20]; // тип самолёта
            };

struct ElementB // описание элемента списка B
{
trip data; // данные
ElementB *prev; // указатель на предыдущий элемент
ElementB *next; // указатель на следующий элемент
};

ElementB *beginB; // указатель на начало списка
ElementB *endB; // указатель на конец списка

void InitB() // инициализация списка
{
beginB=NULL;
endB=NULL;
numB=0;
}

void AddB(trip data) // добавление в конец списка
{
ElementB *q = new ElementB; // создаем новый элемент
q->data=data; // переносим в него данные
q->next=NULL; // следующего элемента нет
q->prev=endB;  // предыдущий - конец списка
if(numB==0) // если список пуст, то
 endB=beginB=q; // начало равно концу и равно
  else       // единственному элементу
   {
   endB->next=q; // новый элемент
   endB=q;      // является последним
   }
numB++; // увеличение количества элементов на 1
}

void PrintListB() // вывод всего списка на экран
{
if (numB)
 {
 int i=1;
 Form1->StringGrid2->RowCount=numB+1;
 ElementB *temp; // временная переменная
 temp=beginB;
 for(i=1;i<=numB;i++) // выводим все элементы
  {
  Form1->StringGrid2->Cells[0][i]=temp->data.timestart;
  Form1->StringGrid2->Cells[1][i]=temp->data.timestop;
  Form1->StringGrid2->Cells[2][i]=temp->data.type;
  temp=temp->next;
  }
 }
vis();
}

void DeleteAllB() // удаление всего списка
{
int i;
ElementB *temp, // временная переменная
 	 *temp1; // временная переменная
temp=beginB;
for(i=0;i<numB;i++) // удаляем весь список
 {
 temp1=temp->next;
 delete temp;
 temp=temp1;
 }
beginB=NULL;
endB=NULL;
numB=0;
}

void SortB(char a) // сортировка списка методом "пузырьковой" сортировки
{
if (numB) // если список не пустой
 {
 int i,j; // счётчики для циклов
 ElementB *temp; // временная переменная
 trip h;
 Form1->StringGrid3->RowCount++;
 for(j=0;j<numB-1;j++) // несколько проходов
  {
  temp=beginB;
  for(i=1;i<numB-j;i++) // один проход по всему списку
   {
   if (a==1&&strcmp(temp->data.timestart,temp->next->data.timestart)>0|| // по времени вылета и по возрастанию
       a==2&&strcmp(temp->data.timestart,temp->next->data.timestart)<0|| // по времени вылета и по убыванию
       a==3&&strcmp(temp->data.timestop,temp->next->data.timestop)>0|| // по времени прилёта и по возрастанию
       a==4&&strcmp(temp->data.timestop,temp->next->data.timestop)<0|| // по времени прилёта и по убыванию
       a==5&&strcmp(temp->data.type,temp->next->data.type)>0|| // по типу самолёта и по возрастанию
       a==6&&strcmp(temp->data.type,temp->next->data.type)<0) // по типу самолёта и по убыванию
       {
       h=temp->data;
       temp->data=temp->next->data;
       temp->next->data=h;
       Form1->StringGrid3->Rows[Form1->StringGrid3->RowCount-1]->Text=Form1->StringGrid3->Rows[i-1]->Text;
       Form1->StringGrid3->Rows[i-1]->Text=Form1->StringGrid3->Rows[i]->Text;
       Form1->StringGrid3->Rows[i]->Text=Form1->StringGrid3->Rows[Form1->StringGrid3->RowCount-1]->Text;
       }
   temp=temp->next;
   }
  }
 Form1->StringGrid3->RowCount--;
 }
}
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
void loadstring(FILE *f,char *s) // считывание строки символов из текстового файла
{
int i;
for(i=0;(s[i]=fgetc(f))!=10&&!feof(f);i++); // пока не дошли до конца строки или до конца файла, считываем данные по одному символу
s[i]=0; // помечаем конец строки
}

char LoadText(AnsiString filename)
{
port temp;
trip temp1;
char s[10];
FILE *f;
int i,j,m,n;
if ((f=fopen(filename.c_str(),"rt"))!=NULL)
 {
 DeleteAllA();
 fscanf(f,"%d\n",&n);
 for(i=0;i<n;i++)
  {
  loadstring(f,temp.city);
  AddA(temp);
  }
 DeleteAllB();
 fscanf(f,"%d\n",&m);
 for(i=0;i<m;i++)
  {
  loadstring(f,temp1.timestart);
  loadstring(f,temp1.timestop);
  loadstring(f,temp1.type);
  AddB(temp1);
  }
 vis();
 for(i=0;i<n;i++)
  for(j=0;j<m;j++)
   {
   loadstring(f,s);
   Form1->StringGrid3->Cells[i][j]=s;
   }
 fclose(f);
 return 0;
 } else return 1;
}

char SaveText(AnsiString filename)
{
FILE *f;
ElementA *temp;
ElementB *temp1;
int i,j;
if ((f=fopen(filename.c_str(),"wt"))!=NULL)
 {
 fprintf(f,"%d\n",numA);
 temp=beginA;
 for(i=1;i<=numA;i++) // записываем все элементы
  {
  fprintf(f,"%s\n",temp->data.city);
  temp=temp->next;
  }
 fprintf(f,"%d\n",numB);
 temp1=beginB;
 for(i=1;i<=numB;i++) // записываем все элементы
  {
  fprintf(f,"%s\n%s\n%s\n",temp1->data.timestart,temp1->data.timestop,temp1->data.type);
  temp1=temp1->next;
  }
 for(i=0;i<numA;i++)
  for(j=0;j<numB;j++)
   if (Form1->StringGrid3->Cells[i][j]!="+")
    fprintf(f," \n"); else fprintf(f,"+\n");
 fclose(f);
 return 0;
 } else return 1;
}
//================================================================================
void __fastcall TForm1::FormCreate(TObject *Sender)
{
const AnsiString Names1[1]={"Город"};
const AnsiString Names2[3]={"Время вылета","Время прилёта","Тип самолёта"};
int i;
OpenDialog2->InitialDir=GetCurrentDir();
SaveDialog2->InitialDir=GetCurrentDir();
for(i=0;i<1;i++) // цикл для подписи заголовков столбцов первой таблицы
 StringGrid1->Cells[i][0]=Names1[i];
for(i=0;i<3;i++) // цикл для подписи заголовков столбцов второй таблицы
 StringGrid2->Cells[i][0]=Names2[i];
InitA();
InitB();
vis();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
port temp;
CheckBox1->Checked=false;
Form2->Edit1->Text="";
Form2->SpeedButton1->Enabled=false;
Form2->Position=poMainFormCenter;
Form2->ShowModal();
if (CheckBox1->Checked)
 {
 strcpy(temp.city,Form2->Edit1->Text.c_str());
 AddA(temp);
 PrintListA();
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
if (OpenDialog2->Execute())
 {
 LoadText(OpenDialog2->FileName);
 PrintListA();
 PrintListB();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
if (SaveDialog2->Execute())
 SaveText(SaveDialog2->FileName);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
trip temp;
CheckBox1->Checked=false;
Form3->Edit1->Text="";
Form3->Edit2->Text="";
Form3->Edit3->Text="";
Form3->SpeedButton1->Enabled=false;
Form3->Position=poMainFormCenter;
Form3->ShowModal();
if (CheckBox1->Checked)
 {
 strcpy(temp.timestart,Form3->Edit1->Text.c_str());
 strcpy(temp.timestop,Form3->Edit2->Text.c_str());
 strcpy(temp.type,Form3->Edit3->Text.c_str());
 AddB(temp);
 PrintListB();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid3KeyPress(TObject *Sender, char &Key)
{
if (StringGrid3->Cells[StringGrid3->Col][StringGrid3->Row]=="")
 StringGrid3->Cells[StringGrid3->Col][StringGrid3->Row]="+";
  else StringGrid3->Cells[StringGrid3->Col][StringGrid3->Row]="";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
SortA(StringGrid1->Col*2+1);
PrintListA();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
SortA(StringGrid1->Col*2+2);
PrintListA();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
SortB(StringGrid2->Col*2+1);
PrintListB();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton8Click(TObject *Sender)
{
SortB(StringGrid2->Col*2+2);
PrintListB();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton9Click(TObject *Sender)
{
int i;
boolean found=false;
Form4->StringGrid1->RowCount=2;
for(i=0;i<StringGrid3->RowCount;i++)
 if (StringGrid3->Cells[StringGrid1->Row-1][i]=="+")
  {
  Form4->StringGrid1->Rows[Form4->StringGrid1->RowCount-1]->Text=StringGrid2->Rows[i+1]->Text;
  Form4->StringGrid1->RowCount++;
  found=true;
  }
if (found)
 {
 Form4->StringGrid1->RowCount--;
 Form4->Position=poMainFormCenter;
 Form4->ShowModal();
 } else {
        Form5->Label1->Caption="Нет сущностей B, связанных";
        Form5->Label2->Caption="с выбранной сущностью A";
        Form5->Position=poMainFormCenter;
        Form5->ShowModal();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton10Click(TObject *Sender)
{
int i;
boolean found=false;
Form6->StringGrid1->RowCount=2;
for(i=0;i<StringGrid3->ColCount;i++)
 if (StringGrid3->Cells[i][StringGrid2->Row-1]=="+")
  {
  Form6->StringGrid1->Rows[Form6->StringGrid1->RowCount-1]->Text=StringGrid1->Rows[i+1]->Text;
  Form6->StringGrid1->RowCount++;
  found=true;
  }
if (found)
 {
 Form6->StringGrid1->RowCount--;
 Form6->Position=poMainFormCenter;
 Form6->ShowModal();
 } else {
        Form5->Label1->Caption="Нет сущностей A, связанных";
        Form5->Label2->Caption="с выбранной сущностью B";
        Form5->Position=poMainFormCenter;
        Form5->ShowModal();
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton11Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------

