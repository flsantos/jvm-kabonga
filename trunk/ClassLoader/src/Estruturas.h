

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* Definicao dos tipos */

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

typedef struct structFloat {
	union {
		u4 bits;
		float valor;
	} uf;
} uFloat;

typedef struct structDouble {
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
typedef struct CP_info {
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

typedef struct {
	u2 start_pc;
	u2 end_pc;
	u2 handler_pc;
	u2 catch_type;
} exception_table;

typedef struct {
	u2 start_pc;
	u2 line_number;
} line_number_table;

typedef struct {
	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;
} local_variable_table;

typedef struct {
	u2 inner_class_info_index;
	u2 outer_class_info_index;
	u2 inner_name_index;
	u2 inner_class_access_flags;
} classes;

typedef struct attribute_Info {
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
			struct attribute_Info * attributes;
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

typedef struct Field {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info *attributes;
} field_info;

typedef struct Method {
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
typedef struct classfile {
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
