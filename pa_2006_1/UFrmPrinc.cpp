//---------------------------------------------------------------------------
#include <vcl.h>
#include <fstream.h>
#include <sstream.h>
const delimitador = ';';
#pragma hdrstop

#include "UFrmPrinc.h"
#include "UAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmPrinc *FrmPrinc;
//---------------------------------------------------------------------------
__fastcall TFrmPrinc::TFrmPrinc(TComponent* Owner) : TForm(Owner)
{
    ifstream in("config.ini"); // Arquivo com a quantidade de eleitores da seção

    if (!in.fail()) {
        char aux[10];
        int num;
        while(!in.eof())
        {
            in.getline(aux, sizeof(aux),'\n');
        }
        num = StrToInt(aux);
        numEleitores = num;     // Quantidade de Eleitores da seção
        in.close();
    } else {
        Application->MessageBoxA("Erro o arquivo de inicializão config.ini\nNão foi carregado corretamente","Erro Fatal", 0);
        Application->Terminate();
    }

    if (numEleitores <= 0)
    {
        Application->MessageBoxA("Erro na quantidade de eleitores","Erro Fatal", 0);
        Application->Terminate();
    }
    // Cargo por extenso
    cargos[0] = "DEPUTADO(A) FEDERAL";
    cargos[1] = "DEPUTADO(A) ESTADUAL";
    cargos[2] = "SENADOR(A)";
    cargos[3] = "GOVERNADOR(A)";
    cargos[4] = "PRESIDENTE(A)";
    // Titulo
    lbCargo->Caption = cargos[numCargo = 0];

    // Carregar candidatos pra a memória
    if (!abrirArq("deputado_federal.txt", depFederal))
    {
        Application->MessageBoxA("\tErro o arquivo de inicializão \"deputado_federal.txt\".\t\t\n\tNão foi carregado corretamente","Erro Fatal", 0);
        Application->Terminate(); // Finalizar Aplicação
    }

    if (!abrirArq("deputado_estadual.txt", depEstadual))
    {
        Application->MessageBoxA("\tErro o arquivo de inicializão \"deputado_estadual.txt\".\t\t\n\tNão foi carregado corretamente","Erro Fatal", 0);
        Application->Terminate();
    }

    if (!abrirArq("governador.txt", governador))
    {
        Application->MessageBoxA("\tErro o arquivo de inicializão \"governador.txt\".\t\t\n\tNão foi carregado corretamente","Erro Fatal", 0);
        Application->Terminate();
    }

    if (!abrirArq("senador.txt", senador))
    {
        Application->MessageBoxA("\tErro o arquivo de inicializão \"governador.txt\".\t\t\n\tNão foi carregado corretamente","Erro Fatal", 0);
        Application->Terminate();
    }

    if (!abrirArq("presidente.txt", presidente)) {
        // Error ao abrir os arquivos de inicialização da urna
        Application->MessageBoxA("\tErro os arquivos de inicializão da urna.\t\t\n\tNão foram carregado corretamente","Erro Fatal", 0);
        Application->Terminate(); // Finalizar Aplicação
    }
    
    // inicializando os votos brancos e nulos
    for (int i=0; i < 5; i++) {
        votosBrancos[i] = 0;
        votosNulos[i]   = 0;
    }
    // Desabilitar botão Confirmar
    pnlConfirmar->Enabled = false;
    lbBrancoNulo->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrmPrinc::pnlUmClick(TObject *Sender)
{
    bool check = false;
    
    MediaPlayer1->FileName="sons\\butao.wav";
    MediaPlayer1->Open();
    MediaPlayer1->Play();
    
    // Deputado Federal
    if ((numCargo == 0) && (lbNumero->GetTextLen() < 4)) {
        lbNumero->Caption = lbNumero->Caption + ((TLabel*)Sender)->Caption;
        if (lbNumero->GetTextLen() == 4) check = true;
    }
    // Deputado Estadual
    else if ((numCargo == 1) && (lbNumero->GetTextLen() < 5)) {
         lbNumero->Caption = lbNumero->Caption + ((TLabel*)Sender)->Caption;
        if (lbNumero->GetTextLen() == 5) check = true;
    }
    // Senador
    else if ((numCargo == 2) && (lbNumero->GetTextLen() < 3)) {
         lbNumero->Caption = lbNumero->Caption + ((TLabel*)Sender)->Caption;
        if (lbNumero->GetTextLen() == 3) check = true;
    }
    // Govenador
    else if ((numCargo == 3) && (lbNumero->GetTextLen() < 2)) {
         lbNumero->Caption = lbNumero->Caption + ((TLabel*)Sender)->Caption;
        if (lbNumero->GetTextLen() == 2) check = true;
    }
    // Presidente
    else if ((numCargo == 4) && (lbNumero->GetTextLen() < 2)) {
         lbNumero->Caption = lbNumero->Caption + ((TLabel*)Sender)->Caption;
        if (lbNumero->GetTextLen() == 2) check = true;
    }
    if (check)
        pesquisar();
}
//---------------------------------------------------------------------------
void __fastcall TFrmPrinc::FormCreate(TObject *Sender)
{
    // Refinamento para a tela
    pnlTeclas->Caption = "";
    lbNumero->Caption = "";
    pnlDados->Visible = false;
    pnlRodapeTela->Visible = false;
    lbNum->Visible = true;
    lbFim->Visible = false;
}
//---------------------------------------------------------------------------
int TFrmPrinc::abrirArq(char *arquivo, CANDIDATO *c) {
    ifstream arq(arquivo);
    int i = 0;
    char str[80];

    if (!arq.fail()) {
        while (!arq.eof()) {
            arq.getline(str, sizeof(str), delimitador);
            strcpy((*(c+i)).candidato, str);
            arq.getline(str, sizeof(str), delimitador);
            (*(c+i)).numero = StrToInt(str);
            arq.getline(str, sizeof(str), delimitador);
            strcpy((*(c+i)).partido, str);
            arq.getline(str, sizeof(str), delimitador);
            strcpy((*(c+i)).coligacao, str);
            arq.getline(str, sizeof(str), '\n');
            (*(c+i)).voto = 0;  // Inicializa cada candidato com 0 (zero) votos
            i++;
        }
        arq.close();
        return i;
    }
    return 0;
}
//---------------------------------------------------------------------------
bool TFrmPrinc::pesquisar(void)
{
    int tamanho;
    unsigned int numero = StrToInt(lbNumero->Caption);

    if (numCargo == 0) {
        cargo = depFederal;
        tamanho = 84;
    } else if (numCargo == 1) {
        cargo = depEstadual;
        tamanho = 360;
    } else if (numCargo == 2) {
        cargo = senador;
        tamanho = 5;
    } else if (numCargo == 3) {
        cargo = governador;
        tamanho = 5;
    } else if (numCargo == 4) {
        cargo = presidente;
        tamanho = 8;
    }
    pnlConfirmar->Enabled = true;
    for (int i=0; i < tamanho; i++) {
        if ((*(cargo+i)).numero == numero) {
            lbPartido->Caption   = (*(cargo+i)).partido;
            lbCandidato->Caption = (*(cargo+i)).candidato;
            lbColigacao->Caption = (*(cargo+i)).coligacao;
            imgCandidato->Visible = true;
            pnlDados->Visible = true;
            pnlRodapeTela->Visible = true;
            lbNum->Visible = true;
            confirma = CONFIRMA;
            /*if (numCargo < 2) {
               imgCandidato->Picture->LoadFromFile("fotos/default.jpg");
            } else{*/
            if (numCargo == 0) // Deputado federal
            {
                if (FileExists("fotos/dep_federal/"+lbNumero->Caption+".jpg"))
                    imgCandidato->Picture->LoadFromFile("fotos/dep_federal/"+lbNumero->Caption+".jpg");
                else
                    imgCandidato->Picture->LoadFromFile("fotos/default.jpg");
            }
            else if (numCargo == 1) // Deputado estadual
            {
                if (FileExists("fotos/dep_estadual/"+lbNumero->Caption+".jpg"))
                    imgCandidato->Picture->LoadFromFile("fotos/dep_estadual/"+lbNumero->Caption+".jpg");
                else
                    imgCandidato->Picture->LoadFromFile("fotos/default.jpg");
            }
            else if (numCargo == 2) // Senador
            {
                if (FileExists("fotos/senado/"+lbNumero->Caption+".jpg"))
                    imgCandidato->Picture->LoadFromFile("fotos/senado/"+lbNumero->Caption+".jpg");
                else
                    imgCandidato->Picture->LoadFromFile("fotos/default.jpg");
            }
            else if (numCargo == 3) // Governador
            {
                if (FileExists("fotos/governo/"+lbNumero->Caption+".jpg"))
                    imgCandidato->Picture->LoadFromFile("fotos/governo/"+lbNumero->Caption+".jpg");
                else
                    imgCandidato->Picture->LoadFromFile("fotos/default.jpg");
            }
            else // Presidente
                if (FileExists("fotos/presidencia/"+lbNumero->Caption+".jpg"))
                    imgCandidato->Picture->LoadFromFile("fotos/presidencia/"+lbNumero->Caption+".jpg");
                else
                    imgCandidato->Picture->LoadFromFile("fotos/default.jpg");
            //}
            cargo = (cargo+i);
            return true;
        }
    }
    
    // Limpar Visor
    pnlDados->Visible = false;
    imgCandidato->Visible = false;
    lbNum->Visible = false;
    lbNumero->Caption = "";
    pnlTeclas->Enabled = false;
    confirma = NULO;
    lbBrancoNulo->Caption = "   VOTO NULO ";
    lbBrancoNulo->Visible = true;
    pnlRodapeTela->Visible = true;
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TFrmPrinc::pnlUmMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //((TPanel*)Sender)->BorderStyle = bsSingle;
    ((TPanel*)Sender)->BevelInner = bvLowered;
}
//---------------------------------------------------------------------------
void __fastcall TFrmPrinc::pnlUmMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //((TPanel*)Sender)->BorderStyle = bsNone;
    ((TPanel*)Sender)->BevelInner = bvNone;
}
//---------------------------------------------------------------------------
void __fastcall TFrmPrinc::pnlCorrigeClick(TObject *Sender)
{
    // Tocar son de butao
    MediaPlayer1->FileName="sons\\butao.wav";
    MediaPlayer1->Open();
    MediaPlayer1->Play();
    
    pnlDados->Visible = false;
    pnlRodapeTela->Visible = false;
    imgCandidato->Visible = false;
    lbNum->Visible = true;
    lbNumero->Caption = "";
    pnlConfirmar->Enabled = false;
    pnlTeclas->Enabled = true;
    lbBrancoNulo->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrmPrinc::pnlConfirmarClick(TObject *Sender)
{
    // Tocar son de butao
    //MediaPlayer1->FileName="sons\\meio.wav";
    //MediaPlayer1->Open();
    //MediaPlayer1->Play();

    ostringstream os;
    os << "res-" << cargos[numCargo] << ".dat";
    ofstream saida(os.str().c_str());
    int tamanho, i = 0;

    if (confirma == CONFIRMA)       // Confirmar Voto
        cargo->voto++;
    else if (confirma == NULO)      // Confirmar Nulo
        votosNulos[numCargo]++;
    else if (confirma == BRANCO)    // Confirmar Branco
        votosBrancos[numCargo]++;

    // Jogar Resultado para o arquivo  --- inicio
    if (numCargo == 0) {
        cargo = depFederal;
        tamanho = 360;
    } else if (numCargo == 1) {
        cargo = depEstadual;
        tamanho = 84;
    } else if (numCargo == 2) {
        cargo = senador;
        tamanho = 5;
    } else if (numCargo == 3) {
        cargo = governador;
        tamanho = 5;
    } else if (numCargo == 4) {
        cargo = presidente;
        tamanho = 8;
    }
    while (i < tamanho) {
        saida.write((cargo+i)->candidato, strlen((cargo+i)->candidato));
        saida << ";" << (cargo+i)->numero << ";";
        saida.write((cargo+i)->partido, strlen((cargo+i)->partido));
        saida << ";";
        saida.write((cargo+i)->coligacao, strlen((cargo+i)->coligacao));
        saida << ";"  << (cargo+i)->voto << ";" << endl;
        i++;
    }
    saida << "BRANCOS;" << votosBrancos[numCargo] << ";" << endl;
    saida << "NULOS;" << votosNulos[numCargo] << ";" ;
    // Jogar Resultado para o arquivo  --- fim

    pnlCorrigeClick(Sender);
    if (numCargo == 4) {
        lbNum->Visible = false;
        lbFim->Visible = true;
        pnlTeclas->Enabled = false;
        pnlTeclado->Enabled = false;
        lbCargo->Caption = "";
        MediaPlayer1->FileName="sons\\fim.wav";
        MediaPlayer1->Open();
        MediaPlayer1->Play();
        numEleitores--;
    } else {
        MediaPlayer1->FileName="sons\\meio.wav";
        MediaPlayer1->Open();
        MediaPlayer1->Play();
        lbCargo->Caption = cargos[++numCargo];
    }
}
//---------------------------------------------------------------------------
void __fastcall TFrmPrinc::pnlBrancoClick(TObject *Sender)
{
    MediaPlayer1->FileName="sons\\branco.wav";
    MediaPlayer1->Open();
    MediaPlayer1->Play();

    //pnlCorrigeClick(Sender);
    //------------------------
    pnlDados->Visible = false;
    pnlRodapeTela->Visible = false;
    imgCandidato->Visible = false;
    lbNum->Visible = true;
    lbNumero->Caption = "";
    pnlConfirmar->Enabled = false;
    pnlTeclas->Enabled = true;
    lbBrancoNulo->Visible = false;
    //------------------------
    confirma = BRANCO;
    lbBrancoNulo->Caption = "VOTO EM BRANCO";
    pnlConfirmar->Enabled = true;
    lbBrancoNulo->Visible = true;
    pnlRodapeTela->Visible = true;
    pnlTeclas->Enabled = false;
    lbNum->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TFrmPrinc::FormKeyPress(TObject *Sender, char &Key)
{
    if (Key == 27 && lbFim->Visible) {
          if (!numEleitores) {
               Application->CreateForm(__classid(TFrmAbout), &FrmAbout);
               FrmAbout->ShowModal();
          }
          lbCargo->Caption = cargos[numCargo = 0];    // Reiniciar Urna
          lbFim->Visible = false;
          lbNum->Visible = true;
          pnlTeclado->Enabled = true;
          pnlTeclas->Enabled = true;
    }
}
//---------------------------------------------------------------------------

