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
int l2i(AmbienteExecucao *ae) {
//	PilhaOperandos *a;
//	int b;
//	a = desempilhaOperando(ae->pFrame);
//	b = (int) a->elementos->tipo_long;
//
//	empilhaOperando(ae->pFrame, "I", &(b));
//
	return 0;
}

int astore(AmbienteExecucao *ae) {
	u1 pos;

	switch (instrucao) {
	case ASTORE_0:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 0);
		break;
	case ASTORE_1:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 1);
		break;
	case ASTORE_2:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 2);
		break;
	case ASTORE_3:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 3);
		break;
	case ASTORE:
		pos = leU1doPC(ae->pFrame);
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, pos);
		break;
	}
	return 0;
}

int aload(AmbienteExecucao *ae) {

	u1 pos;
	switch(instrucao){
	case ALOAD_0:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 0);
		break;
	case ALOAD_1:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 1);
		break;
	case ALOAD_2:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 2);
		break;
	case ALOAD_3:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 3);
		break;
	case ALOAD:
		pos = leU1doPC(ae->pFrame);
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, pos);
		break;
	}
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
	u1 pos;

	switch(instrucao){
	case ILOAD_0:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 0);
		break;
	case ILOAD_1:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 1);
		break;
	case ILOAD_2:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 2);
		break;
	case ILOAD_3:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 3);
		break;
	case ILOAD:
		pos = leU1doPC(ae->pFrame);
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, pos);
		break;
	}
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

int lrem(AmbienteExecucao *ae) {
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
	u1 pos;

	switch (instrucao) {
	case DSTORE_0:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 0);
		break;
	case DSTORE_1:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 1);
		break;
	case DSTORE_2:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 2);
		break;
	case DSTORE_3:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 3);
		break;
	case DSTORE:
		pos = leU1doPC(ae->pFrame);
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, pos);
		break;
	}
	return 0;
}


int ldc(AmbienteExecucao *ae) {
//	char *string;
//	int integer;
//	float fvalue;
//	long long lvalue;
//	double dvalue;
//	u1 indice;
//
//	switch(instrucao){
//	case LDC_W:
//		break;
//	case LDC2_W:
//		break;
//	case LDC:
//		indice = leU1doPC(ae->pFrame);
//		//switch((signed int)find_tag_info(interpreter->current_frame->class_file, cp_index)) {
//		switch((signed int)(ae->pFrame->cf->constant_pool[indice -1]))
//		case 8:
//			/* CONSTANT_String */
//
////			string = find_string_info(interpreter->current_frame->class_file, cp_index);
////			opstack_push(&(interpreter->current_frame->opstack), "[", string);
//			string = ae->pFrame->cf->constant_pool[indice -1].u.Utf8.bytes;
//			empilhaOperando(ae->pFrame, "[",string);
//
//			break;
//		case 3:
//			/* CONSTANT_Integer */
//			integer = find_integer_info(interpreter->current_frame->class_file, cp_index);
//			opstack_push(&(interpreter->current_frame->opstack), "I", &integer);
//
//			break;
//		case 4:
//			/* CONSTANT_Float */
//			fvalue = find_float_info(interpreter->current_frame->class_file, cp_index);
//			opstack_push(&(interpreter->current_frame->opstack), "F", &fvalue);
//
//			break;
//		case 5:
//			/* CONSTANT_Long */
//			lvalue = find_long_info(interpreter->current_frame->class_file, cp_index);
//			opstack_push(&(interpreter->current_frame->opstack), "J", &lvalue);
//
//			break;
//		case 6:
//			/* CONSTANT_Double */
//			dvalue = find_double_info(interpreter->current_frame->class_file, cp_index);
//			opstack_push(&(interpreter->current_frame->opstack), "D", &dvalue);
//
//			break;
//
//		default:
//			fprintf(stderr,"Erro em 'ldc' tag: %d\n", (signed int)find_tag_info(interpreter->current_frame->class_file, cp_index));
//			exit(1);
//			break;
//		}
//
//		return 0;
//		break;
//	}
	return 0;
}

int fstore(AmbienteExecucao *ae) {
	u1 pos;

	switch (instrucao) {
	case FSTORE_0:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 0);
		break;
	case FSTORE_1:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 1);
		break;
	case FSTORE_2:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 2);
		break;
	case FSTORE_3:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 3);
		break;
	case FSTORE:
		pos = leU1doPC(ae->pFrame);
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, pos);
		break;
	}
	return 0;
}

int fload(AmbienteExecucao *ae) {
	u1 pos;
	switch(instrucao){
	case FLOAD_0:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 0);
		break;
	case FLOAD_1:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 1);
		break;
	case FLOAD_2:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 2);
		break;
	case FLOAD_3:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 3);
		break;
	case FLOAD:
		pos = leU1doPC(ae->pFrame);
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, pos);
		break;
	}
	return 0;
}

int f2l(AmbienteExecucao *ae) {
	return 0;
}

int lstore(AmbienteExecucao *ae) {
	u1 pos;

	switch (instrucao) {
	case LSTORE_0:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 0);
		break;
	case LSTORE_1:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 1);
		break;
	case LSTORE_2:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 2);
		break;
	case LSTORE_3:
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, 3);
		break;
	case LSTORE:
		pos = leU1doPC(ae->pFrame);
		transferePilhaOperandosParaVariavelLocal(ae->pFrame, pos);
		break;
	}
	return 0;
}

int dload(AmbienteExecucao *ae) {
	u1 pos;
	switch(instrucao){
	case DLOAD_0:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 0);
		break;
	case DLOAD_1:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 1);
		break;
	case DLOAD_2:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 2);
		break;
	case DLOAD_3:
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 3);
		break;
	case DLOAD:
		pos = leU1doPC(ae->pFrame);
		transfereVariavelLocalParaPilhaOperandos(ae->pFrame, pos);
		break;
	}
	return 0;
}

int d2i(AmbienteExecucao *ae) {
	return 0;
}
int lload(AmbienteExecucao *ae) {
	u1 pos;
	switch(instrucao){
		case LLOAD_0:
			transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 0);
			break;
		case LLOAD_1:
			transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 1);
			break;
		case LLOAD_2:
			transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 2);
			break;
		case LLOAD_3:
			transfereVariavelLocalParaPilhaOperandos(ae->pFrame, 3);
			break;
		case LLOAD:
			pos = leU1doPC(ae->pFrame);
			transfereVariavelLocalParaPilhaOperandos(ae->pFrame, pos);
			break;
		}
		return 0;
}

int lconst(AmbienteExecucao *ae) {
//	empilhaOperando(ae->pFrame, "J", &valor);
//
	return 0;
}

int fconst(AmbienteExecucao *ae) {
//	empilhaOperando(ae->pFrame, "F", &valor);
//
	return 0;
}

int dconst(AmbienteExecucao *ae) {
//	empilhaOperando(ae->pFrame, "D", &valor);
//
	return 0;
}

int sipush(AmbienteExecucao *ae) {
//	empilhaOperando(ae->pFrame, "I", &valor);
//
	return 0;
}

int pop(AmbienteExecucao *ae) {
	desempilhaOperando(ae->pFrame);

	return 0;
}

int pop2(AmbienteExecucao *ae) {
	if((*(ae->pFrame->pilhaOperandos->tipo)[0] == 'D') ||	(*(ae->pFrame->pilhaOperandos->tipo)[0] == 'J')) {
		 desempilhaOperando(ae->pFrame);
	} else {
		 desempilhaOperando(ae->pFrame);
		 desempilhaOperando(ae->pFrame);
	}

	return 0;
}


int d2f(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	float b;
	a = desempilhaOperando(ae->pFrame);
	b = (float) a->elementos->tipo_double;

	empilhaOperando(ae->pFrame, "F", &b);

	return 0;
}
//
int d2l(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	long long b;

	a = desempilhaOperando(ae->pFrame);
	b = (long long) a->elementos->tipo_double;

	empilhaOperando(ae->pFrame, "J", &b);

	return 0;
}

int f2d(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	double b;

	a = desempilhaOperando(ae->pFrame);
	b = (double) a->elementos->tipo_float;

	empilhaOperando(ae->pFrame, "D", &b);

	return 0;
}

int f2i(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	int b;

	a = desempilhaOperando(ae->pFrame);
	b = (int) a->elementos->tipo_float;

	empilhaOperando(ae->pFrame, "I", &b);

	return 0;
}

int i2b(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	char b;

	a = desempilhaOperando(ae->pFrame);
	b = (char) a->elementos->tipo_int;

	empilhaOperando(ae->pFrame, "B", &b);

	return 0;

}

int i2c(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	char b;

	a = desempilhaOperando(ae->pFrame);
	b = (char) a->elementos->tipo_int;

	empilhaOperando(ae->pFrame, "C", &b);

	return 0;
}

int i2f(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	float b;

	a = desempilhaOperando(ae->pFrame);
	b = (char) a->elementos->tipo_int;

	empilhaOperando(ae->pFrame, "F", &b);

	return 0;

}

int i2l(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	long long b;

	a = desempilhaOperando(ae->pFrame);
	b = (long long) a->elementos->tipo_int;

	empilhaOperando(ae->pFrame, "J", &b);

	return 0;
}

int i2s(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	short b;

	a = desempilhaOperando(ae->pFrame);
	b = (short) a->elementos->tipo_int;

	empilhaOperando(ae->pFrame, "S", &b);

	return 0;
}

int l2d(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	double b;

	a = desempilhaOperando(ae->pFrame);
	b = (double) a->elementos->tipo_long;

	empilhaOperando(ae->pFrame, "D", &b);

	return 0;
}

int l2f(AmbienteExecucao *ae) {
	PilhaOperandos *a;
	float b;

	a = desempilhaOperando(ae->pFrame);
	b = (float) a->elementos->tipo_long;

	empilhaOperando(ae->pFrame, "F", &b);

	return 0;
}

int dmul(AmbienteExecucao *ae) {
	double a, b, mul;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_double;

	mul = a*b;

	empilhaOperando(ae->pFrame, "D", &mul);

	return 0;
}

int fmul(AmbienteExecucao *ae) {
	float a, b, mul;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_float;

	mul = a*b;

	empilhaOperando(ae->pFrame, "F", &mul);

	return 0;
}

int imul(AmbienteExecucao *ae) {
	int a, b, mul;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_int;

	mul = a*b;

	empilhaOperando(ae->pFrame, "I", &mul);

	return 0;
}

int lmul(AmbienteExecucao *ae) {
	long long a, b, mul;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;

	mul = a*b;

	empilhaOperando(ae->pFrame, "J", &mul);

	return 0;
}

int getstatic(AmbienteExecucao *ae) {
	return 0;
}

int dadd(AmbienteExecucao *ae) {
	double a, b, sum;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	sum = a + b;

	empilhaOperando(ae->pFrame, "D", &sum);

	return 0;
}

int dsub(AmbienteExecucao *ae) {
	double a, b, sub;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	sub = b - a;

	empilhaOperando(ae->pFrame, "D", &sub);

	return 0;
}

int fadd(AmbienteExecucao *ae){
	float a, b, sum;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	sum = a + b;

	empilhaOperando(ae->pFrame,"F", &sum);

	return 0;
}

int fsub(AmbienteExecucao *ae) {
	float a, b, sub;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	sub = b - a;

	empilhaOperando(ae->pFrame, "F", &sub);

	return 0;
}

int isub(AmbienteExecucao *ae) {
	int a, b, sub;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	sub = b - a;

	empilhaOperando(ae->pFrame, "I", &sub);

	return 0;
}

int ladd(AmbienteExecucao *ae){
	long long a, b, sum;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	sum = a + b;

	empilhaOperando(ae->pFrame,"J", &sum);

	return 0;
}

int lsub(AmbienteExecucao *ae) {
	long long a, b, sub;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	sub = b - a;

	empilhaOperando(ae->pFrame, "J", &sub);

	return 0;
}

int iand(AmbienteExecucao *ae){
	int a, b, and;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	and = a & b;

	empilhaOperando(ae->pFrame, "I", &and);

	return 0;
}


int ineg(AmbienteExecucao *ae){
	int a, neg;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	neg = -a;

	empilhaOperando(ae->pFrame, "I", &neg);

	return 0;
}


int ior(AmbienteExecucao *ae){
	int a, b, or;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	or = a | b;

	empilhaOperando(ae->pFrame, "I", &or);

	return 0;
}

int ixor(AmbienteExecucao *ae){
	int a, b, xor;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	xor = a ^ b;

	empilhaOperando(ae->pFrame, "I", &xor);

	return 0;
}

int land(AmbienteExecucao *ae){
	long long a, b, and;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	and = a & b;

	empilhaOperando(ae->pFrame, "J", &and);

	return 0;
}

int lneg(AmbienteExecucao *ae){
	long long a, neg;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	neg = -a;

	empilhaOperando(ae->pFrame, "J", &neg);

	return 0;
}

int lor(AmbienteExecucao *ae){
	long long a, b, or;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	or = a | b;

	empilhaOperando(ae->pFrame, "J", &or);

	return 0;
}

int lxor(AmbienteExecucao *ae){
	long long a, b, xor;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	xor = a ^ b;

	empilhaOperando(ae->pFrame, "J", &xor);

	return 0;
}

int dneg(AmbienteExecucao *ae){
	double a, neg;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	neg = -a;

	empilhaOperando(ae->pFrame, "D", &neg);

	return 0;
}

int fneg(AmbienteExecucao *ae){
	float a, neg;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	neg = -a;

	empilhaOperando(ae->pFrame, "F", &neg);

	return 0;
}

int dcmpg(AmbienteExecucao *ae){
	double a, b;
	int pushval;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_double;

	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if(a < b) {
		pushval = -1;
	} else {
		pushval = 1;
	}


	empilhaOperando(ae->pFrame, "I", &pushval);
	return (0);
}

int dcmpl(AmbienteExecucao *ae){
	double a, b;
	int pushval;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if(a < b) {
		pushval = -1;
	} else {
		pushval = -1;
	}


	empilhaOperando(ae->pFrame, "I", &pushval);
	return (0);
}


int fcmpg(AmbienteExecucao *ae){
	float a, b;
	int pushval;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if(a < b) {
		pushval = -1;
	} else {
		pushval = 1;
	}
	empilhaOperando(ae->pFrame, "I", &pushval);
	return (0);
}

int fcmpl(AmbienteExecucao *ae){
	float a, b;
	int pushval;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if(a < b) {
		pushval = -1;
	} else {
		pushval = -1;
	}
	empilhaOperando(ae->pFrame, "I", &pushval);
	return (0);
}


int lcmp(AmbienteExecucao *ae){
	signed long long a, b;
	int pushval;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	if (a > b)
		pushval = 1;
	else {
		if (a == b)
			pushval = 0;
		else
			pushval = -1;
	}
	empilhaOperando(ae->pFrame, "J", &pushval);
	return (0);
}

int frem(AmbienteExecucao *ae) {
	float a, b, rem;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_float;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_float;

	rem = (float) fmod(a,b);

	empilhaOperando(ae->pFrame, "F", &rem);
	return 0;
}

int drem_(AmbienteExecucao *ae) {
	double a, b, rem;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_double;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_double;
	rem = fmod(a,b);

	empilhaOperando(ae->pFrame, "D", &rem);

	return 0;
}

int ishl(AmbienteExecucao *ae) {
	int a, b, mask, res;

	mask = 0x1F;		/* 0x1F, ou 31 seta os 5 primeiros bits como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	res = a<<(b & mask);

	empilhaOperando(ae->pFrame, "I", &res);

	return 0;
}

int ishr(AmbienteExecucao *ae) {
	int a, b, mask, res, sign;

	mask = 0x1F;			/* 0x1F, ou 31 seta os 5 primeiros bits como 1 */
	sign = 0x80000000;		/* Ultimo bit setado como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	sign = sign & a;		/* pegando o sign */
	res = a>>(b & mask);
	res = res | sign;		/* devolvendo o sign */

	empilhaOperando(ae->pFrame, "I", &res);

	return 0;
}

int iushr(AmbienteExecucao *ae) {
	int a, b, mask, res;

	mask = 0x1F;		/* 0x1F, ou 31 seta os 5 primeiros bits como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a >= 0)
		res = a>>(b & mask);
	else
		res = (a>>(b & mask)) + (2>>(b & mask));

	empilhaOperando(ae->pFrame, "I", &res);

	return 0;
}

int lshl(AmbienteExecucao *ae) {
	long long a, mask, res;
	int b;

	mask = 0x3F;		/* 0x3F, ou 63 seta os 6 primeiros bits como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;

	res = a<<(b & mask);

	empilhaOperando(ae->pFrame, "J", &res);

	return 0;
}

int lshr(AmbienteExecucao *ae) {
	long long a, mask, res, sign;
	int b;

	mask = 0x3F;					/* 0x1F, ou 63 seta os 6 primeiros bits como 1 */
	sign = 0x80000000;				/* Ultimo bit setado como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;

	sign = sign & a;		/* pegando o sign */
	res = a>>(b & mask);
	res = res | sign;		/* devolvendo o sign */

	empilhaOperando(ae->pFrame, "J", &res);

	return 0;
}

int lushr(AmbienteExecucao *ae) {
	long long a, mask, res;
	int b;

	mask = 0x3F;		/* 0x1F, ou 63 seta os 6 primeiros bits como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;

	if (a >= 0)
		res = a>>(b & mask);
	else
		res = (a>>(b & mask)) + (2L>>(b & mask));

	empilhaOperando(ae->pFrame, "J", &res);

	return 0;
}

int swap(AmbienteExecucao *ae){
	PilhaOperandos *a, *b;

	b = desempilhaOperando(ae->pFrame);
	a = desempilhaOperando(ae->pFrame);

	empilhaOperando(ae->pFrame,*(a->tipo),&(a->elementos));
	empilhaOperando(ae->pFrame,*(b->tipo),&(b->elementos));


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

int ldiv_(AmbienteExecucao *ae) {
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
		return jumpback(ae, 1);
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
