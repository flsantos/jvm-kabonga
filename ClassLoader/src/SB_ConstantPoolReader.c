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


/*
 * Definicao da estrutura de um Classfile
 * As informacoes nao utilizadas estao comentadas
 */
typedef struct classfile {
	u4 				magic;
	u2 				minor_version;
	u2 				major_version;
	u2 				constant_pool_count;
	cp_info 		*constant_pool /*[constant_pool_count-1]*/;
/*	u2 				access_flags;
	u2 				this_class;
	u2 				super_class;
	u2 				interfaces_count;
	u2 				interfaces [struct classfile.interfaces_count];
	u2 				fields_count;
	field_info 		fields [struct classfile.fields_count];
	u2 				methods_count;
	method_info 	methods [struct classfile.methods_count];
	u2 				attributes_count;
	attribute_info 	attributes [struct classfile.attributes_count];*/
} ClassFile;

FILE *fp;

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

void readConstantPool(ClassFile *cf){
	int i = 0, j = 0;

	for (i = 0; i<((*cf).constant_pool_count-1); i++) {
				cp_info cp = (*cf).constant_pool[i];
				cp.tag = u1Read(fp);

				printf("\n\ntag : %d (%s)", cp.tag, getTag(cp.tag));

				switch(cp.tag) {
					case CONSTANT_Class:
						cp.u.Class.name_index = u2Read(fp);
						printf("\nname_index : %d", cp.u.Class.name_index);
						break;
					case CONSTANT_Fieldred:
						cp.u.Fieldref.class_index = u2Read(fp);
						cp.u.Fieldref.name_and_type_index = u2Read(fp);
						printf("\nclass_index : %d", cp.u.Fieldref.class_index);
						printf("\nname_and_type_index : %d", cp.u.Fieldref.name_and_type_index);
						break;
					case CONSTANT_NameAndType:
						cp.u.NameAndType.name_index = u2Read(fp);
						cp.u.NameAndType.descriptor_index = u2Read(fp);
						printf("\nname_index : %d", cp.u.NameAndType.name_index);
						printf("\ndescriptor_index : %d", cp.u.NameAndType.descriptor_index);
						break;
					case CONSTANT_Utf8: /*Nesse caso o programa aloca memoria para a string e concatena um \0 no fim da string*/
						cp.u.Utf8.length = u2Read(fp);
						cp.u.Utf8.bytes = malloc(sizeof(u1) * cp.u.Utf8.length + 1);
						for (j=0; j<cp.u.Utf8.length; j++) {
							cp.u.Utf8.bytes[j] = u1Read(fp);
						}
						cp.u.Utf8.bytes[j] = '\0';
						printf("\nlength : %d", cp.u.Utf8.length);
						printf("\nbytes : %s", cp.u.Utf8.bytes);
						break;
					case CONSTANT_Methodref:
						cp.u.Methodref.class_index = u2Read(fp);
						cp.u.Methodref.name_and_type_index = u2Read(fp);
						printf("\nclass_index : %d", cp.u.Methodref.class_index);
						printf("\nname_and_type_index : %d", cp.u.Methodref.name_and_type_index);
						break;
					case CONSTANT_InterfaceMethodref:
						cp.u.InterfaceMethodref.class_index = u2Read(fp);
						cp.u.InterfaceMethodref.name_and_type_index = u2Read(fp);
						printf("\nclass_index : %d", cp.u.InterfaceMethodref.class_index);
						printf("\nname_and_type_index : %d", cp.u.InterfaceMethodref.name_and_type_index);
						break;
					case CONSTANT_String:
						cp.u.String.string_index= u2Read(fp);
						printf("\nstring_index : %d", cp.u.String.string_index);
						break;
					case CONSTANT_Integer:
						cp.u.Integer.bytes = u4Read(fp);
						printf("\nbytes : %d", cp.u.Integer.bytes);
						break;
					case CONSTANT_Float:
						cp.u.Float.bytes.uf.bits = u4Read(fp);
						printf("\nbytes : %f", cp.u.Float.bytes.uf.valor);
						break;
					case CONSTANT_Long:
						cp.u.Long.high_bytes = u4Read(fp);
						cp.u.Long.low_bytes = u4Read(fp);
						printf("\nhigh_bytes : %d", cp.u.Long.high_bytes);
						printf("\nllow_bytes : %d", cp.u.Long.low_bytes);
						break;
					case CONSTANT_Double:
						cp.u.Double.bytes.ud.bits= u8Read(fp);
						printf("\nbytes : %f", cp.u.Double.bytes.ud.valor);
						break;
					default:
						break;
				}
			}
}


/*
 * Funcao principal do sistema.
 *
 * Essa funcao abre o arquivo .class e vai lendo seu conteudo.
 * Le as informacoes iniciais (magic, minor_version, major_version, constant_pool_count) e depois le a ConstantPool

 */
int main(int argc, char *argv[]) {
	ClassFile cf;

	if (argc == 2) {
		fp = fopen(argv[1], "rb");

		cf.magic = u4Read(fp);
		cf.minor_version = u2Read(fp);
		cf.major_version = u2Read(fp);
		cf.constant_pool_count = u2Read(fp);


		if (cf.magic == 0xCAFEBABE) printf("\nmagic_number : 0xCAFEBABE");
		printf("\nminor_version : %d", cf.minor_version);
		printf("\nmajor_version : %d", cf.major_version);
		printf("\nconstant_pool_count : %d", cf.constant_pool_count);


		/* Alocacao de memoria para a constant_pool */
		cf.constant_pool = malloc((cf.constant_pool_count-1) * sizeof(cp_info));

		/* Esse loop itera uma vez para cada elemento da constant_pool.
		 * Ele descobre a tag e faz um switch case para identificar o que deve ser lido do arquivo e mostrado na tela
		 */
		readConstantPool(&cf);
	}
	else {
		printf("O arquivo .class a ser lido deve ser passado como parametro.");
	}



	return 0;
}
