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
#include "Debug.h"

void iniciaExecucaoMetodo(char nomeClassFile[], AmbienteExecucao *ae,
		char *nomeMetodo, char *descritor, u1 argumentos) {
	Frame *frame = NULL;
	ClassFile *cf = NULL;
	int i;

	cf = verificarClassFile(ae, nomeClassFile);
	if (ae->pFrame == NULL) {
		ae->pFrame = criaFrame(ae->pClassHeap, cf, nomeMetodo, descritor, frame);
		ae->pFrame->frameAnterior = NULL;
	} else {
		frame = criaFrame(ae->pClassHeap, cf, nomeMetodo, descritor, frame);
		frame->frameAnterior = ae->pFrame;
		ae->pFrame = frame;
		for (i = (argumentos - 1); i >= 0; i--) {
			transferePilhaOperandosParaVariavelLocalPorFrames(
					ae->pFrame->frameAnterior, ae->pFrame, i);
		}
	}

}

void iniciaClasse(char nomeClassFile[], AmbienteExecucao *ae, char *nomeMetodo,
		char *descritor, u1 argumentos) {
	List_Classfile *lista;
	iniciaExecucaoMetodo(nomeClassFile, ae, nomeMetodo, descritor, argumentos);
	lista = ae->pClassHeap;
	while(strcmp((char *)ae->pClassHeap->class_name, (char *)retornaNomeClasse(ae->pFrame->cf)) != 0){
		ae->pClassHeap = ae->pClassHeap->prox;
	}
	execute_iteration(ae);
	ae->pClassHeap = lista;
}

void checkDebugFlag(char *flag) {
	if (strcmp(flag,"-d") == 0) {
		m_debug = 1;
	}
	else if (strcmp(flag, "-D") == 0) {
		m_debug = 2;
	}
	else {
		m_debug = 0;
	}
}

void procuraPath(char *nomeClassFile) {
	char *p;
	int i;
	p = nomeClassFile;
	caminhoArquivo = NULL;
	primeiraVez = 0;

	if ((strrchr(nomeClassFile, '\\') == NULL) && (strrchr(nomeClassFile, '/') == NULL)) {
		caminhoArquivo = NULL;
	}
	else {
		if ((strrchr(nomeClassFile, '\\') != NULL) && (strrchr(nomeClassFile, '/') != NULL)) {
			char *p1, *p2;
			p1 = strrchr(nomeClassFile, '\\');
			p2 = strrchr(nomeClassFile, '/');
			if (p1 > p2) {
				caminhoArquivo = malloc(p1-nomeClassFile+1);
				i = 0;
				for (p = nomeClassFile; p<=p1; p++) {
					caminhoArquivo[i] = *p;
					i++;
				}
				caminhoArquivo[i] = '\0';
			}
			else {
				caminhoArquivo = malloc(sizeof(p2-nomeClassFile+1));
				i = 0;
				for (p = nomeClassFile; p<=p2; p++) {
					caminhoArquivo[i] = *p;
					i++;
				}
				caminhoArquivo[i] = '\0';
			}

		}
	}
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
		procuraPath(nomeClassFile);
		printf("\nVALOR AKAAII : %s\n", caminhoArquivo);
		if (argc >= 3) {
			checkDebugFlag(argv[2]);
		}
		iniciaClasse(nomeClassFile, &ae, "main", "([Ljava/lang/String;)V", 0);
	} else {
		printf(
				"O nome do arquivo .class deve ser passado como parametro.\nFavor verificar documentacao.\n"
						"Ex: java Teste.class");
		return 1;
	}
	return 0;
}
