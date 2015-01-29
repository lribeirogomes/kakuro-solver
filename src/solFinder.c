/*****************************************************************************
 *
 * Nome do Ficheiro: solFinder.c
 *                   (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Dada a matrix do sistema, procura a solução do kakuro
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "resolution.h"
#include "defs.h"
#include "error.h"

/******************************************************************************
 * copiaMatrix()
 *
 * Descrição:
 ****************************************************************************/
matrix * copiaMatrix(matrix * M)
{
  matrix * Mcopy;
  int aux,i,j;

  Mcopy=(matrix*)calloc(1,sizeof(matrix));
  Mcopy->i=M->i;
  Mcopy->j=M->j;
  Mcopy->Ab=calloc(Mcopy->i,sizeof(int *));
  for(aux=0; aux<Mcopy->i;aux++)  Mcopy->Ab[aux]=calloc(Mcopy->j,sizeof(int));
  for(i=0;i<(M->i);i++)for(j=0;j<(M->j);j++) Mcopy->Ab[i][j] = M->Ab[i][j];

  return Mcopy;
}

/******************************************************************************
 * geraVar()
 *
 * Descrição:  atribui as variaveis independentes uma combinação dep. de inc
 *****************************************************************************/

int * geraVar(int * vIndep, int inc, matrix * M)
{
  int i,aux,first;

  for(first=0;first<(M->j)-1;first++)if(vIndep[first]){break;}
  while(inc)
  {
	if(vIndep[first]<9)
	{
      vIndep[first]++;
      inc--;
	}
	else
	{
      vIndep[first]=1;
      for(i=first+1;i<(M->j)-1;i++) if(vIndep[i]) break;
      for(aux=inc; inc!=aux-1 ; )
      {
        if(vIndep[i]<9)
        {
          vIndep[i]++;
          inc--;
        }
        else
        {
          vIndep[i]=1;
        }
        for(i++;i<(M->j)-1;i++) if(vIndep[i]) break;
      }
	}
  }

  return vIndep;
}

/******************************************************************************
 * calculaVar()
 *
 * Descrição: calcula vSol em função das vIndep e vDep
 *****************************************************************************/

int * calculaVar(int * vIndep, int * vDepOrig, int * vSol, matrix * M)
{
  int i, j, aux,*vDep,nIndep=(M->j)-(M->i);

  vDep = calloc((M->j)-nIndep,sizeof(int));
  if(vDep==NULL)error(ALLOC);
  for(i=0;i<(M->i);i++)vDep[i]=vDepOrig[i];
  for(i=0;i<(M->i);i++) for(j=0;j<(M->j)-1;j++) if(vIndep[j]!=0) vDep[i] = vDep[i] - M->Ab[i][j]*vIndep[j];
  for(j=0,aux=0;j<(M->j)-1;j++)if(vIndep[j]==0)
  {
    vSol[j]=vDep[j-aux];
  }
  else
  {
    vSol[j]=vIndep[j];
    aux++;
  }
  free(vDep);

  return vSol;
}

/******************************************************************************
 * pDominio()
 *
 * Descrição: verifica se sol's pertencem a [1,9], e retorna modulo de avanço
 *****************************************************************************/

int pDominio(int *vSol,matrix *M,int *inc)
{
  int j,possible=1;

  *inc=1;
  for(j=0;j<(M->j)-1;j++) if((vSol[j]<1)||(vSol[j]>9))
  {
    possible=0;
    if(vSol[j]<1)
    {
      if(1-vSol[j]>*inc) *inc=(1-vSol[j]);
    }
    else
    {
      if(vSol[j]-9>*inc) *inc=(vSol[j]-9);
    }
  }

  return possible;
}

 /******************************************************************************
 * pSum()
 *
 * Descrição:  verifica parametro da soma
 na matrix Original substitui valores de vSol na resp. coluna ----->depois noutro ciclo  soma o valor das linhaas e compara com o fim da linha
 *****************************************************************************/

int pSum(matrix *M,int *vSol, matrix *Morig)
{
  int somaL,j,i;
  matrix *Maux;

  Maux = copiaMatrix(Morig);
  for(j=0;j<(M->j)-1;j++) for(i=0;i<(M->i);i++) Maux->Ab[i][j]=Maux->Ab[i][j]*vSol[j];
  for(i=0,somaL=0;i<(M->i);i++,somaL=0)
  {
    for(j=0;j<(M->j)-1;j++) somaL+=Maux->Ab[i][j];
    if(somaL!= Maux->Ab[i][(M->j)-1])
    {
      Maux=freeMatrix(Maux);
      return 0;
    }
  }
  Maux=freeMatrix(Maux);

  return 1;
}

 /******************************************************************************
 * void sortVector()
 *
 * Descrição:  arruma vector de inteiros pelo tamanho dos seus elementos
 *****************************************************************************/

void sortVector(int *L,matrix *M)
{
  int jE,jI,aux;

  for(jE=0;jE<(M->j)-1;jE++) for(jI=(M->j)-2;jI>jE;jI--) if(L[jI] < L[jE])
  {
    aux=L[jI];
    L[jI]=L[jE];
    L[jE]=aux;
  }
}

 /******************************************************************************
 * pAlldiferent()
 *
 * Descrição:  verifica parametro Alldiferent
 *****************************************************************************/

int pAlldiferent(matrix * M,int * vSol, matrix * Morig)
{
  matrix * Maux;
  int i,j;

  Maux= copiaMatrix(Morig);
  for(j=0;j<(M->j)-1;j++) for(i=0;i<(M->i);i++) Maux->Ab[i][j]*=vSol[j];
  for(i=0;i<(M->i);i++) sortVector(Maux->Ab[i],M);
  for(i=0;i<(M->i);i++) for(j=0;j<(M->j)-2;j++) if((Maux->Ab[i][j]==Maux->Ab[i][j+1])&&(Maux->Ab[i][j]!=0))
  {
    Maux=freeMatrix(Maux);
    return 0;
  }
  Maux=freeMatrix(Maux);

  return 1;
}

/******************************************************************************
 * solFinder()
 *
 * Descrição:  dada a matrix do sistema procura a solução do kakuro
 *****************************************************************************/

int *solFinder(int * vIndep ,matrix * M,matrix * Morig)
{
  int i,j,nIndep=(M->j)-(M->i),aux,inc,*vDepOrig,*vSol;

  vDepOrig=calloc((M->j)-nIndep,sizeof(int));
  if(vDepOrig==NULL)error(ALLOC);
  for(i=0,j=0,aux=0;j<(M->j)-1;i++,j++) if(vIndep[j]==0)
  {
    vDepOrig[j-aux]=M->Ab[i][(M->j)-1];
  }else{
    aux++;
    i--;
  }
  vSol=calloc((M->j)-1,sizeof(int));
  if(vSol==NULL) error(ALLOC);
  for(aux=0,inc=1;1;aux++)
  {
    vIndep=geraVar(vIndep,inc,M);
    inc=1;
    vSol=calculaVar(vIndep,vDepOrig,vSol,M);
    if(pDominio(vSol,M,&inc)) if(pSum(M,vSol,Morig)) if(pAlldiferent(M,vSol,Morig)) break;
  }
  free(vDepOrig);
  free(vIndep);

  return vSol;
}
