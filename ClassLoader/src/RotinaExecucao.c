/*
 * RotinaExecucao.c
 *
 *  Created on: 10/12/2011
 *      Author: Frederico
 */

/**
 * Le um byte do PC.
 * @param frame a variavel do frame atual
 */
#include "Estruturas.h"
#include "Instrucoes.h"

u1 leU1doPC(Frame *frame) {
	u1 instrucao;
	instrucao = *(frame->pc);
	frame->pc++;
	frame->enderecoPC++;
	return instrucao;
}

/**
 * Le dois bytes do PC.
 * @param frame a variavel do frame atual
 */
u2 leU2doPC(Frame *frame) {
	u1 part1, part2;
	u2 valor;
	part1 = *(frame->pc);

	part2 = *(frame->pc + 1);
	(frame->pc) += 2;

	frame->enderecoPC += 2;

	valor = (part1 << sizeof(u1) * 8) + part2;

	return valor;
}

/**
 * Le quatro bytes do PC.
 * @param frame a variavel do frame atual
 */
u4 leU4doPC(Frame *frame) {
	u1 part4, part3, part2, part1;
	u8 value;
	part4 = *(frame->pc);
	(frame->pc)++;
	part3 = *(frame->pc);
	(frame->pc)++;
	part2 = *(frame->pc);
	(frame->pc)++;
	part1 = *(frame->pc);
	(frame->pc)++;

	frame->enderecoPC += 4;

	value = (part4 << 3 * sizeof(u1) * 8) + (part3 << 2 * sizeof(u1) * 8)
			+ (part2 << 1 * sizeof(u1) * 8) + part1;
	return value;
}

int execute_iteration(AmbienteExecucao *ae) {

	while (1) {
		instrucao = leU1doPC(ae->pFrame);
		printf("\ninstrucao: %d", instrucao);
		vetFunc[instrucao](ae);
		if(instrucao == RETURN){
			break;
		}
	}
	return 0;
}
