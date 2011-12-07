
/*
 * Util.h
 *
 * Interface do Util.c
 */

#ifndef ESTRUTURAS
	#define ESTRUTURAS
	#include "Estruturas.h"
#endif

char * retornaUtf8(ClassFile *cf, u2 index);

method_info *retornaMetodoPorNome(ClassFile *cf, char *nomeMetodo, char *nomeDescritor);

char * retornaNomeMetodo(ClassFile *cf, method_info *mi);

char * retornaNomeClasse (ClassFile *cf);
