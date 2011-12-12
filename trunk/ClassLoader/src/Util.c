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

u1 * retornaUtf8(ClassFile *cf, u2 index) {
	return cf->constant_pool[index - 1].u.Utf8.bytes;
}

method_info *retornaMetodoPorNome(ClassFile *cf, char *nomeMetodo,
		char *nomeDescritor) {
	int i = 0;
	for (i = 0; i < cf->methods_count; i++) {
		if (strcmp(nomeMetodo,
				(char *) retornaUtf8(cf, cf->methods[i].name_index)) == 0
				&& strcmp(
						nomeDescritor,
						(char *) retornaUtf8(cf,
								cf->methods[i].descriptor_index)) == 0) {
			return &(cf->methods[i]);
		}
	}
	return NULL;

}

u1 * retornaNomeMetodo(ClassFile *cf, method_info *mi) {
	return retornaUtf8(cf, mi->name_index);
}

u1 * retornaNomeClasse(ClassFile *cf) {
	return retornaUtf8(cf,
			cf->constant_pool[cf->this_class - 1].u.Class.name_index);
}

u2 retornaTamanhoPilha(attribute_info *ai) {
	return ai->u.Code.max_stack;
}

u2 retornaTamanhoVariaveisLocais(attribute_info *ai) {
	return ai->u.Code.max_locals;
}

u1 *retornaClassInfo(ClassFile *cf, int indice) {
	return retornaUtf8(cf, cf->constant_pool[indice-1].u.Class.name_index);
}

DadosNameAndType *retornaDadosNameAndTypeInfo(ClassFile *cf, int n) {
	int indiceNome, indiceTipo;
	DadosNameAndType *dadosNameAndType;
	dadosNameAndType = malloc(sizeof(DadosNameAndType));

	indiceNome = (cf->constant_pool + n - 1)->u.NameAndType.name_index;
	indiceTipo = (cf->constant_pool + n - 1)->u.NameAndType.descriptor_index;
	dadosNameAndType->nome = (char *) retornaUtf8(cf, indiceNome);
	dadosNameAndType->tipo = (char *) retornaUtf8(cf, indiceTipo);

	return dadosNameAndType;

}

DadosMetodo *retornaDadosMetodo(ClassFile *cf, int n) {
	DadosMetodo *dadosMetodo;
	DadosNameAndType *dadosNameAndType;

	dadosMetodo = malloc(sizeof(DadosMetodo));

	dadosMetodo->nomeClasse = (char *)retornaClassInfo(cf,
			(cf->constant_pool[n - 1]).u.Fieldref.class_index);
	dadosNameAndType = retornaDadosNameAndTypeInfo(cf,
			(cf->constant_pool[n - 1]).u.Fieldref.name_and_type_index);
	dadosMetodo->nomeMetodo = dadosNameAndType->nome;
	dadosMetodo->tipo = dadosNameAndType->tipo;

	return dadosMetodo;
}

/*
 * Funcoes uteis para pilha de operandos
 */

void empilhaOperando(Frame *frame, char *tipo, void *operando) {
	i2 sp = 0;
	frame->pilhaOperandos->sp++;

	sp = frame->pilhaOperandos->sp;

	frame->pilhaOperandos->tipo[sp] = tipo;

	if (tipo[0] == 'B') {
		frame->pilhaOperandos->elementos[sp].tipo_byte = *((i1 *) operando);
	} else if (tipo[0] == 'C') {
		frame->pilhaOperandos->elementos[sp].tipo_char = *((u1 *) operando);
	} else if (tipo[0] == 'D') {
		frame->pilhaOperandos->elementos[sp].tipo_double =
				*((double *) operando);
	} else if (tipo[0] == 'F') {
		frame->pilhaOperandos->elementos[sp].tipo_float = *((float *) operando);
	} else if (tipo[0] == 'I') {
		frame->pilhaOperandos->elementos[sp].tipo_int = *((u4 *) operando);
	} else if (tipo[0] == 'J') {
		frame->pilhaOperandos->elementos[sp].tipo_long = *((long *) operando);
	} else if (tipo[0] == 'L') {
		frame->pilhaOperandos->elementos[sp].tipo_referencia = operando;
	} else if (tipo[0] == 'S') {
		frame->pilhaOperandos->elementos[sp].tipo_short = *((u2 *) operando);
	} else if (tipo[0] == 'Z') {
		frame->pilhaOperandos->elementos[sp].tipo_boolean =
				*((char *) operando);
	} else if (tipo[0] == '[') {
		frame->pilhaOperandos->elementos[sp].tipo_retorno = *((u1 **) operando);
	}
}

PilhaOperandos *desempilhaOperando(Frame *frame) {
	i2 sp = 0;
	PilhaOperandos *operando = NULL;
	sp = frame->pilhaOperandos->sp;

	operando = malloc(sizeof(PilhaOperandos));

	if (sp > -1) {

		operando->elementos = malloc(sizeof(Tipo));
		operando->tipo = malloc(sizeof(char *));

		operando->elementos[0] = frame->pilhaOperandos->elementos[sp];
		operando->tipo = &(frame->pilhaOperandos->tipo[sp]);

		operando->sp = sp;

		frame->pilhaOperandos->sp--;
	} else {
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

void transferePilhaOperandosParaVariavelLocal(Frame *frame, u1 indiceVariavel) {
	PilhaOperandos *op;

	op = desempilhaOperando(frame);

	frame->pilhaVariaveisLocais->elementos[indiceVariavel] = op->elementos[0];
	frame->pilhaVariaveisLocais->tipo[indiceVariavel] = op->tipo[0];
}

void transferePilhaOperandosParaVariavelLocalPorFrames(Frame *frame1, Frame *frame2, u1 indiceVariavel) {
	PilhaOperandos *op;

	op = desempilhaOperando(frame1);

	frame2->pilhaVariaveisLocais->elementos[indiceVariavel] = op->elementos[0];
	frame2->pilhaVariaveisLocais->tipo[indiceVariavel] = op->tipo[0];
}

void transfereVariavelLocalParaPilhaOperandos(Frame *frame, u1 indiceVariavel) {
	empilhaOperando(frame, frame->pilhaVariaveisLocais->tipo[indiceVariavel],
			&(frame->pilhaVariaveisLocais->elementos[indiceVariavel]));
}

int retornaContadorArgumentos(char *descriptor) {
	char *c1;
	int count;
	int add_counter;

	count = 0;
	add_counter = 0;

	c1 = descriptor;
	while (*c1 != '\0') {
		switch (*c1) {
		case 'B':
			if (add_counter)
				count++;
			break;
		case 'C':
			if (add_counter)
				count++;
			break;
		case 'D':
			if (add_counter)
				count++;
			break;
		case 'F':
			if (add_counter)
				count++;
			break;
		case 'I':
			if (add_counter)
				count++;
			break;
		case 'J':
			if (add_counter)
				count++;
			break;
		case 'L':
			if (add_counter) {
				count++;
				add_counter = 0;
			}
			break;
		case 'S':
			if (add_counter)
				count++;
			break;
		case 'Z':
			if (add_counter)
				count++;
			break;
		case '[':
			break;
		case '(':
			add_counter = 1;
			break;
		case ')':
			add_counter = 0;
			break;
		case ';':
			add_counter = 1;
			break;

		default:
			break;
		}
		c1++;

	}
	return count;
}



void adicionaValorArray(Array *array, int posicao, char *tipo, void *info) {
	if(tipo[0] == 'B') {
		array->elementos[posicao].tipo_byte = *((i1 *)info);
	} else if(tipo[0] == 'C') {
		array->elementos[posicao].tipo_char = *((u1 *)info);
	} else if(tipo[0] == 'D') {
		array->elementos[posicao].tipo_double = *((double*)info);
	} else if(tipo[0] == 'F') {
		array->elementos[posicao].tipo_float= *((float*)info);
	} else if(tipo[0] == 'I') {
		array->elementos[posicao].tipo_int = *((u4*)info);
	} else if(tipo[0] == 'J') {
		array->elementos[posicao].tipo_long = *((long*)info);
	} else if(tipo[0] == 'L') {
		array->elementos[posicao].tipo_referencia = info;
	} else if(tipo[0] == 'S') {
		array->elementos[posicao].tipo_short = *((u2*)info);
	} else if(tipo[0] == 'Z') {
		array->elementos[posicao].tipo_boolean = *((char*)info);
	} else if(tipo[0] == '[') {
		array->elementos[posicao].tipo_referencia = info;
	} else if(tipo[0] == 'r') {
		array->elementos[posicao].tipo_retorno = *((u1 **) info);
	}
	array->tipo[posicao] = tipo;
}
