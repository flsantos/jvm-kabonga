/*
 * Heap.h
 *
 *  Created on: 09/12/2011
 *      Author: Frederico
 */

#ifndef HEAP_H_
#define HEAP_H_

void adicionaClasse (ClassFile *cf, List_Classfile **lcf, Objeto *obj);

ClassFile * buscarClassePorNome(List_Classfile *lcf, char *nomeClasse);

#endif /* HEAP_H_ */
