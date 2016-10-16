
/****************************************************************************
 * Copyright (C) 2016 by Macedo Levy, Castilho Lucas, Marie ...             *
 *                                                                          *
 * This file is part of Box.                                                *
****************************************************************************/

/*!
 * \file graphics.h
 * \author Levy Mateus Macedo
 * \author Lucas Franson de Castilho
 * \author Maria ...
 *
 * \date 15 Oct 2016
 *
 * \brief Esse arquivo de cabeçalho contem as definições para a implementação
 * do arquivo \see grapchics.cpp.
 *
 */

#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

double GP_RADIUS = 0;               //<! Raio da circunferencia (Global)
int INICOORDX = 0, INICOORDY = 0;   //<! Coordenadas do centro do arco. (Global)
float DATA[4] = { };               //<! Vetor de valores/variaveis do grafico. (Global)
//char* LEGENDA[4];                  /**< Vetor de strings para a legenda do grafico
GLbyte COLOURS[4] = { (GLbyte) 0101, /**< Vetor de cores do grafico */
                      (GLbyte) 1111,
                      (GLbyte) 0110,
                      (GLbyte) 1101};

/** \fn void gpReshape(int w, int h);
 * \fn void gpReshape_(int w, int h);
 * \brief Chamada quando a janela e redimencionada.
 * \brief \sa gpReshape_ é chamada para o grafico em colunas;
 *
 * \param [in] int w: Comprimento da janela;
 * \param [in] int h: Largura da janela;
 *
 * \return void.
 *
 */

void gpReshape(int w, int h); void gpReshape_(int w, int h);

/** \fn void gpInit(void);
 *
 * \brief Iniciliza a tela.
 *
 */

void gpInit(void);



/** \brief Desenha uma grafico pizza com 4 variáveis.
 * As valores em '%' das fatias do gráfico são definidos no vetor \sa DATA \sa grapchis.h.
 *
 * \return nada.
 *
 */

void gpDrawGraphicP (void);



/** \brief Converte valor em graus para radianos.
 *
 * \param a[in] double angulo;
 *
 * \return Valor em radianos.
 *
 */

double GrausParaRadianos(double angulo);



/** \brief Converte valor em graus para radianos.
 *
 * \param a[in] double percent: Valor em '%';
 *
 * \return Valor em graus.
 *
 */

double PercentEmGraus(double percent);



/** \brief Converte valor em graus para radianos.
 *
 * \param a[in] double angulo;
 *
 * \return Valor em radianos.
 *
 */

double RadianoParaGraus(double rad);



/** \brief Imprime um texto na tela nas coordenadas x e y;
 *
 * \param [in] char* str: Ponteira para a string que deseja imprimir;
 * \param [in] double x: Coordenada x;
 * \param [in] double y: Coordenada y;
 *
 * \return Nada.
 *
 */

void PrintString (char* str, double x, double y);



/** \brief Desenha uma grafico em colunas de 4 variáveis;
 * As valores em '%' das colunas do gráfico são definidos no vetor \sa DATA.
 */

void gpDrawColumn (void);


#include "defines.h"
#include <stdio.h>
#include <math.h>

#include "../src/graphics.cpp"

#endif // GRAPHICS_H_INCLUDED
