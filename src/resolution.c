/******************************************************************************
 *
 * Nome do Ficheiro: resolution.c
 *	                 (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Resolve o puzzle
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "metGauss.h"
#include "solFinder.h"
#include "defs.h"
#include "error.h"

/******************************************************************************
 * allocMatrix()
 *
 * Valores de entrada: solution - ponteiro da estrutura de dados do puzzle
 *                     solver - ponteiro da estrutura de dados da matrix resolvente
 * Valores de saída: solver - ponteiro da estrutura de dados da matrix resolvente
 * Descrição: Aloca a estrutura de dados da matrix resolvente
 *****************************************************************************/

matrix *allocMatrix(vector *solution,matrix *solver)
{
  int aux;

  solver=(matrix*)malloc(sizeof(matrix));
  solver->i=solution->t;
  solver->j=solution->b+1;
  solver->Ab=(int**)calloc(solver->i,sizeof(int*));
  for(aux=0;aux<solver->i;aux++) solver->Ab[aux]=(int*)calloc(solver->j,sizeof(int));
  for(aux=0;aux<2;aux++) solver->b[aux]=(int*)calloc(solver->j,sizeof(int));

  return solver;
}

/******************************************************************************
 * completeVector()
 *
 * Valores de entrada: solution - ponteiro da estrutura de dados do puzzle
 *                     solver - ponteiro da estrutura de dados da matrix resolvente
 *                     vIndep - vector com a solução da matriz resolvente
 * Valores de saída: solution - ponteiro da estrutura de dados do puzzle
 * Descrição: Finaliza o preenchimento da estrutura de dados do puzzle
 *****************************************************************************/

vector *completeVector(vector *solution,matrix *solver,int *vIndep)
{
  int aux_j;

  for(aux_j=0;aux_j<solver->j-1;aux_j++) solution->info[solver->b[I][aux_j]][solver->b[J][aux_j]]=vIndep[aux_j];
  solution->sol=1;

  return solution;
}

/******************************************************************************
 * freeMatrix()
 *
 * Valores de entrada: m - ponteiro da estrutura de dados da matrix resolvente
 * Valores de saída: NULL
 * Descrição: Liberta a estrutura de dados da matrix resolvente
 *****************************************************************************/

matrix *freeMatrix(matrix *m)
{
  int aux;

  for(aux=0;aux<m->i;aux++) free(m->Ab[aux]);
  free(m->Ab);
  free(m->b[0]);
  free(m->b[1]);
  free(m);

  return NULL;
}

/******************************************************************************
 * fillMatrix()
 *
 * Valores de entrada: solution - ponteiro da estrutura de dados do puzzle
 *                     solver - ponteiro da estrutura de dados da matrix resolvente
 * Valores de saída: solver - ponteiro da estrutura de dados da matrix resolvente
 * Descrição: Preenche a estrutura de dados da matrix resolvente
 *****************************************************************************/

matrix *fillMatrix(vector *solution,matrix *solver)
{
  int t=-1,i,j,b=0,**aux,upper=0,lower=0;

  aux=solution->info;
  for(i=0;i<solution->i;i++) for(j=0;j<solution->j;j++)
  {
    if(solution->info[i][j]%100<0)
    {
      t++;
      solver->Ab[t][solver->j-1]=-solution->info[i][j]%100;
      upper+=solver->Ab[t][solver->j-1];
    }
    if(solution->info[i][j]>0)
    {
      solver->b[I][b]=i;
      solver->b[J][b]=j;
      aux[i][j]=b+1;
      solver->Ab[t][b]=1;
      b++;
    }
  }
  for(j=0;j<solution->j;j++) for(i=0;i<solution->i;i++)
  {
    if(solution->info[i][j]/100!=0)
    {
      t++;
      solver->Ab[t][solver->j-1]=-solution->info[i][j]/100;
      lower+=solver->Ab[t][solver->j-1];
    }
    if(aux[i][j]>0) solver->Ab[t][aux[i][j]-1]=1;
  }
  if(lower!=upper)
  {
    solver=freeMatrix(solver);
    solution->sol=0;
  }

  return solver;
}

/******************************************************************************
 * resolution()
 *
 * Valores de entrada: problem - ponteiro da estrutura de dados do puzzle
 * Valores de saída: solution - ponteiro da estrutura de dados do puzzle
 * Descrição: Interface do resolution.c
 *****************************************************************************/

vector *resolution(vector *solution)
{
  int *vIndep;
  matrix *solver=NULL, *Morig=NULL;

  solver=allocMatrix(solution,solver);
  solver=fillMatrix(solution,solver);
  if(solver==NULL) return solution;
  Morig=copiaMatrix(solver);
  vIndep=metGauss(solution,solver);
  if(solution->sol==0) return solution;
  vIndep=solFinder(vIndep,solver,Morig);
  solution=completeVector(solution,solver,vIndep);
  free(vIndep);
  solver=freeMatrix(solver);
  Morig=freeMatrix(Morig);

  return solution;
}
