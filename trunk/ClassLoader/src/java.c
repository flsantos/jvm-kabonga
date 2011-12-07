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

void iniciaExecucaoJVM(char nomeClassFile[], char *nomeMetodo, char *descritor) {
	ClassFile cf;
	List_Classfile *lcf = NULL;
	u2 i = 0;
	//Frame frame;

	nomeMetodo = realloc(nomeMetodo, (strlen(nomeMetodo) + 7) * sizeof(char));
	strcat(nomeClassFile, ".class");
	cf = lerClassFile(nomeClassFile);


	adicionaClasse(&cf, &lcf);
	//printf("A classe eh %s\n", lcf->class_name);

	method_info *mi;
	mi = retornaMetodoPorNome(&cf, "multiplica", "()I");
	printf("***\n\nmethod info %s\n\n", retornaNomeMetodo(&cf, mi));
	printf("\n%s \n ", retornaNomeClasse(&cf));
	printf("\nmethod name : %s\n", retornaUtf8(&cf, mi->name_index));
//a
	for (i=0; i<cf.methods_count ; i++) {
		if (strcmp("main",cf.constant_pool[cf.methods[i].name_index -1].u.Utf8.bytes) == 0 ) {
			/* Cria frame para executar o metodo porque as vezes agente vai chamar outro e passar isso por parametrs*/
			/*frame = iniciarFrame(indice_classe,indice_metodo,(numero_argumentos(indice_classe,indice_metodo)));
			executar_metodo(frame);
			free(frame);
			break;*/

		}
	}

	//Agora tem que ver se dentro desse cf existe a funcao main.

	printf("\n\nFim");
}

void iniciaClasse(char nomeClassFile[], List_Classfile *lcf) {
	ClassFile cf;

	nomeClassFile = realloc(nomeClassFile, (strlen(nomeClassFile) + 7) * sizeof(char));
	strcat(nomeClassFile, ".class");
	cf = lerClassFile(nomeClassFile);

	adicionaClasse(&cf, &lcf);
}

/*
 * Funcao inicial da JVM
 *
 */
int main(int argc, char *argv[]) {
	char *nomeClassFile;

	if (argc >= 2) {
		nomeClassFile= argv[1];
		iniciaExecucaoJVM(nomeClassFile, "main", "([LJava/lang/String;)V");
	}
	else {
		printf("O nome do arquivo .class deve ser passado como parametro.\nFavor verificar documentacao.\n"
			   "Ex: java Teste.class");
		return 1;
	}
	return 0;
}
