/*
 * Codigo inicial da JVM
 *
 * Este arquivo da inicio ao procedimento de execucao da Java Virtual Machine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ClassLoader.h"
#include "Util.h"

/*
 * Adiciona uma nova classe a lista de classes
 * */
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

Frame criaFrame(ClassFile *cf, char *nomeMetodo, char *descritor){
	Frame frame;
	method_info *metodo;
	int i;

	metodo = retornaMetodoPorNome(cf, nomeMetodo, descritor);
	for(i = 0; i < metodo->attributes_count; i++){
		if(strcmp((char*) retornaUtf8(cf, metodo->attributes[i].attribute_name_index), "Code") == 0){ //TODO Usar metodo criado
			frame.code_length = metodo->attributes[i].u.Code.code_length;
			frame.code = metodo->attributes[i].u.Code.code;
			break;
		}
	}
	frame.constant_pool = cf->constant_pool;
	frame.pilhaOperandos = malloc(/*maxPilha() * */sizeof(tipo));
	return frame;
}

void iniciaExecucaoMetodo(ClassFile *cf, List_Classfile *lcf, char *nomeMetodo, char *descritor) {
	Frame frame;

	frame = criaFrame(cf, nomeMetodo, descritor);

	printf("\n\nFim");
}

void iniciaClasse(char nomeClassFile[], List_Classfile *lcf, char *nomeMetodo, char *descritor) {
	ClassFile cf;

	strcat(nomeClassFile, ".class");
	cf = lerClassFile(nomeClassFile);
	adicionaClasse(&cf, &lcf);
	iniciaExecucaoMetodo(&cf, lcf, nomeMetodo, descritor);
}


/*
 * Funcao inicial da JVM
 *
 */
int main(int argc, char *argv[]) {
	List_Classfile *lcf = NULL;
	char *nomeClassFile;
	if (argc >= 2) {
		nomeClassFile = argv[1];
		iniciaClasse(nomeClassFile, lcf, "main", "([Ljava/lang/String;)V");
	}
	else {
		printf("O nome do arquivo .class deve ser passado como parametro.\nFavor verificar documentacao.\n"
			   "Ex: java Teste.class");
		return 1;
	}
	return 0;
}
