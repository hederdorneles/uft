/*
 *  Heder Dorneles Soares 
 *  Computação Gráfica
 */

#include <windows.h>
#include <GL/glut.h>
#include "globais.h"
#include <stdio.h>


// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Gera a matriz dos cubos
    for (i = 0; i < 3; i++)
    {
        for ( j = 0; j < 9; j++ )
        {
            cubo[i][j].x = x1;
            cubo[i][j].y = y1;
            cubo[i][j].enable = 1;
            x1 += 30.0f;
        }
        x1 = 10.0f;
        y1 -= 30.0f;
    }    
}

void DesenhaRaquete()
{
    glBegin(GL_QUADS);
        glVertex2i(barx , bary + 5);
        glVertex2i(barx, bary);
        glVertex2i(barx + 30, bary);
        glVertex2i(barx + 30, bary + 5);
    glEnd();
}

// Peguei emprestada do site http://alunos.di.ubi.pt/~a14676/galaxia/index.html
// <!- inicio

void desenhacircunferencia(GLfloat radius, GLfloat x, GLfloat y, GLfloat anguloinf, GLfloat angulosup) 
{
    GLfloat ang;
    glLineWidth(0.2);
    glBegin(GL_LINE_LOOP);
        for(ang = anguloinf; ang <= angulosup+0.1; ang = ang + 0.2)
            glVertex2d(radius * cos(ang) + x, radius * sin(ang) + y);
    glEnd();
}

void DesenhaCirculo(GLfloat radius, GLfloat x, GLfloat y, GLfloat anguloinf, GLfloat angulosup)
{
    GLfloat i;
    glColor3f(30, 100 , 20);
    for (i = 0; i <= radius; i+=0.1)
        desenhacircunferencia(i, x,y,anguloinf, angulosup);
    glColor3f(0.0f, 1.0f, 0.0f);
}
// fim...  -> 

void Texto(char *string, int x, int y) 
{  
  	glPushMatrix();
        glRasterPos2f(x, y); // Posição no universo onde o texto será colocado 
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++); 
	glPopMatrix();
}

void DesenhaLinha()
{
    glBegin(GL_QUADS);
        glVertex2i(275,300); glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2i(275,0); glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2i(276,0); glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2i(276,300); glColor3f(1.0f, 0.0f, 0.0f);               
    glEnd();
}

void Desenha()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    
    for ( i = 0; i < 3; i++ )
    {
        for ( j = 0; j < 9; j++ )
        {
            if (cubo[i][j].enable == TRUE)
            {
                glBegin(GL_QUADS);
                    glVertex2i(cubo[i][j].x, cubo[i][j].y + TAM );
                    glVertex2i(cubo[i][j].x, cubo[i][j].y);
                    glVertex2i(cubo[i][j].x + TAM, cubo[i][j].y);
                    glVertex2i(cubo[i][j].x + TAM, cubo[i][j].y + TAM);
                glEnd();
            }
        }
    }
    
    DesenhaCirculo(RBOLA, xbola, ybola, 0.1f, 2 * 3.1415);
    DesenhaRaquete();
    DesenhaLinha();
    
    glColor3f(1.0f,1.0f,1.0f);
    
    sprintf(texto, "Placar: %d", ponto);
    Texto(texto, 278, 233);
    sprintf(texto, "Vidas: %d", vidas);
    Texto(texto, 278, 220);
    sprintf(texto, "Fase: %d", fase);
    Texto(texto, 278, 207);
    
    if ( numblocos == 0)
    {
        numblocos = 27;
        fase ++;
        x1 = X1;
        y1 = Y1 - 30.0f;
        Inicializa();
    }
    
    if ( vidas == 0 )
    {
        Texto("Game Over!!!", 115, 120);
        Texto("Pressione F2 para jogar novamente ou ESC para sair.", 35, 107);
        xstep = 0;
        ystep = 0;
        gameover = TRUE;
    }
    
    glutSwapBuffers();  // Executa os comandos OpenGL
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
     if(h == 0) h = 1; // Evita a divisao por zero
     glViewport(0, 0, w, h); // Especifica as dimensões da Viewport
     glMatrixMode(GL_PROJECTION); // Inicializa o sistema de coordenadas
     glLoadIdentity();
     if (w <= h) // Estabelece a janela de seleção (left, right, bottom, top)     
     {
		windowHeight = 250.0f*h/w;
		windowWidth = 250.0f;
     }
     else  
     { 
		windowWidth = 250.0f*w/h;
		windowHeight = 250.0f;
     }
     gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

void GerenciaTeclas(unsigned char key, int x, int y)
{
    if (key == 27 || key == 'q')  // Sair com ESCAPE
        exit(0);    
}

void GerenciaTeclasEspeciais(int key, int x, int y)
{
    if ( key == GLUT_KEY_RIGHT )
        if (barx < 242)    
            barx += 4;
    if ( key == GLUT_KEY_LEFT )
        if (barx > 2) 
            barx -= 4;
    if ( key == GLUT_KEY_F2 && gameover == TRUE)
    {
        vidas = 3;
        numblocos = 27;
        xstep = ystep = 1.0f;
        gameover = FALSE;
        ponto = 0;
        fase = 1;
        xbola = 125.0f, ybola = 30.0f;
        barx = 125.0f, bary = 10.0f;
        x1 = X1, y1 = Y1;
        Inicializa();
    }
}

void Timer()
{
    if(xbola > 275 - RBOLA || xbola < 0 + RBOLA) // Muda a direção quando chega na borda esquerda ou direita
            xstep = -xstep;
    
    // Muda a direção quando chega na borda superior da janela
    //if(ybola > 245 - RBOLA || ybola < 0 + RBOLA)
    if(ybola > 245 - RBOLA)
          ystep = -ystep;
    if (ybola < 0 + RBOLA) // Muda a direção quando chega na borda janela da janela e decrementa "vidas"
          vidas--,ystep = -ystep;
    
    
    // Esse troço aki tá quase . . . 
    if ( xbola >= barx && xbola <= barx + 30)
        if ( ybola - RBOLA == bary + 5) 
          ystep = -ystep;
    
    for ( i = 0; i < 3; i++ )
    {
        for ( j = 0; j < 9; j++ )
        {
            if (cubo[i][j].enable == TRUE) // Verifica se o cubo ainda existe
            {
                // verifica se a bola se chocou com a barra inferior do cubo
                if ( cubo[i][j].y == (ybola + RBOLA) && 
                   ( ( (xbola + RBOLA) >= cubo[i][j].x && (xbola + RBOLA) <= cubo[i][j].x + TAM ) ||
                      ( xbola - RBOLA >= cubo[i][j].x && xbola -RBOLA <= cubo[i][j].x + TAM )) )
                {
                     xstep = -xstep;
                     ystep = -ystep;
                     cubo[i][j].enable = FALSE;
                     ponto++;
                     numblocos--;
                }
                
                // verifica se a bola se chocou com a barra superior do cubo
                if ( cubo[i][j].y + TAM == (ybola - RBOLA) && 
                   ( ( (xbola + RBOLA) >= cubo[i][j].x && (xbola + RBOLA) <= cubo[i][j].x + TAM ) ||
                      ( xbola - RBOLA >= cubo[i][j].x && xbola -RBOLA <= cubo[i][j].x + TAM )) )
                {
                     xstep = -xstep;
                     ystep = -ystep;
                     cubo[i][j].enable = FALSE;
                     ponto++;
                     numblocos--;
                }
                
                
                if ( cubo[i][j].x == (xbola + RBOLA) &&
                   ( ( ybola + RBOLA) >= cubo[i][j].y && (ybola + RBOLA) <= cubo[i][j].y + TAM ) )
                {
                     xstep = -xstep;
                     ystep = -ystep;
                     cubo[i][j].enable = FALSE;
                     ponto++;
                     numblocos--;
                }
                
                // bola choque barra esquerda
                if ( cubo[i][j].x + TAM == (xbola - RBOLA) &&
                   ( ( ybola + RBOLA) >= cubo[i][j].y && (ybola + RBOLA) <= cubo[i][j].y + TAM ) )
                {
                     xstep = -xstep;
                     ystep = -ystep;
                     cubo[i][j].enable = FALSE;
                     ponto++;
                     numblocos--;
                }
                
            }
        }
    }
    // Move a bola
    xbola += xstep; 
    ybola += ystep;
    
    glutPostRedisplay();
    glutTimerFunc(1, Timer, 1);
}

int main()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Arkanoid - HEDER");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(GerenciaTeclas);
    glutSpecialFunc(GerenciaTeclasEspeciais);
    glutTimerFunc(4, Timer, 1);
    Inicializa();
    glutMainLoop(); 
    return 0;
}
