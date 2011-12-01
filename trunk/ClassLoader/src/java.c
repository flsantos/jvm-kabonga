/*
 * Codigo inicial da JVM
 *
 * Este arquivo da inicio ao procedimento de execucao da Java Virtual Machine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ClassLoader.h"
#include "Estruturas.h"



int iniciaExecucaoJVM(char nomeClassFile[], int numParametros, char *parametrosJava[]) {
//	ClassFile cf;

	strcat(nomeClassFile, ".class");
	//cf = lerClassFile(nomeClassFile);

	//Agora tem que ver se dentro desse cf existe a funcao main.
	printf("\n\nFim");
}


/*
 * Funcao inicial da JVM
 *
 */
int main(int argc, char *argv[]) {
	int i = 0;
	char *nomeClassFile;
	char **parametros;

	if (argc >= 2) {
		nomeClassFile= argv[1];
		parametros = &argv[2];
		iniciaExecucaoJVM(nomeClassFile, argc-2, parametros);
	}
	else {
		printf("O nome do arquivo .class deve ser passado como parametro.\nFavor verificar documentacao.\n"
			   "Ex: java Teste.class");
		return 1;
	}

	return 0;
}
