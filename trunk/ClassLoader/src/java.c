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
#include "RotinaExecucao.h"



void iniciaExecucaoMetodo(ClassFile *cf, AmbienteExecucao *ae, char *nomeMetodo, char *descritor) {
	Frame *frame = NULL;

	if(ae->pFrame == NULL){
		ae->pFrame = criaFrame(cf, nomeMetodo, descritor, frame);
		ae->pFrame->frameAnterior = NULL;
	} else {
		frame =  criaFrame(cf, nomeMetodo, descritor, frame);
		frame->frameAnterior = ae->pFrame;
		ae->pFrame = frame;
	}
	printf("\n\nFrame");
	execute_iteration(ae);
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
	AmbienteExecucao ae;
	char *nomeClassFile;

	ae.pClassHeap = NULL;
	ae.pFrame = NULL;
	if (argc >= 2) {
		nomeClassFile = argv[1];
		iniciaClasse(nomeClassFile, &ae, "main", "([Ljava/lang/String;)V");
	}
	else {
		printf("O nome do arquivo .class deve ser passado como parametro.\nFavor verificar documentacao.\n"
			   "Ex: java Teste.class");
		return 1;
	}
	return 0;
}
