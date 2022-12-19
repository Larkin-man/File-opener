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

void vis(boolean a) // ���������� ���������� � ������������ ��������� �����������
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

class Spisok // ����� ��� ������
{            // � ���������� �������
public:
struct Element // �������� �������� ������
{
Breed data; // ������
Element *prev; // ��������� �� ���������� �������
Element *next; // ��������� �� ��������� �������
};
void Add(Breed); // ���������� � ����� ������
void Print(); // ����� ����� ������ �� �����
void Delete(int k); // �������� �������� �� ������ ��� ������� k
void DeleteAll(); // �������� ����� ������
char LoadBinary(AnsiString filename); // �������� ������ �� ��������� �����
char SaveBinary(AnsiString filename); // ���������� ������ � �������� �����
char LoadText(AnsiString filename); // �������� ������ �� ���������� �����
char SaveText(AnsiString filename); // ���������� ������ � ��������� �����
void Report(); // ����� ������
Element *begin; // ��������� �� ������ ������
Element *end; // ��������� �� ����� ������
int num; // ���������� ��������� � ������
Spisok(); // ����������� ������
~Spisok(); // ���������� ������
};

Spisok::Spisok() // ����������� ������
{
begin=NULL; // ������������� ������
end=NULL;
num=0;
}

Spisok::~Spisok() // ���������� ������
{
DeleteAll(); // ������� ���� ������
}

void Spisok::Add(Breed data) // ���������� � ����� ������
{
Element *q = new Element; // ������� ����� �������
q->data=data; // ��������� � ���� ������
q->next=NULL; // ���������� �������� ���
q->prev=end;  // ���������� - ����� ������
if(num==0) // ���� ������ ����, ��
 end=begin=q; // ������ ����� ����� � �����
  else       // ������������� ��������
   {
   end->next=q; // ����� �������
   end=q;      // �������� ���������
   }
num++; // ���������� ���������� ��������� �� 1
}

void Spisok::Print() // ����� ����� ������ �� �����
{
if (num)
 {
 int i=1;
 vis(true);
 Form1->StringGrid1->RowCount=num+1;
 Element *temp; // ��������� ����������
 temp=begin;
 for(i=1;i<=num;i++) // ������� ��� ��������
  {
  Form1->StringGrid1->Cells[0][i]=temp->data.name;
  Form1->StringGrid1->Cells[1][i]=temp->data.name2;
  Form1->StringGrid1->Cells[2][i]=IntToStr(temp->data.int1);
  Form1->StringGrid1->Cells[3][i]=IntToStr(temp->data.int2);
  temp=temp->next;
  }
 } else vis(false);
}

void Spisok::Delete(int k) // �������� �������� �� ������ ��� ������� k
{
Element *temp,*temp1,*temp2; // ��������� ����������
int i;
temp=begin; // ������ �� ������
if (k==0) // ���� ���� ������� ������ �������
 if (num==1)
  {
  begin=NULL; // ������
  end=NULL;   // ����
  } else {
         begin=temp->next; // ����������� ��������� �� ������ �� ������� ��������
         begin->prev=NULL; // � ������� �������� ����� �������� ������� ����������� �� �����
         } else if (k<num-1) // ���� ���� ������� "�������" �������
 	         {
	         for(i=0;i<k;i++) temp=temp->next; // ������� ���� �������
	         temp->prev->next=temp->next; // ������������
	         temp->next->prev=temp->prev; // ���������
	         } else { // ���� ���� ������� ��������� �������
		        temp=end; // ������ �� ��������� �������
		        temp->prev->next=NULL; // � �������������� �������� ����� �������� ����������, ���������� �� �����
		        end=temp->prev; // ����������� ��������� �� ����� �� ������������� �������
		        }
delete (temp); // ������� ������� �� ������
num--; // ��������� ���-�� ��������� � ������
}

void Spisok::DeleteAll() // �������� ����� ������
{
int i;
Element *temp, // ��������� ����������
	*temp1; // ��������� ����������
temp=begin;
for(i=0;i<num;i++) // ������� ���� ������
 {
 temp1=temp->next;
 delete temp;
 temp=temp1;
 }
begin=NULL;
end=NULL;
num=0;
}

char Spisok::LoadBinary(AnsiString filename) // �������� ������ �� ��������� �����
{
Breed temp;
FILE *f;
if ((f=fopen(filename.c_str(),"rb"))!=NULL) // ���� ���� ����������, �� ��������� ��� �� ������ ��� ��������
 {
 DeleteAll();
 while (!feof(f)) // ���� �� ����� �����
  {
  fread(&temp,sizeof(Breed),1,f); // ��������� ������
  if (!feof(f)) Add(temp); // ��������� ������ � ������
  }
 fclose(f); // ��������� ����
 return 0; // ������ �� ����
 } else return 1; // ���� �� ������
}

char Spisok::SaveBinary(AnsiString filename)
{
FILE *f;
Element *temp; // ��������� ����������
int i;
if ((f=fopen(filename.c_str(),"wb"))!=NULL)
 {
 temp=begin;
 for(i=1;i<=num;i++) // ���������� ��� ��������
  {
  fwrite(temp,sizeof(Breed),1,f);
  temp=temp->next;
  }
 fclose(f);
 return 0;
 } else return 1;
}

void loadstring(FILE *f,char *s) // ���������� ������ �������� �� ���������� �����
{
int i;
for(i=0;(s[i]=fgetc(f))!=10&&!feof(f);i++); // ���� �� ����� �� ����� ������ ��� �� ����� �����, ��������� ������ �� ������ �������
s[i]=0; // �������� ����� ������
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
Element *temp; // ��������� ����������
int i;
if ((f=fopen(filename.c_str(),"wt"))!=NULL)
 {
 temp=begin;
 for(i=1;i<=num;i++) // ���������� ��� ��������
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
char s[1000]; // ���� ������ ������
Element *temp; // ��������� ����������
Form4->RichEdit1->Clear(); // ������� �����
Form4->RichEdit1->Lines->Add("          ������                �� �����������������           ��� ���� � �����     ���� ���� � �����");
Form4->RichEdit1->Lines->Add("");
temp=begin;
for(i=1;i<=num;i++) // ������� ��� ��������
 {
 sprintf(s,"%20s %20s %11d %11d",temp->data.name,temp->data.name2,temp->data.int1,temp->data.int2); // ������� ���� ������ ������
 Form4->RichEdit1->Lines->Add(s); // ��������� ������ � �����
 temp=temp->next;
 }
}

Spisok s; // ���������� ��� ������

void __fastcall TForm1::FormCreate(TObject *Sender)
{
const AnsiString Names[4]={"bred","live","min","max"};
int i;
OpenDialog1->InitialDir=GetCurrentDir();
SaveDialog1->InitialDir=GetCurrentDir();
for(i=0;i<4;i++) // ���� ��� ������� ���������� �������� �������
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

