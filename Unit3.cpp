//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
#include "Unit1.h"
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::BitBtn1Click(TObject *Sender)
{
Form1->CheckBox1->Checked=true;
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::BitBtn2Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Edit1Change(TObject *Sender)
{
SpeedButton1->Enabled=Edit1->Text.operator!=("")&&
                      Edit2->Text.operator!=("")&&
                      Edit3->Text.operator!=("");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton2Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormShow(TObject *Sender)
{
Edit1->SetFocus();        
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton1Click(TObject *Sender)
{
Form1->CheckBox1->Checked=true;
Close();
}
//---------------------------------------------------------------------------
