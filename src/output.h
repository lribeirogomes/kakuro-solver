/******************************************************************************
 *
 * Nome do Ficheiro: output.h
 *	                 (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Header do output.c
 *
 *****************************************************************************/

#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "defs.h"

FILE *createFile(char *namefile);
void copyFile(FILE *fileOut,FILE *fileIn);
void fillFile(FILE *fileOut,vector *solution);
vector *freeVector(vector *solution);
vector *output(char *namefile,vector *solution);

#endif
