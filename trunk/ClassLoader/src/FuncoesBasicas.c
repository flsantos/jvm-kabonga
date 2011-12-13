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
	int i;

	cf = buscarClassePorNome(ae->pClassHeap, nomeClasse);
	if (cf == NULL) {
		nomeArquivo = malloc(strlen(nomeClasse) + 7 * sizeof(char));
		for(i = 0; i <= strlen(nomeClasse); i++){
			nomeArquivo[i] = nomeClasse[i];
		}
		strcat(nomeArquivo, ".class");
		cf = malloc(sizeof(ClassFile));
		cf[0] = lerClassFile(nomeArquivo);
		Objeto *obj = instanciaObjeto(cf, ae);
		adicionaClasse(cf, &(ae->pClassHeap), obj);
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
		p1 = verificarClassFile(ae,
				(char *) retornaClassInfo(p1, p1->super_class));
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

/**
 * Funcao de jump. Funcao responsavel por desviar o contexto do ambiente de execucao para outro metodo determinado.
 *
 * Essa funcao ira desviar o contexto do ambiente de execucao para outro metodo. Para isso, ele cria um novo frame,
 * determina seus valores com base na classPath e methodName especificados, passa os argumentos da pilha
 * de operandos do frame atual para as variaveis locais do novo frame, empilha o frame atual e coloca o frame
 * novo como o novo frame. A partir dai retorna e continua com o ambiente de execucao conforme ja ocorria.
 * Caso nao tenha nenhum frame na pilha de frames, este e o primeiro metodo a ser executado pelo ambiente de execucao.
 *
 * @param ae a variavel do ambiente de execucao
 * @param classPath o caminho da classe
 * @param methodName  nome do metodo
 * @param descriptor o descritor do metodo
 * @param n_arguments o numero de parametros do metodo
 *
 * @return void
 *
 */

//void jump(AmbienteExecucao *ae, char *classPath, char *methodName, char *descriptor, int n_arguments) {
//	t_class_file *class_file;
//	t_method_and_class *metclass;
//	Frame *frame_novo;
//	int i;
//	u2 mask = 0x0100;
//
//	class_file = leitura_class_file(ae, classPath);
//	metclass = find_method_by_name(class_file, methodName, descriptor, ae);
//	if((metclass->method_info->acess_flags & mask) == 0x0100) {
//		printf("Metodos nativos nao suportados\n");
//		exit(1);
//	}
//	frame_novo = malloc(sizeof(t_frame));
//	frame_novo->opstack = NULL;
//	frame_novo->class_file = metclass->class_file;
//	frame_novo->pc_address = 0;
//
//	frame_novo->pc = find_method_attribute_by_name(metclass->class_file, metclass->method_info, "Code")->_info.code.code;
//	frame_novo->pc_inicial = frame_novo->pc;
//	frame_novo->local_variables = calloc(find_method_attribute_by_name(metclass->class_file, metclass->method_info, "Code")->_info.code.max_locals, sizeof(t_local_variable_list));
//
//
//	frame_stack_push(&(ae->frame_stack), ae->current_frame);
//	if(ae->current_frame != NULL) {
//
//		for(i=(n_arguments-1); i!= -1; i--) {
//			transfer_opstack_to_localvar(&(ae->current_frame->opstack),&(frame_novo->local_variables), i);
//		}
//	}
//
//	ae->current_frame = frame_novo;
//}
/**
 * Jumpback faz o contrario do jump - ele retorna o ambiente de execucao para o frame que esta no topo da pilha
 * de frames, ou seja, o frame anterior.
 *
 * A funcao jumpback tem como objetivo retornar o ambiente de execucao para o frame que esta no topo da pilha de frames, alem de
 * passar a variavel de retorno para o frame do topo da pilha, se houver.
 *
 * @param ae a variavel do ambiente de execucao
 * @param n_return o numero de retorno. Pode ser 0 ou 1 (ainda que a funcao seja generica e aceite n retornos)
 */

int jumpback(AmbienteExecucao *ae, int n_return) {
	int i;
	PilhaOperandos *pilhaoperandos;
	Frame *frame;
	frame = ae->pFrame;

	if (ae->pFrame->frameAnterior != NULL) {
		frame = ae->pFrame;
		ae->pFrame = ae->pFrame->frameAnterior;

		for (i = 0; i < n_return; i++) {
			pilhaoperandos = desempilhaOperando(frame);
			empilhaOperandoTipo(ae->pFrame, pilhaoperandos->tipo[pilhaoperandos->sp],
					pilhaoperandos->elementos[pilhaoperandos->sp]);
			printf("\npilha: %d", ae->pFrame->pilhaOperandos->elementos[ae->pFrame->pilhaOperandos->sp]);
		}

		return 0;
	}
	return -1;

}
