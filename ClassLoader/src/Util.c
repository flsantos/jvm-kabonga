/*
 * util.c
 *
 *  Created on: 06/12/2011
 *      Author: Daniel
 *
 * RetornaNomeMetodo
 * RetornaNomeClasse
 * RetornaMetodoRecebendoNome
 * RetornaValorDoField
 * RetornaTamanhoPilha
 * RetornaNumeroDeVariaveisLocais
 */
#include "Util.h"
#include <string.h>



/*
 * Funcoes de busca no pool de constantes
 */

u1 * retornaUtf8(ClassFile *cf, u2 index){
	return cf->constant_pool[index-1].u.Utf8.bytes;
}

method_info *retornaMetodoPorNome(ClassFile *cf, char *nomeMetodo, char *nomeDescritor ){
	int i=0;
	for (i=0; i<cf->methods_count; i++) {
		if (strcmp(nomeMetodo, (char *)retornaUtf8(cf, cf->methods[i].name_index)) == 0
				&&
				strcmp(nomeDescritor, (char *)retornaUtf8(cf, cf->methods[i].descriptor_index)) == 0) {
			return &(cf->methods[i]) ;
		}
	}
	return NULL;

}

u1 * retornaNomeMetodo(ClassFile *cf, method_info *mi){
	return retornaUtf8(cf, mi->name_index);
}

u1 * retornaNomeClasse (ClassFile *cf){
	return retornaUtf8(cf, cf->constant_pool[cf->this_class-1].u.Class.name_index);
}

u2 retornaTamanhoPilha (attribute_info *ai){
	return ai->u.Code.max_stack;
}

u2 retornaTamanhoVariaveisLocais(attribute_info *ai) {
	return ai->u.Code.max_locals;
}


/*
 * Funcoes uteis para pilha de operandos
 */


void empilhaOperando(Frame *frame, char *tipo, void *operando) {
	frame->pilhaOperandos.sp++;
}

//ver se a pilha ta vazia
//push
//pop
//transferir pilha pra lista de variaveis locais
//transferir da lista de variaveis locais para a pilha
