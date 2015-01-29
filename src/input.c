/******************************************************************************
 *
 * Nome do Ficheiro: input.c
 *	                 (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Transfere dados do ficheiro .cfg para o programa
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "error.h"

/******************************************************************************
 * openFile()
 *
 * Valores de entrada: namefile - tabela de ponteiros de string's do terminal
 * Valores de saída: file - ponteiro do ficheiro .cfg
 * Descrição: Abre o ficheiro .cfg
 *****************************************************************************/

FILE *openFile(char *namefile)
{
  FILE *file;
  char address[strlen(namefile)];

  strcpy(address,namefile);
  strtok(address,".");
  if(strcmp(address,".cfg")==0) error(TIPOFICHEIRO);
  file=fopen(namefile,"r");
  if(file==NULL) error(FICHEIRO);

  return file;
}

/******************************************************************************
 * allocVector()
 *
 * Valores de entrada: file - ponteiro do ficheiro .cfg
 *                     problem - ponteiro da estrutura de dados do puzzle
 * Valores de saída: problem - ponteiro da estrutura de dados do puzzle
 * Descrição: Aloca a estrutura de dados do puzzle
 *****************************************************************************/

vector *allocVector(FILE *file,vector *problem)
{
  int aux;

  problem=(vector*)malloc(sizeof(vector));
  fscanf(file,"%d",&problem->i);
  fscanf(file,"%d",&problem->j);
  if(problem->i<=1) error(LINHA);
  problem->info=(int**)calloc(problem->i,sizeof(int*));
  if(problem->j<=1) error(COLUNA);
  for(aux=0;aux<problem->i;aux++) problem->info[aux]=(int*)calloc(problem->j,sizeof(int));

  return problem;
}

/******************************************************************************
 * fillNode()
 *
 * Valores de entrada: file - ponteiro do ficheiro .cfg
 *                     problem - ponteiro da estrutura de dados do puzzle
 * Valores de saída: problem - ponteiro da estrutura de dados do puzzle
 * Descrição: Preenche a estrutura de dados do puzzle
 *****************************************************************************/

vector *fillVector(FILE *file,vector *problem)
{
  int MAX_LINE=problem->j*5,i,j;
  char line[MAX_LINE],*code;

  problem->b=0;
  problem->t=0;
  problem->sol=0;
  for(i=0;i!=3;i++) fgets(line,MAX_LINE,file);
  for(i=0;i<problem->i;fgets(line,MAX_LINE,file),i++)
    for(j=0,code=strtok(line,":");code!=NULL;code=strtok(NULL,":"),j++)
      switch(code[0])
      {
        case '-':problem->info[i][j]=1;
                 problem->b++;
                 break;
        case '0':problem->info[i][j]=0;
                 break;
        default:problem->info[i][j]=-atoi(code);
                if(problem->info[i][j]/100<0) problem->t++;
                if(problem->info[i][j]%100<0) problem->t++;
                break;
      }
  if(fgets(line,MAX_LINE,file)!=NULL) error(LEITURA);

  return problem;
}

/******************************************************************************
 * input()
 *
 * Valores de entrada: argc - número de ponteiros de string's do terminal
 *                     argv - tabela de ponteiros de string's do terminal
 * Valores de saída: problem - ponteiro da estrutura de dados do puzzle
 * Descrição: Interface do input.c
 *****************************************************************************/

vector *input(char *namefile,vector *problem)
{
  FILE *file;

  file=openFile(namefile);
  problem=allocVector(file,problem);
  problem=fillVector(file,problem);
  fclose(file);

  return problem;
}
