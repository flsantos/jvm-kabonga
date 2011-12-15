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

/*Newarray tags*/
#define T_BOOLEAN	4
#define T_CHAR   	5
#define T_FLOAT 	6
#define T_DOUBLE 	7
#define T_BYTE      8
#define T_SHORT 	9
#define T_INT       10
#define T_LONG      11

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
	nop,
	nop,
	new_,
	newarray,
	anewarray,
	arraylength,
	athrow,
	checkcast,
	instanceof,
	nop,
	nop,
	wide,
	multianewarray,
	ifnull,
	ifnonnull,
	goto_w,
	jsr_w
};

/*
 * @author Bruno Capu
 */
int l2i(AmbienteExecucao *ae) {
	long long a;
	int b;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;
	b = (int) a;

	empilhaOperando(ae->pFrame, "I", &b);

	return 0;
}

/*
 * @author Bruno Capu
 */
int lrem(AmbienteExecucao *ae) {
	long long a, b, rem;
	rem = 0;

	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;
	rem = b % a;
	empilhaOperando(ae->pFrame, "J", &rem);

	return 0;
}

int astore(AmbienteExecucao *ae) {
	int pos;

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

	int pos;
	switch (instrucao) {
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
	int pos;

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
	int indice = leU2doPC(ae->pFrame);
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
	iniciaExecucaoMetodo(dadosMetodo->nomeClasse, ae, dadosMetodo->nomeMetodo, dadosMetodo->tipo, argumento);

	return 0;
}

int dup(AmbienteExecucao *ae) {

	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	if (((a->tipo[a->sp][0]) == 'J') || ((a->tipo[a->sp][0]) == 'D')) {
		printf("Instrucao 'dup' nao permitida para valores 'double' ou 'long'.\n");
		exit(1);
	}

	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);

	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);

	return 0;
}

int new_(AmbienteExecucao *ae) {
	int indice = leU2doPC(ae->pFrame);
	char *nomeClasse;
	Objeto *objeto;
	nomeClasse = (char *) retornaClassInfo(ae->pFrame->cf, indice);
	/* ajustando para o caso da StringBuffer */
	if ((strcmp(nomeClasse, "java/lang/StringBuffer") == 0 || strcmp(nomeClasse, "java/lang/StringBuilder") == 0)) {
		char * strvazia;
		strvazia = calloc(1, sizeof(char));
		*strvazia = '\0';

		empilhaOperando(ae->pFrame, "[C", strvazia);
		return 0;
	}

	verificarClassFile(ae, nomeClasse); //TODO: Criar metodo
	objeto = ae->pClassHeap->obj;

	empilhaOperando(ae->pFrame, "L", objeto);

	return 0;

}

/**
 * @author Daniel
 */
int if_icmplt(AmbienteExecucao *ae) {
	i2 offsetDestino = leU2doPC(ae->pFrame);
	int a, b;

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a < b) {
		ae->pFrame->pc += offsetDestino - 3;
		ae->pFrame->enderecoPC += offsetDestino - 3;

	}

	return 0;
}

//TODO: VERIFICAR
int iinc(AmbienteExecucao *ae) {
	int indice = leU1doPC(ae->pFrame);
	int const_ = leU1doPC(ae->pFrame);

	ae->pFrame->pilhaVariaveisLocais->elementos[indice].tipo_int += const_;
	return 0;
}

int ifne(AmbienteExecucao *ae) {
	int a;
	int branchoffset = leU2doPC(ae->pFrame);
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a != 0) {
		ae->pFrame->pc += branchoffset - 3;
		ae->pFrame->enderecoPC += branchoffset - 3;
	}

	return 0;
}

int iload(AmbienteExecucao *ae) {
	int pos;

	switch (instrucao) {
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
	short int branchoffset = leU2doPC(ae->pFrame);

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
	DadosMetodo *dadosMetodo;
	PilhaOperandos *data;
	char *tipo;
	char *string1, *string2;
	int result_strcmp;
	char *string_to_append, *string_appended, *string_append;

	dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, cp_indice);

	if (strcmp(dadosMetodo->nomeClasse, "java/io/PrintStream") == 0
			&& (strcmp(dadosMetodo->nomeMetodo, "println") == 0 || strcmp(dadosMetodo->nomeMetodo, "print") == 0)) {
		/* realiza o println */
		if (ae->pFrame->pilhaOperandos->tipo[ae->pFrame->pilhaOperandos->sp][0] != '#') {
			data = desempilhaOperando(ae->pFrame);
			tipo = data->tipo[data->sp];
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
				printf("%lld", data->elementos[data->sp].tipo_long);
			} else if (tipo[0] == 'L') {
				printf("Impressao de um objeto nao implementada!");
			} else if (tipo[0] == 'S') {
				printf("%d", data->elementos[data->sp].tipo_short);
			} else if (tipo[0] == 'Z') {
				printf("\nboolean %d", data->elementos[data->sp].tipo_boolean);
			} else if (tipo[0] == '[') {
				printf("\n%s", (char*) data->elementos[data->sp].tipo_referencia);
			} else if (tipo[0] == 'r') {
				printf("\nImpressao de uma referencia. Nao implementado.");
			}
		}
		desempilhaOperando(ae->pFrame);

		if ((strcmp(dadosMetodo->nomeMetodo, "println") == 0)) {
			printf("\n");
		}
	} else if (strcmp(dadosMetodo->nomeClasse, "java/lang/String") == 0 && strcmp(dadosMetodo->nomeMetodo, "equals") == 0) {
		string1 = (char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
		string2 = (char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

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
		tipo = data->tipo[data->sp];
		string_to_append = (char*) desempilhaOperando(ae->pFrame)->elementos[data->sp].tipo_referencia;
		if (tipo[0] == 'B') {
			sprintf(string_append, "%d", data->elementos[data->sp].tipo_byte);
		} else if (tipo[0] == 'C') {
			sprintf(string_append, "%c", (unsigned char) data->elementos[data->sp].tipo_char);
		} else if (tipo[0] == 'D') {
			sprintf(string_append, "%f", data->elementos[data->sp].tipo_double);
		} else if (tipo[0] == 'F') {
			sprintf(string_append, "%f", data->elementos[data->sp].tipo_float);
		} else if (tipo[0] == 'I') {
			sprintf(string_append, "%d", data->elementos[data->sp].tipo_int);
		} else if (tipo[0] == 'J') {
			sprintf(string_append, "%d", data->elementos[data->sp].tipo_long);
		} else if (tipo[0] == 'L') {
			sprintf(string_append, "Impressao de um objeto?!");
		} else if (tipo[0] == 'S') {
			sprintf(string_append, "%d", data->elementos[data->sp].tipo_short);
		} else if (tipo[0] == 'Z') {
			sprintf(string_append, "%d", data->elementos[data->sp].tipo_boolean);
		} else if (tipo[0] == '[') {
			string_append = (char*) data->elementos[data->sp].tipo_referencia;
		} else if (tipo[0] == 'r') {
			sprintf(string_append, "Impressao de uma referencia. Arrumar.");
		}

		string_appended = calloc(strlen(string_append) + strlen(string_to_append) + 1, sizeof(char));
		*string_appended = '\0';
		strcat(string_appended, string_to_append);
		strcat(string_appended, string_append);

		empilhaOperando(ae->pFrame, "[C", string_appended);
		return 0;

	} else if ((strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuffer") == 0
			|| strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuilder") == 0)
			&& strcmp(dadosMetodo->nomeMetodo, "toString") == 0) {
		return 0;
	} else if (strcmp(dadosMetodo->nomeClasse, "java/lang/String") == 0 && strcmp(dadosMetodo->nomeMetodo, "length") == 0) {
		int len;
		string1 = (char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

		len = strlen(string1);

		empilhaOperando(ae->pFrame, "I", &len);

		return 0;
	} else if (strcmp(dadosMetodo->nomeClasse, "java/lang/String") == 0 && strcmp(dadosMetodo->nomeMetodo, "compareTo") == 0) {
		int strcm;
		string1 = (char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
		string2 = (char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

		strcm = strcmp(string1, string2);

		empilhaOperando(ae->pFrame, "I", &strcm);

		return 0;
	} else if (strcmp(dadosMetodo->nomeMetodo, "java/lang/String") == 0 && strcmp(dadosMetodo->nomeMetodo, "indexOf") == 0
			&& strcmp(dadosMetodo->tipo, "(Ljava/lang/String;)I") == 0) {
		int strstr_value;
		char *strstr_char;
		string1 = (char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
		string2 = (char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

		strstr_char = strstr(string1, string2);
		strstr_value = strstr_char - string1;

		empilhaOperando(ae->pFrame, "I", &strstr_value);

		return 0;
	} else if (strcmp(dadosMetodo->nomeMetodo, "java/lang/String") == 0 && strcmp(dadosMetodo->nomeMetodo, "startsWith") == 0
			&& strcmp(dadosMetodo->tipo, "(Ljava/lang/String;)Z") == 0) {
		char bool_return;
		char *strstr_char;
		string1 = (char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
		string2 = (char*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

		strstr_char = strstr(string1, string2);
		bool_return = (strstr_char - string1 == 0) ? 1 : 0;

		empilhaOperando(ae->pFrame, "Z", &bool_return);

		return 0;

	} else {
		DadosMetodo *dadosMetodo;
		int argumento;

		dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, cp_indice);

		argumento = retornaContadorArgumentos(dadosMetodo->tipo) + 1;

		iniciaExecucaoMetodo(dadosMetodo->nomeClasse, ae, dadosMetodo->nomeMetodo, dadosMetodo->tipo, argumento);
	}

	return 0;

}

int nop(AmbienteExecucao *ae) {
	return 0;
}
int bipush(AmbienteExecucao *ae) {
	int valor;
	valor = leU1doPC(ae->pFrame);

	empilhaOperando(ae->pFrame, "I", (&valor));
	return 0;
}

/*
 * @author Daniel
 */
int aconst_null(AmbienteExecucao *ae) {
	empilhaOperando(ae->pFrame, "[", NULL);
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
	int pos;

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
	float fvalue;
	long long lvalue;
	double dvalue;
	int indice;

	switch (instrucao) {
	case LDC_W:
		indice = (int) leU2doPC(ae->pFrame);
		break;
	case LDC2_W:
		indice = (unsigned short int) leU2doPC(ae->pFrame);
		break;
	case LDC:
		indice = (unsigned char) leU1doPC(ae->pFrame);
		break;
	}
	switch ((signed int) (ae->pFrame->cf->constant_pool[indice - 1].tag)) {
	case 8:
		/* CONSTANT_String */
		string = (char *) retornaUtf8(ae->pFrame->cf, ae->pFrame->cf->constant_pool[indice - 1].u.String.string_index);
		empilhaOperando(ae->pFrame, "[", string);
		break;
	case 3:
		/* CONSTANT_Integer */
		integer = ae->pFrame->cf->constant_pool[indice - 1].u.Integer.bytes;
		empilhaOperando(ae->pFrame, "I", &integer);

		break;
	case 4:
		/* CONSTANT_Float */
		fvalue = ae->pFrame->cf->constant_pool[indice - 1].u.Float.bytes.uf.valor;
		empilhaOperando(ae->pFrame, "F", &fvalue);

		break;
	case 5:
		/* CONSTANT_Long */
		lvalue = retornaLong(ae->pFrame->cf, indice);
		empilhaOperando(ae->pFrame, "J", &lvalue);

		break;
	case 6:
		/* CONSTANT_Double */

		dvalue = ae->pFrame->cf->constant_pool[indice - 1].u.Double.bytes.ud.valor;
		empilhaOperando(ae->pFrame, "D", &dvalue);

		break;

	default:
		printf("Erro em 'ldc' tag: %d\n", (signed int) ae->pFrame->cf->constant_pool[indice - 1].tag);
		exit(1);
		break;
	}

	return 0;
}

int fstore(AmbienteExecucao *ae) {
	int pos;

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
	int pos;
	switch (instrucao) {
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

	empilhaOperando(ae->pFrame, "J", &b);
	return 0;
}

int lstore(AmbienteExecucao *ae) {
	int pos;

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
	int pos;
	switch (instrucao) {
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
	b = (int) a;

	empilhaOperando(ae->pFrame, "I", &b);
	return 0;
}
int lload(AmbienteExecucao *ae) {
	int pos;
	switch (instrucao) {
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
/**
 * @author Fred
 */

int lconst(AmbienteExecucao *ae) {
	long long valor;
	if (instrucao == LCONST_0) {
		valor = 0;
	} else {
		valor = 1;
	}
	empilhaOperando(ae->pFrame, "J", &valor);

	return 0;
}

/*
 * @author Bruno Capu
 */
int fconst(AmbienteExecucao *ae) {
	float valor;
	valor = 0;

	switch (instrucao) {
	case FCONST_0:
		valor = 0;
		break;
	case FCONST_1:
		valor = 1;
		break;
	case FCONST_2:
		valor = 2;
		break;
	}

	empilhaOperando(ae->pFrame, "F", &valor);

	return 0;
}

/*
 * @author Bruno Capu
 */
int dconst(AmbienteExecucao *ae) {
	double valor;
	valor = 0;

	switch (instrucao) {
	case DCONST_0:
		valor = 0;
		break;
	case DCONST_1:
		valor = 1;
		break;
	}

	empilhaOperando(ae->pFrame, "D", &valor);
	return 0;
}

int sipush(AmbienteExecucao *ae) {
	int valor = leU2doPC(ae->pFrame);
	empilhaOperando(ae->pFrame, "I", &valor);

	return 0;
}

int pop(AmbienteExecucao *ae) {
	desempilhaOperando(ae->pFrame);

	return 0;
}

int pop2(AmbienteExecucao *ae) {
	if ((*(ae->pFrame->pilhaOperandos->tipo)[0] == 'D') || (*(ae->pFrame->pilhaOperandos->tipo)[0] == 'J')) {
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

	mul = a * b;

	empilhaOperando(ae->pFrame, "D", &mul);

	return 0;
}

int fmul(AmbienteExecucao *ae) {
	float a, b, mul;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_float;

	mul = a * b;

	empilhaOperando(ae->pFrame, "F", &mul);

	return 0;
}

int imul(AmbienteExecucao *ae) {
	int a, b, mul;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_int;

	mul = a * b;

	empilhaOperando(ae->pFrame, "I", &mul);

	return 0;
}

int lmul(AmbienteExecucao *ae) {
	long long a, b, mul;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;

	mul = a * b;

	empilhaOperando(ae->pFrame, "J", &mul);

	return 0;
}

/*
 * @author Bruno Capu
 */
int getstatic(AmbienteExecucao *ae) {
	int indiceDF;
	DadosField *dadosField;
	tipo_info *fieldRet;
	List_Classfile *p1, *p3;
	List_Classfile *superClasses, *p2;

	indiceDF = leU2doPC(ae->pFrame);

	dadosField = retornaDadosField(ae->pFrame->cf, indiceDF);

	if (strcmp(dadosField->nomeClasse, "java/lang/System") == 0 && strcmp(dadosField->nomeField, "out") == 0
			&& strcmp(dadosField->tipo, "Ljava/io/PrintStream;") == 0) {

		empilhaOperando(ae->pFrame, "#", NULL);
	} else {
		p1 = ae->pClassHeap;
		while (p1 != NULL) {
			if (strcmp((char *) p1->class_name, dadosField->nomeClasse) == 0) {
				fieldRet = retornaFieldObjeto(p1->obj, dadosField->nomeField);
				if (fieldRet != NULL) {
					empilhaOperandoTipo(ae->pFrame, fieldRet->tipo, fieldRet->elemento);
					return 0;
				} else {
					superClasses = retornaSuperClasses(ae, p1->cf);
					p2 = superClasses;
					while (p2 != NULL) {
						while (p3 != NULL) {
							if (strcmp((char *) p2->class_name, (char *) p3->class_name) == 0) {
								fieldRet = retornaFieldObjeto(p3->obj, dadosField->nomeField);
								if (fieldRet != NULL) {
									empilhaOperandoTipo(ae->pFrame, fieldRet->tipo, fieldRet->elemento);
									return 0;
								}
							}
							p3 = p3->prox;
						}
						p2 = p2->prox;
					}
				}
			}
			p1 = p1->prox;
		}
		fprintf(stderr, "Algum problema com o 'getstatic'.\n");
		exit(1);
	}

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

int fadd(AmbienteExecucao *ae) {
	float a, b, sum;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	sum = a + b;

	empilhaOperando(ae->pFrame, "F", &sum);

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

int ladd(AmbienteExecucao *ae) {
	long long a, b, sum;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	sum = a + b;

	empilhaOperando(ae->pFrame, "J", &sum);

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

int iand(AmbienteExecucao *ae) {
	int a, b, and;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	and = a & b;

	empilhaOperando(ae->pFrame, "I", &and);

	return 0;
}

int ineg(AmbienteExecucao *ae) {
	int a, neg;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	neg = -a;

	empilhaOperando(ae->pFrame, "I", &neg);

	return 0;
}

int ior(AmbienteExecucao *ae) {
	int a, b, or;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	or = a | b;

	empilhaOperando(ae->pFrame, "I", &or);

	return 0;
}

int ixor(AmbienteExecucao *ae) {
	int a, b, xor;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_int;
	xor = a ^ b;

	empilhaOperando(ae->pFrame, "I", &xor);

	return 0;
}

int land(AmbienteExecucao *ae) {
	long long a, b, and;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	and = a & b;

	empilhaOperando(ae->pFrame, "J", &and);

	return 0;
}

int lneg(AmbienteExecucao *ae) {
	long long a, neg;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	neg = -a;

	empilhaOperando(ae->pFrame, "J", &neg);

	return 0;
}

int lor(AmbienteExecucao *ae) {
	long long a, b, or;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	or = a | b;

	empilhaOperando(ae->pFrame, "J", &or);

	return 0;
}

int lxor(AmbienteExecucao *ae) {
	long long a, b, xor;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	xor = a ^ b;

	empilhaOperando(ae->pFrame, "J", &xor);

	return 0;
}

int dneg(AmbienteExecucao *ae) {
	double a, neg;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	neg = -a;

	empilhaOperando(ae->pFrame, "D", &neg);

	return 0;
}

int fneg(AmbienteExecucao *ae) {
	float a, neg;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	neg = -a;

	empilhaOperando(ae->pFrame, "F", &neg);

	return 0;
}

int dcmpg(AmbienteExecucao *ae) {
	double a, b;
	int pushval;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;

	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if (a < b) {
		pushval = -1;
	} else {
		pushval = 1;
	}

	empilhaOperando(ae->pFrame, "I", &pushval);
	return (0);
}

int dcmpl(AmbienteExecucao *ae) {
	double a, b;
	int pushval;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_double;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if (a < b) {
		pushval = -1;
	} else {
		pushval = -1;
	}

	empilhaOperando(ae->pFrame, "I", &pushval);
	return (0);
}

int fcmpg(AmbienteExecucao *ae) {
	float a, b;
	int pushval;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if (a < b) {
		pushval = -1;
	} else {
		pushval = 1;
	}
	empilhaOperando(ae->pFrame, "I", &pushval);
	return (0);
}

int fcmpl(AmbienteExecucao *ae) {
	float a, b;
	int pushval;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_float;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if (a < b) {
		pushval = -1;
	} else {
		pushval = -1;
	}
	empilhaOperando(ae->pFrame, "I", &pushval);
	return (0);
}

int lcmp(AmbienteExecucao *ae) {
	signed long long a, b;
	int pushval;
	b = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
	a = desempilhaOperando(ae->pFrame)->elementos->tipo_long;
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

	rem = (float) fmod(a, b);

	empilhaOperando(ae->pFrame, "F", &rem);
	return 0;
}

/*
 * @author Bruno Capu
 */
int drem_(AmbienteExecucao *ae) {
	double a, b, rem;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_double;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_double;

	rem = fmod(a, b);

	empilhaOperando(ae->pFrame, "D", &rem);

	return 0;
}

int ishl(AmbienteExecucao *ae) {
	int a, b, mask, res;

	mask = 0x1F; /* 0x1F, ou 31 seta os 5 primeiros bits como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	res = a << (b & mask);

	empilhaOperando(ae->pFrame, "I", &res);

	return 0;
}

int ishr(AmbienteExecucao *ae) {
	int a, b, mask, res, sign;

	mask = 0x1F; /* 0x1F, ou 31 seta os 5 primeiros bits como 1 */
	sign = 0x80000000; /* Ultimo bit setado como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	sign = sign & a; /* pegando o sign */
	res = a >> (b & mask);
	res = res | sign; /* devolvendo o sign */

	empilhaOperando(ae->pFrame, "I", &res);

	return 0;
}
int iushr(AmbienteExecucao *ae) {
	int a, b, mask, res;

	mask = 0x1F; /* 0x1F, ou 31 seta os 5 primeiros bits como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a >= 0)
		res = a >> (b & mask);
	else
		res = (a >> (b & mask)) + (2 >> (b & mask));

	empilhaOperando(ae->pFrame, "I", &res);

	return 0;
}
int lshl(AmbienteExecucao *ae) {
	long long a, mask, res;
	int b;

	mask = 0x3F; /* 0x3F, ou 63 seta os 6 primeiros bits como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;

	res = a << (b & mask);

	empilhaOperando(ae->pFrame, "J", &res);

	return 0;
}
int lshr(AmbienteExecucao *ae) {
	long long a, mask, res, sign;
	int b;

	mask = 0x3F; /* 0x1F, ou 63 seta os 6 primeiros bits como 1 */
	sign = 0x80000000; /* Ultimo bit setado como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;

	sign = sign & a; /* pegando o sign */
	res = a >> (b & mask);
	res = res | sign; /* devolvendo o sign */

	empilhaOperando(ae->pFrame, "J", &res);

	return 0;
}
int lushr(AmbienteExecucao *ae) {
	long long a, mask, res;
	int b;

	mask = 0x3F; /* 0x1F, ou 63 seta os 6 primeiros bits como 1 */

	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;

	if (a >= 0)
		res = a >> (b & mask);
	else
		res = (a >> (b & mask)) + (2L >> (b & mask));

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
	empilhaOperando(ae->pFrame, b->tipo[b->sp], b->elementos);

	return 0;
}

int dup2(AmbienteExecucao *ae) {
	PilhaOperandos *a, *b;

	a = desempilhaOperando(ae->pFrame);
	if ((a->tipo[a->sp][0] == 'J') || (a->tipo[a->sp][0] == 'D')) {
		/*float type e double type*/
		empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
		empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
		return 0;
	}

	b = desempilhaOperando(ae->pFrame);
	if ((*(b->tipo)[0] == 'J') || (*(b->tipo)[0] == 'D')) {
		fprintf(stderr, "Operacao 'dup2' nao permitida para value2 'float' ou 'double' type.\n");
		exit(1);
	}

	empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
	empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);

	return 0;
}

int dup_x1(AmbienteExecucao *ae) {

	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	PilhaOperandos *b = desempilhaOperando(ae->pFrame);
	if ((strchr((b->tipo)[0], 'J') != NULL) || (strchr((b->tipo)[0], 'D') != NULL) || (strchr((a->tipo)[0], 'J') != NULL)
			|| (strchr((a->tipo)[0], 'D') != NULL)) {
		fprintf(stderr, "Instrucao 'dup_x1' nao permitida para 'float' ou 'double' type.\n");
		exit(1);
	}

	empilhaOperandoTipo(ae->pFrame, (a->tipo)[a->sp], a->elementos[a->sp]);
	empilhaOperandoTipo(ae->pFrame, (b->tipo)[b->sp], b->elementos[b->sp]);
	empilhaOperandoTipo(ae->pFrame, (a->tipo)[a->sp], a->elementos[a->sp]);
	return 0;
}

int dup_x2(AmbienteExecucao *ae) {

	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	if ((strchr(a->tipo[0], 'J') != NULL) || (strchr(a->tipo[0], 'D') != NULL)) {
		fprintf(stderr, "Instrucao 'dup_x2' nao permitida para 'double' ou 'long'1.\n");
		exit(1);
	}

	PilhaOperandos *b = desempilhaOperando(ae->pFrame);
	if ((strchr(b->tipo[0], 'J') != NULL) || (strchr(b->tipo[0], 'D') != NULL)) {
		/*form 2*/
		empilhaOperandoTipo(ae->pFrame, (a->tipo)[a->sp], a->elementos[a->sp]);
		empilhaOperandoTipo(ae->pFrame, (b->tipo)[b->sp], b->elementos[b->sp]);
		empilhaOperandoTipo(ae->pFrame, (a->tipo)[a->sp], a->elementos[a->sp]);
		return 0;
	}

	PilhaOperandos *c = desempilhaOperando(ae->pFrame);
	if ((strchr(c->tipo[0], 'J') != NULL) || (strchr(c->tipo[0], 'D') != NULL)) {
		fprintf(stderr, "Instrucao 'dup_x2' nao permitida para 'double' ou 'long'2.\n");
		exit(1);
	}

	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
	empilhaOperandoTipo(ae->pFrame, c->tipo[c->sp], c->elementos[c->sp]);
	empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);

	return 0;
}

int dup2_x1(AmbienteExecucao *ae) {

	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	PilhaOperandos *b = desempilhaOperando(ae->pFrame);
	if ((strchr((b->tipo)[0], 'J') != NULL) || (strchr((b->tipo)[0], 'D') != NULL)) {
		fprintf(stderr, "Instrucao 'dup2_x1' nao permitida para value2 of 'double' ou 'float'.\n");
		exit(1);
	}
	if ((strchr((a->tipo)[0], 'J') != NULL) || (strchr((a->tipo)[0], 'D') != NULL)) {
		empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
		empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
		empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
		return 0;
	}
	PilhaOperandos *c = desempilhaOperando(ae->pFrame);
	if ((strchr((c->tipo)[0], 'J') != NULL) || (strchr((c->tipo)[0], 'D') != NULL)) {
		fprintf(stderr, "Instrucao 'dup2_x1' nao permitida para value3 ou 'double' ou 'float'.\n");
		exit(1);
	}

	empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
	empilhaOperandoTipo(ae->pFrame, c->tipo[c->sp], c->elementos[c->sp]);
	empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);

	return 0;
}

int dup2_x2(AmbienteExecucao *ae) {

	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	PilhaOperandos *b = desempilhaOperando(ae->pFrame);
	PilhaOperandos *c, *d;
	if (((strchr((a->tipo)[0], 'J') != NULL) || (strchr((a->tipo)[0], 'D') != NULL))) {

		if (((strchr((b->tipo)[0], 'J') != NULL) || (strchr((b->tipo)[0], 'D') != NULL))) {
			empilhaOperandoTipo(ae->pFrame, (a->tipo)[a->sp], a->elementos[a->sp]);
			empilhaOperandoTipo(ae->pFrame, (b->tipo)[b->sp], b->elementos[b->sp]);
			empilhaOperandoTipo(ae->pFrame, (a->tipo)[a->sp], a->elementos[a->sp]);
			return 0;
		}

		c = desempilhaOperando(ae->pFrame);
		if ((strchr((c->tipo)[0], 'J') != NULL) || (strchr((c->tipo)[0], 'D') != NULL)) {
			fprintf(stderr,
					"Instrucao 'dup2_x2' nao permitida para value3 de 'double' ou 'float' e value1 de 'double' ou 'float'.\n");
			exit(1);
		}

		empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
		empilhaOperandoTipo(ae->pFrame, c->tipo[c->sp], c->elementos[c->sp]);
		empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
		empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
		return 0;

	}

	if ((strchr((b->tipo)[0], 'J') != NULL) || (strchr((b->tipo)[0], 'D') != NULL)) {
		fprintf(stderr, "Operacao 'dup2_x2' nao permitida para value1 of type 1 e value2 d tipo 'float' ou 'double'.\n");
		exit(1);
	}

	c = desempilhaOperando(ae->pFrame);
	if ((strchr((c->tipo)[0], 'J') != NULL) || (strchr((c->tipo)[0], 'D') != NULL)) {
		empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
		empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
		empilhaOperandoTipo(ae->pFrame, c->tipo[c->sp], c->elementos[c->sp]);
		empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
		empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
		return 0;
	}

	d = desempilhaOperando(ae->pFrame);
	if ((strchr((d->tipo)[0], 'J') != NULL) || (strchr((d->tipo)[0], 'D') != NULL)) {
		fprintf(stderr, "Operacao 'dup2_x2' nao permitida para value4 do tipo 'float' ou 'double'.\n");
		exit(1);
	}

	empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);
	empilhaOperandoTipo(ae->pFrame, d->tipo[d->sp], d->elementos[d->sp]);
	empilhaOperandoTipo(ae->pFrame, c->tipo[c->sp], c->elementos[c->sp]);
	empilhaOperandoTipo(ae->pFrame, b->tipo[b->sp], b->elementos[b->sp]);
	empilhaOperandoTipo(ae->pFrame, a->tipo[a->sp], a->elementos[a->sp]);

	return 0;
}

/*
 * @author Bruno Capu
 */
int goto_w(AmbienteExecucao *ae) {
	int branchOffset;
	branchOffset = leU4doPC(ae->pFrame);
	ae->pFrame->pc += branchOffset;
	return 0;
}

/*
 * @author Bruno Capu
 */
int jsr(AmbienteExecucao *ae) {
	short int branchOffset;
	branchOffset = leU2doPC(ae->pFrame);
	empilhaOperando(ae->pFrame, "tipo_retorno", ae->pFrame->pc);
	ae->pFrame->pc += branchOffset;
	ae->pFrame->enderecoPC += branchOffset;
	return 0;
}

/*
 * @author Bruno Capu
 */
int jsr_w(AmbienteExecucao *ae) {
	int branchOffset;
	branchOffset = leU4doPC(ae->pFrame);
	empilhaOperando(ae->pFrame, "tipo_retorno", ae->pFrame->pc);
	ae->pFrame->pc += branchOffset;
	ae->pFrame->enderecoPC += branchOffset;
	return 0;
}

/*
 * @author Bruno Capu
 */
int newarray(AmbienteExecucao *ae) {
	int valor;
	int tamanho;
	Array *vetor;
	valor = leU1doPC(ae->pFrame);

	tamanho = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	switch (valor) {
	case T_BOOLEAN:
		vetor = alocarVetor("Z", 1, tamanho);
		empilhaOperando(ae->pFrame, "[Z", vetor);
		break;
	case T_CHAR:
		vetor = alocarVetor("C", 1, tamanho);
		empilhaOperando(ae->pFrame, "[C", vetor);
		break;
	case T_FLOAT:
		vetor = alocarVetor("F", 1, tamanho);
		empilhaOperando(ae->pFrame, "[F", vetor);
		break;
	case T_DOUBLE:
		vetor = alocarVetor("D", 1, tamanho);
		empilhaOperando(ae->pFrame, "[D", vetor);
		break;

	case T_BYTE:
		vetor = alocarVetor("B", 1, tamanho);
		empilhaOperando(ae->pFrame, "[B", vetor);
		break;
	case T_SHORT:
		vetor = alocarVetor("S", 1, tamanho);
		empilhaOperando(ae->pFrame, "[S", vetor);
		break;
	case T_INT:
		vetor = alocarVetor("I", 1, tamanho);
		empilhaOperando(ae->pFrame, "[I", vetor);
		break;
	case T_LONG:
		vetor = alocarVetor("J", 1, tamanho);
		empilhaOperando(ae->pFrame, "[J", vetor);
		break;
	default:
		fprintf(stderr, "Problema em 'anewarray', tipo de array nao reconhecido\n");
		exit(1);
		break;
	}

	return 0;
}

/*
 * @author Rubens
 */
int aaload(AmbienteExecucao *ae) {
	int index;
	Array *lista;
	void *ref;

	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (PilhaOperandos*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	ref = lista->elementos[index].tipo_referencia;

	empilhaOperando(ae->pFrame, lista->tipo[index], ref);
	return 0;
}

/*
 * @author Rubens
 */
int iaload(AmbienteExecucao *ae) {
	int integer, index;
	Array *lista;

	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (PilhaOperandos*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	integer = lista->elementos[index].tipo_int;

	empilhaOperando(ae->pFrame, "I", &integer);

	return 0;
}
/*
 * @author Rubens
 */
int aastore(AmbienteExecucao *ae) {
	int index;
	char *tipo;
	PilhaOperandos *opvalor;
	Array *lista;

	opvalor = desempilhaOperando(ae->pFrame);
	tipo = opvalor->tipo[opvalor->sp];
	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (PilhaOperandos*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	adicionaValorArray(lista, index, tipo, opvalor->elementos[0].tipo_referencia);

	return 0;
}
/*
 * @author Rubens
 */
int iastore(AmbienteExecucao *ae) {
	int valor, index;
	Array *lista;

	valor = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (Array*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	adicionaValorArray(lista, index, "I", &valor);
	return 0;
}

/*
 * @author Bruno Capu
 */
int idiv_(AmbienteExecucao *ae) {
	int a, b, div;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	if (a == 0) {
		printf("Divisao de int por zero, retornando valor nulo\n");
		div = 0;
	} else {
		div = b / a;
	}
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

	if (a == 0) {
		printf("\nDivisao de long por zero requisitada, retornando valor nulo.\n");
		div = 0;
	} else {
		div = b / a;
	}
	empilhaOperando(ae->pFrame, "J", &div);
	return 0;
}
/*
 * @author Fernando
 */
//TODO Continuar daqui
int if_acmpeq(AmbienteExecucao *ae) {
	void *a, *b;
	int offset;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	offset = leU2doPC(ae->pFrame);
	if (a == b) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}
	return 0;
}

/*
 * @author Fernando
 */
int if_acmpne(AmbienteExecucao *ae) {
	void *a, *b;
	int offset;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	offset = leU2doPC(ae->pFrame);
	if (a != b) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}
	return 0;
}

int if_icmpeq(AmbienteExecucao *ae) {
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a == b) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}

int if_icmpne(AmbienteExecucao *ae) {
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a != b) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}

int if_icmple(AmbienteExecucao *ae) {
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a <= b) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}

int if_icmpgt(AmbienteExecucao *ae) {
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a > b) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}

int if_icmpge(AmbienteExecucao *ae) {
	int a, b;
	int offset;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	offset = leU2doPC(ae->pFrame);
	if (a >= b) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}
int ifeq(AmbienteExecucao *ae) {
	int a;
	int offset;

	offset = leU2doPC(ae->pFrame);
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a == 0) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}

int iflt(AmbienteExecucao *ae) {
	int a;
	int offset;

	offset = leU2doPC(ae->pFrame);
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a < 0) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}
int ifle(AmbienteExecucao *ae) {
	int a;
	int offset;

	offset = leU2doPC(ae->pFrame);
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a <= 0) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}
int ifgt(AmbienteExecucao *ae) {
	int a;
	int offset;

	offset = leU2doPC(ae->pFrame);
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a > 0) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}
int ifge(AmbienteExecucao *ae) {
	int a;
	int offset;

	offset = leU2doPC(ae->pFrame);
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;

	if (a >= 0) {
		ae->pFrame->pc += offset - 3;
		ae->pFrame->enderecoPC += offset - 3;
	}

	return 0;
}
int ifnonnull(AmbienteExecucao *ae) {
	void *a;
	int branchOffset;

	branchOffset = leU2doPC(ae->pFrame);

	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	if (a != NULL) {
		ae->pFrame->pc += branchOffset - 3;
		ae->pFrame->enderecoPC += branchOffset - 3;
	}
	return 0;
}

/*
 * @author Bruno Capu
 */
int ifnull(AmbienteExecucao *ae) {
	void *a;
	int branchOffset;

	branchOffset = leU2doPC(ae->pFrame);

	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	if (a == NULL) {
		ae->pFrame->pc += branchOffset;
		ae->pFrame->enderecoPC += branchOffset;
	}

	return 0;
}

/*
 * @author Rubens
 */
int faload(AmbienteExecucao *ae) {
	int index;
	float valor;
	Array *lista;

	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (Array *) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	valor = lista->elementos[index].tipo_float;

	empilhaOperando(ae->pFrame, "F", &valor);

	return 0;
}

/*
 * @author Rubens
 */
int fastore(AmbienteExecucao *ae) {
	int index;
	float valor;
	Array *lista;

	valor = desempilhaOperando(ae->pFrame)->elementos[0].tipo_float;
	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (Array *) desempilhaOperando(ae->pFrame)->elementos->tipo_referencia;

	adicionaValorArray(lista, index, "F", &valor);

	return 0;
}

/*
 * @author Rubens
 */
int dastore(AmbienteExecucao *ae) {
	int index;
	double valor;
	Array *lista;

	valor = desempilhaOperando(ae->pFrame)->elementos[0].tipo_double;
	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (Array *) desempilhaOperando(ae->pFrame)->elementos->tipo_referencia;

	adicionaValorArray(lista, index, "D", &valor);

	return 0;
}

/*
 * @author Rubens
 */
int daload(AmbienteExecucao *ae) {
	int index;
	double valor;
	Array *lista;

	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (Array *) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	valor = lista->elementos[index].tipo_double;

	empilhaOperando(ae->pFrame, "D", &valor);

	return 0;
}

/*
 * @author Rubens
 */
int castore(AmbienteExecucao *ae) {
	int index;
	char valor;
	Array *lista;

	valor = desempilhaOperando(ae->pFrame)->elementos[0].tipo_char;
	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (Array *) desempilhaOperando(ae->pFrame)->elementos->tipo_referencia;

	adicionaValorArray(lista, index, "C", &valor);

	return 0;
}

/*
 * @author Rubens
 */
int caload(AmbienteExecucao *ae) {
	int index;
	char valor;
	Array *lista;

	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (Array *) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	valor = lista->elementos[index].tipo_char;

	empilhaOperando(ae->pFrame, "D", &valor);

	return 0;
}

/*
 * @author Rubens
 */
int lastore(AmbienteExecucao *ae) {
	int index;
	long long valor;
	Array *lista;

	valor = desempilhaOperando(ae->pFrame)->elementos[0].tipo_long;
	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (Array *) desempilhaOperando(ae->pFrame)->elementos->tipo_referencia;

	adicionaValorArray(lista, index, "J", &valor);

	return 0;
}

/*
 * @author Rubens
 */
int laload(AmbienteExecucao *ae) {
	int index;
	long long valor;
	Array *lista;

	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (Array *) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	valor = lista->elementos[index].tipo_long;

	empilhaOperando(ae->pFrame, "J", &valor);

	return 0;
}

/*
 * @author Rubens
 */
int sastore(AmbienteExecucao *ae) {
	int index;
	short valor;
	Array *lista;

	valor = desempilhaOperando(ae->pFrame)->elementos[0].tipo_short;
	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (PilhaOperandos*) desempilhaOperando(ae->pFrame)->elementos->tipo_referencia;

	adicionaValorArray(lista, index, "S", &valor);

	return 0;
}

/*
 * @author Rubens
 */
int saload(AmbienteExecucao *ae) {
	int index;
	short valor;
	Array *lista;

	index = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	lista = (PilhaOperandos*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	valor = lista->elementos[index].tipo_short;

	empilhaOperando(ae->pFrame, "S", &valor);

	return 0;
}

/*
 * @author Daniel
 */
int baload(AmbienteExecucao *ae) {
	int indice, valorInt, valorChar;
	int tamanhoVetor;
	int zero;
	Array *vetorRef;

	zero = 0;
	tamanhoVetor = 0;

	indice = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	vetorRef = (Array*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	while (vetorRef->tipo[vetorRef->sp][tamanhoVetor] == '[') {
		tamanhoVetor++;
	}
	if (vetorRef->tipo[vetorRef->sp][tamanhoVetor] == 'B') {
		valorChar = vetorRef->elementos[indice].tipo_byte;
		valorInt = (int) valorChar;
		empilhaOperando(ae->pFrame, "I", &valorInt);
	} else if ((vetorRef->tipo)[vetorRef->sp][tamanhoVetor] == 'Z') {
		valorChar = vetorRef->elementos[indice].tipo_boolean;
		valorInt = (zero | valorChar);
		empilhaOperando(ae->pFrame, "I", &valorInt);
	} else {
		printf("Problema em 'baload', tipo incorreto de dados passado.\n");
		exit(1);
	}

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

	valor = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	indice = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	referencias = (Array*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	while (referencias->tipo[referencias->sp][tamanho] == '[') {
		tamanho++;
	}
	if ((referencias->tipo[referencias->sp])[tamanho] == 'B') {
		valorChar = (int) valor;
		adicionaValorArray(referencias, indice, "B", &valorChar);
	} else if ((referencias->tipo)[referencias->sp][tamanho] == 'Z') {
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

	array = (Array*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	length = (int) array->sp;

	empilhaOperando(ae->pFrame, "I", &length);

	return 0;
}

int return0(AmbienteExecucao *ae) {
	return RetornaFrame(ae, 0);
}
int return1(AmbienteExecucao *ae) {
	return RetornaFrame(ae, 1);
}

int athrow(AmbienteExecucao *ae) {
	void *refObjeto;
	refObjeto = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	if (refObjeto == NULL) {
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
	int indice;
	indice = leU1doPC(ae->pFrame);
	VariaveisLocais localvar = (ae->pFrame->pilhaVariaveisLocais)[indice];
	if (localvar.tipo[localvar.sp][0] != 'r') {
		printf("Endereco de retorno invalido, tipo errado.\n");
		exit(1);
	}
	ae->pFrame->pc = (u1 *) localvar.elementos->tipo_retorno;
	return 0;
}

int multianewarray(AmbienteExecucao *ae) {
	char *tipox, *p1, *p2, *tipo;
	int cont, i;
	int *dimensao, *pi;
	Array *arr;
	int indice = leU2doPC(ae->pFrame);
	int tamanho = leU1doPC(ae->pFrame);

	if ((signed int) ae->pFrame->cf->constant_pool[indice - 1].tag == 7) {
		tipox = (char *) retornaClassInfo(ae->pFrame->cf, indice);
		p1 = tipox;
		cont = 0;
		while (*p1 != '[') {
			p1++;
			cont++;
		}
		tipo = calloc(strlen(tipox) - cont + 2, sizeof(char));
		p2 = tipo;
		while (*p1 != '\0') {
			*p2 = *p1;
			p1++;
			p2++;
		}

		p2 = '\0';

		dimensao = calloc(tamanho, sizeof(int));
		pi = dimensao + tamanho - 1;

		for (i = 0; i < tamanho; i++) {
			*pi = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
			pi--;
		}

		arr = alocarVetor__(tipo, tamanho, dimensao);
		/* TODO: arrumar o tipo abaixo */
		empilhaOperando(ae->pFrame, "[", arr);

	} else {
		printf("Erro em multinewarray, tipo inapropriado.\n");
		exit(1);
	}
	return 0;
}

int anewarray(AmbienteExecucao *ae) {
	int i;
	Array *array;
	char *tipo;
	int valor = leU2doPC(ae->pFrame);

	i = desempilhaOperando(ae->pFrame)->elementos[0].tipo_int;
	tipo = (char *) retornaClassInfo(ae->pFrame->cf, valor);

	tipo++;
	if (i == 0) {
		array = NULL;
	} else {
		array = alocarVetor(tipo, 1, i);
	}

	empilhaOperando(ae->pFrame, "[", array);

	return 0;
}

/*
 * @author Daniel
 */

int wide(AmbienteExecucao *ae) {
	int opcode = leU1doPC(ae->pFrame);
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
	obj = (Objeto*) desempilhaOperando(ae->pFrame)->elementos->tipo_referencia;

	defineFieldObjeto(obj, dadosField->nomeField, pilhaOp->tipo[0], pilhaOp->elementos[0]);

	return 0;
}

/*
 * @autor Fernando
 */
//TODO Continuar Daqui
int getfield(AmbienteExecucao *ae) {
	Objeto *obj;
	DadosField *dadosField;
	tipo_info *tipo;
	dadosField = retornaDadosField(ae->pFrame->cf, leU2doPC(ae->pFrame));
	obj = (Objeto*) desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;

	tipo = retornaFieldObjeto(obj, dadosField->nomeField);

	empilhaOperandoTipo(ae->pFrame, tipo->tipo, tipo->elemento);

	return 0;
}

/*
 * @author Fernando
 */
int fdiv(AmbienteExecucao *ae) {
	float a, b, div;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_float;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_float;

	div = b / a;

	empilhaOperando(ae->pFrame, "F", &div);
	return 0;
}
/*
 * @author Fernando
 */
int ddiv(AmbienteExecucao *ae) {
	double a, b, div;
	a = desempilhaOperando(ae->pFrame)->elementos[0].tipo_double;
	b = desempilhaOperando(ae->pFrame)->elementos[0].tipo_double;

	div = b / a;

	empilhaOperando(ae->pFrame, "D", &div);
	return 0;
}
/*
 * @author Daniel
 */
int checkcast(AmbienteExecucao *ae) {
	int indice;
	indice = leU2doPC(ae->pFrame);

	PilhaOperandos *ref;
	Objeto *obj;
	Array *arr;
	ref = desempilhaOperando(ae->pFrame);
	if ((ref->tipo[ref->sp][0] != '[') || (ref->tipo[ref->sp][0] != 'L')) {
		printf("Falha em 'checkcast', objeto na pilha inadequado.\n");
		exit(0);
	}
	if (ref->elementos->tipo_referencia == NULL) {
		return 0;
	}
	int tag = (signed int) (ae->pFrame->cf->constant_pool[indice - 1].u.Utf8.bytes);

	if (tag != 7) {
		printf("Falha em 'checkcast', tipo do objeto na pilha inadequado.\n");
		exit(0);
	} else {
		char *T = (char *) retornaClassInfo(ae->pFrame->cf, indice);
		if (ref->tipo[ref->sp][0] == 'L') {
			obj = (Objeto *) ref->elementos->tipo_referencia;
			if (strcmp(T, obj->nomeClasse) != 0) {
				printf("Falha em 'checkcast', class types not compatible.\n");
				exit(1);
			}
			/* TODO: Checar tipo de subclasse  */
		} else if (ref->tipo[ref->sp][0] == '[') {
			arr = (Array *) ref->elementos->tipo_referencia;
			/* TODO: Descobrir como est o type e arrumar isso aqui!  */
			if (strcmp(T, arr->tipo[ref->sp]) != 0) {
				printf("Falha em 'checkcast', array class type duuh?.\n");
				exit(1);
			}
			/* TODO: Arrumar o resto daqui tambm  */
		}
	}
	empilhaOperando(ae->pFrame, ref->tipo[ref->sp], ref->elementos);
	return 0;
}
/*
 * @author Fernando
 */
int instanceof(AmbienteExecucao *ae) {
	PilhaOperandos *refObjeto;
	Objeto *obj;
	Array *array;
	int resultado = 0;
	char *S, *T;
	int indice;

	indice = leU2doPC(ae->pFrame);

	refObjeto = desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
	if (refObjeto == NULL) {
		empilhaOperando(ae->pFrame, "I", &resultado);
		return 0;
	}

	if ((signed int) ae->pFrame->cf->constant_pool[indice - 1].tag != 7) {
		printf("Erro em 'instanceof'.\n");
		exit(1);
	}

	T = (char *) retornaClassInfo(ae->pFrame->cf, indice);
	S = refObjeto->tipo[0];
	if (refObjeto->tipo[refObjeto->sp][0] == 'L') {
		obj = (Objeto *) refObjeto->elementos[0].tipo_referencia;
		if (strcmp(T, obj->nomeClasse)) {
			printf("Erro.\n");
			empilhaOperando(ae->pFrame, "I", &resultado);
		}

	} else if (refObjeto->tipo[refObjeto->sp][0] == '[') {
		array = (Array *) refObjeto->elementos[0].tipo_referencia;
		if (strcmp(T, (char *) array->tipo)) {
			printf("Erro.\n");
			empilhaOperando(ae->pFrame, "I", &resultado);
		}
	}

	empilhaOperando(ae->pFrame, "I", &resultado);
	return 0;
}

int invokestatic(AmbienteExecucao *ae) {
	DadosMetodo *dadosMetodo;
	int arg_cont;
	int indice;

	indice = leU2doPC(ae->pFrame);

	dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, indice);

	arg_cont = retornaContadorArgumentos(dadosMetodo->tipo);

	if (strcmp(dadosMetodo->nomeClasse, "Object") == 0 && strcmp(dadosMetodo->nomeMetodo, "<init>") == 0) {
		return 0;
	}
	iniciaExecucaoMetodo(dadosMetodo->nomeClasse, ae, dadosMetodo->nomeMetodo, dadosMetodo->tipo, arg_cont);

	return 0;
}

int putstatic(AmbienteExecucao *ae) {
	DadosField *dadosField;
	PilhaOperandos *pilha;
	List_Classfile *lista1, *lista3;
	List_Classfile *superClasses, *lista2;
	int erro, erro2, indice;
	indice = leU2doPC(ae->pFrame);

	dadosField = retornaDadosField(ae->pFrame->cf, indice);

	pilha = desempilhaOperando(ae->pFrame);
	lista1 = ae->pClassHeap;

	while (lista1 != NULL) {
		if (strcmp((char *) lista1->class_name, dadosField->nomeClasse) == 0) {
			erro = defineFieldObjeto(lista1->obj, dadosField->nomeField, pilha->tipo[pilha->sp], pilha->elementos[pilha->sp]);
			if (erro == -1) {
				superClasses = retornaSuperClasses(ae, lista1->cf);
				lista2 = superClasses;
				while (lista2 != NULL) {
					lista3 = ae->pClassHeap;
					while (lista3 != NULL) {
						if (strcmp((char *) lista3->class_name, (char *) lista2->class_name) == 0) {
							erro2 = defineFieldObjeto(lista3->obj, dadosField->nomeField, pilha->tipo[pilha->sp],
									pilha->elementos[pilha->sp]);
							if (erro2 != -1)
								return 0;
						}
						lista3 = lista3->prox;
					}
					lista2 = lista2->prox;
				}
			}
			return 0;
		}
		lista1 = lista1->prox;

	}

	fprintf(stderr, "Falha em 'putstatic'. Nao acho o elemento buscado na lista de classes.");
	exit(1);

	return 0;
}

int lookupswitch(AmbienteExecucao *ae) {
	int bytepads;
	int npairs;
	int defaultbyte;

	bytepads = (4 - (ae->pFrame->pc - ae->pFrame->pcInicial) % 4) % 4;
	ae->pFrame->pc += bytepads;
	defaultbyte = leU4doPC(ae->pFrame);
	npairs = leU4doPC(ae->pFrame);

	PilhaOperandos * objref;
	int foundInPairs = 0;
	int case_value;

	int offsets[npairs][2];
	unsigned long int i;

	for (i = 0; i < npairs; i++) {
		offsets[i][1] = (int) leU4doPC(ae->pFrame);
		offsets[i][2] = (int) leU4doPC(ae->pFrame);
	}

	objref = desempilhaOperando(ae->pFrame);
	case_value = objref->elementos[objref->sp].tipo_int;

	if (objref->tipo[objref->sp][0] != 'I') {
		printf("Falha em 'tableswitch', elemento de switch diferente de inteiro.\n");
		exit(1);
	} else {
		/* Recuando para o endereco original da funcao */
		ae->pFrame->pc += -(2 * sizeof(int) + npairs * sizeof(int) * 2 + 1 + bytepads);
		ae->pFrame->enderecoPC += -(3 * sizeof(int) + npairs * sizeof(int) * 2 + 1 + bytepads);
		for (i = 0; i < npairs; i++) {
			if (offsets[i][1] == case_value)
				foundInPairs = i + 1;
		}

		if (foundInPairs == 0) {
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
	int highbyte, lowbyte;
	int defaultbyte;
	bytepads = (4 - (ae->pFrame->pc - ae->pFrame->pcInicial) % 4) % 4;
	ae->pFrame->pc += bytepads;
	defaultbyte = leU4doPC(ae->pFrame);
	lowbyte = leU4doPC(ae->pFrame);
	highbyte = leU4doPC(ae->pFrame);

	PilhaOperandos * objref;
	int case_value;

	int switchsize = (highbyte - lowbyte + 1);
	int offsets[switchsize];
	int i;

	if (switchsize < 0) {
		printf("Erro na 'tableswitch', lowbyte maior que highbyte.\n");
		exit(1);
	}

	for (i = 0; i < switchsize; i++) {
		offsets[i] = (int) leU4doPC(ae->pFrame);
	}

	objref = desempilhaOperando(ae->pFrame);
	case_value = objref->elementos->tipo_int;

	if (objref->tipo[objref->sp][0] != 'I') {
		printf("Falha em 'tableswitch', elemento de switch diferente de inteiro.\n");
		exit(1);
	} else {
		/* Recuando para o endereco original da funcao */
		ae->pFrame->pc += -(3 * sizeof(int) + switchsize * sizeof(int) + 1 + bytepads);
		ae->pFrame->enderecoPC += -(3 * sizeof(int) + switchsize * sizeof(int) + 1 + bytepads);
		if ((case_value > (int) highbyte) || (case_value < (int) lowbyte)) {
			ae->pFrame->pc += defaultbyte;
			ae->pFrame->enderecoPC += defaultbyte;
		} else {
			ae->pFrame->pc += offsets[objref->elementos->tipo_int - lowbyte];
			ae->pFrame->enderecoPC += offsets[objref->elementos->tipo_int - lowbyte];
		}
	}

	return 0;
}
