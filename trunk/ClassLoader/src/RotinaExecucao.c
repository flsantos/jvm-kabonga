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
#include "RotinaExecucao.h"

char* mnemonicos[]={
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
	int i = 0;
	while (1) {
		instrucao = leU1doPC(ae->pFrame);
		debugPrintLinha();
		debugPrintInstrucoes(mnemonicos[instrucao], i++);
		if(vetFunc[instrucao](ae) == -1 && instrucao == RETURN){
			break;
		}
	}
	return 0;
}
