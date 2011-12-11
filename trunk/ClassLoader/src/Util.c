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
	i2 sp = 0;
	frame->pilhaOperandos->sp++;


	sp = frame->pilhaOperandos->sp;

	frame->pilhaOperandos->tipo[sp] = tipo;

	if (strcmp("B", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_byte = *((i1 *)operando);
	}else if (strcmp("C", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_char = *((u1 *)operando);
	}else if (strcmp("D", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_double = *((double *)operando);
	}else if (strcmp("F", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_float = *((float *)operando);
	}else if (strcmp("I", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_int = *((u4 *)operando);
	}else if (strcmp("J", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_long = *((long *)operando);
	}else if (strcmp("L", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_referencia = operando;
	}else if (strcmp("S", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_short = *((u2 *)operando);
	}else if (strcmp("Z", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_boolean = *((char *)operando);
	}else if (strcmp("[", tipo)) {
		frame->pilhaOperandos->elementos[sp].tipo_retorno = *((u1 *)operando);
	}
}

PilhaOperandos desempilhaOperando(Frame *frame) {
	i2 sp = 0;
	PilhaOperandos operando;
	sp = frame->pilhaOperandos->sp;

	if (sp > -1) {

		operando.elementos = malloc(sizeof(Tipo));
		operando.tipo = malloc(sizeof(char *));

		operando.elementos[0] = frame->pilhaOperandos->elementos[sp];
		operando.tipo = frame->pilhaOperandos->tipo[sp];


		frame->pilhaOperandos->sp--;
	}
	else {
		printf("\nErro! Pilha vazia.");
		exit(1);
	}
	return operando;
}

int pilhaOperandosVazia(Frame *frame) {
	if (frame->pilhaOperandos->sp == -1)
		return 1;
	else
		return 0;
}


void transferePilhaOperandosParaVariavelLocal(Frame *frame, int indiceVariavel) {
	PilhaOperandos op;
	i2 spVarLocal = 0;

	op = desempilhaOperando(frame);

	frame->pilhaVariaveisLocais->elementos[indiceVariavel] = op->elementos[0];
	frame->pilhaVariaveisLocais->tipo[indiceVariavel] = op->tipo[0];
}


void transfereVariavelLocalParaPilhaOperandos(Frame *frame, int indiceVariavel) {
	empilhaOperando(frame, frame->pilhaVariaveisLocais->tipo[indiceVariavel], frame->pilhaVariaveisLocais->elementos[indiceVariavel]);
}


