/******************************************************************************
 *
 * Nome do Ficheiro: input.h
 *	                 (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Header do input.c
 *
 *****************************************************************************/

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "defs.h"

FILE *openFile(char *namefile);
vector *allocVector(FILE *file,vector *problem);
vector *fillVector(FILE *file,vector *problem);
vector *input(char *namefile,vector *problem);

#endif
