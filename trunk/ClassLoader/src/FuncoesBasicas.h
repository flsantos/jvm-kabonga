/*
 * FuncoesBasicas.h
 *
 *  Created on: Dec 10, 2011
 *      Author: Bruno
 */

#ifndef FUNCOESBASICAS_H_
#define FUNCOESBASICAS_H_


void jump(AmbienteExecucao *ambienteexecucao, char *classPath, char *methodName, char *descriptor, int n_arguments);

int jumpback(AmbienteExecucao *ambienteexecucao, int n_return);



#endif /* FUNCOESBASICAS_H_ */
