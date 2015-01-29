/*****************************************************************************
 *
 * Nome do Ficheiro: metGauss.h
 *                   (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Header do metGauss.c
 *
 *****************************************************************************/

#ifndef METGAUSS_H_INCLUDED
#define METGAUSS_H_INCLUDED

#include "defs.h"

void KLa(float K, int * La, matrix * M);
void troca_La_Lb(int * La, int * Lb, matrix * M);
void La_mais_KLb(float K, int * La, int * Lb, matrix * M);
int grau(int * L, matrix * M);
void sortLines(matrix * M);
void arrumaLinhas(int j, matrix * M);
void escada(matrix * M);
void escadaReduzida(matrix * M);
int * tipomatrix(vector *solution,matrix *M);
int* metGauss(vector *solution,matrix * M);

#endif
