/*
 * Codigo inicial da JVM
 *
 * Este arquivo da inicio ao procedimento de execucao da Java Virtual Machine
 */

#include <stdio.h>
#include <stdlib.h>

#include "ClassLoader.h"
#include "Util.h"
#include "Frame.h"
#include "Heap.h"



void iniciaExecucaoMetodo(ClassFile *cf, AmbienteExecucao *ae, char *nomeMetodo, char *descritor) {


	ae->pFrame = malloc(sizeof(Frame));
	ae->pFrame = criaFrame(cf, nomeMetodo, descritor);


	printf("\n\nFim");
}

void iniciaClasse(char nomeClassFile[], AmbienteExecucao *ae, char *nomeMetodo, char *descritor) {
	ClassFile cf;

	//TODO Adicionar Realloc!

	strcat(nomeClassFile, ".class");
	cf = lerClassFile(nomeClassFile);
	adicionaClasse(&cf, &(ae->pClassHeap));
	iniciaExecucaoMetodo(&cf, ae, nomeMetodo, descritor);
}


/*
 * Funcao inicial da JVM
 *
 */
int main(int argc, char *argv[]) {
	AmbienteExecucao *ae = NULL;
	char *nomeClassFile;
	if (argc >= 2) {
		nomeClassFile = argv[1];
		iniciaClasse(nomeClassFile, ae, "main", "([Ljava/lang/String;)V");
	}
	else {
		printf("O nome do arquivo .class deve ser passado como parametro.\nFavor verificar documentacao.\n"
			   "Ex: java Teste.class");
		return 1;
	}
	return 0;
}
