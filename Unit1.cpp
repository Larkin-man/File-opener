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

int numA; // ���������� ��������� � ������ A
int numB; // ���������� ��������� � ������ B

void vis() // ���������� ���������� � ������������ ��������� �����������
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

struct port { // ��������� ��� �������� ���������� �� ����������
            char city[20]; // �����
            };

struct ElementA // �������� �������� ������ A
{
port data; // ������
ElementA *prev; // ��������� �� ���������� �������
ElementA *next; // ��������� �� ��������� �������
};

ElementA *beginA; // ��������� �� ������ ������
ElementA *endA; // ��������� �� ����� ������

void InitA() // ������������� ������
{
beginA=NULL;
endA=NULL;
numA=0;
}

void AddA(port data) // ���������� � ����� ������
{
ElementA *q = new ElementA; // ������� ����� �������
q->data=data; // ��������� � ���� ������
q->next=NULL; // ���������� �������� ���
q->prev=endA;  // ���������� - ����� ������
if(numA==0) // ���� ������ ����, ��
 endA=beginA=q; // ������ ����� ����� � �����
  else       // ������������� ��������
   {
   endA->next=q; // ����� �������
   endA=q;      // �������� ���������
   }
numA++; // ���������� ���������� ��������� �� 1
}

void PrintListA() // ����� ����� ������ �� �����
{
if (numA)
 {
 int i=1;
 Form1->StringGrid1->RowCount=numA+1;
 ElementA *temp; // ��������� ����������
 temp=beginA;
 for(i=1;i<=numA;i++) // ������� ��� ��������
  {
  Form1->StringGrid1->Cells[0][i]=temp->data.city;
  temp=temp->next;
  }
 }
vis();
}

void DeleteAllA() // �������� ����� ������
{
int i;
ElementA *temp, // ��������� ����������
 	 *temp1; // ��������� ����������
temp=beginA;
for(i=0;i<numA;i++) // ������� ���� ������
 {
 temp1=temp->next;
 delete temp;
 temp=temp1;
 }
beginA=NULL;
endA=NULL;
numA=0;
}

void SortA(char a) // ���������� ������ ������� "�����������" ����������
{
if (numA) // ���� ������ �� ������
 {
 int i,j; // �������� ��� ������
 ElementA *temp; // ��������� ����������
 port h;
 Form1->StringGrid3->ColCount++;
 for(j=0;j<numA-1;j++) // ��������� ��������
  {
  temp=beginA;
  for(i=1;i<numA-j;i++) // ���� ������ �� ����� ������
   {
   if (a==1&&strcmp(temp->data.city,temp->next->data.city)>0|| // �� ������ � �� �����������
       a==2&&strcmp(temp->data.city,temp->next->data.city)<0) // �� ������ � �� ��������
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
struct trip { // ��������� ��� �������� ���������� � ������
            char timestart[6]; // ����� ������
            char timestop[6]; // ����� ������
            char type[20]; // ��� �������
            };

struct ElementB // �������� �������� ������ B
{
trip data; // ������
ElementB *prev; // ��������� �� ���������� �������
ElementB *next; // ��������� �� ��������� �������
};

ElementB *beginB; // ��������� �� ������ ������
ElementB *endB; // ��������� �� ����� ������

void InitB() // ������������� ������
{
beginB=NULL;
endB=NULL;
numB=0;
}

void AddB(trip data) // ���������� � ����� ������
{
ElementB *q = new ElementB; // ������� ����� �������
q->data=data; // ��������� � ���� ������
q->next=NULL; // ���������� �������� ���
q->prev=endB;  // ���������� - ����� ������
if(numB==0) // ���� ������ ����, ��
 endB=beginB=q; // ������ ����� ����� � �����
  else       // ������������� ��������
   {
   endB->next=q; // ����� �������
   endB=q;      // �������� ���������
   }
numB++; // ���������� ���������� ��������� �� 1
}

void PrintListB() // ����� ����� ������ �� �����
{
if (numB)
 {
 int i=1;
 Form1->StringGrid2->RowCount=numB+1;
 ElementB *temp; // ��������� ����������
 temp=beginB;
 for(i=1;i<=numB;i++) // ������� ��� ��������
  {
  Form1->StringGrid2->Cells[0][i]=temp->data.timestart;
  Form1->StringGrid2->Cells[1][i]=temp->data.timestop;
  Form1->StringGrid2->Cells[2][i]=temp->data.type;
  temp=temp->next;
  }
 }
vis();
}

void DeleteAllB() // �������� ����� ������
{
int i;
ElementB *temp, // ��������� ����������
 	 *temp1; // ��������� ����������
temp=beginB;
for(i=0;i<numB;i++) // ������� ���� ������
 {
 temp1=temp->next;
 delete temp;
 temp=temp1;
 }
beginB=NULL;
endB=NULL;
numB=0;
}

void SortB(char a) // ���������� ������ ������� "�����������" ����������
{
if (numB) // ���� ������ �� ������
 {
 int i,j; // �������� ��� ������
 ElementB *temp; // ��������� ����������
 trip h;
 Form1->StringGrid3->RowCount++;
 for(j=0;j<numB-1;j++) // ��������� ��������
  {
  temp=beginB;
  for(i=1;i<numB-j;i++) // ���� ������ �� ����� ������
   {
   if (a==1&&strcmp(temp->data.timestart,temp->next->data.timestart)>0|| // �� ������� ������ � �� �����������
       a==2&&strcmp(temp->data.timestart,temp->next->data.timestart)<0|| // �� ������� ������ � �� ��������
       a==3&&strcmp(temp->data.timestop,temp->next->data.timestop)>0|| // �� ������� ������ � �� �����������
       a==4&&strcmp(temp->data.timestop,temp->next->data.timestop)<0|| // �� ������� ������ � �� ��������
       a==5&&strcmp(temp->data.type,temp->next->data.type)>0|| // �� ���� ������� � �� �����������
       a==6&&strcmp(temp->data.type,temp->next->data.type)<0) // �� ���� ������� � �� ��������
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
void loadstring(FILE *f,char *s) // ���������� ������ �������� �� ���������� �����
{
int i;
for(i=0;(s[i]=fgetc(f))!=10&&!feof(f);i++); // ���� �� ����� �� ����� ������ ��� �� ����� �����, ��������� ������ �� ������ �������
s[i]=0; // �������� ����� ������
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
 for(i=1;i<=numA;i++) // ���������� ��� ��������
  {
  fprintf(f,"%s\n",temp->data.city);
  temp=temp->next;
  }
 fprintf(f,"%d\n",numB);
 temp1=beginB;
 for(i=1;i<=numB;i++) // ���������� ��� ��������
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
const AnsiString Names1[1]={"�����"};
const AnsiString Names2[3]={"����� ������","����� ������","��� �������"};
int i;
OpenDialog2->InitialDir=GetCurrentDir();
SaveDialog2->InitialDir=GetCurrentDir();
for(i=0;i<1;i++) // ���� ��� ������� ���������� �������� ������ �������
 StringGrid1->Cells[i][0]=Names1[i];
for(i=0;i<3;i++) // ���� ��� ������� ���������� �������� ������ �������
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
        Form5->Label1->Caption="��� ��������� B, ���������";
        Form5->Label2->Caption="� ��������� ��������� A";
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
        Form5->Label1->Caption="��� ��������� A, ���������";
        Form5->Label2->Caption="� ��������� ��������� B";
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

