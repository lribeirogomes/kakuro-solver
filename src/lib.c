#include<stdio.h>
#include<stdlib.h>

int **makeSpecial(int **m){
  int i;
  int v[34];

  v[0]=2*3;
  v[1]=2*4;
  v[2]=2*16;
  v[3]=2*17;
  v[4]=3*6;
  v[5]=3*7;
  v[6]=3*23;
  v[7]=3*24;
  v[8]=4*10;
  v[9]=4*11;
  v[10]=4*29;
  v[11]=4*30;
  v[12]=5*15;
  v[13]=5*16;
  v[14]=5*34;
  v[15]=5*35;
  v[16]=6*21;
  v[17]=6*22;
  v[18]=6*38;
  v[19]=6*39;
  v[20]=7*28;
  v[21]=7*29;
  v[22]=7*41;
  v[23]=7*42;


  m=(int**)calloc(295,sizeof(int));  /*7*42=294*/
  for(i=0;i!=295;i++) m[i]=NULL;
  for(i=0;i!=24;i++){
    m[v[i]]=malloc(sizeof(int));
    *m[v[i]]=0;
  }

  return m;
}
