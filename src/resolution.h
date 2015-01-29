/******************************************************************************
 *
 * File Name: resolution.h
 *	      (c) 2012 AED
 * Authors:    ist172942 Gerardo Lima;
 *             ist172904 Luís Gomes;
 * Last modified: ACR 2012-10-30
 * resolutionision:  v1.1
 *
 * COMMENTS
 *		resolution header
 *
 *****************************************************************************/

#ifndef resolution_H_INCLUDED
#define resolution_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

int searchSeed(vector *v,int *i,int *j);
int diferentValue(vector *v,int i,int j,int info);
int generatev(vector *v,int i,int j,int seta,FILE *teste);

#endif // resolution_H_INCLUDED
