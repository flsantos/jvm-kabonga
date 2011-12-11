/*
 * Heap.c
 *
 *  Created on: 09/12/2011
 *      Author: Frederico
 */

/*
 *TODO Todas as funções de adição e remoção de Classe e objetos no HeapClass e no HeapObject
 *
 *@descrição HeapClass Lista de classes
 *@descrição HeapObject Union com u1, u2, u4, float, long e double e Object
 */

/*
 * Adiciona uma nova classe a lista de classes
 * */

#include "Estruturas.h"
#include "Util.h"

void adicionaClasse (ClassFile *cf, List_Classfile **lcf){
	List_Classfile *aux;

	if ((*lcf) == NULL){
		(*lcf) = malloc(sizeof(List_Classfile));
		(*lcf)->cf = NULL;
		(*lcf)->class_name = NULL;
		(*lcf)->prox = NULL;
		(*lcf)->cf = cf;
		(*lcf)->class_name = malloc(sizeof(cf->constant_pool[cf->constant_pool[cf->this_class -1].u.Class.name_index -1].u.Utf8.length));
		(*lcf)->class_name = cf->constant_pool[cf->constant_pool[cf->this_class -1].u.Class.name_index -1].u.Utf8.bytes;

	}
	else{
		aux = malloc(sizeof(List_Classfile));
		aux->cf = NULL;
		aux->class_name = NULL;
		aux->prox = (*lcf);
		aux->cf = cf;
		aux->class_name = malloc(sizeof(cf->constant_pool[cf->constant_pool[cf->this_class -1].u.Class.name_index -1].u.Utf8.length));
		aux->class_name = cf->constant_pool[cf->constant_pool[cf->this_class -1].u.Class.name_index -1].u.Utf8.bytes;
	}
}

ClassFile * buscarClassePorNome(List_Classfile *lcf, char *nomeClasse) {
	List_Classfile *plcf;
	plcf = lcf;

	while (plcf != NULL) {
		if (strcmp((char *)retornaClassInfo(plcf->cf, plcf->cf->this_class), nomeClasse) == 0) {
			return plcf->cf;
		}
		plcf = plcf->prox;
	}
	return NULL;
}
