/*
 * Universidade de Brasília
 * Instituto de Ciências Exatas
 * Departamento de Ciência da Computação
 * Software Básico
 *
 * Nome: Fernando Leandro dos Santos
 * Matrícula: 09/0006038
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Definicao das constantes */
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

void readAttributesInfo(ClassFile *cf, attribute_info *ai);

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
char *getTag(int8_t tag) {
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
	printf("\n--------------------");
	printf("\nthis_class: %d", cf->this_class);
	printf("\n%s", cf->constant_pool[cf->constant_pool[cf->this_class - 1].u.Class.name_index - 1].u.Utf8.bytes);
	printf("\n--------------------");
}

/*
 * Ler indice do constant_pool que aponta para nome
 * da classe pai do arquivo .class
 */
void readSuperClass(ClassFile *cf) {
	cf->super_class = u2Read();
	printf("\nsuper_class: %d", cf->super_class);
	printf("\n%s", cf->constant_pool[cf->constant_pool[cf->super_class - 1].u.Class.name_index - 1].u.Utf8.bytes);
	printf("\n--------------------");
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
}

void readAttributeCode(ClassFile *cf, attribute_info *ai) {
	int i;
	ai->u.Code.max_stack = u2Read();
	ai->u.Code.max_locals = u2Read();
	ai->u.Code.code_length = u4Read();
	ai->u.Code.code = malloc(ai->u.Code.code_length * sizeof(u1));
	for (i = 0; i < ai->u.Code.code_length; i++) {
		ai->u.Code.code[i] = u1Read();
	}
	ai->u.Code.exception_table_length = u2Read();
	ai->u.Code.exception_table = malloc(ai->u.Code.exception_table_length * sizeof(exception_table));
	for (i = 0; i < ai->u.Code.exception_table_length; i++) {
		ai->u.Code.exception_table[i].start_pc = u2Read();
		ai->u.Code.exception_table[i].end_pc = u2Read();
		ai->u.Code.exception_table[i].handler_pc = u2Read();
		ai->u.Code.exception_table[i].catch_type = u2Read();
	}
	ai->u.Code.attributes_count = u2Read();
	ai->u.Code.attributes = malloc(ai->u.Code.attributes_count * sizeof(attribute_info));
	for (i = 0; i < ai->u.Code.attributes_count; i++) {
		readAttributesInfo(cf, &(ai->u.Code.attributes[i]));
	}
}

void readAttributeExceptions(attribute_info *ai) {
	int i;

	ai->u.Exceptions.number_of_exceptions = u2Read();

	ai->u.Exceptions.exception_index_table = malloc(ai->u.Exceptions.number_of_exceptions * sizeof(u2));
	for (i = 0; i < ai->u.Exceptions.number_of_exceptions; i++) {
		ai->u.Exceptions.exception_index_table[i] = u2Read();
	}
}

void readAttributeInnerClasses(attribute_info *ai) {
	int i;
	ai->u.InnerClasses.number_of_classes = u2Read();
	ai->u.InnerClasses.classes = malloc(ai->u.InnerClasses.number_of_classes * sizeof(classes));
	for (i = 0; i < ai->u.InnerClasses.number_of_classes; i++) {
		ai->u.InnerClasses.classes[i].inner_class_info_index = u2Read();
		ai->u.InnerClasses.classes[i].outer_class_info_index = u2Read();
		ai->u.InnerClasses.classes[i].inner_name_index = u2Read();
		ai->u.InnerClasses.classes[i].inner_class_access_flags = u2Read();
	}
}

void readAttributeSynthetic(attribute_info *ai) {
	ai->u.Synthetic.attribute_name_index = u2Read();
	ai->u.Synthetic.attribute_length = u4Read();
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
	printf("\nNome do Atributo: %s", str);
	if (strcmp(str, "ConstantValue")) {
		readAttributeConstantValue(ai);
	} else if (strcmp(str, "Code")) {
		readAttributeCode(cf, ai);
	} else if (strcmp(str, "Exceptions")) {
		readAttributeExceptions(ai);
	} else if (strcmp(str, "InnerClasses")) {
		readAttributeInnerClasses(ai);
	} else if (strcmp(str, "Synthetic")) {
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
		for (j = 0; j < cf->fields[i].attributes_count; j++) {
			readAttributesInfo(cf, &(cf->fields[i].attributes[j]));
			/*			cf->fields[i].attributes[j].attribute_name_index = u2Read();
			 cf->fields[i].attributes[j].attribute_length = u4Read();
			 cf->fields[i].attributes[j].info = malloc((cf->fields[i].attributes[j].attribute_length) * sizeof(attribute_info));
			 for(k = 0; k < cf->fields[i].attributes[j].attribute_length; k++){
			 cf->fields[i].attributes[j].info[k] = u1Read();
			 }*/
		}
		printf("\n\nfield.access_flags: 0x%04X", cf->fields[i].access_flags);
		printf("\nfield.name_index: %d", cf->fields[i].name_index);
		printf("\nfield.descriptor_index: %d", cf->fields[i].descriptor_index);
		printf("\nfield.attributes_count: %d", cf->fields[i].attributes_count);
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
		for (j = 0; j < cf->methods[i].attributes_count; j++) {
			readAttributesInfo(cf, &(cf->fields[i].attributes[j]));
		}
		/*for(j = 0; j < cf->methods[i].attributes_count; j++){
		 cf->methods[i].attributes[j].attribute_name_index = u2Read();
		 cf->methods[i].attributes[j].attribute_length = u4Read();
		 cf->methods[i].attributes[j].info = malloc((cf->methods[i].attributes[j].attribute_length) * sizeof(attribute_info));
		 for(k = 0; k < cf->methods[i].attributes[j].attribute_length; k++){
		 cf->methods[i].attributes[j].info[k] = u1Read();
		 }
		 }*/
		printf("\n\nfield.access_flags: 0x%04X", cf->methods[i].access_flags);
		printf("\nfield.name_index: %d", cf->methods[i].name_index);
		printf("\nfield.descriptor_index: %d", cf->methods[i].descriptor_index);
		printf("\nfield.attributes_count: %d", cf->methods[i].attributes_count);
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
 * Funcao principal do sistema.
 *
 * Essa funcao abre o arquivo .class e vai lendo seu conteudo.
 * Le as informacoes iniciais (magic, minor_version, major_version, constant_pool_count) e depois le a ConstantPool

 */
int main(int argc, char *argv[]) {
	ClassFile cf;
	int i;

	if (argc == 2) {
		fp = fopen(argv[1], "rb");

		cf.magic = u4Read();
		if (cf.magic == 0xCAFEBABE) {

			cf.minor_version = u2Read();
			cf.major_version = u2Read();
			cf.constant_pool_count = u2Read();
			printf("\nmagic_number : 0xCAFEBABE");
			printf("\nminor_version : %d", cf.minor_version);
			printf("\nmajor_version : %d", cf.major_version);
			printf("\nconstant_pool_count : %d", cf.constant_pool_count);

			/* Alocacao de memoria para a constant_pool */
			cf.constant_pool = malloc((cf.constant_pool_count - 1) * sizeof(cp_info));

			readConstantPool(&cf);
			readAccessFlags(&cf);
			readThisClass(&cf);
			readSuperClass(&cf);
			readInterfaceCount(&cf);
			readInterfaces(&cf);
			readFieldsCount(&cf);
			readFieldsInfo(&cf);
			readMethodsCount(&cf);
			readMethodsInfo(&cf);
			//readAttributesCount(&cf);
			//cf.attributes = malloc(cf.attributes_count *  sizeof(attribute_info));
			//for(i = 0; i< cf.attributes_count; i++){
			//	readAttributesInfo(&cf, &(cf.attributes[i]));
			//}

		} else {
			printf("O magic number esta incorreto. Nao foi dessa vez que voce conseguiu bugar o meu programa.");
		}
	} else {
		printf("O arquivo .class a ser lido deve ser passado como parametro.");
	}

	return 0;
}
