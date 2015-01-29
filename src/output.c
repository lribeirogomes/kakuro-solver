/******************************************************************************
 *
 * Nome do Ficheiro: output.c
 *	                 (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Envia o resultado do puzzle para um ficheiro .sol
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "input.h"
#include "defs.h"

/******************************************************************************
 * fillFile()
 *
 * Valores de entrada: namefile - tabela de ponteiros de string's do terminal
 * Valores de saída: file - ponteiro do ficheiro .sol
 * Descrição: Abre o ficheiro .sol
 *****************************************************************************/

FILE *createFile(char *namefile){
  FILE *file;
  char *address;

  address=strtok(namefile,".");
  strcat(address,".sol");
  if(strcmp(address,".sol")==0) error(TIPOFICHEIRO);
  file=fopen(namefile,"w+");
  if(file==NULL) error(FICHEIRO);

  return file;
}

/******************************************************************************
 * fillFile()
 *
 * Valores de entrada: fileIn - ponteiro do ficheiro .cfg
 *                     fileOut - ponteiro do ficheiro .sol
 * Valores de saída: (nenhum)
 * Descrição: Copia conteúdo do ficheiro .cfg para o ficheiro .sol
 *****************************************************************************/

void copyFile(FILE *fileOut,FILE *fileIn){
  char *copy;
  int size,MAX_SIZE;

  fscanf(fileIn,"%d",&size);
  fprintf(fileOut,"%d\n",size);
  fscanf(fileIn,"%d",&size);
  fprintf(fileOut,"%d",size);

  MAX_SIZE=size*5;
  copy=(char*)calloc(MAX_SIZE,sizeof(char));
  while(fgets(copy,MAX_SIZE,fileIn)!=NULL) fprintf(fileOut,"%s",copy);
  free(copy);

  return;
}

/******************************************************************************
 * fillFile()
 *
 * Valores de entrada: fileOut - ponteiro do ficheiro .sol
 *                   solution - ponteiro da estrutura de dados do puzzle
 * Valores de saída: (nenhum)
 * Descrição: Finaliza o preenchimento do ficheiro .sol
 *****************************************************************************/

void fillFile(FILE *fileOut,vector *solution){
  int aux,j;

  for(aux=0;aux<solution->i;aux++,fprintf(fileOut,"\n")) for(j=0;j<solution->j;j++)
  {
    if(solution->info[aux][j]>0) fprintf(fileOut,"%d",solution->info[aux][j]);
    else fprintf(fileOut,"-");
    if(j<solution->j-1) fprintf(fileOut,":");
  }
  fprintf(fileOut,"\n");

  return;
}

/******************************************************************************
 * freeVector()
 *
 * Valores de entrada: v - ponteiro da estrutura de dados do puzzle
 * Valores de saída: NULL
 * Descrição: Liberta a estrutura de dados do puzzle
 *****************************************************************************/

vector *freeVector(vector *v)
{
  int i;

  for(i=0;i<v->i;i++) free(v->info[i]);
  free(v->info);
  free(v);

  return NULL;
}

/******************************************************************************
 * output()
 *
 * Valores de entrada: solution - ponteiro da estrutura de dados do puzzle
 * Valores de saída: NULL (solution)
 * Descrição: Interface do output.c
 *****************************************************************************/

vector *output(char *namefile,vector *solution)
{
  FILE *fileOut,*fileIn;

  fileIn=openFile(namefile);
  fileOut=createFile(namefile);
  copyFile(fileOut,fileIn);
  if(solution->sol==1) fillFile(fileOut,solution);
  fclose(fileOut);
  fclose(fileIn);
  solution=freeVector(solution);

  return solution;
}
