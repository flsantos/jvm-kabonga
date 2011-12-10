/*
 * FuncoesBasicas.c
 *
 *  Created on: Dec 10, 2011
 *      Author: Bruno C.
 */
#include <stdlib.h>

#include "FuncoesBasicas.h"
#include "Estruturas.h"
#include "Util.h"
#include "Heap.h"
#include "ClassLoader.h"


/*
 * Retorna a estrutura ClassFile na lista de Classes solicitada pelo nome da Classe. Caso o ClassFile nao
 * esteja na lista de Classes, ele é criado e adicionado a lista.
 */
ClassFile * verificarClassFile(AmbienteExecucao *ae, char *nomeClasse) {
	ClassFile *classFile;
	char *nomeArquivo;

	nomeArquivo = nomeClasse;
	strcat(nomeArquivo, ".class");
	classFile = buscarClassePorNome(ae->pClassHeap, nomeClasse);
	if (classFile == NULL) {
		classFile = lerClassFile(nomeArquivo);
		adicionaClasse(classFile, ae->pClassHeap);
	}
	/* TODO Fazer criar ClassFile de classes de outros packages

	return classFile;
}



/*
 * Retorna uma lista de Classes contendo as super classes do ClassFile passado.
 */
List_Classfile *retornaSuperClasses(AmbienteExecucao *ae, ClassFile *cf) {
	ClassFile *p1;
	List_Classfile *listaClasses;
	listaClasses = NULL;
	p1 = cf;

	while (p1->super_class != 0) {
		p1 = verificarClassFile(ae, retornaNomeClasse(p1->super_class));
		adicionaClasse(p1, &listaClasses);
	}
	return listaClasses;
}



/*
 * Cria e retorna uma struct Objeto.
 */
Objeto * instanciaObjeto( ClassFile *cf, ) {
	Objeto *newObjeto;
	List_Classfile *superClasses, *p1;
	int fieldsCount = 0;
	int i = 0;

	fieldsCount = cf->fields_count;
	newObjeto = malloc(sizeof(Objeto));
	superClasses = retornaSuperClasses(ae, cf);

	if (superClasses != NULL) {
		p1 = superClasses;
		while (p1->prox != NULL) {
			fieldsCount += p1->cf->fields_count;
			p1 = p1->prox;
		}
	}

	newObjeto->fields_count = fieldsCount;
	newObjeto->fields = malloc(fieldsCount*sizeof(field_info));
	newObjeto->nomeClasse = retornaNomeClasse(cf);

	return newObjeto;
}
