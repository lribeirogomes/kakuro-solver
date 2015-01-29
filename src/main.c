/******************************************************************************
 *
 * File Name: main.c
 *	      (c) 2012 AED
 * Authors:    ist172942 Gerardo Lima;
 *             ist172904 Luís Gomes;
 * Last modified: ACR 2012-10-30
 * resolutionision:  v2.0
 *
 * COMMENTS
 *		Main/trigger program
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "resolution.h"
#include "defs.h"
#include "error.h"

/******************************************************************************
 * input()
 *
 * Valores de entrada: argc - número de ponteiros de string's do terminal
 *                     argv - tabela de ponteiros de string's do terminal
 * Valores de saída: v - ponteiro da estrutura de dados do puzzle
 * Descrição: Interface do input.c
 *****************************************************************************/

vector *input(char *s,vector *v)
{
  FILE *f;

  f=openFile(s);
  v=addMap(f,v);
  v=inputMap(f,v);
  v=modMap(v);
  v=sortMap(v);
  readMap(v);
  fclose(f);

  return v;
}

/******************************************************************************
 * resolution ()
 *
 * Arguments: v - pointer of the v node
 * Returns: node
 * Side-Effects: none
 * Description: resolution main Program
 *****************************************************************************/

vector *resolution(vector *v)
{
  int sol;
  FILE *teste;

  teste=fopen("teste.teste","w+");
  sol=generatev(v,v->iprior[0],v->jprior[0],CIMA,teste);
  fprintf(teste,"\n\n%d\n\n",sol);
  fclose(teste);

  return v;
}

/******************************************************************************
 * foput()
 *
 * Valores de entrada: v - ponteiro da estrutura de dados do puzzle
 * Valores de saída: NULL (v)
 * Descrição: Interface do foput.c
 *****************************************************************************/

vector *output(char *s,vector *v)
{
  FILE *fo,*fi;

  fi=openFile(s);
  fo=addFile(s);
  copyFile(fo,fi);
  if(v->sol==1) outputMap(fo,v);
  fclose(fo);
  fclose(fi);
  v=freeMap(v);

  return v;
}

/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * Returns: int
 * Side-Effects: none
 * Description: main Program
 *****************************************************************************/

int main(int argc, char **argv)
{
  vector *v=NULL;

  printf("Projecto de AED : KAKURO\nPrograma de Luís Gomes e Gerardo Lima\n");
  printf("\n\n(Clique em qualquer tecla para começar)\n");
  getchar();
  printf("\nComeçar Programa KAKURO\n");
  if(argc==1) error(ARGV);
  v=input(argv[1],v);
  v=resolution(v);
  v=output(argv[1],v);
  printf("\nPrograma KAKURO Concluído\n");

  exit(0);
}
