/*****************************************************************************
 *
 * Nome do Ficheiro: error.c
 *                   (c) 2012 AED
 * Trabalho realizado por: ist172942 Gerardo Lima;
 *                         ist172904 Luís Gomes;
 * Descrição: Envia para o terminal o erro encontrado no programa
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

void error(int i)
{
  switch(i){
    case ARGV:printf("Erro: Falta colocar os dados do problema\n");
              break;
    case TIPOFICHEIRO:printf("Erro: Ficheiro nao pode ser lido.\n");
                      break;
    case FICHEIRO:printf("Erro: Ficheiro nao existe.");
                  break;
    case LINHA:printf("Erro: O Kakuro deve ter mais do que uma linha\n");
               break;
    case COLUNA:printf("Erro: O Kakuro deve ter mais do que uma coluna\n");
                break;
    case LEITURA:printf("Erro na leitura do ficheiro\n");
                 break;
    case SOMA:printf("Erro nas somas do puzzle\n");
              break;
    case ALLOC:printf("Erro de alocação de memoria\n");
               break;
  }
  printf("\nSair do KAKURO\n");
  exit(0);
}
