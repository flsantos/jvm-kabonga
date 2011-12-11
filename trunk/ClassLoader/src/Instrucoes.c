/*
 * Instrucoes.c
 *
 *  Created on: 09/12/2011
 *      Author: Frederico
 */

#include "Estruturas.h"

int (*vetFunc[])(unsigned char *p) = {
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



int ireturn(AmbienteExecucao *ambienteexecucao){
	int return_v;
	return_v = jumpback(ambienteexecucao, 1);


	return return_v;
}





int astore(AmbienteExecucao *ae) {
	u1 pos = lerU1doPc(ae->pFrame);
	//transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);
	transferePilha2VariavelLocal(ae->pFrame, pos);
	return 0;
}

int aload(AmbienteExecucao *ae) {
	u1 pos = lerU1doPc(ae->pFrame);
	//transfer_localvar_to_opstack(&(interpreter->current_frame->local_variables), pos, &(interpreter->current_frame->opstack));
	transfereVariavelLocal2Pilha(ae->pFrame, pos);
	return 0;
}

int istore(AmbienteExecucao *ae) {
	u1 pos = lerU1doPc(ae->pFrame);
	//transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);
	transferePilhaOperandos2VariavelLocal(ae->pFrame, pos);
	return 0;
}

int invokespecial(AmbienteExecucao *ae) {
	u2 indice = lerU2doPc(ae->pFrame);
	t_method_about *method_about;
	int arg_count;

	method_about = find_method_info(interpreter->current_frame->class_file,
			index);

	if ((strcmp(method_about->className, "java/lang/StringBuffer") == 0
			|| strcmp(method_about->className, "java/lang/StringBuilder") == 0)
			&& strcmp(method_about->methodName, "<init>") == 0) {
		opstack_pop(&(interpreter->current_frame->opstack));
		return 0;
	}

	arg_count = arguments_count(method_about->type) + 1;

	jump(interpreter, method_about->className, method_about->methodName,
			method_about->type, arg_count);

	return 0;
}

int dup(AmbienteExecucao *ae) {

	//t_opstack *a = opstack_pop((&interpreter->current_frame->opstack));
	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	if ((*(a->tipo[0]) == 'J') || (*(a->tipo[0]) == 'D')) {
		printf(
				stderr,
				"Instrucao 'dup' nao permitida para valores 'double' ou 'long'.\n");
		exit(1);
	}

	//opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame, a->tipo[0], a->elementos[a->sp]);
	//opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame, a->tipo[0], a->elementos[a->sp]);

	return 0;
}

int new_(AmbienteExecucao *ae) {
	u2 indice = lerU2doPc(ae->pFrame);
	char *classname;
	ClassFile *cf;
	Objeto *objeto;

	classname = retornaNomeClasse(&(ae->pFrame->cf[indice]));

	/* ajustando para o caso da StringBuffer */
	if ((strcmp(classname, "java/lang/StringBuffer") == 0
			|| strcmp(classname, "java/lang/StringBuilder") == 0)) {
		char * strvazia;
		strvazia = calloc(1, sizeof(char));
		*strvazia = '\0';
		//opstack_push(&(interpreter->current_frame->opstack), "[C", strvazia);
		empilhaOperandos(ae->pFrame, "[C", strvazia);
		return 0;
	}

	//class_file = leitura_class_file(interpreter, classname);
	cf = iniciaClasse(classname, ae, "<init>", "()V");

	//TODO esperando o capuleto para o objeto
	//object = instanciate_object(class_file, interpreter);

	//opstack_push(&(interpreter->current_frame->opstack), "L", object);
	empilhaOperandos(ae->pFrame, "L", objeto);

	return 0;

}

int if_icmplt(AmbienteExecucao *ae) {
	u2 branchoffset = lerU2doPc(ae->pFrame);

	int a, b;
	//b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	//a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = desempilhaOperandos(ae->pFrame)->elementos.tipo_int;
	a = desempilhaOperandos(ae->pFrame)->elementos.tipo_int;

	if (a < b) {
		//interpreter->current_frame->pc += branchoffset -3;
		ae->pFrame->pc += branchoffset - 3;
		//interpreter->current_frame->pc_address += branchoffset -3;
		ae->pFrame->enderecoPC += branchoffset - 3;

	}

	return 0;
}

int iinc(AmbienteExecucao *ae) {
	u1 indice = lerU1doPc(ae->pFrame);
	u1 const_ = lerU1doPc(ae->pFrame);

	//(interpreter->current_frame->local_variables)[index].data.data_int += const_;
	ae->pFrame->pilhaVariaveisLocais[indice]->elementos->tipo_int += const_;
	return 0;
}

int ireturn(AmbienteExecucao *ae) {
	//TODO: retornar para o frame anterior

}

int ifne(AmbienteExecucao *ae) {
	int a;
	u2 branchoffset = lerU2doPc(ae->pFrame);
	a = desempilhaOperando(ae->pFrame)->Tipo.tipo_int;

	if (a != 0) {
		//interpreter->current_frame->pc += branchoffset -3;
		ae->pFrame->pc += branchoffset - 3;
		//interpreter->current_frame->pc_address += branchoffset -3;
		ae->pFrame->enderecoPc += branchoffset - 3;
	}

	return 0;
}

int iload(AmbienteExecucao *ae) {
	u1 pos = lerU1doPc(ae->pFrame);

	transfereVariavelLocal2Pilha(ae->pFrame, pos);
}

int irem(AmbienteExecucao *ae) {
	int a, b, rem;
	a = desempilhaOperandos(ae->pFrame)->Tipo.tipo_int;
	b = desempilhaOperandos(ae->pFrame)->Tipo.tipo_int;

	rem = b % a;

	opstack_push(ae->pFrame, "I", &rem);

	return 0;
}

int goto_(AmbienteExecucao *ae) {
	u2 branchoffset = lerU2doPc(ae->pFrame);

	ae->pFrame->pc += branchoffset - 3;

	return 0;
}

int istore(AmbienteExecucao *ae) {
	u1 pos = lerU1doPc(ae->pFrame);

	transferePilha2Variavel(ae->pFrame, pos);
	return 0;
}

int iconst(AmbienteExecucao *ae, int valor) {

	unsigned char instrucao = (unsigned char) lerInstrucao(ae->pFrame);
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

	empilhaOperandos(ae->pFrame, "I", &valor);

	return 0;
}

int invokevirtual(AmbienteExecucao *interpreter) {
	/* TODO: este invoke virtual nao esta pronto. so foi feito invoke
	 * virtual de excecao para o println, apenas!
	 */
	int cp_index = Leru2doPC(interpreter->pFrame);
	//TODO: t_method_about *method_about;
	PilhaOperandos *data;
	char *tipo;
	char *string1, *string2;
	int result_strcmp;
	char *string_to_append, *string_appended, *string_append;

	method_about = find_method_info(interpreter->pFrame->cf, cp_index);

	if (strcmp(method_about->className, "java/io/PrintStream") == 0
			&& (strcmp(method_about->methodName, "println") == 0
					|| strcmp(method_about->methodName, "print") == 0)) {
		/* realiza o println */
		if (interpreter->pFrame->pilhaOperandos->tipo[0] != '#') {
			data = DesempilhaOperando(interpreter->pFrame);
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
		desempilhaOperando(&(interpreter->pFrame->pilhaOperandos));

		if ((strcmp(method_about->methodName, "println") == 0)) {
			printf("\n");
		}
	} else if (strcmp(method_about->className, "java/lang/String") == 0
			&& strcmp(method_about->methodName, "equals") == 0) {
		string1 =
				(char*) desempilhaOperando(
						(&interpreter->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando(
						(&interpreter->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

		if (strcmp(string1, string2) == 0) {
			result_strcmp = 1;
			pilhaOperandos_push(&(interpreter->pFrame->pilhaOperandos), "I",
					&result_strcmp);
			return 0;
		} else {
			result_strcmp = 0;
			pilhaOperandos_push(&(interpreter->pFrame->pilhaOperandos), "I",
					&result_strcmp);
			return 0;
		}
	} else if ((strcmp(method_about->className, "java/lang/StringBuffer") == 0
			|| strcmp(method_about->className, "java/lang/StringBuilder") == 0)
			&& strcmp(method_about->methodName, "append") == 0) {
		string_append = calloc(50, sizeof(char));
		data = desempilhaOperando(&(interpreter->pFrame->pilhaOperandos));
		tipo = data->tipo;
		string_to_append =
				(char*) desempilhaOperando(
						&(interpreter->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;
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

		pilhaOperandos_push(&(interpreter->pFrame->pilhaOperandos), "[C",
				string_appended);
		return 0;

	} else if ((strcmp(method_about->className, "java/lang/StringBuffer") == 0
			|| strcmp(method_about->className, "java/lang/StringBuilder") == 0)
			&& strcmp(method_about->methodName, "toString") == 0) {
		return 0;
	} else if (strcmp(method_about->className, "java/lang/String") == 0
			&& strcmp(method_about->methodName, "length") == 0) {
		int len;
		string1 =
				(char*) desempilhaOperando(
						(&interpreter->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

		len = strlen(string1);

		pilhaOperandos_push(&(interpreter->pFrame->pilhaOperandos), "I", &len);

		return 0;
	} else if (strcmp(method_about->className, "java/lang/String") == 0
			&& strcmp(method_about->methodName, "compareTo") == 0) {
		int strcm;
		string1 =
				(char*) desempilhaOperando(
						(&interpreter->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando(
						(&interpreter->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

		strcm = strcmp(string1, string2);

		pilhaOperandos_push(&(interpreter->pFrame->pilhaOperandos), "I",
				&strcm);

		return 0;
	} else if (strcmp(method_about->className, "java/lang/String") == 0
			&& strcmp(method_about->methodName, "indexOf") == 0
			&& strcmp(method_about->tipo, "(Ljava/lang/String;)I") == 0) {
		int strstr_value;
		char *strstr_char;
		string1 =
				(char*) desempilhaOperando(
						(&interpreter->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;
		string2 =
				(char*) desempilhaOperando(
						(&interpreter->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

		strstr_char = strstr(string1, string2);
		strstr_value = strstr_char - string1;

		pilhaOperandos_push(&(interpreter->pFrame->pilhaOperandos), "I",
				&strstr_value);

		return 0;
	} else if (strcmp(method_about->className, "java/lang/String") == 0
			&& strcmp(method_about->methodName, "startsWith") == 0
			&& strcmp(method_about->tipo, "(Ljava/lang/String;)Z") == 0) {
		char bool_return;
		char *strstr_char;
		string1 = (char*)DesempilhaOperandos((&interpreter->pFrame->pilhaOperandos->elementos[0].tipo_referencia;
		string2 =
				(char*) DesempilhaOperandos(
						(&interpreter->pFrame->pilhaOperandos))->elementos[0].tipo_referencia;

		strstr_char = strstr(string1, string2);
		bool_return = (strstr_char - string1 == 0) ? 1 : 0;

		pilhaOperandos_push(
				&(interpreter->pFrame->pilhaOperandos), "Z",
				&bool_return);

		return 0;

	} else {
		t_method_about *method_about;
		int arg_count;

		method_about = find_method_info(
				interpreter->pFrame->class_file, cp_index);

		arg_count = arguments_count(method_about->tipo) + 1;

		jump(interpreter, method_about->className,
				method_about->methodName, method_about->tipo,
				arg_count);
	}

	return 0;
}
