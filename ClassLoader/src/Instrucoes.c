/*
 * Instrucoes.c
 *
 *  Created on: 09/12/2011
 *      Author: Frederico
 */

#include "Estruturas.h"

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

	method_about = find_method_info(interpreter->current_frame->class_file, index);

	if((strcmp(method_about->className, "java/lang/StringBuffer") == 0 || strcmp(method_about->className, "java/lang/StringBuilder") == 0) &&
	   strcmp(method_about->methodName, "<init>") == 0) {
		opstack_pop(&(interpreter->current_frame->opstack));
		return 0;
	}

	arg_count = arguments_count(method_about->type) + 1;

	jump(interpreter, method_about->className, method_about->methodName, method_about->type, arg_count);


	return 0;
}

int dup(AmbienteExecucao *ae){

	//t_opstack *a = opstack_pop((&interpreter->current_frame->opstack));
	PilhaOperandos *a = desempilhaOperando(ae->pFrame);
	if(( *(a->tipo[0])=='J' ) || ( *(a->tipo[0])=='D' )){
		printf(stderr,"Instrucao 'dup' nao permitida para valores 'double' ou 'long'.\n");
		exit(1);
	}

	//opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame,a->tipo[0],a->elementos[a->sp]);
	//opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	empilhaOperando(ae->pFrame,a->tipo[0],a->elementos[a->sp]);

	return 0;
}


int new_(AmbienteExecucao *ae) {
	u2 indice = lerU2doPc(ae->pFrame);
	char *classname;
	ClassFile *cf;
	Objeto *objeto;

	classname = retornaNomeClasse(&(ae->pFrame->cf[indice]));


	/* ajustando para o caso da StringBuffer */
	if((strcmp(classname, "java/lang/StringBuffer") == 0 || strcmp(classname, "java/lang/StringBuilder") == 0)) {
		char * strvazia;
		strvazia = calloc(1, sizeof(char));
		*strvazia = '\0';
		//opstack_push(&(interpreter->current_frame->opstack), "[C", strvazia);
		empilhaOperandos(ae->pFrame, "[C", strvazia);
		return 0;
	}

	//class_file = leitura_class_file(interpreter, classname);
	cf = iniciaClasse(classname, ae,"<init>","()V");

	//TODO esperando o capuleto para o objeto
	//object = instanciate_object(class_file, interpreter);


	//opstack_push(&(interpreter->current_frame->opstack), "L", object);
	empilhaOperandos(ae->pFrame, "L", objeto);

	return 0;

}

int if_icmplt(AmbienteExecucao *ae){
	u2 branchoffset = lerU2doPc(ae->pFrame);

	int a, b;
	//b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	//a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = desempilhaOperandos(ae->pFrame)->elementos.tipo_int;
	a = desempilhaOperandos(ae->pFrame)->elementos.tipo_int;

	if (a < b){
		//interpreter->current_frame->pc += branchoffset -3;
		ae->pFrame->pc += branchoffset -3;
		//interpreter->current_frame->pc_address += branchoffset -3;
		ae->pFrame->enderecoPC += branchoffset -3;

	}

	return 0;
}

int iinc(AmbienteExecucao *ae){
	u1 indice = lerU1doPc(ae->pFrame);
	u1 const_ = lerU1doPc(ae->pFrame);

	//(interpreter->current_frame->local_variables)[index].data.data_int += const_;
	ae->pFrame->pilhaVariaveisLocais[indice]->elementos->tipo_int += const_;
	return 0;
}

int ireturn(AmbienteExecucao *ae){
	//TODO: retornar para o frame anterior

}

int ifne(AmbienteExecucao *ae){
	int a;
	u2 branchoffset = lerU2doPc(ae->pFrame);
	a = desempilhaOperando(ae->pFrame)->Tipo.tipo_int;

	if (a != 0){
		//interpreter->current_frame->pc += branchoffset -3;
		ae->pFrame->pc += branchoffset -3;
		//interpreter->current_frame->pc_address += branchoffset -3;
		ae->pFrame->enderecoPc += branchoffset -3;
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

	rem = b%a;

	opstack_push(ae->pFrame, "I", &rem);

	return 0;
}

int goto_(AmbienteExecucao *ae){
	u2 branchoffset = lerU2doPc(ae->pFrame);

	ae->pFrame->pc += branchoffset -3;

	return 0;
}

int istore(AmbienteExecucao *ae) {
	u1 pos = lerU1doPc(ae->pFrame);

	transferePilha2Variavel(ae->pFrame , pos);
	return 0;
}

int iconst(AmbienteExecucao *ae, int valor) {

	unsigned char instrucao = (unsigned char)lerInstrucao(ae->pFrame);
	switch(instrucao) {
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

	empilhaOperandos(ae->pFrame, "I", &valor);

	return 0;
}
