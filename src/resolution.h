/******************************************************************************
 *
 * Nome do Ficheiro: resolution.h
 *	                 (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Header do resolution.c
 *
 *****************************************************************************/

#ifndef RESOLUTION_H_INCLUDED
#define RESOLUTION_H_INCLUDED

#include "defs.h"

matrix *allocMatrix(vector *solution,matrix *solver);
matrix *fillMatrix(vector *solution,matrix *solver);
vector *completeVector(vector *solution,matrix *solver,int *vIndep);
matrix *freeMatrix(matrix *m);

vector *resolution(vector *solution);

#endif
