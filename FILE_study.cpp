//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FILE_study.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	in = NULL;
	out = NULL;
	full = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	fclose(in);
	fclose(out);
	delete [] full;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::fopenBtnClick(TObject *Sender)
{
	in = fopen(fileE->Text.c_str(), Edit1->Text.c_str());
	if (!in)
		return ShowMessage ( "Cannot open binary file");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ReadBtnClick(TObject *Sender)
{
	//wchar_t c;
	if (feof(in))
	{
      return ShowMessage("eof");
   }

	char c;
	fread(&c, sizeof(char), 1, in);
	Out->Lines->Add(c);
	Out->Lines->Add(feof(in));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SizeBtnClick(TObject *Sender)
{
	//FILE*  fMyFile = fopen("data.dat","r");
	fseek(in,0,SEEK_END);
	long size = ftell(in);
	Out->Lines->Add("size="+IntToStr((int)size));
	struct stat st;
	stat(fileE->Text.c_str(), &st);
	Out->Lines->Add("Size: bytes "+IntToStr((int) st.st_size));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::fseekBtnClick(TObject *Sender)
{
	fseek(in, Pos->Position, SEEK_CUR);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WriteBtnClick(TObject *Sender)
{
	char w;
	if (WE->Text.IsEmpty())
	{
		w = Pos->Position;
	}
	else
		w = WE->Text[1];
	fwrite(&w, sizeof(char), 1, in);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::fcloseBtnClick(TObject *Sender)
{
	fclose(in);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	struct stat st;
	stat(fileE->Text.c_str(), &st);
	Out->Lines->Add("Size: bytes "+IntToStr((int) st.st_size));
	full = new char [st.st_size];
	fread(full, st.st_size, 1, in);
	Out->Lines->Add(full);
	fseek(in, Pos->Position, SEEK_SET);
   fwrite(full, st.st_size, 1, in);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ftellBTNClick(TObject *Sender)
{
	Out->Lines->Add(ftell(in));
}
//---------------------------------------------------------------------------

