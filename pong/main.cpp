
/***********************************************************************************************
 * Copyright (C) 2016 by Levy Mateus Macedo, Lucas Franson, Maria Vitória                      *
 *                                                                                             *
 * This file is part of Box.                                                                   *
************************************************************************************************/

/*!
 * \file main.cpp
 * \author Levy Mateus Macedo
 * \author Lucas Barros Franson de Castilho
 * \author Maria Vitória Ostapiv Correia
 *
 * \date 13 Oct 2016
 *
 * \brief Esse é o arquivo princial do projeto
 *
 */

#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI (3.14159265359)
#define FPS (100) // FRAMES PER SECOND

static int WINDOW_WIDTH = 640;
static int WINDOW_HEIGHT = 480;

typedef struct PLATAFORMA_ESQUERDA{
    float top = 120; /**<! top - Referente a coordenada do topo do retangulo */
    float mid1 = 120+13; /**<! mid1 - Referente a coordenada superior do segmento central */
    float mid2 = 120+28; /**<! mid2 - Referente a coordenada inferiro do segmento central */
    float bottom = 80; /**<! top - Referente a coordenada mais inferior do retangulo */
    float areaColisao = 3; /**<! areaColisao - Referente ao valor da area de colisao da plataforma */
}PLATAFORMA_ESQUERDA;

static PLATAFORMA_ESQUERDA PLAT_ESQ;

typedef struct PLATAFORMA_DIREITA{
    float top = 120; /**<! top - Referente a coordenada do topo do retangulo */
    float mid1 = 120+13; /**<! mid1 - Referente a coordenada superior do segmento central */
    float mid2 = 120+28; /**<! mid2 - Referente a coordenada inferiro do segmento central */
    float bottom = 80; /**<! top - Referente a coordenada mais inferior do retangulo */
    float areaColisao = 197; /**<! areaColison - Referente ao valor da area de colisao da plataforma */
}PLATAFORMA_DIREITA;

static PLATAFORMA_DIREITA PLAT_DIR;

/**
* O primeiro valor é refente ao jogador da esquerda e o segundo valor ao jogador da direita
*/
static int SCORE[] = {0, 0};

/**
* Primeiro valor é referente a coorednada x do "bola"
* Segundo valor é referente a coorednada y do "bola"
*/
static float QUAD[] = {4, 100};

float quad_velocity = 100;
double last_time = time(NULL);
double current_time = 0;
int frame_count = 0;
float frame_rate = 0;
int current_fps = 0;

/**
* Usado para controlar os incrementos realizados na coordenada da "bola"
*/
float ctrl_quad_x = 1.00;
float ctrl_quad_y = 0.00;

/* GLUT callback Handlers */

static void resize(int w, int h)
{

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 200.0, 0.0, 200.0, -20, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    WINDOW_WIDTH = w;
    WINDOW_HEIGHT = h;

}

void PlataformaEsq(float y)
{

    glBegin(GL_QUADS);
    {
      // lado esquerdo
      glColor3f(1.0, 0.0, 0.0);
      glVertex2f(1, y);
      glVertex2f(4, y);
      glVertex2f(4, y - 40);
      glVertex2f(1, y - 40);
    }
    glEnd();

}

void PlataformaDir(float y)
{

    glBegin(GL_QUADS);
    {
      // lado direito
      glColor3f(0.0, 0.0, 1.0);
      glVertex2f(199, y);
      glVertex2f(196, y);
      glVertex2f(196, y - 40);
      glVertex2f(199, y - 40);
    }
    glEnd();

}

void quad(float x, float y)
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);

      glVertex2f(QUAD[0], QUAD[1]);//redesenhado apartir deste ponto
      glVertex2f(QUAD[0] + 3, QUAD[1] + 3);
      glVertex2f(QUAD[0] - 3, QUAD[1] + 3);
      glVertex2f(QUAD[0] - 3, QUAD[1] - 3);
      glVertex2f(QUAD[0] + 3, QUAD[1] - 3);
      glVertex2f(QUAD[0] + 3, QUAD[1] + 3);

    glEnd();

}

static void display(void)
{

    glColor3f(1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    * Rede
    */
    glBegin(GL_LINES);
    {
      glColor3f(1.0, 1.0, 1.0);
        glVertex2f(100, 200);
        glVertex2f(100, 0);

    }
    glEnd();

    glBegin(GL_LINES);
    {
       glColor3f(1.0, 1.0, 1.0);
        glLineWidth(6);
        glVertex2f(0, 1);
        glVertex2f(200, 1);
    }
    glEnd();

    glBegin(GL_LINES);
    {
      glColor3f(1.0, 1.0, 1.0);
      glLineWidth(6);
      glVertex2f(0, 199);
      glVertex2f(199, 199);
    }
    glEnd();

    PlataformaDir(PLAT_DIR.top);
    PlataformaEsq(PLAT_ESQ.top);
    quad(QUAD[0], QUAD[1]);

    glFlush();

    frame_count++;
    current_time = time(NULL);

    if(current_time - last_time > 0)
    {
      frame_rate = frame_count/(current_time-last_time);
      printf("FPS: %lf\n", frame_rate);
      frame_count = 0;
      last_time = current_time;
    }

}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'l':
        if(PLAT_DIR.bottom > 0){
            PLAT_DIR.top -= 5.0;
            PlataformaDir(PLAT_DIR.top);
            PLAT_DIR.mid1 = PLAT_DIR.top-13;
            PLAT_DIR.mid2 = PLAT_DIR.top-26;
            PLAT_DIR.bottom = PLAT_DIR.top - 40;
            //printf("QUAD=%f", QUAD[0] );
            //printf("top=%f   bot=%f\n", PLAT_DIR.top, PLAT_DIR.bottom );
        }
        break;

    case 'o':
        if(PLAT_DIR.top < 200){
            PLAT_DIR.top += 5.0;
            PlataformaDir(PLAT_DIR.top);
            PLAT_DIR.mid1 = PLAT_DIR.top-13;
            PLAT_DIR.mid2 = PLAT_DIR.top-26;
            PLAT_DIR.bottom = PLAT_DIR.top - 40;
            //printf("top=%f   bot=%f\n", PLAT_DIR.top, PLAT_DIR.bottom );
        }
        break;

    case 'w':
        if(PLAT_ESQ.top < 200){
            PLAT_ESQ.top += 5.0;
            PlataformaEsq(PLAT_ESQ.top);
            // atualiza valores da plataforma >>>>
            PLAT_ESQ.mid1 = PLAT_ESQ.top-13;
            PLAT_ESQ.mid2 = PLAT_ESQ.top-26;
            PLAT_ESQ.bottom = PLAT_ESQ.top - 40;
            //printf("x=%fy=%f\n", PLAT_ESQ.mid1, PLAT_ESQ.mid2 );
        }
        break;

    case 's':
        if( PLAT_ESQ.bottom > 0){
            PLAT_ESQ.top -= 5.0;
            PlataformaEsq(PLAT_ESQ.top);
            PLAT_ESQ.mid1 = PLAT_ESQ.top-13;
            PLAT_ESQ.mid2 = PLAT_ESQ.top-26;
            PLAT_ESQ.bottom = PLAT_ESQ.top - 40;
            //printf("x=%fy=%f\n", PLAT_ESQ.mid1, PLAT_ESQ.mid2 );
        }
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void colisao()
{

    if((QUAD[1]>=200)||(QUAD[1]<=0)){
        ctrl_quad_y *= -1;
    }

    if(QUAD[0] >= 196){

        if((PLAT_DIR.top >= QUAD[1]) && (PLAT_DIR.mid1 <= QUAD[1]))
        {
            ctrl_quad_x = -(quad_velocity/frame_rate);
            ctrl_quad_y = (quad_velocity/frame_rate)*0.5;
            printf("R1 = %f\n", ctrl_quad_y);

        } else if((PLAT_DIR.mid1 >= QUAD[1]) && (PLAT_DIR.mid2 <= QUAD[1])){

            ctrl_quad_x = -(quad_velocity/frame_rate);
            ctrl_quad_y = 0;
            printf("R2 = %f\n", ctrl_quad_y);

        } else if((PLAT_DIR.mid2 >= QUAD[1]) && (PLAT_DIR.bottom <= QUAD[1])){

            ctrl_quad_x = -(quad_velocity/frame_rate);
            ctrl_quad_y = -(quad_velocity/frame_rate)*0.5;
            printf("R3 = %f\n", ctrl_quad_y);
            printf("R top = %f  mid1 = %f  mid2 = %f   bottom = %f\n", PLAT_DIR.top, PLAT_DIR.mid1, PLAT_DIR.mid2, PLAT_DIR.bottom);

        } else {

            SCORE[0] += 1;
            QUAD[0] = 4;
            QUAD[1] = 100;
            Sleep(1000);
            PLAT_DIR.top = 120;
            PLAT_DIR.mid1 = 120+13;
            PLAT_DIR.mid2 = 120+26;
            PLAT_DIR.bottom = PLAT_DIR.top - 40;

            PLAT_ESQ.top = 120;
            PLAT_ESQ.mid1 = 120+13;
            PLAT_ESQ.mid2 = 120+26;
            PLAT_ESQ.bottom = PLAT_ESQ.top - 40;

            return;
        }
    }

    if(QUAD[0] <= 4){

        if((PLAT_ESQ.top >= QUAD[1]) && (PLAT_ESQ.mid1 <= QUAD[1]))
        {
            ctrl_quad_x = (quad_velocity/frame_rate);
            ctrl_quad_y = (quad_velocity/frame_rate)*0.5;
            printf("L1 = %f\n", ctrl_quad_y);

        } else if((PLAT_ESQ.mid1 >= QUAD[1]) && (PLAT_ESQ.mid2 <= QUAD[1])){

            ctrl_quad_x = (quad_velocity/frame_rate);
            ctrl_quad_y = 0;
            printf("L2 = %f\n", ctrl_quad_y);

        } else if((PLAT_ESQ.mid2 >= QUAD[1]) && (PLAT_ESQ.bottom <= QUAD[1])){

            ctrl_quad_x = (quad_velocity/frame_rate);
            ctrl_quad_y = -(quad_velocity/frame_rate)*0.5;
            printf("L3 = %f\n", ctrl_quad_y);
            printf("L top = %f  mid1 = %f  mid2 = %f   bottom = %f\n", PLAT_DIR.top, PLAT_DIR.mid1, PLAT_DIR.mid2, PLAT_DIR.bottom);

        } else {

            SCORE[0] += 1;
            QUAD[0] = 5;
            QUAD[1] = 100;
            Sleep(1000);
            PLAT_DIR.top = 120;
            PLAT_DIR.mid1 = 120+13;
            PLAT_DIR.mid2 = 120+26;
            PLAT_DIR.bottom = PLAT_DIR.top - 40;

            PLAT_ESQ.top = 120;
            PLAT_ESQ.mid1 = 120+13;
            PLAT_ESQ.mid2 = 120+26;
            PLAT_ESQ.bottom = PLAT_ESQ.top - 40;

            return;
        }

    }


}

static void idle(int)
{

    QUAD[0] += ctrl_quad_x;
    QUAD[1] += ctrl_quad_y;

    colisao();

    glutPostRedisplay();
    glutTimerFunc(1000/FPS, idle, 0);

}

/* Program entry point */

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("PONG");
    glClearColor(0, 0, 0, 0);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    glutTimerFunc(1000/FPS, idle, 0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
