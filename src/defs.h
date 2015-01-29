/******************************************************************************
 *
 * Nome do Ficheiro: defs.h
 *	                 (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Define as estruturas de dados do programa
 *
 *****************************************************************************/

#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define LOWER 0
#define UPPER 1

#define PALAVRASIZE 50
#define LINHASIZE 200

#define CIMA 0
#define BAIXO 1
#define ESQUERDA 2
#define DIREITA 3

#define ARGV 1
#define TIPOFICHEIRO 2
#define FICHEIRO 3
#define LINHA 4
#define COLUNA 5
#define LEITURA 6
#define SOMA 7
#define ALLOC 8

#define PRIORLIMIT (100*v->i+v->j)


typedef struct vector {int i,j,sol,**info,*prior,*iprior,*jprior,cprior;} vector;

FILE *openFile(char *s);
FILE *addFile(char *s);
void copyFile(FILE *fo,FILE *fi);

vector *addMap(FILE *file,vector *v);
vector *inputMap(FILE *file,vector *v);
vector *modMap(vector *v);
vector *sortMap(vector *v);
void readMap(vector *v);
void outputMap(FILE *fo,vector *v);
vector *freeMap(vector *v);

#endif // DEFS_H_INCLUDED
