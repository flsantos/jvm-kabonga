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

int (*vetFunc[])(AmbienteExecucao *p) = {
	"nop",
	"aconst_null",
	"iconst_m1",
	"iconst_0",
	"iconst_1",
	"iconst_2",
	"iconst_3",
	"iconst_4",
	"iconst_5",
	"lconst_0",
	"lconst_1",
	"fconst_0",
	"fconst_1",
	"fconst_2",
	"dconst_0",
	"dconst_1",
	"bipush",
	"sipush",
	"ldc",
	"ldc_w",
	"ldc2_w",
	"iload",
	"lload",
	"fload",
	"dload",
	"aload",
	"iload_0",
	"iload_1",
	"iload_2",
	"iload_3",
	"lload_0",
	"lload_1",
	"lload_2",
	"lload_3",
	"fload_0",
	"fload_1",
	"fload_2",
	"fload_3",
	"dload_0",
	"dload_1",
	"dload_2",
	"dload_3",
	"aload_0",
	"aload_1",
	"aload_2",
	"aload_3",
	"iaload",
	"laload",
	"faload",
	"daload",
	"aaload",
	"baload",
	"caload",
	"saload",
	"istore",
	"lstore",
	"fstore",
	"dstore",
	"astore",
	"istore_0",
	"istore_1",
	"istore_2",
	"istore_3",
	"lstore_0",
	"lstore_1",
	"lstore_2",
	"lstore_3",
	"fstore_0",
	"fstore_1",
	"fstore_2",
	"fstore_3",
	"dstore_0",
	"dstore_1",
	"dstore_2",
	"dstore_3",
	"astore_0",
	"astore_1",
	"astore_2",
	"astore_3",
	"iastore",
	"lastore",
	"fastore",
	"dastore",
	"aastore",
	"bastore",
	"castore",
	"sastore",
	"pop",
	"pop2",
	"dup",
	"dup_x1",
	"dup_x2",
	"dup2",
	"dup2_x1",
	"dup2_x2",
	"swap",
	"iadd",
	"ladd",
	"fadd",
	"dadd",
	"isub",
	"lsub",
	"fsub",
	"dsub",
	"imul",
	"lmul",
	"fmul",
	"dmul",
	"idiv",
	"ldiv",
	"fdiv",
	"ddiv",
	"irem",
	"lrem",
	"frem",
	"drem",
	"ineg",
	"lneg",
	"fneg",
	"dneg",
	"ishl",
	"lshl",
	"ishr",
	"lshr",
	"iushr",
	"lushr",
	"iand",
	"land",
	"ior",
	"lor",
	"ixor",
	"lxor",
	"iinc",
	"i2l",
	"i2f",
	"i2d",
	"l2i",
	"l2f",
	"l2d",
	"f2i",
	"f2l",
	"f2d",
	"d2i",
	"d2l",
	"d2f",
	"i2b",
	"i2c",
	"i2s",
	"lcmp",
	"fcmpl",
	"fcmpg",
	"dcmpl",
	"dcmpg",
	"ifeq",
	"ifne",
	"iflt",
	"ifge",
	"ifgt",
	"ifle",
	"if_icmpeq",
	"if_icmpne",
	"if_icmplt",
	"if_icmpge",
	"if_icmpgt",
	"if_icmple",
	"if_acmpeq",
	"if_acmpne",
	"goto",
	"jsr",
	"ret",
	"tableswitch",
	"lookupswitch",
	"ireturn",
	"lreturn",
	"freturn",
	"dreturn",
	"areturn",
	"return",
	"getstatic",
	"putstatic",
	"getfield",
	"putfield",
	"invokevirtual",
	"invokespecial",
	"invokestatic",
	"invokeinterface",
	"",
	"new",
	"newarray",
	"anewarray",
	"arraylength",
	"athrow",
	"checkcast",
	"instanceof",
	"monitorenter",
	"monitorexit",
	"wide",
	"multianewarray",
	"ifnull",
	"ifnonnull",
	"goto_w",
	"jsr_w"
};

int ireturn(AmbienteExecucao *ae) {
	int return_v;
	return_v = jumpback(ae, 1);

	return return_v;
}

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
	u1 pos = leU1doPC(ae->pFrame);
	//transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);
	transferePilhaOperandosParaVariavelLocal(ae->pFrame, pos);
	return 0;
}

int invokespecial(AmbienteExecucao *ae) {
	char *nomeClasse, *nomeMetodo;
	u2 indice = leU2doPC(ae->pFrame);
	DadosMetodo *dadosMetodo;
	int arg_count;

	dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, indice);

	if ((strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuffer") == 0
			|| strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuilder") == 0)
			&& strcmp(dadosMetodo->nomeMetodo, "<init>") == 0) {
		desempilhaOperando(&(ae->pFrame));
		return 0;
	}

	arg_count = retornaContadorArgumentos(dadosMetodo->tipo) + 1;

	/*jump(ae, dadosMetodo->nomeClasse, dadosMetodo->nomeMetodo,
			dadosMetodo->tipo, arg_count);*/
	iniciaClasse(dadosMetodo->nomeClasse, ae, dadosMetodo->nomeMetodo, dadosMetodo->tipo);

	return 0;
}

int dup(AmbienteExecucao *ae) {

	//t_opstack *a = desempilhaOperando((&interpreter->current_frame->opstack));
	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	if ((*(a->tipo[0]) == 'J') || (*(a->tipo[0]) == 'D')) {
		printf(
				stderr,
				"Instrucao 'dup' nao permitida para valores 'double' ou 'long'.\n");
		exit(1);
	}

	//empilhaOperando_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame, a->tipo[0], &(a->elementos[a->sp]));
	//empilhaOperando_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame, a->tipo[0],&(a->elementos[a->sp]));

	return 0;
}

int new_(AmbienteExecucao *ae) {
	u2 indice = leU2doPC(ae->pFrame);
	char *nomeClasse;
	Objeto *objeto;

	nomeClasse = retornaClassInfo(ae->pFrame->cf, indice);

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

	//TODO esperando o capuleto para o objeto
	//object = instanciate_object(class_file, interpreter);

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
		if (ae->pFrame->pilhaOperandos->tipo[0] != '#') {
			data = desempilhaOperando(ae->pFrame);
			tipo = data->tipo;
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
				printf("%lld", data->elementos[0].tipo_long);
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
		desempilhaOperando(&(ae->pFrame->pilhaOperandos));

		if ((strcmp(dadosMetodo->nomeMetodo, "println") == 0)) {
			printf("\n");
		}
	} else if (strcmp(dadosMetodo->nomeClasse, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "equals") == 0) {
		string1 =
				(char*) desempilhaOperando((&ae->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando((&ae->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

		if (strcmp(string1, string2) == 0) {
			result_strcmp = 1;
			empilhaOperando(&(ae->pFrame->pilhaOperandos), "I",
					&result_strcmp);
			return 0;
		} else {
			result_strcmp = 0;
			empilhaOperando(&(ae->pFrame->pilhaOperandos), "I",
					&result_strcmp);
			return 0;
		}
	} else if ((strcmp(dadosMetodo->nomeMetodo, "java/lang/StringBuffer") == 0
			|| strcmp(dadosMetodo->nomeMetodo, "java/lang/StringBuilder") == 0)
			&& strcmp(dadosMetodo->nomeMetodo, "append") == 0) {
		string_append = calloc(50, sizeof(char));
		data = desempilhaOperando(&(ae->pFrame->pilhaOperandos));
		tipo = data->tipo;
		string_to_append = (char*) desempilhaOperando(
				&(ae->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;
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
			sprintf(string_append, "%lld", data->elementos[0].tipo_long);
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

		empilhaOperando(&(ae->pFrame->pilhaOperandos), "[C",
				string_appended);
		return 0;

	} else if ((strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuffer") == 0
			|| strcmp(dadosMetodo->nomeClasse, "java/lang/StringBuilder") == 0)
			&& strcmp(dadosMetodo->nomeMetodo, "toString") == 0) {
		return 0;
	} else if (strcmp(dadosMetodo->nomeClasse, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "length") == 0) {
		int len;
		string1 =
				(char*) desempilhaOperando((&ae->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

		len = strlen(string1);

		empilhaOperando(&(ae->pFrame->pilhaOperandos), "I", &len);

		return 0;
	} else if (strcmp(dadosMetodo->nomeClasse, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "compareTo") == 0) {
		int strcm;
		string1 =
				(char*) desempilhaOperando((&ae->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando((&ae->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

		strcm = strcmp(string1, string2);

		empilhaOperando(&(ae->pFrame->pilhaOperandos), "I", &strcm);

		return 0;
	} else if (strcmp(dadosMetodo->nomeMetodo, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "indexOf") == 0
			&& strcmp(dadosMetodo->tipo, "(Ljava/lang/String;)I") == 0) {
		int strstr_value;
		char *strstr_char;
		string1 =
				(char*) desempilhaOperando((&ae->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando((&ae->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

		strstr_char = strstr(string1, string2);
		strstr_value = strstr_char - string1;

		empilhaOperando(&(ae->pFrame->pilhaOperandos), "I", &strstr_value);

		return 0;
	} else if (strcmp(dadosMetodo->nomeMetodo, "java/lang/String") == 0
			&& strcmp(dadosMetodo->nomeMetodo, "startsWith") == 0
			&& strcmp(dadosMetodo->tipo, "(Ljava/lang/String;)Z") == 0) {
		char bool_return;
		char *strstr_char;
		string1 = (char*)desempilhaOperando(ae->pFrame)->elementos[0].tipo_referencia;
				string2 =
						(char*) desempilhaOperando(
								(&ae->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

				strstr_char = strstr(string1, string2);
				bool_return = (strstr_char - string1 == 0) ? 1 : 0;

				empilhaOperando(&(ae->pFrame->pilhaOperandos), "Z",
						&bool_return);

				return 0;

			} else {
				DadosMetodo *dadosMetodo;
				int arg_count;

				dadosMetodo = retornaDadosMetodo(ae->pFrame->cf, cp_indice);

				arg_count = retornaContadorArgumentos(dadosMetodo->tipo) + 1;

//				jump(ae, dadosMetodo->nomeClasse, dadosMetodo->nomeMetodo,
//						dadosMetodo->tipo, arg_count);

				iniciaClasse(dadosMetodo->nomeClasse, ae, dadosMetodo->nomeMetodo, dadosMetodo->tipo);
			}

			return 0;

		}

