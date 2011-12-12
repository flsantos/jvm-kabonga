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
#include "FuncoesBasicas.h"
void iniciaExecucaoMetodo(char nomeClassFile[], AmbienteExecucao *ae,
		char *nomeMetodo, char *descritor, u1 argumentos) {
	Frame *frame = NULL;
	ClassFile *cf = NULL;
	int i;

	cf = verificarClassFile(ae, nomeClassFile);
	if (ae->pFrame == NULL) {
		ae->pFrame = criaFrame(cf, nomeMetodo, descritor, frame);
		ae->pFrame->frameAnterior = NULL;
	} else {
		frame = criaFrame(cf, nomeMetodo, descritor, frame);
		frame->frameAnterior = ae->pFrame;
		ae->pFrame = frame;
		for (i = (argumentos - 1); i >= 0; i--) {
			transferePilhaOperandosParaVariavelLocalPorFrames(ae->pFrame->frameAnterior, ae->pFrame, i);
		}
	}
	printf("\n\nFrame");
}

void iniciaClasse(char nomeClassFile[], AmbienteExecucao *ae, char *nomeMetodo,
		char *descritor, u1 argumentos) {

	//TODO Adicionar Realloc!
	iniciaExecucaoMetodo(nomeClassFile, ae, nomeMetodo, descritor, argumentos);
	execute_iteration(ae);
}

void iniciaMain(char nomeClassFile[], AmbienteExecucao *ae, char *nomeMetodo,
		char *descritor) {

	//TODO Adicionar Realloc!
	iniciaExecucaoMetodo(nomeClassFile, ae, nomeMetodo, descritor, 0);
	execute_iteration(ae);
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
		iniciaMain(nomeClassFile, &ae, "main", "([Ljava/lang/String;)V");
	} else {
		printf(
				"O nome do arquivo .class deve ser passado como parametro.\nFavor verificar documentacao.\n"
						"Ex: java Teste.class");
		return 1;
	}
	return 0;
}
