//---------------------------------------------------------------------------

#ifndef UFrmPrincH
#define UFrmPrincH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
typedef struct {
    char candidato[80];
    char partido[10];
    char coligacao[45];
    unsigned int numero;
    unsigned int voto;
} CANDIDATO;
//---------------------------------------------------------------------------
class TFrmPrinc : public TForm
{
__published:	// IDE-managed Components
    TPanel *pnlTela;
    TPanel *pnlTeclado;
    TPanel *pnlBranco;
    TPanel *pnlCorrige;
    TPanel *pnlConfirmar;
    TPanel *pnlTeclas;
    TPanel *pnlDados;
    TLabel *lbCargo;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *lbNumero;
    TLabel *lbNum;
    TImage *imgCandidato;
    TLabel *lbPartido;
    TLabel *lbCandidato;
    TLabel *lbColigacao;
    TPanel *pnlUm;
    TPanel *pnlDois;
    TPanel *pnlTres;
    TPanel *pnlQuatro;
    TPanel *pnlCinco;
    TPanel *pnlSeis;
    TPanel *pnlSete;
    TPanel *pnlOito;
    TPanel *pnlNove;
    TPanel *pnlZero;
    TPanel *pnlRodapeTela;
    TScrollBox *scrLinha;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *lbBrancoNulo;
    TLabel *lbFim;
    TMediaPlayer *MediaPlayer1;
    TPanel *pnlJustica;
    TImage *imgJustica;
    TLabel *Label6;
    TLabel *Label7;
    void __fastcall pnlUmClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall pnlUmMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall pnlUmMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall pnlCorrigeClick(TObject *Sender);
    void __fastcall pnlConfirmarClick(TObject *Sender);
    void __fastcall pnlBrancoClick(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:
    enum  {NULO, BRANCO, CONFIRMA} confirma;
    unsigned int numCargo;          // Cargo de 0 a 4
    char *cargos[5];                 // cargo por extenso
    unsigned int numEleitores;      // numero de votantes da seção
    unsigned int votosBrancos[5];   // Armazena os votos Brancos de todos os Cargos
    unsigned int votosNulos[5];     // Armazena os votos Nulos de todos os Cargos
    CANDIDATO *cargo;               // Ponteiro pro candidato atual
    CANDIDATO depFederal[84];
    CANDIDATO depEstadual[360];
    CANDIDATO senador[5];
    CANDIDATO governador[5];
    CANDIDATO presidente[8];

public:
    __fastcall TFrmPrinc(TComponent* Owner);
    int abrirArq(char *, CANDIDATO *);
    bool pesquisar(void);                 // Localizar candidato
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmPrinc *FrmPrinc;
//---------------------------------------------------------------------------
#endif
