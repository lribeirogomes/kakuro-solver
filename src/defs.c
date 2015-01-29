/******************************************************************************
 *
 * Nome do Ficheiro: defs.c
 *	                 (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Define as estruturas de dados do programa
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "defs.h"

#define PRINT

/******************************************************************************
 * openFile()
 *
 * Valores de entrada: s - tabela de ponteiros de string's do terminal
 * Valores de saída: file - ponteiro do ficheiro .cfg
 * Descrição: Abre o ficheiro .cfg
 *****************************************************************************/

FILE *openFile(char *s)
{
  FILE *file;
  char *address;

  address=(char*)calloc(strlen(s)+6,sizeof(char));
  strcpy(address,"Dados/");
  strcat(address,s);
  if(strstr(address,".cfg")==0) error(TIPOFICHEIRO);
  file=fopen(address,"r");
  if(file==NULL) error(FICHEIRO);

  return file;
}

/******************************************************************************
 * outputMap()
 *
 * Valores de entrada: s - tabela de ponteiros de string's do terminal
 * Valores de saída: file - ponteiro do ficheiro .sol
 * Descrição: Abre o ficheiro .sol
 *****************************************************************************/

FILE *addFile(char *s){
  FILE *file;
  char *address, type[4];
  int aux;

  strcpy(type,".sol");
  address=(char*)calloc(strlen(s)+6,sizeof(char));
  strcpy(address,"Dados/");
  strcat(address,s);
  for(aux=4;aux!=0;aux--)
    address[strlen(address)-aux]=type[4-aux];
  file=fopen(address,"w+");
  if(file==NULL) error(FICHEIRO);

  return file;
}

/******************************************************************************
 * outputMap()
 *
 * Valores de entrada: in - ponteiro do ficheiro .cfg
 *                     fo - ponteiro do ficheiro .sol
 * Valores de saída: (nenhum)
 * Descrição: Copia conteúdo do ficheiro .cfg para o ficheiro .sol
 *****************************************************************************/

void copyFile(FILE *fo,FILE *fi){
  char *copy;
  int size,MAX_SIZE;

  fscanf(fi,"%d",&size);
  fprintf(fo,"%d\n",size);
  fscanf(fi,"%d",&size);
  fprintf(fo,"%d",size);

  MAX_SIZE=size*5;
  copy=(char*)calloc(MAX_SIZE,sizeof(char));
  while(fgets(copy,MAX_SIZE,fi)!=NULL)
    fprintf(fo,"%s",copy);

  return;
}

/******************************************************************************
 * addMap()
 *
 * Valores de entrada: file - ponteiro do ficheiro .cfg
 *                     v - ponteiro da estrutura de dados do puzzle
 * Valores de saída: v - ponteiro da estrutura de dados do puzzle
 * Descrição: Aloca a estrutura de dados do puzzle
 *****************************************************************************/

vector *addMap(FILE *file,vector *v)
{
  int aux;

  v=(vector*)malloc(sizeof(vector));
  fscanf(file,"%d",&v->i);
  fscanf(file,"%d",&v->j);
  if(v->i<=1) error(LINHA);
  v->info=(int**)calloc(v->i,sizeof(int));
  if(v->j<=1) error(COLUNA);
  for(aux=0;aux<v->i;aux++) v->info[aux]=(int*)calloc(v->j,sizeof(int));
  v->prior=(int*)calloc(aux=PRIORLIMIT,sizeof(int));
  v->iprior=(int*)calloc(aux,sizeof(int));
  v->jprior=(int*)calloc(aux,sizeof(int));

  return v;
}

/******************************************************************************
 * fillNode()
 *
 * Valores de entrada: file - ponteiro do ficheiro .cfg
 *                     v - ponteiro da estrutura de dados do puzzle
 * Valores de saída: v - ponteiro da estrutura de dados do puzzle
 * Descrição: Preenche a estrutura de dados do puzzle
 *****************************************************************************/

vector *inputMap(FILE *file,vector *v)
{
  int MAX_LINE=v->j*5,i,j;
  char line[MAX_LINE],*code;

  for(i=0;i!=3;i++) fgets(line,MAX_LINE,file);
  for(i=0;i<v->i;fgets(line,MAX_LINE,file),i++) for(j=0,code=strtok(line,":");code!=NULL;j++,code=strtok(NULL,":")) switch(code[0])
  {
    case '-':v->info[i][j]=10;
             break;
    case '0':v->info[i][j]=0;
             break;
    default:v->info[i][j]=-atoi(code);
            break;
  }
  if(fgets(line,MAX_LINE,file)!=NULL) error(LEITURA);

  return v;
}

vector *modMap(vector *v)
{
  int i,j,r=PRIORLIMIT,s,c;

  for(i=0;i!=r;i++) v->prior[i]=1000;
  for(i=0;i!=v->i;i++) for(j=0;j!=v->j;j++) if(v->info[i][j]==10)
  {
    s=100*i+j;
    if((i+1==v->i || v->info[i+1][j]!=10) && (j+1==v->j || v->info[i][j+1]!=10))
    {
      for(c=i,v->prior[s]=0;v->info[c][j]==10;c--,v->prior[s]++);
      for(c=j;v->info[i][c]==10;c--,v->prior[s]++);
    }
    if(i+1!=v->i && (j+1==v->j || v->info[i][j+1]!=10))
    {
      for(c=i;c+1!=v->i && v->info[c][j]==10;c++);
      for(c--,v->prior[s]=0;v->info[c][j]==10;c--,v->prior[s]++);
      for(c=j;v->info[i][c]==10;c--,v->prior[s]++);
    }
    if((i+1==v->i || v->info[i+1][j]!=10) && j+1!=v->j)
    {
      for(c=i,v->prior[s]=0;v->info[c][j]==10;c--,v->prior[s]++);
      for(c=j;c+1!=v->j && v->info[i][c]==10;c++);
      for(c--;v->info[i][c]==10;c--,v->prior[s]++);
    }
    v->iprior[s]=i;
    v->jprior[s]=j;
  }
  v->cprior=0;

  return v;
}

vector *sortMap(vector *v)
{
  int i,j,d,e,f,r=PRIORLIMIT;

  for(i=0;i!=r;i++) for(j=i;j!=r;j++)
  {
    if(v->prior[j]<v->prior[i])
    {
      d=v->prior[i];
      e=v->iprior[i];
      f=v->jprior[i];
      v->prior[i]=v->prior[j];
      v->iprior[i]=v->iprior[j];
      v->jprior[i]=v->jprior[j];
      v->prior[j]=d;
      v->iprior[j]=e;
      v->jprior[j]=f;
    }
  }

  return v;
}

/******************************************************************************
 * readMap()
 *
 * Valores de entrada: v - ponteiro da estrutura de dados do puzzle
 * Valores de saída: (nenhum)
 * Descrição: Descreve, no terminal, os dados do puzzle
 *****************************************************************************/

void readMap(vector *v)
{
#ifdef PRINT
  int i,j,r=PRIORLIMIT;

  printf("\n");
  for(i=0;i<v->i;i++,printf("\n")) for(j=0;j<v->j;j++)
  {
    printf("%5d",v->info[i][j]);
    if(j<v->j-1)printf(":");
  }
  printf("\n");
  for(i=0;i!=r;i++) if(v->prior[i]!=1000) printf("priority:%d i=%d j=%d priority level:%d\n",i+1,v->iprior[i]+1,v->jprior[i]+1,v->prior[i]);
  printf("\n");
#endif

  return;
}

/******************************************************************************
 * outputMap()
 *
 * Valores de entrada: fo - ponteiro do ficheiro .sol
 *                   v - ponteiro da estrutura de dados do puzzle
 * Valores de saída: (nenhum)
 * Descrição: Finaliza o preenchimento do ficheiro .sol
 *****************************************************************************/

void outputMap(FILE *fo,vector *v){
  int aux,j;

  for(aux=0;aux<v->i;aux++,fprintf(fo,"\n")) for(j=0;j<v->j;j++)
  {
    if(v->info[aux][j]>0) fprintf(fo,"%d",v->info[aux][j]);
    else fprintf(fo,"-");
    if(j<v->j-1) fprintf(fo,":");
  }
  fprintf(fo,"\n");

  return;
}

/******************************************************************************
 * freeMap()
 *
 * Valores de entrada: v - ponteiro da estrutura de dados do puzzle
 * Valores de saída: NULL
 * Descrição: Liberta a estrutura de dados do puzzle
 *****************************************************************************/

vector *freeMap(vector *v)
{
  int i;

  for(i=0;i<v->i;i++) free(v->info[i]);
  free(v->info);
  free(v->prior);
  free(v->iprior);
  free(v->jprior);
  free(v);

  return NULL;
}
