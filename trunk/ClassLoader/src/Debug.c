/*
 * Debug.c
 *
 *  Created on: Dec 13, 2011
 *      Author: Bruno Capu
 */

#include "Debug.h"

void debugPrintEmpilha(char *tipo, Frame *frame) {
	i2 sp = frame->pilhaOperandos->sp;

	if (tipo[0] == 'B') {
			printf("\n    empilha: B  %d", frame->pilhaOperandos->elementos[sp].tipo_byte);
		} else if (tipo[0] == 'C') {
			printf("\n    empilha: C  %c", frame->pilhaOperandos->elementos[sp].tipo_char);
		} else if (tipo[0] == 'D') {
			printf("\n    empilha: D  %f", frame->pilhaOperandos->elementos[sp].tipo_double);
		} else if (tipo[0] == 'F') {
			printf("\n    empilha: F  %f", frame->pilhaOperandos->elementos[sp].tipo_float);
		} else if (tipo[0] == 'I') {
			printf("\n    empilha: I  %d", frame->pilhaOperandos->elementos[sp].tipo_int);
		} else if (tipo[0] == 'J') {
			printf("\n    empilha: J  %d", frame->pilhaOperandos->elementos[sp].tipo_long);
		} else if (tipo[0] == 'L') {
			printf("\n    empilha: L  %s", (char *)(frame->pilhaOperandos->elementos[sp].tipo_referencia));
		} else if (tipo[0] == 'S') {
			printf("\n    empilha: S  %d", frame->pilhaOperandos->elementos[sp].tipo_short);
		} else if (tipo[0] == 'Z') {
			printf("\n    empilha: Z  %s", frame->pilhaOperandos->elementos[sp].tipo_boolean);
		} else if (tipo[0] == '[') {
			printf("\n    empilha: [  %s", (char *)frame->pilhaOperandos->elementos[sp].tipo_referencia);
		} else if(tipo[0] == 'r') {
			printf("\n    empilha: retorno");
		}
}

