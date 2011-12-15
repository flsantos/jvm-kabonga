/*
 * FuncoesBasicas.c
 *
 *  Created on: Dec 10, 2011
 *      Author: Bruno C.
 */

#include "FuncoesBasicas.h"

/*
 * Retorna a estrutura ClassFile na lista de Classes solicitada pelo nome da Classe. Caso o ClassFile nao
 * esteja na lista de Classes, ele é criado e adicionado a lista.
 */
ClassFile * verificarClassFile(AmbienteExecucao *ae, char *nomeClasse) {
	ClassFile *cf = NULL;
	char *nomeArquivo;
	Frame *frame = NULL;
	int i;

	cf = buscarClassePorNome(ae->pClassHeap, nomeClasse);
	if (cf == NULL) {
		nomeArquivo = malloc(strlen(nomeClasse) + 7 * sizeof(char));
		for (i = 0; i <= strlen(nomeClasse); i++) {
			nomeArquivo[i] = nomeClasse[i];
		}
		strcat(nomeArquivo, ".class");
		cf = malloc(sizeof(ClassFile));
		cf[0] = lerClassFile(nomeArquivo);
		//TODO ERRO DO FIELD ESTA AQUI
		Objeto *obj = instanciaObjeto(cf, ae);
		adicionaClasse(cf, &(ae->pClassHeap), obj);
		if (ae->pFrame == NULL) {
			if (retornaMetodoPorNome(ae->pClassHeap, &cf, "<clinit>", "()V") != NULL) {
				if (strcmp("java/lang/Object", nomeClasse) != 0 && strcmp(nomeClasse, "Object") != 0
						&& strcmp(nomeClasse, "java/lang/Class") != 0 && strcmp(nomeClasse, "Class") != 0
						&& strcmp(nomeClasse, "java/lang/Long") != 0 && strcmp(nomeClasse, "Long") != 0
						&& strcmp(nomeClasse, "java/lang/String") != 0 && strcmp(nomeClasse, "String") != 0) {
					ae->pFrame = criaFrame(ae->pClassHeap, cf, "<clinit>", "()V", frame);
					ae->pFrame->frameAnterior = NULL;
					execute_iteration(ae);
					frame = ae->pFrame;
					ae->pFrame = ae->pFrame->frameAnterior;
					free(frame);
				}
			}
		} else {
			if (retornaMetodoPorNome(ae->pClassHeap, &cf, "<clinit>", "()V") != NULL) {
				if (strcmp("java/lang/Object", nomeClasse) != 0 && strcmp(nomeClasse, "Object") != 0
						&& strcmp(nomeClasse, "java/lang/Class") != 0 && strcmp(nomeClasse, "Class") != 0
						&& strcmp(nomeClasse, "java/lang/Long") != 0 && strcmp(nomeClasse, "Long") != 0
						&& strcmp(nomeClasse, "java/lang/String") != 0 && strcmp(nomeClasse, "String") != 0) {
					frame = criaFrame(ae->pClassHeap, cf, "<clinit>", "()V", frame);
					frame->frameAnterior = ae->pFrame;
					ae->pFrame = frame;
					execute_iteration(ae);
					frame = ae->pFrame;
					ae->pFrame = ae->pFrame->frameAnterior;
					free(frame);
				}
			}
		}
	}
	return cf;
}

/*
 * Retorna uma lista de Classes contendo as super classes do ClassFile passado.
 */
List_Classfile *retornaSuperClasses(AmbienteExecucao *ae, ClassFile *cf) {
	ClassFile *p1;
	List_Classfile *listaClasses;
	char *str;
	listaClasses = NULL;
	p1 = cf;
	while (p1->super_class != 0) {
		str = (char *) retornaClassInfo(p1, p1->super_class);
		p1 = verificarClassFile(ae, (char *) retornaClassInfo(p1, p1->super_class));
		adicionaClasse(p1, &listaClasses, instanciaObjeto(p1, ae));
	}
	return listaClasses;
}

/*
 * Cria e retorna uma struct Objeto.
 */
Objeto * instanciaObjeto(ClassFile *cf, AmbienteExecucao *ae) {
	Objeto *newObjeto;
	List_Classfile *superClasses, *p1;
	tipo_info *ti;
	field_info *pFieldInfo;
	int tiposCount = 0;
	int i = 0;
	int index, tiposIndex, count;

	tiposCount = cf->fields_count;
	newObjeto = malloc(sizeof(Objeto));
	superClasses = retornaSuperClasses(ae, cf);
	if (superClasses != NULL) {
		p1 = superClasses;
		while (p1 != NULL) {
			tiposCount += p1->cf->fields_count;
			p1 = p1->prox;
		}
	}
	newObjeto->numeroTipos = tiposCount;
	newObjeto->tipos = malloc(tiposCount * sizeof(tipo_info));
	ti = newObjeto->tipos;
	newObjeto->nomeClasse = (char *) retornaNomeClasse(cf);
	pFieldInfo = cf->fields;
	tiposIndex = 0;
	count = cf->fields_count;
	for (i = 0; i < count; i++) {

		index = cf->fields[i].name_index;
		newObjeto->tipos[tiposIndex].nome = (char *) retornaUtf8(cf, index);

		index = cf->fields[i].descriptor_index;
		newObjeto->tipos[tiposIndex].tipo = (char *) retornaUtf8(cf, index);

		tiposIndex++;
	}
	p1 = superClasses;
	while (p1 != NULL) {
		count = p1->cf->fields_count;
		for (i = 0; i < count; i++) {
			index = p1->cf->fields[i].name_index;
			newObjeto->tipos[tiposIndex].nome = (char *) retornaUtf8(cf, index);

			index = p1->cf->fields[i].descriptor_index;
			newObjeto->tipos[tiposIndex].tipo = (char *) retornaUtf8(cf, index);

			tiposIndex++;
		}
		p1 = p1->prox;
	}

	return newObjeto;
}

int RetornaFrame(AmbienteExecucao *ae, int n_return) {
	int i;
	PilhaOperandos *pilhaoperandos;
	Frame *frame;

	if (ae->pFrame->frameAnterior != NULL) {
		frame = ae->pFrame;
		ae->pFrame = ae->pFrame->frameAnterior;
		for (i = 0; i < n_return; i++) {
			pilhaoperandos = desempilhaOperando(frame);
			empilhaOperandoTipo(ae->pFrame, pilhaoperandos->tipo[pilhaoperandos->sp],
					pilhaoperandos->elementos[pilhaoperandos->sp]);
		}
		free(frame);
		return 0;
	}
	return -1;

}
