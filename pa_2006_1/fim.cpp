//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fim.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmFim *frmFim;
//---------------------------------------------------------------------------
__fastcall TfrmFim::TfrmFim(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmFim::btnSairClick(TObject *Sender)
{
    Application->Terminate();
}
//---------------------------------------------------------------------------

