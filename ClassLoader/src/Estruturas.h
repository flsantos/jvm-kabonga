#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Definicao dos tipos */

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

typedef int8_t i1;
typedef int16_t i2;
typedef int32_t i4;
typedef int64_t i8;

typedef struct UFLOAT {
	union {
		u4 bits;
		float valor;
	} uf;
} uFloat;

typedef struct UDOUBLE {
	union {
		u8 bits;
		double valor;
	} ud;
} uDouble;

/*
 * Definicao da estrutura de uma Constant_Pool
 * A estrutura e composta por uma tag e por uma union.
 * A union e composta por cada uma das possiveis tags.
 */
typedef struct CP_INFO {
	u1 tag;
	union {
		struct {
			u2 name_index;
		} Class;
		struct {
			u2 class_index;
			u2 name_and_type_index;
		} Fieldref;
		struct {
			u2 name_index;
			u2 descriptor_index;
		} NameAndType;
		struct {
			u2 length;
			u1 *bytes;
		} Utf8;
		struct {
			u2 class_index;
			u2 name_and_type_index;
		} Methodref;
		struct {
			u2 class_index;
			u2 name_and_type_index;
		} InterfaceMethodref;
		struct {
			u2 string_index;
		} String;
		struct {
			u4 bytes;
		} Integer;
		struct {
			uFloat bytes;
		} Float;
		struct {
			u4 high_bytes;
			u4 low_bytes;
		} Long;
		struct {
			uDouble bytes;
		} Double;

	} u;
} cp_info;

typedef struct EXCEPTION_TABLE{
	u2 start_pc;
	u2 end_pc;
	u2 handler_pc;
	u2 catch_type;
} exception_table;

typedef struct LINE_NUMBER_TABLE{
	u2 start_pc;
	u2 line_number;
} line_number_table;

typedef struct LOCAL_VARIABLE_TABLE{
	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;
} local_variable_table;

typedef struct CLASSES{
	u2 inner_class_info_index;
	u2 outer_class_info_index;
	u2 inner_name_index;
	u2 inner_class_access_flags;
} classes;

typedef struct ATTRIBUTE_INFO {
	u2 attribute_name_index;
	u4 attribute_length;
	//u1 *info;
	union {
		struct ConstantValue_attribute {
			u2 constantvalue_index;
		} ConstantValue;
		struct Code_attribute {
			u2 max_stack;
			u2 max_locals;
			u4 code_length;
			u1 * code;
			u2 exception_table_length;
			exception_table * exception_table;
			u2 attributes_count;
			struct ATTRIBUTE_INFO * attributes;
		} Code;
		struct Exceptions_attribute {
			u2 number_of_exceptions;
			u2 * exception_index_table;
		} Exceptions;
		struct InnerClasses_attribute {
			u2 number_of_classes;
			classes * classes;
		} InnerClasses;
		struct Synthetic_attribute {
			u2 attribute_name_index;
			u4 attribute_length;
		} Synthetic;
		struct Default_attribute {
			u1 *info;
		} Default;
	} u;

} attribute_info;

typedef struct FIELD_INFO {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info *attributes;
} field_info;

typedef struct METHOD_INFO {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info *attributes;
} method_info;

/*
 * Definicao da estrutura de um Classfile
 * As informacoes nao utilizadas estao comentadas
 */
typedef struct  CLASSFILE{
	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
	cp_info *constant_pool /*[constant_pool_count-1]*/;
	u2 access_flags;
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2 *interfaces;
	u2 fields_count;
	field_info *fields;
	u2 methods_count;
	method_info *methods /*[struct classfile.methods_count]*/;
	u2 attributes_count;
	attribute_info *attributes;
} ClassFile;

typedef struct LIST_CLASSFILE{
	u1 *class_name;
	ClassFile *cf;
	struct LIST_CLASSFILE *prox;
}List_Classfile;


typedef union TIPO{
	i1 tipo_byte;
	u1 tipo_char;
	u2 tipo_short;
	u4 tipo_int;
	float tipo_float;
	double tipo_double;
	long tipo_long;
	char tipo_boolean;
	void *tipo_referencia;
	u1 *tipo_retorno;
} Tipo;

typedef struct PILHA{
	i2 sp;
	Tipo *elementos;
	char **tipo;
} PilhaOperandos, PilhaVariaveisLocais;

typedef struct FRAME{
	int enderecoPC;
	u4 *pc;
	u4 code_length;
	cp_info *constant_pool;
	PilhaOperandos *pilhaOperandos;
	PilhaVariaveisLocais *pilhaVariaveisLocais;
	ClassFile *cf;
	struct FRAME *frameAnterior;
} Frame;

typedef struct AMBIENTEEXECUCAO{
	Frame *pFrame;
	List_Classfile *pClassHeap;
}AmbienteExecucao;


typedef struct TIPO_INFO {
	char *nome;
	char *tipo;
	Tipo elemento;
} tipo_info;


/*
 * Estrutura do Objeto a ser instanciado
 */
typedef struct OBJETO {
	char *nomeClasse;
	int tipos_count;
	tipo_info *tipos;
} Objeto;

typedef struct DADOSMETODO {
	char *nomeClasse;
	char *nomeMetodo;
	char *tipo;

} DadosMetodo;

typedef struct DADOSFIELD {
	char *nomeClasse;
	char *nomeMetodo;
	char *tipo;
} DadosField;

typedef struct DADOSNAMEANDTYPE {
	char *nome;
	char *tipo;
} DadosNameAndType;

typedef struct DADOSMETHODANDCLASS {
	method_info *method_info;
	ClassFile *class_file;
} DadosMethodAndClass;

#endif
