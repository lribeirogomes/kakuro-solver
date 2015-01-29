/*****************************************************************************
 *
 * Nome do Ficheiro: metGauss.c
 *                   (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Aplica o método de Gauss
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "resolution.h"
#include "defs.h"
#include "error.h"

/******************************************************************************
 * KLa()
 *
 * Descrição:  multiplica linha La por uma constante K
 *****************************************************************************/

void KLa(float K, int * La, matrix * M)
{
  int aux;

  if(K==0) error(CONSTANTE);
  for(aux=0;aux<(M->j);aux++) La[aux]=La[aux]*K;
}

/******************************************************************************
 * troca_La_Lb();
 *
 * Descrição: troca a linha La pela linha Lb
 *****************************************************************************/

void troca_La_Lb(int * La, int * Lb, matrix * M)
{
  int *auxL,aux;

  auxL=calloc(M->j,sizeof(int));
  if(auxL==NULL) error(ALLOC);
  for(aux=0;aux<(M->j);aux++) auxL[aux]=La[aux];
  for(aux=0;aux<(M->j);aux++) La[aux]=Lb[aux];
  for(aux=0;aux<(M->j);aux++) Lb[aux]=auxL[aux];
  free(auxL);
}

/******************************************************************************
 * La_mais_KLb()
 *
 * Descrição: adiciona a linha Lb a linha La multiplicada por uma constante K
 *****************************************************************************/

void La_mais_KLb(float K, int * La, int * Lb, matrix * M){
  int *auxL,aux;

  if(K==0) error(CONSTANTE);
  auxL=calloc(M->j,sizeof(int));
  if(auxL==NULL) error(ALLOC);
  for(aux=0;aux<(M->j);aux++) auxL[aux]=Lb[aux];
  for(aux=0;aux<(M->j);aux++) auxL[aux]=auxL[aux]*K;
  for(aux=0;aux<(M->j);aux++) La[aux]=La[aux]+auxL[aux];
  free(auxL);
}

/******************************************************************************
 * grau()
 *
 * Descrição:
 *****************************************************************************/

int grau(int * L, matrix * M)
{
  int j;

  for(j=0;j<(M->j)-1;j++) if(L[j]!=0) break;

  return j;
}

/******************************************************************************
 * sort()
 *
 * Descrição: arruma linhas pelo seus graus
 *****************************************************************************/

void sortLines(matrix * M)
{
  int iE,iI,aux;

  for(iE=0;iE<(M->i)-1;iE++)
  {
    for(iI=(M->i)-1,aux=iE;iI>iE;iI--) if(grau(M->Ab[iI], M)<grau(M->Ab[aux], M)) aux=iI;
    troca_La_Lb(M->Ab[aux],M->Ab[iE],M);
  }
}

/******************************************************************************
 * arrumaLinhas()
 *
 * Descrição: se houver numeros diferentes de zero debaixo da diagonal e pivo==0 troca as respectivas linhas
 *****************************************************************************/

void arrumaLinhas(int j, matrix *M)
{
  int i;

  for(i=j+1;i<(M->i);i++) if(M->Ab[i][j]!=0)
  {
    troca_La_Lb(M->Ab[j],M->Ab[i],M);
    break;
  }
}

/******************************************************************************
 * escada()
 *
 * Descrição:
 *****************************************************************************/

void escada(matrix * M)
{
  int i,j,iI;

  for(i=0,j=0; i<(M->i)-1; i++,j++)
  {
    sortLines(M);
    switch(M->Ab[i][j])
    {
      case 0:arrumaLinhas(i, M);
             break;
      case 1:break;
      default:KLa(1/(M->Ab[i][j]),M->Ab[i],M);
              break;
    }
    if(M->Ab[i][j]==0) i--;
    else
    {
      for(iI=(M->i)-1;iI>i;iI--) if(M->Ab[iI][j]!=0) La_mais_KLb(-(M->Ab[iI][j])/(M->Ab[i][j]),M->Ab[iI],M->Ab[i],M);
      if(M->Ab[i][j]<0) KLa(-1,M->Ab[i],M);
    }
  }
}

/******************************************************************************
 * escadaReduzida()
 *
 * Descrição: trasforma matrix em escada para escada reduzida
 *****************************************************************************/

void escadaReduzida(matrix * M)
{
  int i,j,iI;

  for(i=0,j=0 ; i<(M->i)-1 ; i++,j++) if(M->Ab[i][j]!=0)
  {
    for(iI=0;iI<i;iI++) if(M->Ab[iI][j]!=0)
      La_mais_KLb(-(M->Ab[iI][j])/(M->Ab[i][j]),M->Ab[iI],M->Ab[i],M);
  }
  else i--;
}

/******************************************************************************
 * tipomatrix()
 *
 * Descrição:possivel/impossivel? determinada/indeterminada?
 *****************************************************************************/

int * tipomatrix(vector *solution,matrix *M)
{
  int i,j,cont=0,*vIndep;

  vIndep=calloc((M->j),sizeof(int));
  if(vIndep==NULL) error(ALLOC);
  for(i=0,cont=0;i<(M->i);i++)
  {
    for(j=0;j<(M->j);j++)  if(M->Ab[i][j]!=0) cont++;
    if((cont==1) && (M->Ab[i][(M->j)-1])!=0) return NULL;
  }
  for(i=0,j=0,cont=0 ; i<(M->i)&&(j<M->j-1) ; i++,j++) if(M->Ab[i][j]==0)
  {
    solution->sol++;
	vIndep[j]=1;
	i--;
  }
  if(solution->sol==0) M=freeMatrix(M);

  return vIndep;
}

/******************************************************************************
 * metGauss()
 *
 * Descrição:
 *****************************************************************************/
int* metGauss(vector *solution,matrix * M)
{
  int* vIndep;

  escada(M);
  escadaReduzida(M);
  vIndep=tipomatrix(solution,M);


  return vIndep;
}
