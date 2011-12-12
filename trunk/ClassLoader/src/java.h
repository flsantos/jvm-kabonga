/*
 * java.h
 *
 *  Created on: 11/12/2011
 *      Author: Frederico
 */

#ifndef JAVA_H_
#define JAVA_H_

void iniciaExecucaoMetodo(char nomeClassFile[], AmbienteExecucao *ae, char *nomeMetodo, char *descritor, u1 argumentos);

void iniciaClasse(char nomeClassFile[], AmbienteExecucao *ae, char *nomeMetodo, char *descritor, u1 argumentos);

#endif /* JAVA_H_ */
