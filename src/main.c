/******************************************************************************
 *
 * Nome do Ficheiro: main.c
 *	                 (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Interface do programa
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "resolution.h"
#include "output.h"
#include "error.h"

/******************************************************************************
 * main()
 *
 * Valores de entrada: argc - número de ponteiros de string's do terminal
 *                     argv - tabela de ponteiros de string's do terminal
 * Valores de saída: exit(0)
 * Descrição: Interface principal
 *****************************************************************************/

int main(int argc, char **argv)
{
  vector *kakuro=NULL;

  if(argc==1) error(ARGV);
  kakuro=input(argv[1],kakuro);
  kakuro=resolution(kakuro);
  kakuro=output(argv[1],kakuro);

  exit(0);
}
