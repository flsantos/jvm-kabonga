/*
 * Frame.c
 *
 *  Created on: 09/12/2011
 *      Author: Frederico
 */
#include "Estruturas.h"
#include "Util.h"

Frame *criaFrame(ClassFile *cf, char *nomeMetodo, char *descritor){
	Frame *frame = NULL;
	method_info *metodo = NULL;
	attribute_info attribute;
	int i;

	metodo = retornaMetodoPorNome(cf, nomeMetodo, descritor);
	for(i = 0; i < metodo->attributes_count; i++){
		if(strcmp((char*) retornaUtf8(cf, metodo->attributes[i].attribute_name_index), "Code") == 0){ //TODO Usar metodo criado
			attribute = metodo->attributes[i];
			break;
		}
	}
	//TODO Verificar se funciona com as setinhas
	frame = malloc(sizeof(Frame));
	frame->code_length = attribute.u.Code.code_length;
	frame->code = attribute.u.Code.code;
	frame->constant_pool = cf->constant_pool;
	frame->pilhaOperandos = malloc(sizeof(PilhaOperandos));
	//TODO verificar se esse ->tipo nao term q ser pilhaOperandos[0]->tipo
	frame->pilhaOperandos->tipo = malloc(retornaTamanhoPilha(&attribute) * sizeof(char *));
	frame->pilhaOperandos->elementos = malloc(retornaTamanhoPilha(&attribute) * sizeof(Tipo));
	frame->pilhaOperandos->sp = -1;

	frame->pilhaVariaveisLocais = malloc(sizeof(PilhaVariaveisLocais));
	frame->pilhaVariaveisLocais->tipo = malloc(retornaTamanhoVariaveisLocais(&attribute) * sizeof(char *));
	frame->pilhaVariaveisLocais->elementos = malloc(retornaTamanhoVariaveisLocais(&attribute)*sizeof(Tipo));
	frame->pilhaVariaveisLocais->sp = retornaTamanhoVariaveisLocais(&attribute);
	frame->cf = cf;
	frame->pc = 0;
	return frame;
}

