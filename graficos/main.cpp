
/****************************************************************************
 * Copyright (C) 2016 by Macedo Levy, Castilho Lucas, Marie ...             *
 *                                                                          *
 * This file is part of Box.                                                *
****************************************************************************/

/*!
 * \file main.cpp
 * \author Levy Mateus Macedo
 * \author Lucas Franson de Castilho
 * \author Maria ...
 *
 * \date 15 Oct 2016
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
#include "header/defines.h"
#include "header/graphics.h"

using namespace std;
int static option = 0;

/*!  Program entry point */
int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 0);
    glutCreateWindow("Graphic");

    printf("1 = Grafico circular\n2 = Grafico de colunas\nEm seguida informe os quatro valores em porcentagem:\n");
   scanf(" %d", &option);

    switch(option)
    {
    case 1:
      scanf("%f%f%f%f", &DATA[0],&DATA[1],&DATA[2],&DATA[3]);
      GP_RADIUS = 6;    // raio da pizza
      INICOORDX = 0;    // coordenada inicial x
      INICOORDY = 0;    // coordenada inicial y
      gpInit();
      glutDisplayFunc(gpDrawGraphicP);
      glutReshapeFunc(gpReshape);
      break;
    case 2:
      scanf("%f%f%f%f", &DATA[0],&DATA[1],&DATA[2],&DATA[3]);
      gpInit();
      glutDisplayFunc(gpDrawColumn);
      glutReshapeFunc(gpReshape_);
      break;
   default: break;
    }

    glutMainLoop();

    return EXIT_SUCCESS;

}
