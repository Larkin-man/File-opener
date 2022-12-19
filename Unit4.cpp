//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::SpeedButton1Click(TObject *Sender)
{
if (SaveDialog1->Execute())
 RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormCreate(TObject *Sender)
{
SaveDialog1->InitialDir=GetCurrentDir();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::SpeedButton2Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------
