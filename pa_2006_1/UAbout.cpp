//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmAbout *FrmAbout;
//---------------------------------------------------------------------------
__fastcall TFrmAbout::TFrmAbout(TComponent* Owner)  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmAbout::btnSairClick(TObject *Sender)
{
    Application->Terminate();
}
//---------------------------------------------------------------------------


