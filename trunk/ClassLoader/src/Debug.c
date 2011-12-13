/*
 * Debug.c
 *
 *  Created on: Dec 13, 2011
 *      Author: Bruno Capu
 */

#include "Debug.h"

void debugPrintEmpilha(char *tipo, Frame *frame) {

	if (m_debug != 0) {
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
			if (frame->pilhaOperandos->elementos[sp].tipo_referencia == NULL) {
				printf("\n    empilha: L NULL");
			}
			else {
				printf("\n    empilha: L  0x%X", (char *)(frame->pilhaOperandos->elementos[sp].tipo_referencia));
			}
		} else if (tipo[0] == 'S') {
			printf("\n    empilha: S  %d", frame->pilhaOperandos->elementos[sp].tipo_short);
		} else if (tipo[0] == 'Z') {
			printf("\n    empilha: Z  %s", frame->pilhaOperandos->elementos[sp].tipo_boolean);
		} else if (tipo[0] == '[') {
			if (frame->pilhaOperandos->elementos[sp].tipo_referencia == NULL) {
				printf("\n    empilha: L NULL");
			}
			else {
				printf("\n    empilha: [  0x%X", (char *)frame->pilhaOperandos->elementos[sp].tipo_referencia);
			}
		} else if(tipo[0] == 'r') {
			printf("\n    empilha: retorno");
		}
	}
}

void debugPrintDesempilha(PilhaOperandos *operando) {

	if (m_debug != 0) {
		if (operando->tipo[operando->sp][0] == 'B') {
			printf("\n    desempilha: B  %d", operando->elementos[0].tipo_byte);
		} else if (operando->tipo[operando->sp][0] == 'C') {
			printf("\n    desempilha: C  %c", operando->elementos[0].tipo_char);
		} else if (operando->tipo[operando->sp][0] == 'D') {
			printf("\n    desempilha: D  %f", operando->elementos[0].tipo_double);
		} else if (operando->tipo[operando->sp][0] == 'F') {
			printf("\n    desempilha: F  %f", operando->elementos[0].tipo_float);
		} else if (operando->tipo[operando->sp][0] == 'I') {
			printf("\n    desempilha: I  %d", operando->elementos[0].tipo_int);
		} else if (operando->tipo[operando->sp][0] == 'J') {
			printf("\n    desempilha: J  %d", operando->elementos[0].tipo_long);
		} else if (operando->tipo[operando->sp][0] == 'L') {
			if (operando->elementos[0].tipo_referencia == NULL) {
				printf("\n    desempilha: [ NULL");
			}
			else {
				printf("\n    desempilha: L  0x%X", (char *)operando->elementos[0].tipo_referencia);
			}
		} else if (operando->tipo[operando->sp][0] == 'S') {
			printf("\n    desempilha: S  %d", operando->elementos[0].tipo_short);
		} else if (operando->tipo[operando->sp][0] == 'Z') {
			printf("\n    desempilha: Z  %s", operando->elementos[0].tipo_boolean);
		} else if (operando->tipo[operando->sp][0] == '[') {
			if (operando->elementos[0].tipo_referencia == NULL) {
				printf("\n    desempilha: [ NULL");
			}
			else {
				printf("\n    desempilha: [  0x%X", (char *)operando->elementos[0].tipo_referencia);
			}
		} else if(operando->tipo[operando->sp][0] == 'r') {
			printf("\n    desempilha: retorno");
		}
	}
}

void debugPrintEmpilhaTipo(PilhaOperandos *p1) {
	if (m_debug != 0) {
		if (p1->tipo[p1->sp][0] == 'B') {
			printf("\n    empilha: B  %d", p1->elementos[p1->sp].tipo_boolean);
		} else if (p1->tipo[p1->sp][0] == 'C') {
			printf("\n    empilha: C  %c", p1->elementos[p1->sp].tipo_char);
		} else if (p1->tipo[p1->sp][0] == 'D') {
			printf("\n    empilha: D  %f", p1->elementos[p1->sp].tipo_double);
		} else if (p1->tipo[p1->sp][0] == 'F') {
			printf("\n    empilha: F  %f", p1->elementos[p1->sp].tipo_float);
		} else if (p1->tipo[p1->sp][0] == 'I') {
			printf("\n    empilha: I  %d", p1->elementos[p1->sp].tipo_int);
		} else if (p1->tipo[p1->sp][0] == 'J') {
			printf("\n    empilha: J  %d", p1->elementos[p1->sp].tipo_long);
		} else if (p1->tipo[p1->sp][0] == 'L') {
			printf("\n    empilha: L  %s", (char *)(p1->elementos[p1->sp].tipo_referencia));
		} else if (p1->tipo[p1->sp][0] == 'S') {
			printf("\n    empilha: S  %d", p1->elementos[p1->sp].tipo_short);
		} else if (p1->tipo[p1->sp][0] == 'Z') {
			printf("\n    empilha: Z  %s", p1->elementos[p1->sp].tipo_boolean);
		} else if (p1->tipo[p1->sp][0] == '[') {
			printf("\n    empilha: [  %s", (char *)p1->elementos[p1->sp].tipo_referencia);
		} else if(p1->tipo[p1->sp][0] == 'r') {
			printf("\n    empilha: retorno");
		}
	}
}

void debugPause() {
	if (m_debug != 0) {
		getchar();
		getchar();
	}
}

void debugPrintLinha() {
	if (m_debug != 0) {
		printf("\n-----------------------------");

	}
}

