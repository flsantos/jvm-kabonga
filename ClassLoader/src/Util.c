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

DadosField *retornaDadosField(ClassFile *class, int n) {
	DadosField *dadosField;
	DadosNameAndType *dadosNameAndType;

	dadosField = malloc(sizeof(DadosField));

	dadosField->nomeClasse = (char *)retornaClassInfo(class, (class->constant_pool + n -1)->u.Fieldref.class_index);

	dadosNameAndType = retornaDadosNameAndTypeInfo(class, (class->constant_pool + n - 1)->u.Fieldref.name_and_type_index);
	dadosField->nomeField = dadosNameAndType->nome;
	dadosField->tipo = dadosNameAndType->tipo;

	return dadosField;
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
		frame->pilhaOperandos->elementos[sp].tipo_retorno =  operando;
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

		operando->sp = 0;

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


//TODO entender essa porra
Array *iniciarArray(char *tipo, int n) {
	Array *vetorList, *p1, *p2;
	int i;
	if(n > 0) {
		vetorList = malloc(sizeof(n*Array));
		vetorList->tipo = tipo;
		p1 = vetorList;
		for(i = 1; i < n; i++) {
			p1->tipo = tipo;
			vetorList->sp = 0;
			p1 = vetorList + i;

		}
	} else {
		fprintf(stderr,"Erro no localvar_init_structure\n");
		exit(1);
	}

	return vetorList;
}


Array* alocarVetor__(char* tipo, int dimensao, int *tamanhos) {
	Array *vet, *p1;
	int i, *sub_tamanhos;

	if(dimensao == 1) {
		vet = iniciarArray(tipo, tamanhos[0]);
	} else {
		vet = iniciarArray("[", tamanhos[0]);

		sub_tamanhos = calloc(dimensao-1, sizeof(int));
		for(i= 1; i < dimensao; i++) {
			sub_tamanhos[i-1] = tamanhos[i];
		}
		for(p1 = vet, i=0; i< tamanhos[0]; i++, p1 = vet + i) {
			p1->elementos[0].tipo_referencia = alocarVetor__(tipo, dimensao-1, sub_tamanhos);
		}
	}


	return vet;

}


Array* alocarVetor(char *tipo, int dimensao, ...) {
	Array *vet;
	int contador;
	int *tamanhos, *p1;
	va_list argptr;

	tamanhos = calloc(dimensao, sizeof(int));

	va_start(argptr, dimensao);

	if(dimensao == 0) {
		vet = NULL;
		return vet;
	}

	for(contador = 0, p1 = tamanhos; contador < dimensao; contador++, p1++) {
		*p1 = va_arg(argptr, int);
	}

	vet = alocarVetor__(tipo, dimensao, tamanhos);

	vet->sp = 0;
	return vet;
}


Array *caputarVetor(char *tipo, int dimensao, int tamanho) {
	Array *vetor, p1;

	if (dimensao < 1) {
		return NULL;
	}
	else if (dimensao == 1) {
		//vetor = malloc(vetor->);
	}
	else if (dimensao > 1) {
		//TODO
	}

	return vetor;
}

int defineFieldObjeto(Objeto *object, char *nomeField, char *tipo, Tipo info) {
	tipo_info *p1;
	int n, i;
	n = object->numeroTipos;
	printf("\n\ndefineFieldObjeto");
	for(i=0, p1 = object->tipos; i < n; i++, p1++) {
		if(strcmp(p1->nome, nomeField) == 0) {
			p1->tipo = tipo;
			if(tipo[0] == 'B') {
				p1->elemento.tipo_byte = info.tipo_byte;
			} else if(tipo[0] == 'C') {
				p1->elemento.tipo_char = info.tipo_char;
			} else if(tipo[0] == 'D') {
				p1->elemento.tipo_double = info.tipo_double;
			} else if(tipo[0] == 'F') {
				p1->elemento.tipo_float= info.tipo_float;
			} else if(tipo[0] == 'I') {
				p1->elemento.tipo_int = info.tipo_int;
			} else if(tipo[0] == 'J') {
				p1->elemento.tipo_long = info.tipo_long;
			} else if(tipo[0] == 'L') {
				p1->elemento.tipo_referencia = info.tipo_referencia;
			} else if(tipo[0] == 'S') {
				p1->elemento.tipo_short = info.tipo_short;
			} else if(tipo[0] == 'Z') {
				p1->elemento.tipo_boolean = info.tipo_boolean;
			} else if(tipo[0] == '[') {
				p1->elemento.tipo_referencia = info.tipo_referencia;
			} else if(tipo[0] == 'r') {
				p1->elemento.tipo_retorno = info.tipo_retorno;
			}
			return 1;
		}
	}
	return -1;
}


tipo_info *retornaFieldObjeto(Objeto *object, char *nomeField) {
	tipo_info *p1;
	int n, i;
	n = object->numeroTipos;

	for(i=0, p1 = object->tipos; i<n; i++, p1++) {
		if(strcmp(p1->nome, nomeField) == 0) {
			return p1;
		}
	}
	return NULL;
}

long long retornaLong(ClassFile *cf, int n) {
	long long high, low;
	long long vlong;

	high = (cf->constant_pool + n - 1)->u.Long.high_bytes;
	low = (cf->constant_pool + n - 1)->u.Long.low_bytes;


	vlong = 0;

	vlong = (high << sizeof(u4)*8) | low;

	return vlong;
}
