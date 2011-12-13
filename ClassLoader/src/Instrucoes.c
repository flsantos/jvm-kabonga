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

int lrem(AmbienteExecucao *ae){
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
	int argumento;

	dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, indice);
	if ((strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuffer") == 0
			|| strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuilder") == 0)
			&& strcmp(dadosMetodo->nomeMetodo, "<init>") == 0) {
		desempilhaOperando(ae->pFrame);
		return 0;
	}

	argumento = retornaContadorArgumentos(dadosMetodo->tipo) + 1;

	/*jump(ae, dadosMetodo->nomeClasse, dadosMetodo->nomeMetodo,
	 dadosMetodo->tipo, argumento);*/
	iniciaExecucaoMetodo(dadosMetodo->nomeClasse, ae, dadosMetodo->nomeMetodo,
			dadosMetodo->tipo, argumento);

	return 0;
}

int newarray(AmbienteExecucao *ae){
	return 0;
}

int dup(AmbienteExecucao *ae) {

	//t_opstack *a = desempilhaOperando((&interpreter->current_frame->opstack));
	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	if (((a->tipo[a->sp][0]) == 'J') || ((a->tipo[a->sp][0]) == 'D')) {
		printf(
				"Instrucao 'dup' nao permitida para valores 'double' ou 'long'.\n");
		exit(1);
	}

	//empilhaOperando_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame, a->tipo[a->sp], &(a->elementos[a->sp]));
	//empilhaOperando_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame, a->tipo[a->sp], &(a->elementos[a->sp]));

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
	verificarClassFile(ae, nomeClasse);
	objeto = ae->pClassHeap->obj;

	//empilhaOperando(&(interpreter->current_frame->opstack), "L", object);
	empilhaOperando(ae->pFrame, "L", objeto);

	return 0;

}

/**
 * @author Daniel
 */
int if_icmplt(AmbienteExecucao *ae) {
	i2 offsetDestino = leU2doPC(ae->pFrame);
	int a, b;
	//b = desempilhaOperando(&(interpreter->current_frame->opstack))->data.data_int;
	//a = desempilhaOperando(&(interpreter->current_frame->opstack))->data.data_int;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a < b) {
		//interpreter->current_frame->pc += branchoffset -3;
		ae->pFrame->pc += offsetDestino - 3;
		//interpreter->current_frame->pc_address += branchoffset -3;
		ae->pFrame->enderecoPC += offsetDestino - 3;

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

int goto_(AmbienteExecucao *ae) {
	u2 branchoffset = leU2doPC(ae->pFrame);

	ae->pFrame->pc += branchoffset - 3;

	return 0;
}

int iconst(AmbienteExecucao *ae) {
	int valor;

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
				printf("%d", data->elementos[data->sp].tipo_byte);
			} else if (tipo[0] == 'C') {
				printf("%c", (unsigned char) data->elementos[data->sp].tipo_char);
			} else if (tipo[0] == 'D') {
				printf("%f", data->elementos[data->sp].tipo_double);
			} else if (tipo[0] == 'F') {
				printf("%f", data->elementos[data->sp].tipo_float);
			} else if (tipo[0] == 'I') {
				printf("%d", data->elementos[data->sp].tipo_int);
			} else if (tipo[0] == 'J') {
				printf("%d", data->elementos[data->sp].tipo_long);
			} else if (tipo[0] == 'L') {
				printf("Impressao de um objeto?! Não implementado!");
			} else if (tipo[0] == 'S') {
				printf("%d", data->elementos[data->sp].tipo_short);
			} else if (tipo[0] == 'Z') {
				printf("%d", data->elementos[data->sp].tipo_boolean);
			} else if (tipo[0] == '[') {
				printf("%s", (char*) data->elementos[data->sp].tipo_referencia);
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
		int argumento;

		dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, cp_indice);

		argumento = retornaContadorArgumentos(dadosMetodo->tipo) + 1;

//				jump(ae, dadosMetodo->nomeClasse, dadosMetodo->nomeMetodo,
//						dadosMetodo->tipo, argumento);

		iniciaExecucaoMetodo(dadosMetodo->nomeClasse, ae, dadosMetodo->nomeMetodo,
				dadosMetodo->tipo, argumento);
	}

	return 0;

}

int nop(AmbienteExecucao *ae) {
	return 0;
}
int bipush(AmbienteExecucao *ae) {
	u1 valor;
	valor = leU1doPC(ae->pFrame);

	empilhaOperando(ae->pFrame, "I", (&valor));
	return 0;
}

/*
 * @author Daniel
 */
int aconst_null(AmbienteExecucao *ae) {
	empilhaOperando(ae->pFrame,"[",NULL);
	return 0;
}

/*
 * @author Bruno Capu
 */
int iadd(AmbienteExecucao *ae) {
	int a, b, soma;
	soma = 0;

	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	soma = a + b;
	empilhaOperando(ae->pFrame, "I", &soma);
	return 0;
}

/*
 * @author Bruno capu
 */
int i2d(AmbienteExecucao *ae) {
	int a;
	double b;

	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	b = (double) a;
	empilhaOperando(ae->pFrame, "D", &b);
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

/*
 * @Author: Daniel
 */

int ldc(AmbienteExecucao *ae) {
	char *string;
	int integer;
	uFloat fvalue;
	long long lvalue;
	uDouble dvalue;
	u2 indice;

	switch(instrucao){
	case LDC_W:
		indice = (int)leU1doPC(ae->pFrame);
		break;
	case LDC2_W:
		indice = (int)leU2doPC(ae->pFrame);
		break;
	case LDC:
		indice = (int)leU2doPC(ae->pFrame);
		break;
	}

	switch((signed int)(ae->pFrame->cf->constant_pool[indice -1].tag)){
	case 8:
		/* CONSTANT_String */
		string = ae->pFrame->cf->constant_pool[indice -1].u.Utf8.bytes;
		empilhaOperando(ae->pFrame, "[",string);
		break;
	case 3:
		/* CONSTANT_Integer */
		integer = ae->pFrame->cf->constant_pool[indice -1].u.Integer.bytes;
		empilhaOperando(ae->pFrame,"I", &integer);

		break;
	case 4:
		/* CONSTANT_Float */
		fvalue = ae->pFrame->cf->constant_pool[indice -1].u.Float.bytes;
		empilhaOperando(ae->pFrame,"F", &fvalue);

		break;
	case 5:
		/* CONSTANT_Long */
		lvalue = retornaLong(ae->pFrame->cf, indice -1);
		empilhaOperando(ae->pFrame,"J", &lvalue);

		break;
	case 6:
		/* CONSTANT_Double */

		dvalue = ae->pFrame->cf->constant_pool[indice -1].u.Double.bytes;
		empilhaOperando(ae->pFrame,"D", &dvalue);

		break;

	default:
		printf("Erro em 'ldc' tag: %d\n", (signed int)ae->pFrame->cf->constant_pool[indice -1].tag);
		exit(1);
		break;
	}

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

/*
 * @author Bruno Capu
 */
int f2l(AmbienteExecucao *ae) {
	float a;
	long long b;

	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_float;
	b = (long long) a;

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

/*
 * @autor: Daniel
 */
int d2i(AmbienteExecucao *ae) {
	double a;
	int b;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	b = (int)a;

	empilhaOperando(ae->pFrame, "I", &b);
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

/*
 * @author Bruno Capu
 */
int fconst(AmbienteExecucao *ae) {
	float valor;
	valor = 0;

	switch (instrucao) {
	case FCONST_0 :
		valor = 0;
		break;
	case FCONST_1 :
		valor = 1;
		break;
	case FCONST_2 :
		valor = 2;
		break;
	}

	empilhaOperando(ae->pFrame, "F", &valor);

	return 0;
}

int dconst(AmbienteExecucao *ae) {

//	empilhaOperando(ae->pFrame, "D", &valor);
//
	return 0;
}

int sipush(AmbienteExecucao *ae) {
	u2 valor = leU2doPC(ae->pFrame);
	empilhaOperando(ae->pFrame, "I", &valor);

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

/*
 * @author Capu
 */
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

/*
 * @author Daniel
 */
int swap(AmbienteExecucao *ae) {

	PilhaOperandos *a, *b;
	a = desempilhaOperando(ae->pFrame);
	b = desempilhaOperando(ae->pFrame);

	empilhaOperando(ae->pFrame, a->tipo[a->sp], a->elementos);
	empilhaOperando(ae->pFrame, b->tipo[a->sp], b->elementos);

	return 0;
}

int dup2(AmbienteExecucao *ae){
	PilhaOperandos *a, *b;

	a = desempilhaOperando(ae->pFrame);
	if ( (*(a->tipo)[0] == 'J' ) || (*(a->tipo)[0] == 'D' ) ) {
		/*float type e double type*/
		empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
		empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
		return 0;
	}

	b = desempilhaOperando(ae->pFrame);
	if( (*(b->tipo)[0] == 'J' ) || (*(b->tipo)[0] == 'D') ){
		fprintf(stderr,"Operacao 'dup2' nao permitida para value2 'float' ou 'double' type.\n");
		exit(1);
	}

	empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
	empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);

	return 0;
}

int dup_x1(AmbienteExecucao *ae){

	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	PilhaOperandos *b = desempilhaOperando(ae->pFrame);
	if( ( strchr((b->tipo)[0],'J') != NULL ) || ( strchr((b->tipo)[0],'D') != NULL ) || ( strchr((a->tipo)[0],'J') != NULL ) || ( strchr((a->tipo)[0],'D') != NULL ) ) {
		fprintf(stderr,"Instrucao 'dup_x1' nao permitida para 'float' ou 'double' type.\n");
		exit(1);
	}

	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
	empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
	return 0;
}

int dup_x2(AmbienteExecucao *ae){

	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	if(( strchr((a->tipo)[0],'J') != NULL ) || ( strchr((a->tipo)[0],'D') != NULL )){
		fprintf(stderr,"Instrucao 'dup_x2' nao permitida para 'double' ou 'long'1.\n");
		exit(1);
	}

	PilhaOperandos *b = desempilhaOperando(ae->pFrame);
	if(( strchr((b->tipo)[0],'J') != NULL ) || ( strchr((b->tipo)[0],'D') != NULL )){
		/*form 2*/
		empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
		empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
		empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
		return 0;
	}

	PilhaOperandos *c = desempilhaOperando(ae->pFrame);
	if(( strchr((c->tipo)[0],'J') != NULL ) || ( strchr((c->tipo)[0],'D') != NULL )){
		fprintf(stderr,"Instrucao 'dup_x2' nao permitida para 'double' ou 'long'2.\n");
		exit(1);
	}

	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
	empilhaOperando(ae->pFrame,(c->tipo)[0],c->elementos);
	empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);

	return 0;
}

int dup2_x1(AmbienteExecucao *ae){

	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	PilhaOperandos *b = desempilhaOperando(ae->pFrame);
	if(( strchr((b->tipo)[0],'J') != NULL ) || ( strchr((b->tipo)[0],'D') != NULL )){
		fprintf(stderr,"Instrucao 'dup2_x1' nao permitida para value2 of 'double' ou 'float'.\n");
		exit(1);
	}
	if(( strchr((a->tipo)[0],'J') != NULL ) || ( strchr((a->tipo)[0],'D') != NULL )){
		empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
		empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
		empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
		return 0;
	}
	PilhaOperandos *c = desempilhaOperando(ae->pFrame);
	if(( strchr((c->tipo)[0],'J') != NULL ) || ( strchr((c->tipo)[0],'D') != NULL )){
		fprintf(stderr,"Instrucao 'dup2_x1' nao permitida para value3 ou 'double' ou 'float'.\n");
		exit(1);
	}

	empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
	empilhaOperando(ae->pFrame,(c->tipo)[0],c->elementos);
	empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);

	return 0;
}

int dup2_x2(AmbienteExecucao *ae){

	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	PilhaOperandos *b = desempilhaOperando(ae->pFrame);
	PilhaOperandos *c, *d;
	if( (( strchr((a->tipo)[0],'J') != NULL ) || ( strchr((a->tipo)[0],'D') != NULL )) ){

		if( ((strchr((b->tipo)[0],'J') != NULL) || (strchr((b->tipo)[0],'D') != NULL)) ){
			empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
			empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
			empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
			return 0;
		}

		c = desempilhaOperando(ae->pFrame);
		if(( strchr((c->tipo)[0],'J') != NULL ) || ( strchr((c->tipo)[0],'D') != NULL )){
			fprintf(stderr,"Instrucao 'dup2_x2' nao permitida para value3 de 'double' ou 'float' e value1 de 'double' ou 'float'.\n");
			exit(1);
		}

		empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
		empilhaOperando(ae->pFrame,(c->tipo)[0],c->elementos);
		empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
		empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
		return 0;

	}

	if(( strchr((b->tipo)[0],'J')!=NULL ) || ( strchr((b->tipo)[0],'D')!=NULL )){
		fprintf(stderr,"Operacao 'dup2_x2' nao permitida para value1 of type 1 e value2 d tipo 'float' ou 'double'.\n");
		exit(1);
	}

	c = desempilhaOperando(ae->pFrame);
	if(( strchr((c->tipo)[0],'J') != NULL ) || ( strchr((c->tipo)[0],'D') != NULL )){
		empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
		empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
		empilhaOperando(ae->pFrame,(c->tipo)[0],c->elementos);
		empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
		empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
		return 0;
	}

	d = desempilhaOperando(ae->pFrame);
	if(( strchr((d->tipo)[0],'J')!=NULL ) || ( strchr((d->tipo)[0],'D')!=NULL )){
		fprintf(stderr,"Operacao 'dup2_x2' nao permitida para value4 do tipo 'float' ou 'double'.\n");
		exit(1);
	}

	empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);
	empilhaOperando(ae->pFrame,(a->tipo)[0],d->elementos);
	empilhaOperando(ae->pFrame,(c->tipo)[0],c->elementos);
	empilhaOperando(ae->pFrame,(b->tipo)[0],b->elementos);
	empilhaOperando(ae->pFrame,(a->tipo)[0],a->elementos);

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

/*
 * @author Bruno Capu
 */
int idiv_(AmbienteExecucao *ae) {
	int a, b, div;

	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	div = a/b;

	empilhaOperando(ae->pFrame, "I", &div);
	return 0;
}
/*
 * @Author: Daniel
 */

int ldiv_(AmbienteExecucao *ae) {
	long long a, b, div;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;

	if (a == 0){
		printf("\nDivisao de long por zero requisitada, retornando valor nulo.\n");
		div = 0;
	} else {
		div = b/a;
	}
	empilhaOperando(ae->pFrame,"J", &div);
	return 0;
}
/*
 * @author Fernando
 */
int if_acmpeq(AmbienteExecucao *ae){
	void *a, *b;
	int offset;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	offset = leU2doPC(ae->pFrame);
	if (a == b){
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset -3;
	}
	return 0;
}

/*
 * @author Fernando
 */
int if_acmpne(AmbienteExecucao *ae){
	void *a, *b;
	int offset;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	offset = leU2doPC(ae->pFrame);
	if (a != b){
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset -3;
	}
	return 0;
}

int if_icmpeq(AmbienteExecucao *ae){
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a == b){
		ae->pFrame->pc += offset -3;
		ae->pFrame->enderecoPC += offset -3;
	}

	return 0;
}

int if_icmpne(AmbienteExecucao *ae){
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a != b){
		ae->pFrame->pc += offset -3;
		ae->pFrame->enderecoPC += offset -3;
	}

	return 0;
}

int if_icmple(AmbienteExecucao *ae){
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a <= b){
		ae->pFrame->pc += offset -3;
		ae->pFrame->enderecoPC += offset -3;
	}

	return 0;
}

int if_icmpgt(AmbienteExecucao *ae){
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a > b){
		ae->pFrame->pc += offset -3;
		ae->pFrame->enderecoPC += offset -3;
	}

	return 0;
}

int if_icmpge(AmbienteExecucao *ae){
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a >= b){
		ae->pFrame->pc += offset -3;
		ae->pFrame->enderecoPC += offset -3;
	}

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

/*
 * @author Bruno Capu
 */
int ifnull(AmbienteExecucao *ae) {
	void *a;
	u2 branchOffset;

	branchOffset = leU2doPC(ae->pFrame);

	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	if (a == NULL) {
		ae->pFrame->pc += branchOffset;
		ae->pFrame->enderecoPC += branchOffset;
	}

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
/*
 * @author Fernando
 */
int bastore(AmbienteExecucao *ae) {
	int valor, indice;
	Array *referencias;
	char valorChar;
	int mascara;
	int tamanho = 0;
	mascara = 0x00000001;

	valor = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	indice= desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	referencias = (Array*)desempilhaOperando(ae->pFrame)->elementos->tipo_referencia;

	while (referencias->tipo[referencias->sp][tamanho] == '[' ){
		tamanho++;
	}

	if((referencias->tipo[referencias->sp])[tamanho] == 'B') {
		valorChar = (int)valor;
		adicionaValorArray(referencias, indice, "B", &valorChar);
	} else if((referencias->tipo)[referencias->sp][tamanho] == 'Z') {
		valorChar = (valor & mascara);
		adicionaValorArray(referencias, indice, "Z", &valorChar);
	} else {
		printf("Erro em 'bastore'\n");
		exit(1);
	}

	return 0;
}

int arraylength(AmbienteExecucao *ae) {
	Array *array;
	int length;

	array = (Array*)desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	length = (int) array->sp;


	empilhaOperando(ae->pFrame, "I", &length);

	return 0;
}

int return0(AmbienteExecucao *ae) {
	return jumpback(ae, 0);
}
int return1(AmbienteExecucao *ae) {
	return jumpback(ae, 1);
}

int athrow(AmbienteExecucao *ae) {
	void *refObjeto;
	refObjeto = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	if (refObjeto == NULL){
		printf("Erro em 'athrow' -> NullPointerException\n");
		exit(1);
	}
	return1(ae);

	return 0;
}

/*
 * Author Daniel
 */
int ret(AmbienteExecucao *ae) {
	u1 indice;
	indice = leU1doPC(ae->pFrame);
	//D�vida no acesso abaixo
	VariaveisLocais localvar = (ae->pFrame->pilhaVariaveisLocais)[indice];
	if ( (localvar.tipo)[localvar.sp][0] != 'r'){
			printf("Endereco de retorno invalido, tipo errado.\n");
			exit(1);
		}
	//Checar o acesso abaixo
		ae->pFrame->pc = localvar.elementos->tipo_retorno;
	return 0;
}

int multianewarray(AmbienteExecucao *ae) {
	return 0;
}

int anewarray(AmbienteExecucao *ae) {
	return 0;
}

/*
 * @author Daniel
 */

int wide(AmbienteExecucao *ae) {
	u1 opcode = leU1doPC(ae->pFrame);
	switch (opcode) {
			case ILOAD:
				iload(ae);
				break;
			case FLOAD:
				fload(ae);
				break;
			case ALOAD:
				aload(ae);
				break;
				break;
			case LLOAD:
				lload(ae);
				break;
			case DLOAD:
				dload(ae);
				break;
			case ISTORE:
				istore(ae);
				break;
			case FSTORE:
				fstore(ae);
				break;
			case ASTORE:
				astore(ae);
				break;
			case LSTORE:
				lstore(ae);
				break;
			case DSTORE:
				dstore(ae);
				break;
			case RET:
				ret(ae);
				break;
			case IINC:
				iinc(ae);
				break;
			default:
				printf("Erro na instrucao wide, Opcode invalido para wide.\n");
				exit(1);
				break;
		}
	return 0;
}

/*
 * @autor Fernando
 */
int putfield(AmbienteExecucao *ae) {
	DadosField *dadosField;
	Objeto *obj;
	PilhaOperandos *pilhaOp;

	dadosField = retornaDadosField(ae->pFrame->cf, leU2doPC(ae->pFrame));

	pilhaOp = desempilhaOperando(ae->pFrame);
	obj = (Objeto*)desempilhaOperando(ae->pFrame)->elementos->tipo_referencia;

	defineFieldObjeto(obj, dadosField->nomeField, pilhaOp->tipo[0], pilhaOp->elementos[0]);

	return 0;
}

/*
 * @autor Fernando
 */
int getfield(AmbienteExecucao *ae) {
	Objeto *obj;
	DadosField *dadosField;
	tipo_info *tipo;

	dadosField = retornaDadosField(ae->pFrame->cf, leU2doPC(ae->pFrame));
	obj = (Objeto*)desempilhaOperando(ae->pFrame)->elementos->tipo_referencia;

	tipo = retornaFieldObjeto(obj, dadosField->nomeField);

	empilhaOperando(ae->pFrame, tipo->tipo, &(tipo->elemento));

	return 0;
}

/*
 * @author Fernando
 */
int fdiv(AmbienteExecucao *ae) {
	float a, b, div;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_float;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_float;

	div = b/a;

	empilhaOperando(ae->pFrame, "F", &div);
	return 0;
}
/*
 * @author Fernando
 */
int ddiv(AmbienteExecucao *ae) {
	double a, b, div;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_double;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_double;

	div = b/a;

	empilhaOperando(ae->pFrame, "D", &div);
	return 0;
}
/*
 * @author Daniel
 */
int checkcast(AmbienteExecucao *ae) {
	u2 indice;
	indice = leU2doPC(ae->pFrame);

	PilhaOperandos *ref;
		Objeto *obj;
		Array *arr;
		ref = desempilhaOperando(ae->pFrame);
		if ( (ref->tipo[ref->sp][0] != '[') || (ref->tipo[ref->sp][0] != 'L') ){
			printf("Falha em 'checkcast', objeto na pilha inadequado.\n");
			exit(0);
		}
		if (ref->elementos->tipo_referencia == NULL){
			return 0;
		}
		int tag = (signed int) (ae->pFrame->cf->constant_pool[indice -1].u.Utf8.bytes);

		if (tag != 7){
			printf("Falha em 'checkcast', tipo do objeto na pilha inadequado.\n");
			exit(0);
		} else {
			char *T = (char *)retornaClassInfo(ae->pFrame->cf, indice);
			if (ref->tipo[ref->sp][0] == 'L'){
				obj = (Objeto *) ref->elementos->tipo_referencia;
				if (strcmp(T,obj->nomeClasse) != 0){
					printf("Falha em 'checkcast', class types not compatible.\n");
					exit(1);
				}
			/* TODO: Checar tipo de subclasse  */
			} else 	if (ref->tipo[ref->sp][0]  == '[') {
				arr = (Array *) ref->elementos->tipo_referencia;
				/* TODO: Descobrir como est o type e arrumar isso aqui!  */
				if (strcmp(T, arr->tipo[ref->sp]) != 0){
					printf("Falha em 'checkcast', array class type duuh?.\n");
					exit(1);
				}
				/* TODO: Arrumar o resto daqui tambm  */
			}
		}
		empilhaOperando(ae->pFrame,ref->tipo[ref->sp],ref->elementos);
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

/*
 * @author: Daniel
 */
int lookupswitch(AmbienteExecucao *ae) {
	int bytepads;
	u4 npairs;
	u2 defaultbyte;

	bytepads = (4 - (ae->pFrame->pc - ae->pFrame->pcInicial)%4)%4;
	ae->pFrame->pc += bytepads;
	defaultbyte = leU4doPC(ae->pFrame);
	npairs = leU4doPC(ae->pFrame);

	PilhaOperandos * objref;
	int foundInPairs = 0;
	int case_value;

	u4 offsets[npairs][2];
	unsigned long int i;


	for (i = 0; i < npairs; i++) {
		offsets[i][1] = (u4) leU4doPC(ae->pFrame);
		offsets[i][2] = (u4) leU4doPC(ae->pFrame);
	}

	objref = desempilhaOperando(ae->pFrame);
	case_value = objref->elementos[objref->sp].tipo_int;


	if ( objref->tipo[objref->sp][0] != 'I'){
		printf("Falha em 'tableswitch', elemento de switch diferente de inteiro.\n");
		exit(1);
	} else {
		/* Recuando para o endereco original da funcao */
		ae->pFrame->pc += - ( 2*sizeof(u4) + npairs*sizeof(u4)*2 + 1 + bytepads);
		ae->pFrame->enderecoPC += - ( 3*sizeof(u4) + npairs*sizeof(u4)*2 + 1 + bytepads);
		for (i = 0; i < npairs ; i++) {
			if (offsets[i][1] == case_value)
				foundInPairs = i + 1;
		}

		if ( foundInPairs == 0 ){
			ae->pFrame->pc += defaultbyte;
			ae->pFrame->enderecoPC += defaultbyte;
		} else {
			ae->pFrame->pc += offsets[foundInPairs - 1][2];
			ae->pFrame->enderecoPC += offsets[foundInPairs - 1][2];
		}
	}
	return 0;
}
/*
 * @author Daniel
 */
int tableswitch(AmbienteExecucao *ae) {
	int bytepads;
	u4 highbyte, lowbyte;
	u4 defaultbyte;
	bytepads = (4 - (ae->pFrame->pc - ae->pFrame->pcInicial)%4)%4;
	ae->pFrame->pc += bytepads;
	defaultbyte = leU4doPC(ae->pFrame);
	lowbyte = leU4doPC(ae->pFrame);
	highbyte = leU4doPC(ae->pFrame);

	PilhaOperandos * objref;
		int case_value;

		u4 switchsize = (highbyte - lowbyte + 1);
		u4 offsets[switchsize];
		int i;

		if ( switchsize < 0 ){
			printf("Erro na 'tableswitch', lowbyte maior que highbyte.\n");
			exit(1);
		}

		for (i = 0; i < switchsize; i++) {
			offsets[i] = (u4) leU4doPC(ae->pFrame);
		}

		objref = desempilhaOperando(ae->pFrame);
		case_value = objref->elementos->tipo_int;

		if ( objref->tipo[objref->sp][0] != 'I'){
			printf("Falha em 'tableswitch', elemento de switch diferente de inteiro.\n");
			exit(1);
		} else {
			/* Recuando para o endereco original da funcao */
			//interpreter->current_frame->pc += - ( 3*sizeof(u4) + switchsize*sizeof(u4) + 1 + padbytes);
			ae->pFrame->pc += - ( 3*sizeof(u4) + switchsize*sizeof(u4) + 1 + bytepads);
			//interpreter->current_frame->pc_address += - ( 3*sizeof(u4) + switchsize*sizeof(u4) + 1 + padbytes);
			ae->pFrame->enderecoPC += - ( 3*sizeof(u4) + switchsize*sizeof(u4) + 1 + bytepads);
			if ( ( case_value > (int)highbyte) || ( case_value < (int)lowbyte ) ){
				//interpreter->current_frame->pc += defaultbyte;
				ae->pFrame->pc += defaultbyte;
				//interpreter->current_frame->pc_address += defaultbyte;
				ae->pFrame->enderecoPC += defaultbyte;
			} else {
				//interpreter->current_frame->pc += offsets[objref->data.data_int - lowbyte];
				ae->pFrame->pc += offsets[objref->elementos->tipo_int - lowbyte];
				//interpreter->current_frame->pc_address += offsets[objref->data.data_int - lowbyte];
				ae->pFrame->enderecoPC += offsets[objref->elementos->tipo_int- lowbyte];
			}
		}

	return 0;
}
