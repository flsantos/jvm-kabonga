/*
 * Instrucoes.h
 *
 *  Created on: 10/12/2011
 *      Author: Daniel
 */

#ifndef INSTRUCOES_H_
#define INSTRUCOES_H_


#define NOP 0
#define ACONST_NULL 1
#define ICONST_M1 2
#define ICONST_0 3
#define ICONST_1 4
#define ICONST_2 5
#define ICONST_3 6
#define ICONST_4 7
#define ICONST_5 8
#define LCONST_0 9
#define LCONST_1 10
#define FCONST_0 11
#define FCONST_1 12
#define FCONST_2 13
#define DCONST_0 14
#define DCONST_1 15
#define BIPUSH 16
#define SIPUSH 17
#define LDC 18
#define LDC_W 19
#define LDC2_W 20
#define ILOAD 21
#define LLOAD 22
#define FLOAD 23
#define DLOAD 24
#define ALOAD 25
#define ILOAD_0 26
#define ILOAD_1 27
#define ILOAD_2 28
#define ILOAD_3 29
#define LLOAD_0 30
#define LLOAD_1 31
#define LLOAD_2 32
#define LLOAD_3 33
#define FLOAD_0 34
#define FLOAD_1 35
#define FLOAD_2 36
#define FLOAD_3 37
#define DLOAD_0 38
#define DLOAD_1 39
#define DLOAD_2 40
#define DLOAD_3 41
#define ALOAD_0 42
#define ALOAD_1 43
#define ALOAD_2 44
#define ALOAD_3 45
#define IALOAD 46
#define LALOAD 47
#define FALOAD 48
#define DALOAD 49
#define AALOAD 50
#define BALOAD 51
#define CALOAD 52
#define SALOAD 53
#define ISTORE 54
#define LSTORE 55
#define FSTORE 56
#define DSTORE 57
#define ASTORE 58
#define ISTORE_0 59
#define ISTORE_1 60
#define ISTORE_2 61
#define ISTORE_3 62
#define LSTORE_0 63
#define LSTORE_1 64
#define LSTORE_2 65
#define LSTORE_3 66
#define FSTORE_0 67
#define FSTORE_1 68
#define FSTORE_2 69
#define FSTORE_3 70
#define DSTORE_0 71
#define DSTORE_1 72
#define DSTORE_2 73
#define DSTORE_3 74
#define ASTORE_0 75
#define ASTORE_1 76
#define ASTORE_2 77
#define ASTORE_3 78
#define IASTORE 79
#define LASTORE 80
#define FASTORE 81
#define DASTORE 82
#define AASTORE 83
#define BASTORE 84
#define CASTORE 85
#define SASTORE 86
#define POP 87
#define POP2 88
#define DUP 89
#define DUP_X1 90
#define DUP_X2 91
#define DUP2 92
#define DUP2_X1 93
#define DUP2_X2 94
#define SWAP 95
#define IADD 96
#define LADD 97
#define FADD 98
#define DADD 99
#define ISUB 100
#define LSUB 101
#define FSUB 102
#define DSUB 103
#define IMUL 104
#define LMUL 105
#define FMUL 106
#define DMUL 107
#define IDIV 108
#define LDIV 109
#define FDIV 110
#define DDIV 111
#define IREM 112
#define LREM 113
#define FREM 114
#define DREM 115
#define INEG 116
#define LNEG 117
#define FNEG 118
#define DNEG 119
#define ISHL 120
#define LSHL 121
#define ISHR 122
#define LSHR 123
#define IUSHR 124
#define LUSHR 125
#define IAND 126
#define LAND 127
#define IOR 128
#define LOR 129
#define IXOR 130
#define LXOR 131
#define IINC 132
#define I2L 133
#define I2F 134
#define I2D 135
#define L2I 136
#define L2F 137
#define L2D 138
#define F2I 139
#define F2L 140
#define F2D 141
#define D2I 142
#define D2L 143
#define D2F 144
#define I2B 145
#define I2C 146
#define I2S 147
#define LCMP 148
#define FCMPL 149
#define FCMPG 150
#define DCMPL 151
#define DCMPG 152
#define IFEQ 153
#define IFNE 154
#define IFLT 155
#define IFGE 156
#define IFGT 157
#define IFLE 158
#define IF_ICMPEQ 159
#define IF_ICMPNE 160
#define IF_ICMPLT 161
#define IF_ICMPGE 162
#define IF_ICMPGT 163
#define IF_ICMPLE 164
#define IF_ACMPEQ 165
#define IF_ACMPNE 166
#define GOTO 167
#define JSR 168
#define RET 169
#define TABLESWITCH 170
#define LOOKUPSWITCH 171
#define IRETURN 172
#define LRETURN 173
#define FRETURN 174
#define DRETURN 175
#define ARETURN 176
#define RETURN 177
#define GETSTATIC 178
#define PUTSTATIC 179
#define GETFIELD 180
#define PUTFIELD 181
#define INVOKEVIRTUAL 182
#define INVOKESPECIAL 183
#define INVOKESTATIC 184
#define INVOKEINTERFACE 185
#define XXXUNUSEDXXX1 186
#define NEW 187
#define NEWARRAY 188
#define ANEWARRAY 189
#define ARRAYLENGTH 190
#define ATHROW 191
#define CHECKCAST 192
#define INSTANCEOF 193
#define MONITORENTER 194
#define MONITOREXIT 195
#define WIDE 196
#define MULTIANEWARRAY 197
#define IFNULL 198
#define IFNONNULL 199
#define GOTO_W 200
#define JSR_W 201

int nop(AmbienteExecucao *ae);
int bipush(AmbienteExecucao *ae);
int aconst_null(AmbienteExecucao *ae);
int istore(AmbienteExecucao *ae);


int iload(AmbienteExecucao *ae);

int iadd(AmbienteExecucao *ae);

int i2d(AmbienteExecucao *ae);

int dstore(AmbienteExecucao *ae);

int ldc(AmbienteExecucao *ae);

int fstore(AmbienteExecucao *ae);

int fload(AmbienteExecucao *ae);

int f2l(AmbienteExecucao *ae);

int lstore(AmbienteExecucao *ae);


int iconst(AmbienteExecucao *ae);

int dload(AmbienteExecucao *ae);

int d2i(AmbienteExecucao *ae);
int lload(AmbienteExecucao *ae);

int l2i(AmbienteExecucao *ae);

int lconst(AmbienteExecucao *ae);

int fconst(AmbienteExecucao *ae);

int dconst(AmbienteExecucao *ae);

int sipush(AmbienteExecucao *ae);

int aload(AmbienteExecucao *ae);

int pop(AmbienteExecucao *ae);

int pop2(AmbienteExecucao *ae);

int d2f(AmbienteExecucao *ae);

int d2l(AmbienteExecucao *ae);

int f2d(AmbienteExecucao *ae);

int f2i(AmbienteExecucao *ae);

int i2b(AmbienteExecucao *ae);

int i2c(AmbienteExecucao *ae);

int i2f(AmbienteExecucao *ae);

int i2l(AmbienteExecucao *ae);

int i2s(AmbienteExecucao *ae);

int l2d(AmbienteExecucao *ae);

int l2f(AmbienteExecucao *ae);

int dmul(AmbienteExecucao *ae);

int fmul(AmbienteExecucao *ae);

int imul(AmbienteExecucao *ae);

int lmul(AmbienteExecucao *ae);

int invokevirtual(AmbienteExecucao *ae);

int getstatic(AmbienteExecucao *ae);

int dadd(AmbienteExecucao *ae);
int dsub(AmbienteExecucao *ae);
int fadd(AmbienteExecucao *ae);
int fsub(AmbienteExecucao *ae);
int isub(AmbienteExecucao *ae);
int ladd(AmbienteExecucao *ae);
int lsub(AmbienteExecucao *ae);

int iand(AmbienteExecucao *ae);
int ineg(AmbienteExecucao *ae);
int ior(AmbienteExecucao *ae);
int ixor(AmbienteExecucao *ae);
int land(AmbienteExecucao *ae);
int lneg(AmbienteExecucao *ae);
int lor(AmbienteExecucao *ae);
int lxor(AmbienteExecucao *ae);
int dneg(AmbienteExecucao *ae);
int fneg(AmbienteExecucao *ae);

int astore(AmbienteExecucao *ae);
int ldiv_(AmbienteExecucao *ae);
int lrem(AmbienteExecucao *ae);

int fcmpg(AmbienteExecucao *ae);
int fcmpl(AmbienteExecucao *ae);
int lcmp(AmbienteExecucao *ae);
int frem(AmbienteExecucao *ae);
int drem_(AmbienteExecucao *ae);
int ishl(AmbienteExecucao *ae);
int ishr(AmbienteExecucao *ae);
int iushr(AmbienteExecucao *ae);
int lshl(AmbienteExecucao *ae);
int lshr(AmbienteExecucao *ae);
int lushr(AmbienteExecucao *ae);
int swap(AmbienteExecucao *ae);

int dup(AmbienteExecucao *ae);
int dup2(AmbienteExecucao *ae);
int dup_x1(AmbienteExecucao *ae);
int dup2_x2(AmbienteExecucao *ae);
int dup_x2(AmbienteExecucao *ae);
int dup2_x1(AmbienteExecucao *ae);

int goto_(AmbienteExecucao *ae);
int goto_w(AmbienteExecucao *ae);

int jsr(AmbienteExecucao *ae);
int jsr_w(AmbienteExecucao *ae);

int iinc(AmbienteExecucao *ae);

int newarray(AmbienteExecucao *ae);
int aaload(AmbienteExecucao *ae);
int iaload(AmbienteExecucao *ae);
int aastore(AmbienteExecucao *ae);
int iastore(AmbienteExecucao *ae);

int idiv_(AmbienteExecucao *ae);

int irem(AmbienteExecucao *ae);

int if_acmpeq(AmbienteExecucao *ae);
int if_acmpne(AmbienteExecucao *ae);
int if_icmpeq(AmbienteExecucao *ae);
int if_icmpne(AmbienteExecucao *ae);
int if_icmplt(AmbienteExecucao *ae);
int if_icmple(AmbienteExecucao *ae);
int if_icmpgt(AmbienteExecucao *ae);
int if_icmpge(AmbienteExecucao *ae);
int ifeq(AmbienteExecucao *ae);
int ifne(AmbienteExecucao *ae);
int iflt(AmbienteExecucao *ae);
int ifle(AmbienteExecucao *ae);
int ifgt(AmbienteExecucao *ae);
int ifge(AmbienteExecucao *ae);
int ifnonnull(AmbienteExecucao *ae);
int ifnull(AmbienteExecucao *ae);

int fastore(AmbienteExecucao *ae);
int faload(AmbienteExecucao *ae);
int daload(AmbienteExecucao *ae);
int dastore(AmbienteExecucao *ae);
int caload(AmbienteExecucao *ae);
int castore(AmbienteExecucao *ae);
int laload(AmbienteExecucao *ae);
int lastore(AmbienteExecucao *ae);
int saload(AmbienteExecucao *ae);
int sastore(AmbienteExecucao *ae);
int baload(AmbienteExecucao *ae);
int bastore(AmbienteExecucao *ae);

int arraylength(AmbienteExecucao *ae);

int return0(AmbienteExecucao *ae);
int return1(AmbienteExecucao *ae);

int athrow(AmbienteExecucao *ae);

int ret(AmbienteExecucao *ae);

int multianewarray(AmbienteExecucao *ae);

int anewarray(AmbienteExecucao *ae);

int wide(AmbienteExecucao *ae);

int new_(AmbienteExecucao *ae);
int putfield(AmbienteExecucao *ae);
int getfield(AmbienteExecucao *ae);

int fdiv(AmbienteExecucao *ae);
int ddiv(AmbienteExecucao *ae);
int fneg(AmbienteExecucao *ae);

int dcmpl(AmbienteExecucao *ae);
int dcmpg(AmbienteExecucao *ae);

int checkcast(AmbienteExecucao *ae);
int instanceof(AmbienteExecucao *ae);

int invokestatic(AmbienteExecucao *ae);
int invokespecial(AmbienteExecucao *ae);
int putstatic(AmbienteExecucao *ae);

int lookupswitch(AmbienteExecucao *ae);
int tableswitch(AmbienteExecucao *ae);

#endif /* INSTRUCOES_H_ */

int (*vetFunc[])(AmbienteExecucao *p);
u1 instrucao;


