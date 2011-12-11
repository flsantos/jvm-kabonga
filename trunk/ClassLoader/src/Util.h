
/*
 * Util.h
 *
 * Interface do Util.c
 */

#ifndef ESTRUTURAS
	#define ESTRUTURAS
	#include "Estruturas.h"
#endif

u1 * retornaUtf8(ClassFile *cf, u2 index);

method_info *retornaMetodoPorNome(ClassFile *cf, char *nomeMetodo, char *nomeDescritor);

u1 * retornaNomeMetodo(ClassFile *cf, method_info *mi);

u1 * retornaNomeClasse (ClassFile *cf);

u2 retornaTamanhoPilha (attribute_info *ai);

u2 retornaTamanhoVariaveisLocais(attribute_info *ai);

u1 *retornaClassInfo(ClassFile *cf, int indice);

void empilhaOperando(Frame *frame, char *tipo, void *operando);

PilhaOperandos *desempilhaOperando(Frame *frame);

int pilhaOperandosVazia(Frame *frame);

void transferePilhaOperandosParaVariavelLocal(Frame *frame, int indiceVariavel);

void transfereVariavelLocalParaPilhaOperandos(Frame *frame, int indiceVariavel);

DadosMetodo *retornaDadosMetodo(ClassFile *cf, int n);
