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

char * retornaUtf8(ClassFile *cf, u2 index){
	return cf->constant_pool[index-1].u.Utf8.bytes;
}

method_info retornaMetodoPorNome(ClassFile *cf, char *nomeMetodo, char *nomeDescritor ){
	int i=0;
	for (i=0; i<cf->methods_count; i++) {
			if (strcmp(nomeMetodo, retornaUtf8(cf, cf->methods[i].name_index)) == 0
					&&
					strcmp(nomeDescritor, retornaUtf8(cf, cf->methods[i].descriptor_index)) == 0) {
				printf("\n\n%d \n", i );
				return cf->methods[i];

			}
		}
}
