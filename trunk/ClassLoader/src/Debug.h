/*
 * Debug.h
 *
 *  Created on: Dec 13, 2011
 *      Author: Julio
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>
#include "Estruturas.h"

#endif /* DEBUG_H_ */

void debugPrintEmpilha(char *tipo, Frame *frame);
void debugPrintDesempilha(PilhaOperandos *operando);
void debugPrintEmpilhaTipo(PilhaOperandos *p1);
void debugPrintLinha();
