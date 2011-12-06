/*
 *
 * ClassLoader.c
 *
 * Arquivo responsavel por ler o arquivo .class e
 * criar a estrutura ClassFile.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "ClassLoader.h"

/* Definicao das co nstantes */
#define CONSTANT_Class 7
#define CONSTANT_Fieldred 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1

/* Globals */
FILE *fp;


/*
 * Cabeçalhos
 */
u1 u1Read();
u2 u2Read();
u4 u4Read();
u8 u8Read();
char *getTag(u1);
void readConstantPool(ClassFile *);
void readAccessFlags(ClassFile *);
void readThisClass(ClassFile *);
void readSuperClass(ClassFile *);
void readInterfaceCount(ClassFile *);
void readInterfaces(ClassFile *);
void readFieldsCount(ClassFile *);
void readFieldsInfo(ClassFile *);
void readMethodsCount(ClassFile *);
void readMethodsInfo(ClassFile *);
void readAttributesCount(ClassFile *);
void readAttributesInfo(ClassFile *, attribute_info *);
void readAttributeConstantValue(attribute_info *ai);
void readAttributeCode(ClassFile *cf, attribute_info *ai);
void readAttributeExceptions(attribute_info *ai);
void readAttributeInnerClasses(attribute_info *ai);
void readAttributeSynthetic(attribute_info *ai);
void readAttributeDefault(attribute_info *ai);

/*
 * Funcao para ler um byte do arquivo
 */
u1 u1Read() {
	u1 toReturn = 0;
	toReturn = getc(fp);
	return toReturn;
}
/*
 * Funcao para ler um numero formado por 2 bytes
 */
u2 u2Read() {
	u2 toReturn = 0;
	toReturn = getc(fp);
	toReturn = (toReturn << 8) | (getc(fp));
	return toReturn;
}
/*
 * Funcao para ler um numero formado por 4 bytes
 */
u4 u4Read() {
	u4 toReturn = 0;
	toReturn = getc(fp);
	toReturn = (toReturn << 8) | (getc(fp));
	toReturn = (toReturn << 8) | (getc(fp));
	toReturn = (toReturn << 8) | (getc(fp));
	return toReturn;
}

/*
 * Funcao para ler um numero formado por 8 bytes
 */
u8 u8Read() {
	u8 toReturn = 0;
	toReturn = getc(fp);
	toReturn = (toReturn << 8) | (getc(fp));
	toReturn = (toReturn << 8) | (getc(fp));
	toReturn = (toReturn << 8) | (getc(fp));
	toReturn = (toReturn << 8) | (getc(fp));
	toReturn = (toReturn << 8) | (getc(fp));
	toReturn = (toReturn << 8) | (getc(fp));
	toReturn = (toReturn << 8) | (getc(fp));
	return toReturn;
}

/*
 * Funcao para retornar o nome de cada tag a partir do numero da tag
 */
char *getTag(u1 tag) {
	switch (tag) {
	case CONSTANT_Class:
		return "CONSTANT_Class";
	case CONSTANT_Fieldred:
		return "CONSTANT_Fieldred";
	case CONSTANT_NameAndType:
		return "CONSTANT_NameAndType";
	case CONSTANT_Utf8:
		return "CONSTANT_Utf8";
	case CONSTANT_Methodref:
		return "CONSTANT_Methodref";
	case CONSTANT_InterfaceMethodref:
		return "CONSTANT_InterfaceMethodref";
	case CONSTANT_String:
		return "CONSTANT_String";
	case CONSTANT_Integer:
		return "CONSTANT_Integer";
	case CONSTANT_Float:
		return "CONSTANT_Float";
	case CONSTANT_Long:
		return "CONSTANT_Long";
	case CONSTANT_Double:
		return "CONSTANT_Double";
	default:
		return "Erro! Tag desconhecida";
	}
}
/*
 * Ler o Pool de constantes do arquivo .class
 */

void readConstantPool(ClassFile *cf) {
	int i = 0, j = 0;

	for (i = 0; i < cf->constant_pool_count - 1; i++) {
		cp_info cp;
		cp.tag = u1Read();

		printf("\n\ntag : %d (%s)", cp.tag, getTag(cp.tag));

		switch (cp.tag) {
		case CONSTANT_Class:
			cp.u.Class.name_index = u2Read();
			printf("\nname_index : %d", cp.u.Class.name_index);
			break;
		case CONSTANT_Fieldred:
			cp.u.Fieldref.class_index = u2Read();
			cp.u.Fieldref.name_and_type_index = u2Read();
			printf("\nclass_index : %d", cp.u.Fieldref.class_index);
			printf("\nname_and_type_index : %d", cp.u.Fieldref.name_and_type_index);
			break;
		case CONSTANT_NameAndType:
			cp.u.NameAndType.name_index = u2Read();
			cp.u.NameAndType.descriptor_index = u2Read();
			printf("\nname_index : %d", cp.u.NameAndType.name_index);
			printf("\ndescriptor_index : %d", cp.u.NameAndType.descriptor_index);
			break;
		case CONSTANT_Utf8: /*Nesse caso o programa aloca memoria para a string e concatena um \0 no fim da string*/
			cp.u.Utf8.length = u2Read();
			cp.u.Utf8.bytes = malloc(sizeof(u1) * cp.u.Utf8.length + 1);
			for (j = 0; j < cp.u.Utf8.length; j++) {
				cp.u.Utf8.bytes[j] = u1Read();
			}
			cp.u.Utf8.bytes[j] = '\0';
			printf("\nlength : %d", cp.u.Utf8.length);
			printf("\nbytes : %s", cp.u.Utf8.bytes);
			break;
		case CONSTANT_Methodref:
			cp.u.Methodref.class_index = u2Read();
			cp.u.Methodref.name_and_type_index = u2Read();
			printf("\nclass_index : %d", cp.u.Methodref.class_index);
			printf("\nname_and_type_index : %d", cp.u.Methodref.name_and_type_index);
			break;
		case CONSTANT_InterfaceMethodref:
			cp.u.InterfaceMethodref.class_index = u2Read();
			cp.u.InterfaceMethodref.name_and_type_index = u2Read();
			printf("\nclass_index : %d", cp.u.InterfaceMethodref.class_index);
			printf("\nname_and_type_index : %d", cp.u.InterfaceMethodref.name_and_type_index);
			break;
		case CONSTANT_String:
			cp.u.String.string_index = u2Read();
			printf("\nstring_index : %d", cp.u.String.string_index);
			break;
		case CONSTANT_Integer:
			cp.u.Integer.bytes = u4Read();
			printf("\nbytes : %d", cp.u.Integer.bytes);
			break;
		case CONSTANT_Float:
			cp.u.Float.bytes.uf.bits = u4Read();
			printf("\nbytes : %f", cp.u.Float.bytes.uf.valor);
			break;
		case CONSTANT_Long:
			cp.u.Long.high_bytes = u4Read();
			cp.u.Long.low_bytes = u4Read();
			printf("\nhigh_bytes : %d", cp.u.Long.high_bytes);
			printf("\nllow_bytes : %d", cp.u.Long.low_bytes);
			break;
		case CONSTANT_Double:
			cp.u.Double.bytes.ud.bits = u8Read();
			printf("\nbytes : %f", cp.u.Double.bytes.ud.valor);
			break;
		default:
			break;
		}

		cf->constant_pool[i] = cp;

		printf("\n%d", i);
		if (cp.tag == CONSTANT_Double || cp.tag == CONSTANT_Long) {
			i++;
			cf->constant_pool[i] = cp;
		}
	}
}

/*
 * Ler access_flags do arquivo .class
 */
void readAccessFlags(ClassFile *cf) {
	cf->access_flags = u2Read();
	printf("\naccess_flags: 0x%04X", cf->access_flags);
}

/*
 * Ler indice do constant_pool que aponta para nome
 * da classe do arquivo .class
 */
void readThisClass(ClassFile *cf) {
	cf->this_class = u2Read();
	printf("\nthis_class: %d", cf->this_class);
	printf("\n%s", cf->constant_pool[cf->constant_pool[cf->this_class - 1].u.Class.name_index - 1].u.Utf8.bytes);
}

/*
 * Ler indice do constant_pool que aponta para nome
 * da classe pai do arquivo .class
 */
void readSuperClass(ClassFile *cf) {
	cf->super_class = u2Read();
	printf("\nsuper_class: %d", cf->super_class);
	printf("\n%s", cf->constant_pool[cf->constant_pool[cf->super_class - 1].u.Class.name_index - 1].u.Utf8.bytes);
}

/*
 * Ler interfaces_count do arquivo .class
 */
void readInterfaceCount(ClassFile *cf) {
	cf->interfaces_count = u2Read();
	printf("\ninterfaces_count: %d", cf->interfaces_count);
}

/*
 * Ler as interfaces do arquivo .class
 */
void readInterfaces(ClassFile *cf) {
	int i = 0;
	cf->interfaces = malloc((cf->interfaces_count) * sizeof(u2));
	for (i = 0; i < cf->interfaces_count; i++) {
		cf->interfaces[i] = u2Read();
		printf("\ninterfaces[%d]: %s", i,
				cf->constant_pool[cf->constant_pool[cf->interfaces[i] - 1].u.Class.name_index - 1].u.Utf8.bytes);
	}
}

 /*
 * Ler os atributos do tipo ConstantValue
 */
void readAttributeConstantValue(attribute_info *ai) {
	ai->u.ConstantValue.constantvalue_index = u2Read();
	printf("\nConstantValue.constantvalue_index : %d", ai->u.ConstantValue.constantvalue_index);
}

void readAttributeCode(ClassFile *cf, attribute_info *ai) {
	int i;
	ai->u.Code.max_stack = u2Read();
	printf("\nCode.max_stack: %d", ai->u.Code.max_stack);
	ai->u.Code.max_locals = u2Read();
	printf("\nCode.max_locals: %d", ai->u.Code.max_locals);
	ai->u.Code.code_length = u4Read();
	printf("\nCode.code_length: %d", ai->u.Code.code_length);

	ai->u.Code.code = malloc(ai->u.Code.code_length * sizeof(u1));
	printf("\nCode.code: 0x");
	for (i = 0; i < ai->u.Code.code_length; i++) {
		ai->u.Code.code[i] = u1Read();
		printf("%X", ai->u.Code.code[i]);
	}
	ai->u.Code.exception_table_length = u2Read();
	printf("\nCode.exception_table_length: %d", ai->u.Code.exception_table_length);
	ai->u.Code.exception_table = malloc(ai->u.Code.exception_table_length * sizeof(exception_table));
	for (i = 0; i < ai->u.Code.exception_table_length; i++) {
		ai->u.Code.exception_table[i].start_pc = u2Read();
		printf("\nCode.exception_table[%d].start_pc: %d", i, ai->u.Code.exception_table[i].start_pc);
		ai->u.Code.exception_table[i].end_pc = u2Read();
		printf("\nCode.exception_table[%d].end_pc: %d", i, ai->u.Code.exception_table[i].end_pc);
		ai->u.Code.exception_table[i].handler_pc = u2Read();
		printf("\nCode.exception_table[%d].handler_pc: %d", i, ai->u.Code.exception_table[i].handler_pc);
		ai->u.Code.exception_table[i].catch_type = u2Read();
		printf("\nCode.exception_table[%d].catch_type: %d", i, ai->u.Code.exception_table[i].catch_type);
	}
	ai->u.Code.attributes_count = u2Read();
	printf("\nCode.attributes_count: %d", ai->u.Code.attributes_count);
	ai->u.Code.attributes = malloc(ai->u.Code.attributes_count * sizeof(attribute_info));
	for (i = 0; i < ai->u.Code.attributes_count; i++) {
		readAttributesInfo(cf, &(ai->u.Code.attributes[i]));
	}
}

void readAttributeExceptions(attribute_info *ai) {
	int i;

	ai->u.Exceptions.number_of_exceptions = u2Read();
	printf("\nExceptions.number_of_exceptions: %d", ai->u.Exceptions.number_of_exceptions);
	ai->u.Exceptions.exception_index_table = malloc(ai->u.Exceptions.number_of_exceptions * sizeof(u2));
	for (i = 0; i < ai->u.Exceptions.number_of_exceptions; i++) {
		ai->u.Exceptions.exception_index_table[i] = u2Read();
		printf("\nExceptions.exception_index_table[%d]: %d", i, (int)ai->u.Exceptions.exception_index_table);
	}
}

void readAttributeInnerClasses(attribute_info *ai) {
	int i;
	ai->u.InnerClasses.number_of_classes = u2Read();
	printf("\nInnerClasses.number_of_classes: %d", ai->u.InnerClasses.number_of_classes);
	ai->u.InnerClasses.classes = malloc(ai->u.InnerClasses.number_of_classes * sizeof(classes));
	for (i = 0; i < ai->u.InnerClasses.number_of_classes; i++) {
		ai->u.InnerClasses.classes[i].inner_class_info_index = u2Read();
		printf("\nInnerClasses.classes[%d].inner_class_info_index: %d", i, ai->u.InnerClasses.classes[i].inner_class_info_index);
		ai->u.InnerClasses.classes[i].outer_class_info_index = u2Read();
		printf("\nInnerClasses.classes[%d].outer_class_info_index: %d", i, ai->u.InnerClasses.classes[i].outer_class_info_index);
		ai->u.InnerClasses.classes[i].inner_name_index = u2Read();
		printf("\nInnerClasses.classes[%d].inner_name_index %d", i, ai->u.InnerClasses.classes[i].inner_name_index);
		ai->u.InnerClasses.classes[i].inner_class_access_flags = u2Read();
		printf("\nInnerClasses.classes[%d].inner_class_access_flags: %d", i, ai->u.InnerClasses.classes[i].inner_class_access_flags);
	}
}

void readAttributeSynthetic(attribute_info *ai) {
	ai->u.Synthetic.attribute_name_index = u2Read();
	printf("\nSynthetic.attribute_name_index: %d", ai->u.Synthetic.attribute_name_index);
	ai->u.Synthetic.attribute_length = u4Read();
	printf("\nSynthetic.attribute_length: %d", ai->u.Synthetic.attribute_length);
}

void readAttributeDefault(attribute_info *ai){
	int k;
	ai->u.Default.info = malloc((ai->attribute_length) * sizeof(u1));
	for (k = 0; k < ai->attribute_length; k++) {
		ai->u.Default.info[k] = u1Read();
	}
}

void readAttributesInfo(ClassFile *cf, attribute_info *ai) {
	char *str;

	ai->attribute_name_index = u2Read();
	ai->attribute_length = u4Read();
	str = malloc(sizeof(char) * cf->constant_pool[ai->attribute_name_index - 1].u.Utf8.length);
	strcpy(str, (const char*) cf->constant_pool[ai->attribute_name_index - 1].u.Utf8.bytes);
	printf("\nNome do atributo: %s ", str);
	if (strcmp(str, "ConstantValue") == 0) {
		readAttributeConstantValue(ai);
	} else if (strcmp(str, "Code") == 0) {
		readAttributeCode(cf, ai);
	} else if (strcmp(str, "Exceptions") == 0) {
		readAttributeExceptions(ai);
	} else if (strcmp(str, "InnerClasses") == 0) {
		readAttributeInnerClasses(ai);
	} else if (strcmp(str, "Synthetic") == 0) {
		readAttributeSynthetic(ai);
	} else {
		readAttributeDefault(ai);
	}
}

/*
 * Ler fields_count do arquivo .class
 */

void readFieldsCount(ClassFile *cf) {
	cf->fields_count = u2Read();
	printf("\nfields_count: %d", cf->fields_count);
}

/*
 * Ler o fields_info do arquivo .class
 */
void readFieldsInfo(ClassFile *cf) {

	int i = 0, j = 0;
	cf->fields = malloc((cf->fields_count) * sizeof(field_info));
	for (i = 0; i < cf->fields_count; i++) {
		cf->fields[i].access_flags = u2Read();
		cf->fields[i].name_index = u2Read();
		cf->fields[i].descriptor_index = u2Read();
		cf->fields[i].attributes_count = u2Read();
		cf->fields[i].attributes = malloc((cf->fields[i].attributes_count) * sizeof(attribute_info));
		printf("\n\nfield.access_flags: 0x%04X", cf->fields[i].access_flags);
		printf("\nfield.name_index: %d", cf->fields[i].name_index);
		printf("\nfield.descriptor_index: %d", cf->fields[i].descriptor_index);
		printf("\nfield.attributes_count: %d", cf->fields[i].attributes_count);
		for (j = 0; j < cf->fields[i].attributes_count; j++) {
			readAttributesInfo(cf, &(cf->fields[i].attributes[j]));
		}
	}

}

/*
 * Ler methods_count do arquivo .class
 */
void readMethodsCount(ClassFile *cf) {
	cf->methods_count = u2Read();
	printf("\nmethods_count: %d", cf->methods_count);
}

/*
 * Ler o methods_info do arquivo .class
 */
void readMethodsInfo(ClassFile *cf) {
	int i = 0, j = 0;
	cf->methods = malloc((cf->methods_count) * sizeof(method_info));
	for (i = 0; i < cf->methods_count; i++) {
		cf->methods[i].access_flags = u2Read();
		cf->methods[i].name_index = u2Read();
		cf->methods[i].descriptor_index = u2Read();
		cf->methods[i].attributes_count = u2Read();
		cf->methods[i].attributes = malloc((cf->methods[i].attributes_count) * sizeof(attribute_info));
		printf("\n\nmethod.access_flags: 0x%04X", cf->methods[i].access_flags);
		printf("\nmethod.name_index: %d", cf->methods[i].name_index);
		printf("\nmethod.descriptor_index: %d", cf->methods[i].descriptor_index);
		printf("\nmethod.attributes_count: %d", cf->methods[i].attributes_count);
		for (j = 0; j < cf->methods[i].attributes_count; j++) {
			readAttributesInfo(cf, &(cf->methods[i].attributes[j]));
		}
	}

}

/*
 * Ler attributes_count do arquivo .class
 */
void readAttributesCount(ClassFile *cf) {
	cf->attributes_count = u2Read();
	printf("\nattributes_count: %d", cf->attributes_count);
}

/*
 * Funcao principal do ClassLoader
 *
 * Essa funcao abre o arquivo .class e vai lendo seu conteudo.
 * Le as informacoes iniciais (magic, minor_version, major_version, constant_pool_count) e depois le a ConstantPool

 */
ClassFile lerClassFile(char *nomeArquivo) {
	ClassFile cf;
	int i;

	fp = fopen(nomeArquivo, "rb");
	if (fp == NULL) {
		printf("Arquivo nao encontrado");
		exit(1);
	}

	cf.magic = u4Read();
	if (cf.magic == 0xCAFEBABE) {

		cf.minor_version = u2Read();
		cf.major_version = u2Read();
//		if (cf.major_version < 45 || cf.major_version> 46 || (cf.major_version == 46 && cf.minor_version > 0)) {
//			printf("Versão nao suportada.");
//			exit(1);
//		}
		cf.constant_pool_count = u2Read();
		printf("\nmagic_number : 0xCAFEBABE");
		printf("\nminor_version : %d", cf.minor_version);
		printf("\nmajor_version : %d", cf.major_version);
		printf("\nconstant_pool_count : %d", cf.constant_pool_count);

		/* Alocacao de memoria para a constant_pool */
		cf.constant_pool = malloc((cf.constant_pool_count - 1) * sizeof(cp_info));

		printf("\n--------------------");
		readConstantPool(&cf);
		printf("\n--------------------");
		readAccessFlags(&cf);
		printf("\n--------------------");
		readThisClass(&cf);
		printf("\n--------------------");
		readSuperClass(&cf);
		printf("\n--------------------");
		readInterfaceCount(&cf);
		printf("\n--------------------");
		readInterfaces(&cf);
		printf("\n--------------------");
		readFieldsCount(&cf);
		printf("\n--------------------");
		readFieldsInfo(&cf);
		printf("\n--------------------");
		readMethodsCount(&cf);
		printf("\n--------------------");
		readMethodsInfo(&cf);
		printf("\n--------------------");
		readAttributesCount(&cf);
		printf("\n--------------------");
		cf.attributes = malloc(cf.attributes_count *  sizeof(attribute_info));
		for(i = 0; i< cf.attributes_count; i++){
			readAttributesInfo(&cf, &(cf.attributes[i]));
		}
		printf("\n--------------------\nFim do .class");


	} else {
		printf("O magic number esta incorreto.");
	}


	return cf;
}
