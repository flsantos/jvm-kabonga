
/*
 * Util.h
 *
 * Interface do Util.c
 */

#ifndef ESTRUTURAS
	#define ESTRUTURAS
	#include <stdarg.h>
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

void transferePilhaOperandosParaVariavelLocal(Frame *frame, u1 indiceVariavel);

void transferePilhaOperandosParaVariavelLocalPorFrames(Frame *frame1, Frame *frame2, u1 indiceVariavel);

void transfereVariavelLocalParaPilhaOperandos(Frame *frame, u1 indiceVariavel);

DadosMetodo *retornaDadosMetodo(ClassFile *cf, int n);

DadosNameAndType *retornaDadosNameAndTypeInfo(ClassFile *cf, int n);

DadosField *retornaDadosField(ClassFile *class, int n);

int retornaContadorArgumentos(char *descriptor);

Array *alocarVetor(char *tipo, int dimensao, ...);

void adicionaValorArray(Array *array, int posicao, char *tipo, void *info);

int defineFieldObjeto(Objeto *object, char *nomeField, char *tipo, Tipo info);

tipo_info *retornaFieldObjeto(Objeto *object, char *nomeField);

long long retornaLong(ClassFile *cf, int n);
