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

#define I 0
#define J 1

#define PALAVRASIZE 50
#define LINHASIZE 200

#define ARGV 1
#define TIPOFICHEIRO 2
#define FICHEIRO 3
#define LINHA 5
#define COLUNA 6
#define LEITURA 7
#define SOMA 8
#define CONSTANTE 9
#define ALLOC 10

typedef struct vector {int i,j,b,t,sol,**info;} vector;
typedef struct matrix {int i,j,**Ab,*b[2];} matrix;

#endif
