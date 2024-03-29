/*
 * Frame.c
 *
 *  Created on: 09/12/2011
 *      Author: Frederico
 */
#include "Estruturas.h"
#include "Util.h"

Frame *criaFrame(List_Classfile *lcf, ClassFile *cf, char *nomeMetodo, char *descritor, Frame *frame){
	method_info *metodo = NULL;
	attribute_info attribute;
	int i;

	metodo = retornaMetodoPorNome(lcf ,&cf, nomeMetodo, descritor);
	if(metodo == NULL){
		printf("\nMetodo %s nao encontrado!", nomeMetodo);
		exit(0);
	}
	for(i = 0; i < metodo->attributes_count; i++){
		if(strcmp((char*) retornaUtf8(cf, metodo->attributes[i].attribute_name_index), "Code") == 0){
			attribute = metodo->attributes[i];
			break;
		}
	}
	frame = malloc(sizeof(Frame));
	frame->pc = attribute.u.Code.code;
	frame->pcInicial = frame->pc;
	frame->constant_pool = cf->constant_pool;
	frame->pilhaOperandos = malloc(sizeof(PilhaOperandos));
	frame->pilhaOperandos->tipo = malloc(retornaTamanhoPilha(&attribute) * sizeof(char *));
	frame->pilhaOperandos->elementos = malloc(retornaTamanhoPilha(&attribute) * sizeof(Tipo));
	frame->pilhaOperandos->sp = -1;

	frame->pilhaVariaveisLocais = malloc(sizeof(VariaveisLocais));
	frame->pilhaVariaveisLocais->tipo = malloc(retornaTamanhoVariaveisLocais(&attribute) * sizeof(char *));
	frame->pilhaVariaveisLocais->elementos = malloc(retornaTamanhoVariaveisLocais(&attribute)*sizeof(Tipo));
	frame->pilhaVariaveisLocais->sp = retornaTamanhoVariaveisLocais(&attribute);
	frame->cf = cf;
	return frame;
}

