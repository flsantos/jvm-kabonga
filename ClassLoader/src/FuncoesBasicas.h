/*
 * FuncoesBasicas.h
 *
 *  Created on: Dec 10, 2011
 *      Author: Bruno
 */

#ifndef FUNCOESBASICAS_H_
#define FUNCOESBASICAS_H_

#include "Estruturas.h"
#include "Util.h"
#include "Heap.h"
#include "ClassLoader.h"
#include "Frame.h"
#include "RotinaExecucao.h"

ClassFile * verificarClassFile(AmbienteExecucao *ae, char *nomeClasse);

List_Classfile *retornaSuperClasses(AmbienteExecucao *ae, ClassFile *cf);

Objeto * instanciaObjeto(ClassFile *cf, AmbienteExecucao *ae);

int RetornaFrame(AmbienteExecucao *ambienteexecucao, int n_return);

#endif /* FUNCOESBASICAS_H_ */
