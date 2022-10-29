//---------------------------------------------------------------------------

#ifndef FILE_studyH
#define FILE_studyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <stdio.h>
#include <ComCtrls.hpp>
#include <sys\stat.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Out;
	TButton *fopenBtn;
	TEdit *Edit1;
	TEdit *fileE;
	TButton *ReadBtn;
	TButton *SizeBtn;
	TButton *WriteBtn;
	TEdit *Edit2;
	TUpDown *Pos;
	TButton *fseekBtn;
	TButton *fcloseBtn;
	TEdit *WE;
	TButton *Button1;
	TButton *ftellBTN;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall fopenBtnClick(TObject *Sender);
	void __fastcall ReadBtnClick(TObject *Sender);
	void __fastcall SizeBtnClick(TObject *Sender);
	void __fastcall fseekBtnClick(TObject *Sender);
	void __fastcall WriteBtnClick(TObject *Sender);
	void __fastcall fcloseBtnClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ftellBTNClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	FILE *in, *out;
	char *full;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
