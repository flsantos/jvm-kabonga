/*
 * RotinaExecucao.h
 *
 *  Created on: 10/12/2011
 *      Author: Frederico
 */

#ifndef ROTINAEXECUCAO_H_
#define ROTINAEXECUCAO_H_
#include "Estruturas.h"
#include "Instrucoes.h"
#include "Debug.h"

u1 leU1doPC(Frame *frame);
u2 leU2doPC(Frame *frame);
u4 leU4doPC(Frame *frame);
int execute_iteration(AmbienteExecucao *ae);

#endif /* ROTINAEXECUCAO_H_ */
