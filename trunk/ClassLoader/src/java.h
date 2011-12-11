/*
 * java.h
 *
 *  Created on: 11/12/2011
 *      Author: Frederico
 */

#ifndef JAVA_H_
#define JAVA_H_

void iniciaExecucaoMetodo(ClassFile *cf, AmbienteExecucao *ae, char *nomeMetodo, char *descritor);

void iniciaClasse(char nomeClassFile[], AmbienteExecucao *ae, char *nomeMetodo, char *descritor);

#endif /* JAVA_H_ */
