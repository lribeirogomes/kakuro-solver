/******************************************************************************
 *
 * File Name: resolution.c
 *	      (c) 2012 AED
 * Authors:    ist172942 Gerardo Lima;
 *             ist172904 Luís Gomes;
 * Last modified: ACR 2012-10-30
 * resolutionision:  v1.1
 *
 * COMMENTS
 *		resolution subsistem
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "error.h"
#include "resolution.h"

int searchSeed(vector *v,int *i,int *j)
{
  v->cprior++;
  if(v->prior[v->cprior]==1000)
  {
    v->sol=1;
    return 1;
  }
  *i=v->iprior[v->cprior];
  *j=v->jprior[v->cprior];

  return 0;
}

int diferentValue(vector *v,int i,int j,int info)
{
  int aux;

  for(aux=i;aux!=v->i && v->info[aux][j]>0;aux++) if(info==v->info[aux][j]) return 0;
  for(aux=j;aux!=v->j && v->info[i][aux]>0;aux++) if(info==v->info[i][aux]) return 0;
  for(aux=i;v->info[aux][j]>0;aux--) if(info==v->info[aux][j]) return 0;
  for(aux=j;v->info[i][aux]>0;aux--) if(info==v->info[i][aux]) return 0;

  return 1;
}

int generatev(vector *v,int i,int j,int seta,FILE *teste)
{
  int info;
  char x;

  if(i==-1 || i==v->i || j==-1 || j==v->j)
  {
    fprintf(teste,"está no limite [%d][%d]\n",i+1,j+1);
    return 0;
  }

/*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/

  if(v->info[i][j]<0)
  {
    int aux,sum=0,newseedi,newseedj;
/*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/

    if(seta==CIMA)
    {
      fprintf(teste,"está numa triangular inferior [%d][%d] - ",i+1,j+1);
      for(aux=i+1;v->info[aux][j]<11 && v->info[aux][j]>0;aux++)
      {
        sum+=v->info[aux][j];
        if(aux+1==v->i) break;
      }
      fprintf(teste,"([%d][%d]) -- info=%d sum=%d\n",i+1,j+1,-v->info[i][j]/100,sum);
      if(sum==-v->info[i][j]/100)
      {
        fprintf(teste,"soma correcta: soma:%d == triangular:%d\n",sum,-v->info[i][j]/100);
        fprintf(teste,"\n");
        scanf("%c",&x);
        readMap(v);
        printf("soma correcta: soma:%d == triangular:%d\n",sum,-v->info[i][j]/100);

        if(searchSeed(v,&newseedi,&newseedj)==1) return 1;
        v->cprior++;
        newseedi=v->iprior[v->cprior];
        newseedj=v->jprior[v->cprior];

        fprintf(teste,"vai para extremo direito [%d][%d]\n",newseedi+1,newseedj+1);
        if(generatev(v,newseedi,newseedj,ESQUERDA,teste)==1) return 1;
        fprintf(teste,"volta para [%d][%d]\n",i+1,j+1);
        fprintf(teste,"\n");


/*        fprintf(teste,"vai para direita [%d][%d]\n",i+2,j+2);
        if(generatev(v,i+1,j+1,DIREITA,teste)==1) return 1;
        fprintf(teste,"volta para [%d][%d]\n",i+1,j+1);
        fprintf(teste,"\n");*/
      }
      fprintf(teste,"não dá a soma desejada: soma:%d != triangular:%d - ",sum,-v->info[i][j]/100);
      return 0;
    }

/*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/

    if(seta==ESQUERDA)
    {
      fprintf(teste,"está numa triangular superior [%d][%d] - ",i+1,j+1);
      for(aux=j+1;v->info[i][aux]<11 && v->info[i][aux]>0;aux++)
      {
        sum+=v->info[i][aux];
        if(aux+1==v->j) break;
      }
      fprintf(teste,"([%d][%d]) -- info=%d sum=%d\n",i+1,j+1,-v->info[i][j]%100,sum);
      if(sum==-v->info[i][j]%100)
      {
        fprintf(teste,"soma correcta: soma:%d == triangular:%d\n",sum,-v->info[i][j]%100);
        fprintf(teste,"\n");
        scanf("%c",&x);
        readMap(v);
        printf("soma correcta: soma:%d == triangular:%d\n",sum,-v->info[i][j]%100);

        if(searchSeed(v,&newseedi,&newseedj)==1) return 1;
        v->cprior++;
        newseedi=v->iprior[v->cprior];
        newseedj=v->jprior[v->cprior];

        fprintf(teste,"vai para extremo baixo [%d][%d]\n",newseedi+1,newseedj+1);
        if(generatev(v,newseedi,newseedj,CIMA,teste)==1) return 1;
        fprintf(teste,"volta para [%d][%d]\n",i+1,j+1);
        fprintf(teste,"\n");

/*        fprintf(teste,"vai para baixo [%d][%d]\n",i+2,j+2);
        if(generatev(v,i+1,j+1,BAIXO,teste)==1) return 1;
        fprintf(teste,"volta para [%d][%d]\n",i+1,j+1);
        fprintf(teste,"\n");*/
      }
      fprintf(teste,"não dá a soma desejada: soma:%d != triangular:%d - ",sum,-v->info[i][j]%100);
      return 0;
    }
  }

/*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/

  if(v->info[i][j]==0)
  {
    fprintf(teste,"está numa negra [%d][%d] - ",i+1,j+1);
    return 0;
  }

/*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/

  if(v->info[i][j]>0 && v->info[i][j]<10)
  {
    fprintf(teste,"está numa branca já visitada [%d][%d] - ",i+1,j+1);

    switch(seta)
    {
      case CIMA:fprintf(teste,"vai para cima [%d][%d]\n",i,j+1);
                if(generatev(v,i-1,j,CIMA,teste)==1) return 1;
                fprintf(teste,"volta para baixo [%d][%d]\n",i+1,j+1);
                break;
/*      case BAIXO:fprintf(teste,"vai para baixo [%d][%d]\n",i+2,j+1);
                 if(generatev(v,i+1,j,BAIXO,teste)==1) return 1;
                 fprintf(teste,"volta para cima [%d][%d]\n",i+1,j+1);
                 break;*/
      case ESQUERDA:fprintf(teste,"vai para esquerda [%d][%d]\n",i+1,j);
                    if(generatev(v,i,j-1,ESQUERDA,teste)==1) return 1;
                    fprintf(teste,"volta para direita [%d][%d]\n",i+1,j+1);
                    break;
/*      case DIREITA:fprintf(teste,"vai para direita [%d][%d]\n",i+1,j+2);
                   if(generatev(v,i,j+1,DIREITA,teste)==1) return 1;
                   fprintf(teste,"volta para esquerda [%d][%d]\n",i+1,j+1);
                   break;*/
    }
    return 0;
  }

/*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/

  if(v->info[i][j]==10)
  {
    fprintf(teste,"está numa branca [%d][%d] - ",i+1,j+1);
    for(info=9;info>0;info--)
    {
      if(diferentValue(v,i,j,info))
      {
        fprintf(teste,"([%d][%d]) -- newinfo=%d\n",i+1,j+1,info);
        fprintf(teste,"\n");
        v->info[i][j]=info;

        if(seta==CIMA)
        {
          fprintf(teste,"vai para cima [%d][%d]\n",i,j+1);
          if(generatev(v,i-1,j,CIMA,teste)==1) return 1;
          fprintf(teste,"volta para baixo [%d][%d]\n",i+1,j+1);
          fprintf(teste,"\n");
        }

/*      if(seta==BAIXO)
      {
        fprintf(teste,"vai para baixo [%d][%d]\n",i+2,j+1);
        if(generatev(v,i+1,j,BAIXO,teste)==1) return 1;
        fprintf(teste,"volta para cima [%d][%d]\n",i+1,j+1);
        fprintf(teste,"\n");
      }*/

        if(seta==ESQUERDA)
        {
          fprintf(teste,"vai para esquerda [%d][%d]\n",i+1,j);
          if(generatev(v,i,j-1,ESQUERDA,teste)==1) return 1;
          fprintf(teste,"volta para direita [%d][%d]\n",i+1,j+1);
          fprintf(teste,"\n");
        }

/*      if(seta==DIREITA)
      {
        fprintf(teste,"vai para direita [%d][%d]\n",i+1,j+2);
        if(generatev(v,i,j+1,DIREITA,teste)==1) return 1;
        fprintf(teste,"volta para esquerda [%d][%d]\n",i+1,j+1);
        fprintf(teste,"\n");
      }*/
      }
      else fprintf(teste,"info:%d não compatível",info);
    }
  }
  v->info[i][j]=10;
  return 0;
}
