/*
 * Instrucoes.c
 *
 *  Created on: 09/12/2011
 *      Author: Frederico
 */

#include "Estruturas.h"
#include "Instrucoes.h"
#include "Util.h"
#include "RotinaExecucao.h"
#include "java.h"
#include "FuncoesBasicas.h"

int (*vetFunc[])(AmbienteExecucao *p) = {
	nop,
	aconst_null,
	iconst,
	iconst,
	iconst,
	iconst,
	iconst,
	iconst,
	iconst,
	lconst,
	lconst,
	fconst,
	fconst,
	fconst,
	dconst,
	dconst,
	bipush,
	sipush,
	ldc,
	ldc,
	ldc,
	iload,
	lload,
	fload,
	dload,
	aload,
	iload,
	iload,
	iload,
	iload,
	lload,
	lload,
	lload,
	lload,
	fload,
	fload,
	fload,
	fload,
	dload,
	dload,
	dload,
	dload,
	aload,
	aload,
	aload,
	aload,
	iaload,
	laload,
	faload,
	daload,
	aaload,
	baload,
	caload,
	saload,
	istore,
	lstore,
	fstore,
	dstore,
	astore,
	istore,
	istore,
	istore,
	istore,
	lstore,
	lstore,
	lstore,
	lstore,
	fstore,
	fstore,
	fstore,
	fstore,
	dstore,
	dstore,
	dstore,
	dstore,
	astore,
	astore,
	astore,
	astore,
	iastore,
	lastore,
	fastore,
	dastore,
	aastore,
	bastore,
	castore,
	sastore,
	pop,
	pop2,
	dup,
	dup_x1,
	dup_x2,
	dup2,
	dup2_x1,
	dup2_x2,
	swap,
	iadd,
	ladd,
	fadd,
	dadd,
	isub,
	lsub,
	fsub,
	dsub,
	imul,
	lmul,
	fmul,
	dmul,
	idiv_,
	ldiv_,
	fdiv,
	ddiv,
	irem,
	lrem,
	frem,
	drem_,
	ineg,
	lneg,
	fneg,
	dneg,
	ishl,
	lshl,
	ishr,
	lshr,
	iushr,
	lushr,
	iand,
	land,
	ior,
	lor,
	ixor,
	lxor,
	iinc,
	i2l,
	i2f,
	i2d,
	l2i,
	l2f,
	l2d,
	f2i,
	f2l,
	f2d,
	d2i,
	d2l,
	d2f,
	i2b,
	i2c,
	i2s,
	lcmp,
	fcmpl,
	fcmpg,
	dcmpl,
	dcmpg,
	ifeq,
	ifne,
	iflt,
	ifge,
	ifgt,
	ifle,
	if_icmpeq,
	if_icmpne,
	if_icmplt,
	if_icmpge,
	if_icmpgt,
	if_icmple,
	if_acmpeq,
	if_acmpne,
	goto_,
	jsr,
	ret,
	tableswitch,
	lookupswitch,
	return1,
	return1,
	return1,
	return1,
	return1,
	return0,
	getstatic,
	putstatic,
	getfield,
	putfield,
	invokevirtual,
	invokespecial,
	invokestatic,
	nop, //TODO: invokeinterface,
		nop,//TODO: Mudar para vazio
		new_,
		newarray,
		anewarray,
		arraylength,
		athrow,
		checkcast,
		instanceof,
		nop,//TODO: monitorenter,
		nop,//TODO: monitorexit,
		wide,
		multianewarray,
		ifnull,
		ifnonnull,
		goto_w,
		jsr_w
};

int ireturn(AmbienteExecucao *ae) {
	int return_v;
	return_v = jumpback(ae, 1);

	return return_v;
}

//Inicio TODO do Rubens
//int lload(AmbienteExecucao *ae, int pos) {
//	transfer_localvar_to_opstack(&(ae->current_frame->local_variables), pos, &(ae->current_frame->opstack));
//
//	return 0;
//}
//
//
//int l2i(AmbienteExecucao *ae) {
//	PilhaOperandos *a;
//	int b;
//	a = desempilhaOperando(ae->pFrame);
//	b = (int) a->elementos->tipo_long;
//
//	empilhaOperando(ae->pFrame, "I", &(b));
//
//	return 0;
//}
//
//int lconst(AmbienteExecucao *ae, long long valor) {
//	empilhaOperando(ae->pFrame, "J", &valor);
//
//	return 0;
//}
//
//int fconst(AmbienteExecucao *ae, float valor) {
//	empilhaOperando(ae->pFrame, "F", &valor);
//
//	return 0;
//}
//
//int dconst(AmbienteExecucao *ae, double valor) {
//	empilhaOperando(ae->pFrame, "D", &valor);
//
//	return 0;
//}
//
//int sipush(AmbienteExecucao *ae, int valor) {
//	empilhaOperando(ae->pFrame, "I", &valor);
//
//	return 0;
//}
//TODO: fazer a funcao transfer_localvar_to_opstack
//int aload(AmbienteExecucao *ae, int pos) {
//	transfer_localvar_to_opstack(&(ae->current_frame->local_variables), pos, &(ae->current_frame->opstack));
//
//	return 0;
//}

int astore(AmbienteExecucao *ae) {
	u1 pos = leU1doPC(ae->pFrame);
	//transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);
	transferePilhaOperandosParaVariavelLocal(ae->pFrame, pos);
	return 0;
}

int aload(AmbienteExecucao *ae) {
	u1 pos = leU1doPC(ae->pFrame);
	//transfer_localvar_to_opstack(&(interpreter->current_frame->local_variables), pos, &(interpreter->current_frame->opstack));
	transfereVariavelLocalParaPilhaOperandos(ae->pFrame, pos);
	return 0;
}

int istore(AmbienteExecucao *ae) {
	//transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);
	u1 pos;

	switch (instrucao) {
	case ISTORE_0:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 0);
		break;
	case ISTORE_1:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 1);
		break;
	case ISTORE_2:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 2);
		break;
	case ISTORE_3:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 3);
		break;
	case ISTORE:
		pos = leU1doPC(ae->pFrame);
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, pos);
		break;
	}
	return 0;
}

int invokespecial(AmbienteExecucao *ae) {
	u2 indice = leU2doPC(ae->pFrame);
	DadosMetodo *dadosMetodo;
	int arg_count;

	printf("\ninvokespecial");
	//getchar();

	dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, indice);

	if ((strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuffer") == 0
			|| strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuilder") == 0)
			&& strcmp(dadosMetodo->nomeMetodo, "<init>") == 0) {
		desempilhaOperando(ae->pFrame);
		return 0;
	}

	arg_count = retornaContadorArgumentos(dadosMetodo->tipo) + 1;

	/*jump(ae, dadosMetodo->nomeClasse, dadosMetodo->nomeMetodo,
	 dadosMetodo->tipo, arg_count);*/
	iniciaClasse(dadosMetodo->nomeClasse, ae, dadosMetodo->nomeMetodo,
			dadosMetodo->tipo);

	return 0;
}

int dup(AmbienteExecucao *ae) {

	printf("\ndup");
	//getchar();

	//t_opstack *a = desempilhaOperando((&interpreter->current_frame->opstack));
	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	if ((*(a->tipo[0]) == 'J') || (*(a->tipo[0]) == 'D')) {
		printf(
				"Instrucao 'dup' nao permitida para valores 'double' ou 'long'.\n");
		exit(1);
	}

	//empilhaOperando_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame, a->tipo[0], &(a->elementos[a->sp]));
	//empilhaOperando_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame, a->tipo[0], &(a->elementos[a->sp]));

	return 0;
}

int new_(AmbienteExecucao *ae) {
	u2 indice = leU2doPC(ae->pFrame);
	char *nomeClasse;
	Objeto *objeto;
	printf("\nnew");
	//getchar();
	nomeClasse = (char *) retornaClassInfo(ae->pFrame->cf, indice);
	/* ajustando para o caso da StringBuffer */
	if ((strcmp(nomeClasse, "java/lang/StringBuffer") == 0
			|| strcmp(nomeClasse, "java/lang/StringBuilder") == 0)) {
		char * strvazia;
		strvazia = calloc(1, sizeof(char));
		*strvazia = '\0';
		//empilhaOperando(&(interpreter->current_frame->opstack), "[C", strvazia);
		empilhaOperando(ae->pFrame, "[C", strvazia);
		return 0;
	}

	//class_file = leitura_class_file(interpreter, nomeClasse);
	iniciaClasse(nomeClasse, ae, "<init>", "()V");

	objeto = instanciaObjeto(ae->pFrame->cf, ae);

	//empilhaOperando(&(interpreter->current_frame->opstack), "L", object);
	empilhaOperando(ae->pFrame, "L", objeto);

	return 0;

}

int if_icmplt(AmbienteExecucao *ae) {
	u2 branchoffset = leU2doPC(ae->pFrame);
	int a, b;
	//b = desempilhaOperando(&(interpreter->current_frame->opstack))->data.data_int;
	//a = desempilhaOperando(&(interpreter->current_frame->opstack))->data.data_int;

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a < b) {
		//interpreter->current_frame->pc += branchoffset -3;
		ae->pFrame->pc += branchoffset - 3;
		//interpreter->current_frame->pc_address += branchoffset -3;
		ae->pFrame->enderecoPC += branchoffset - 3;

	}

	return 0;
}

int iinc(AmbienteExecucao *ae) {
	u1 indice = leU1doPC(ae->pFrame);
	u1 const_ = leU1doPC(ae->pFrame);

	//(interpreter->current_frame->local_variables)[index].data.data_int += const_;
	ae->pFrame->pilhaVariaveisLocais->elementos[indice].tipo_int += const_;
	return 0;
}

int ifne(AmbienteExecucao *ae) {
	int a;
	u2 branchoffset = leU2doPC(ae->pFrame);
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a != 0) {
		//interpreter->current_frame->pc += branchoffset -3;
		ae->pFrame->pc += branchoffset - 3;
		//interpreter->current_frame->pc_address += branchoffset -3;
		ae->pFrame->enderecoPC += branchoffset - 3;
	}

	return 0;
}

int iload(AmbienteExecucao *ae) {
	u1 pos = leU1doPC(ae->pFrame);

	transfereVariavelLocalParaPilhaOperandos(ae->pFrame, pos);
	return 0;
}

int irem(AmbienteExecucao *ae) {
	int a, b, rem;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	rem = b % a;

	empilhaOperando(ae->pFrame, "I", &rem);

	return 0;
}

int goto_(AmbienteExecucao *ae) {
	u2 branchoffset = leU2doPC(ae->pFrame);

	ae->pFrame->pc += branchoffset - 3;

	return 0;
}

int iconst(AmbienteExecucao *ae) {
	int valor;

	printf("\niconst");

	switch (instrucao) {
	case ICONST_M1:
		valor = -1;
		break;
	case ICONST_0:
		valor = 0;
		break;
	case ICONST_1:
		valor = 1;
		break;
	case ICONST_2:
		valor = 2;
		break;
	case ICONST_3:
		valor = 3;
		break;
	case ICONST_4:
		valor = 4;
		break;
	case ICONST_5:
		valor = 5;
		break;
	}

	empilhaOperando(ae->pFrame, "I", &valor);

	return 0;
}

int invokevirtual(AmbienteExecucao *ae) {
	/* TODO: este invoke virtual nao esta pronto. so foi feito invoke
	 * virtual de excecao para o println, apenas!
	 */
	int cp_indice = leU2doPC(ae->pFrame);
	//TODO:
	DadosMetodo *dadosMetodo;
	PilhaOperandos *data;
	char *tipo;
	char *string1, *string2;
	int result_strcmp;
	char *string_to_append, *string_appended, *string_append;

	dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, cp_indice);

	if (strcmp(dadosMetodo->nomeClasse, "java/io/PrintStream") == 0
			&& (strcmp(dadosMetodo->nomeMetodo, "println") == 0
					|| strcmp(dadosMetodo->nomeMetodo, "print") == 0)) {
		/* realiza o println */
		if (ae->pFrame->pilhaOperandos->tipo[ae->pFrame->pilhaOperandos->sp][0]
				!= '#') {
			data = desempilhaOperando(ae->pFrame);
			tipo = data->tipo[ae->pFrame->pilhaOperandos->sp];
			if (tipo[0] == 'B') {
				printf("%d", data->elementos[0].tipo_byte);
			} else if (tipo[0] == 'C') {
				printf("%c", (unsigned char) data->elementos[0].tipo_char);
			} else if (tipo[0] == 'D') {
				printf("%f", data->elementos[0].tipo_double);
			} else if (tipo[0] == 'F') {
				printf("%f", data->elementos[0].tipo_float);
			} else if (tipo[0] == 'I') {
				printf("%d", data->elementos[0].tipo_int);
			} else if (tipo[0] == 'J') {
				printf("%d", data->elementos[0].tipo_long);
			} else if (tipo[0] == 'L') {
				printf("Impressao de um objeto?! Não implementado!");
			} else if (tipo[0] == 'S') {
				printf("%d", data->elementos[0].tipo_short);
			} else if (tipo[0] == 'Z') {
				printf("%d", data->elementos[0].tipo_boolean);
			} else if (tipo[0] == '[') {
				printf("%s", (char*) data->elementos[0].tipo_referencia);
			} else if (tipo[0] == 'r') {
				printf("Impressao de uma referencia. Arrumar.");
			}
		}
		desempilhaOperando(ae->pFrame);

		if ((strcmp(dadosMetodo->nomeMetodo, "println") == 0)) {
			printf("\n");
		}
	} else if (strcmp(dadosMetodo->nomeClasse, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "equals") == 0) {
		string1 =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

		if (strcmp(string1, string2) == 0) {
			result_strcmp = 1;
			empilhaOperando(ae->pFrame, "I", &result_strcmp);
			return 0;
		} else {
			result_strcmp = 0;
			empilhaOperando(ae->pFrame, "I", &result_strcmp);
			return 0;
		}
	} else if ((strcmp(dadosMetodo->nomeMetodo, "java/lang/StringBuffer") == 0
			|| strcmp(dadosMetodo->nomeMetodo, "java/lang/StringBuilder") == 0)
			&& strcmp(dadosMetodo->nomeMetodo, "append") == 0) {
		string_append = calloc(50, sizeof(char));
		data = desempilhaOperando(ae->pFrame);
		tipo = data->tipo[ae->pFrame->pilhaOperandos->sp];
		string_to_append =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
		if (tipo[0] == 'B') {
			sprintf(string_append, "%d", data->elementos[0].tipo_byte);
		} else if (tipo[0] == 'C') {
			sprintf(string_append, "%c",
					(unsigned char) data->elementos[0].tipo_char);
		} else if (tipo[0] == 'D') {
			sprintf(string_append, "%f", data->elementos[0].tipo_double);
		} else if (tipo[0] == 'F') {
			sprintf(string_append, "%f", data->elementos[0].tipo_float);
		} else if (tipo[0] == 'I') {
			sprintf(string_append, "%d", data->elementos[0].tipo_int);
		} else if (tipo[0] == 'J') {
			sprintf(string_append, "%d", data->elementos[0].tipo_long);
		} else if (tipo[0] == 'L') {
			sprintf(string_append, "Impressao de um objeto?!");
		} else if (tipo[0] == 'S') {
			sprintf(string_append, "%d", data->elementos[0].tipo_short);
		} else if (tipo[0] == 'Z') {
			sprintf(string_append, "%d", data->elementos[0].tipo_boolean);
		} else if (tipo[0] == '[') {
			string_append = (char*) data->elementos[0].tipo_referencia;
		} else if (tipo[0] == 'r') {
			sprintf(string_append, "Impressao de uma referencia. Arrumar.");
		}

		string_appended = calloc(
				strlen(string_append) + strlen(string_to_append) + 1,
				sizeof(char));
		*string_appended = '\0';
		strcat(string_appended, string_to_append);
		strcat(string_appended, string_append);

		empilhaOperando(ae->pFrame, "[C", string_appended);
		return 0;

	} else if ((strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuffer") == 0
			|| strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuilder") == 0)
			&& strcmp(dadosMetodo->nomeMetodo, "toString") == 0) {
		return 0;
	} else if (strcmp(dadosMetodo->nomeClasse, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "length") == 0) {
		int len;
		string1 =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

		len = strlen(string1);

		empilhaOperando(ae->pFrame, "I", &len);

		return 0;
	} else if (strcmp(dadosMetodo->nomeClasse, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "compareTo") == 0) {
		int strcm;
		string1 =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

		strcm = strcmp(string1, string2);

		empilhaOperando(ae->pFrame, "I", &strcm);

		return 0;
	} else if (strcmp(dadosMetodo->nomeMetodo, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "indexOf") == 0
			&& strcmp(dadosMetodo->tipo, "(Ljava/lang/String;)I") == 0) {
		int strstr_value;
		char *strstr_char;
		string1 =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

		strstr_char = strstr(string1, string2);
		strstr_value = strstr_char - string1;

		empilhaOperando(ae->pFrame, "I", &strstr_value);

		return 0;
	} else if (strcmp(dadosMetodo->nomeMetodo, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "startsWith") == 0
			&& strcmp(dadosMetodo->tipo, "(Ljava/lang/String;)Z") == 0) {
		char bool_return;
		char *strstr_char;
		string1 =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

		strstr_char = strstr(string1, string2);
		bool_return = (strstr_char - string1 == 0) ? 1 : 0;

		empilhaOperando(ae->pFrame, "Z", &bool_return);

		return 0;

	} else {
		DadosMetodo *dadosMetodo;
		int arg_count;

		dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, cp_indice);

		arg_count = retornaContadorArgumentos(dadosMetodo->tipo) + 1;

//				jump(ae, dadosMetodo->nomeClasse, dadosMetodo->nomeMetodo,
//						dadosMetodo->tipo, arg_count);

		iniciaClasse(dadosMetodo->nomeClasse, ae, dadosMetodo->nomeMetodo,
				dadosMetodo->tipo);
	}

	return 0;

}

int nop(AmbienteExecucao *ae) {
	return 0;
}
int bipush(AmbienteExecucao *ae) {
	return 0;
}
int aconst_null(AmbienteExecucao *ae) {
	return 0;
}

int iadd(AmbienteExecucao *ae) {
	return 0;
}

int i2d(AmbienteExecucao *ae) {
	return 0;
}

int dstore(AmbienteExecucao *ae) {
	return 0;
}

int ldc(AmbienteExecucao *ae) {
	return 0;
}

int fstore(AmbienteExecucao *ae) {
	return 0;
}

int fload(AmbienteExecucao *ae) {
	return 0;
}

int f2l(AmbienteExecucao *ae) {
	return 0;
}

int lstore(AmbienteExecucao *ae) {
	return 0;
}

int dload(AmbienteExecucao *ae) {
	return 0;
}

int d2i(AmbienteExecucao *ae) {
	return 0;
}
int lload(AmbienteExecucao *ae) {
	return 0;
}

int l2i(AmbienteExecucao *ae) {
	return 0;
}

int lconst(AmbienteExecucao *ae) {
	return 0;
}

int fconst(AmbienteExecucao *ae) {
	return 0;
}

int dconst(AmbienteExecucao *ae) {
	return 0;
}

int sipush(AmbienteExecucao *ae) {
	return 0;
}

int pop(AmbienteExecucao *ae) {
	return 0;
}

int pop2(AmbienteExecucao *ae) {
	return 0;
}

int d2f(AmbienteExecucao *ae) {
	return 0;
}

int d2l(AmbienteExecucao *ae) {
	return 0;
}

int f2d(AmbienteExecucao *ae) {
	return 0;
}

int f2i(AmbienteExecucao *ae) {
	return 0;
}

int i2b(AmbienteExecucao *ae) {
	return 0;
}

int i2c(AmbienteExecucao *ae) {
	return 0;
}

int i2f(AmbienteExecucao *ae) {
	return 0;
}

int i2l(AmbienteExecucao *ae) {
	return 0;
}

int i2s(AmbienteExecucao *ae) {
	return 0;
}

int l2d(AmbienteExecucao *ae) {
	return 0;
}

int l2f(AmbienteExecucao *ae) {
	return 0;
}

int dmul(AmbienteExecucao *ae) {
	return 0;
}

int fmul(AmbienteExecucao *ae) {
	return 0;
}

int imul(AmbienteExecucao *ae) {
	return 0;
}

int lmul(AmbienteExecucao *ae) {
	return 0;
}

int getstatic(AmbienteExecucao *ae) {
	return 0;
}

int dadd(AmbienteExecucao *ae) {
	return 0;
}
int dsub(AmbienteExecucao *ae) {
	return 0;
}
int fadd(AmbienteExecucao *ae) {
	return 0;
}
int fsub(AmbienteExecucao *ae) {
	return 0;
}
int isub(AmbienteExecucao *ae) {
	return 0;
}
int ladd(AmbienteExecucao *ae) {
	return 0;
}
int lsub(AmbienteExecucao *ae) {
	return 0;
}

int iand(AmbienteExecucao *ae) {
	return 0;
}
int ineg(AmbienteExecucao *ae) {
	return 0;
}
int ior(AmbienteExecucao *ae) {
	return 0;
}
int ixor(AmbienteExecucao *ae) {
	return 0;
}
int land(AmbienteExecucao *ae) {
	return 0;
}
int lneg(AmbienteExecucao *ae) {
	return 0;
}
int lor(AmbienteExecucao *ae) {
	return 0;
}
int lxor(AmbienteExecucao *ae) {
	return 0;
}
int dneg(AmbienteExecucao *ae) {
	return 0;
}
int fneg(AmbienteExecucao *ae) {
	return 0;
}
int ldiv_(AmbienteExecucao *ae) {
	return 0;
}
int lrem(AmbienteExecucao *ae) {
	return 0;
}

int fcmpg(AmbienteExecucao *ae) {
	return 0;
}
int fcmpl(AmbienteExecucao *ae) {
	return 0;
}
int lcmp(AmbienteExecucao *ae) {
	return 0;
}
int frem(AmbienteExecucao *ae) {
	return 0;
}
int drem_(AmbienteExecucao *ae) {
	return 0;
}
int ishl(AmbienteExecucao *ae) {
	return 0;
}
int ishr(AmbienteExecucao *ae) {
	return 0;
}
int iushr(AmbienteExecucao *ae) {
	return 0;
}
int lshl(AmbienteExecucao *ae) {
	return 0;
}
int lshr(AmbienteExecucao *ae) {
	return 0;
}
int lushr(AmbienteExecucao *ae) {
	return 0;
}
int swap(AmbienteExecucao *ae) {
	return 0;
}

int dup2(AmbienteExecucao *ae) {
	return 0;
}
int dup_x1(AmbienteExecucao *ae) {
	return 0;
}
int dup2_x2(AmbienteExecucao *ae) {
	return 0;
}
int dup_x2(AmbienteExecucao *ae) {
	return 0;
}
int dup2_x1(AmbienteExecucao *ae) {
	return 0;
}

int goto_w(AmbienteExecucao *ae) {
	return 0;
}

int jsr(AmbienteExecucao *ae) {
	return 0;
}
int jsr_w(AmbienteExecucao *ae) {
	return 0;
}

int newarray(AmbienteExecucao *ae) {
	return 0;
}
int aaload(AmbienteExecucao *ae) {
	return 0;
}
int iaload(AmbienteExecucao *ae) {
	return 0;
}
int aastore(AmbienteExecucao *ae) {
	return 0;
}
int iastore(AmbienteExecucao *ae) {
	return 0;
}

int idiv_(AmbienteExecucao *ae) {
	return 0;
}

int if_acmpeq(AmbienteExecucao *ae) {
	return 0;
}
int if_acmpne(AmbienteExecucao *ae) {
	return 0;
}
int if_icmpeq(AmbienteExecucao *ae) {
	return 0;
}
int if_icmpne(AmbienteExecucao *ae) {
	return 0;
}

int if_icmple(AmbienteExecucao *ae) {
	return 0;
}
int if_icmpgt(AmbienteExecucao *ae) {
	return 0;
}
int if_icmpge(AmbienteExecucao *ae) {
	return 0;
}
int ifeq(AmbienteExecucao *ae) {
	return 0;
}

int iflt(AmbienteExecucao *ae) {
	return 0;
}
int ifle(AmbienteExecucao *ae) {
	return 0;
}
int ifgt(AmbienteExecucao *ae) {
	return 0;
}
int ifge(AmbienteExecucao *ae) {
	return 0;
}
int ifnonnull(AmbienteExecucao *ae) {
	return 0;
}
int ifnull(AmbienteExecucao *ae) {
	return 0;
}

int fastore(AmbienteExecucao *ae) {
	return 0;
}
int faload(AmbienteExecucao *ae) {
	return 0;
}
int daload(AmbienteExecucao *ae) {
	return 0;
}
int dastore(AmbienteExecucao *ae) {
	return 0;
}
int caload(AmbienteExecucao *ae) {
	return 0;
}
int castore(AmbienteExecucao *ae) {
	return 0;
}
int laload(AmbienteExecucao *ae) {
	return 0;
}
int lastore(AmbienteExecucao *ae) {
	return 0;
}
int saload(AmbienteExecucao *ae) {
	return 0;
}
int sastore(AmbienteExecucao *ae) {
	return 0;
}
int baload(AmbienteExecucao *ae) {
	return 0;
}
int bastore(AmbienteExecucao *ae) {
	return 0;
}

int arraylength(AmbienteExecucao *ae) {
	return 0;
}

int return0(AmbienteExecucao *ae) {
	return 0;
}
int return1(AmbienteExecucao *ae) {
	return 0;
}

int athrow(AmbienteExecucao *ae) {
	return 0;
}

int ret(AmbienteExecucao *ae) {
	return 0;
}

int multianewarray(AmbienteExecucao *ae) {
	return 0;
}

int anewarray(AmbienteExecucao *ae) {
	return 0;
}

int wide(AmbienteExecucao *ae) {
	return 0;
}

int putfield(AmbienteExecucao *ae) {
	return 0;
}
int getfield(AmbienteExecucao *ae) {
	return 0;
}

int fdiv(AmbienteExecucao *ae) {
	return 0;
}
int ddiv(AmbienteExecucao *ae) {
	return 0;
}

int dcmpl(AmbienteExecucao *ae) {
	return 0;
}
int dcmpg(AmbienteExecucao *ae) {
	return 0;
}

int checkcast(AmbienteExecucao *ae) {
	return 0;
}
int instanceof(AmbienteExecucao *ae) {
	return 0;
}

int invokestatic(AmbienteExecucao *ae) {
	return 0;
}

int putstatic(AmbienteExecucao *ae) {
	return 0;
}

int lookupswitch(AmbienteExecucao *ae) {
	return 0;
}
int tableswitch(AmbienteExecucao *ae) {
	return 0;
}
