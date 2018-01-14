#define TRUE 1
#define FALSE 0
#define TAM 20
#define RBOLA 10
#define X1 10.0f
#define Y1 220.0f

// Janela
GLfloat windowWidth;
GLfloat windowHeight;
GLfloat x1 = X1 , y1 = Y1;

// Movimentação e controle da raquete
GLfloat barx = 125.0f, bary = 10.0f;

int i, j;

// Blocos
struct BLOCKS{
    int x;
    int y;
    int enable;
}cubo[3][9];

int numblocos = 27;   // Contador de blocos para definir fim da fase

// Movimentando a bola
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
GLfloat xbola = 125.0f, ybola = 30.0f;

// Pontuação
int ponto = 0;
int vidas = 3;
char texto[20] = "Placar: ";
int gameover = 0;
int fase = 1;
