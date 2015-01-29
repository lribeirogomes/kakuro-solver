/*****************************************************************************
 *
 * Nome do Ficheiro: solFinder.h
 *                   (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Header do solFinder.c
 *
 *****************************************************************************/


#ifndef SOLFINDER_H_INCLUDED
#define SOLFINDER_H_INCLUDED

#include "defs.h"

matrix * copiaMatrix(matrix * M);
int * geraVar(int * vIndep, int inc, matrix * M);
int * calculaVar(int * vIndep, int * vDepOrig, int * vSol, matrix * M);
int pDominio(int * vSol, matrix * M, int * inc);
int pSum(matrix * M,int * vSol, matrix * Morig);
void sortVector(int * L, matrix * M);
int pAlldiferent(matrix * M,int * vSol, matrix * Morig);
int *solFinder(int * vIndep ,matrix * M,matrix * Morig);

#endif
