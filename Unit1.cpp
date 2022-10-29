//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
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

void vis(boolean a) // управление видимостью и доступностью некоторых компонентов
{
Form1->StringGrid1->Visible=a;
Form1->SpeedButton1->Enabled=a;
Form1->SpeedButton3->Enabled=a;
Form1->SpeedButton5->Enabled=a;
Form1->SpeedButton7->Enabled=a;
Form1->SpeedButton8->Enabled=a;
}

struct Breed {
           char name[20];
           char name2[20];
           int int1;
           int int2;
           };

class Spisok // класс для работы
{            // с двусвязным списком
public:
struct Element // описание элемента списка
{
Breed data; // данные
Element *prev; // указатель на предыдущий элемент
Element *next; // указатель на следующий элемент
};
void Add(Breed); // добавление в конец списка
void Print(); // вывод всего списка на экран
void Delete(int k); // удаление элемента из списка под номером k
void DeleteAll(); // удаление всего списка
char LoadBinary(AnsiString filename); // загрузка списка из двоичного файла
char SaveBinary(AnsiString filename); // сохранение списка в двоичном файле
char LoadText(AnsiString filename); // загрузка списка из текстового файла
char SaveText(AnsiString filename); // сохранение списка в текстовом файле
void Report(); // вывод отчёта
Element *begin; // указатель на начало списка
Element *end; // указатель на конец списка
int num; // количество элементов в списке
Spisok(); // конструктор класса
~Spisok(); // деструктор класса
};

Spisok::Spisok() // конструктор класса
{
begin=NULL; // инициализация списка
end=NULL;
num=0;
}

Spisok::~Spisok() // деструктор класса
{
DeleteAll(); // удаляем весь список
}

void Spisok::Add(Breed data) // добавление в конец списка
{
Element *q = new Element; // создаем новый элемент
q->data=data; // переносим в него данные
q->next=NULL; // следующего элемента нет
q->prev=end;  // предыдущий - конец списка
if(num==0) // если список пуст, то
 end=begin=q; // начало равно концу и равно
  else       // единственному элементу
   {
   end->next=q; // новый элемент
   end=q;      // является последним
   }
num++; // увеличение количества элементов на 1
}

void Spisok::Print() // вывод всего списка на экран
{
if (num)
 {
 int i=1;
 vis(true);
 Form1->StringGrid1->RowCount=num+1;
 Element *temp; // временная переменная
 temp=begin;
 for(i=1;i<=num;i++) // выводим все элементы
  {
  Form1->StringGrid1->Cells[0][i]=temp->data.name;
  Form1->StringGrid1->Cells[1][i]=temp->data.name2;
  Form1->StringGrid1->Cells[2][i]=IntToStr(temp->data.int1);
  Form1->StringGrid1->Cells[3][i]=IntToStr(temp->data.int2);
  temp=temp->next;
  }
 } else vis(false);
}

void Spisok::Delete(int k) // удаление элемента из списка под номером k
{
Element *temp,*temp1,*temp2; // временные переменные
int i;
temp=begin; // встаем на начало
if (k==0) // если надо удалить первый элемент
 if (num==1)
  {
  begin=NULL; // список
  end=NULL;   // пуст
  } else {
         begin=temp->next; // передвигаем указатель на начало ко второму элементу
         begin->prev=NULL; // у второго элемента после удаления первого предыдущего не будет
         } else if (k<num-1) // если надо удалить "средний" элемент
 	         {
	         for(i=0;i<k;i++) temp=temp->next; // находим этот элемент
	         temp->prev->next=temp->next; // корректируем
	         temp->next->prev=temp->prev; // указатели
	         } else { // если надо удалить последний элемент
		        temp=end; // встаем на последний элемент
		        temp->prev->next=NULL; // у предпоследнего элемента после удаления последнего, следующего не будет
		        end=temp->prev; // передвигаем указатель на конец на предпоследний элемент
		        }
delete (temp); // удаляем элемент из памяти
num--; // уменьшаем кол-во элементов в списке
}

void Spisok::DeleteAll() // удаление всего списка
{
int i;
Element *temp, // временная переменная
	*temp1; // временная переменная
temp=begin;
for(i=0;i<num;i++) // удаляем весь список
 {
 temp1=temp->next;
 delete temp;
 temp=temp1;
 }
begin=NULL;
end=NULL;
num=0;
}

char Spisok::LoadBinary(AnsiString filename) // загрузка списка из двоичного файла
{
Breed temp;
FILE *f;
if ((f=fopen(filename.c_str(),"rb"))!=NULL) // если файл существует, то открываем его на чтение как двоичный
 {
 DeleteAll();
 while (!feof(f)) // пока не конец файла
  {
  fread(&temp,sizeof(Breed),1,f); // считываем данные
  if (!feof(f)) Add(temp); // добавляем данные в список
  }
 fclose(f); // закрываем файл
 return 0; // ошибок не было
 } else return 1; // файл не найден
}

char Spisok::SaveBinary(AnsiString filename)
{
FILE *f;
Element *temp; // временная переменная
int i;
if ((f=fopen(filename.c_str(),"wb"))!=NULL)
 {
 temp=begin;
 for(i=1;i<=num;i++) // записываем все элементы
  {
  fwrite(temp,sizeof(Breed),1,f);
  temp=temp->next;
  }
 fclose(f);
 return 0;
 } else return 1;
}

void loadstring(FILE *f,char *s) // считывание строки символов из текстового файла
{
int i;
for(i=0;(s[i]=fgetc(f))!=10&&!feof(f);i++); // пока не дошли до конца строки или до конца файла, считываем данные по одному символу
s[i]=0; // помечаем конец строки
}

char Spisok::LoadText(AnsiString filename)
{
Breed temp;
FILE *f;
if ((f=fopen(filename.c_str(),"rt"))!=NULL)
 {
 DeleteAll();
 while (!feof(f))
  {
  loadstring(f,temp.name);
  loadstring(f,temp.name2);
  fscanf(f,"%d\n%d\n",&temp.int1,&temp.int2);
  Add(temp);
  }
 fclose(f);
 return 0;
 } else return 1;
}

char Spisok::SaveText(AnsiString filename)
{
FILE *f;
Element *temp; // временная переменная
int i;
if ((f=fopen(filename.c_str(),"wt"))!=NULL)
 {
 temp=begin;
 for(i=1;i<=num;i++) // записываем все элементы
  {
  fprintf(f,"%s\n%s\n%d\n%d\n",temp->data.name,temp->data.name2,temp->data.int1,temp->data.int2);
  temp=temp->next;
  }
 fclose(f);
 return 0;
 } else return 1;
}

void Spisok::Report()
{
int i;
char s[1000]; // одна строка отчёта
Element *temp; // временная переменная
Form4->RichEdit1->Clear(); // очищаем отчёт
Form4->RichEdit1->Lines->Add("          порода                ср продолжительность           мин рост в холке     Макс рост в холке");
Form4->RichEdit1->Lines->Add("");
temp=begin;
for(i=1;i<=num;i++) // выводим все элементы
 {
 sprintf(s,"%20s %20s %11d %11d",temp->data.name,temp->data.name2,temp->data.int1,temp->data.int2); // выводим одну строку отчёта
 Form4->RichEdit1->Lines->Add(s); // добавляем строку в отчёт
 temp=temp->next;
 }
}

Spisok s; // переменная для списка

void __fastcall TForm1::FormCreate(TObject *Sender)
{
const AnsiString Names[4]={"bred","live","min","max"};
int i;
OpenDialog1->InitialDir=GetCurrentDir();
SaveDialog1->InitialDir=GetCurrentDir();
for(i=0;i<4;i++) // цикл для подписи заголовков столбцов таблицы
 StringGrid1->Cells[i][0]=Names[i];
vis(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
Breed temp;
CheckBox1->Checked=false;
Form2->Edit1->Text="";
Form2->Edit2->Text="";
Form2->Edit3->Text="";
Form2->Edit4->Text="";
Form2->SpeedButton1->Enabled=false;
Form2->Position=poMainFormCenter;
Form2->ShowModal();
if (CheckBox1->Checked)
 {
 strcpy(temp.name,Form2->Edit1->Text.c_str());
 strcpy(temp.name2,Form2->Edit2->Text.c_str());
 temp.int1=StrToInt(Form2->Edit3->Text);
 temp.int2=StrToInt(Form2->Edit4->Text);
 s.Add(temp);
 s.Print();
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
if (SaveDialog1->Execute())
 s.SaveBinary(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
if (OpenDialog1->Execute())
 {
 s.LoadBinary(OpenDialog1->FileName);
 s.Print();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
s.DeleteAll();
s.Print();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
if (OpenDialog2->Execute())
 {
 s.LoadText(OpenDialog2->FileName);
 s.Print();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
if (SaveDialog2->Execute())
 s.SaveText(SaveDialog2->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
int i;
CheckBox1->Checked=false;
Form3->Position=poMainFormCenter;
Form3->ShowModal();
if (CheckBox1->Checked)
 {
 s.Delete(StringGrid1->Row-1);
 s.Print();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton8Click(TObject *Sender)
{
s.Report();
Form4->Position=poMainFormCenter;
Form4->ShowModal();
}
//---------------------------------------------------------------------------

