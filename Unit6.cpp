//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm6::FormCreate(TObject *Sender)
{
const AnsiString Names[1]={"�����"};
int i;
for(i=0;i<1;i++) // ���� ��� ������� ���������� �������� �������
 StringGrid1->Cells[i][0]=Names[i];
}
//---------------------------------------------------------------------------
 