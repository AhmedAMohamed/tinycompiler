#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENDOFFILE	rc == EOF 
#define INCOMMENT	rc=='{'
#define INID		(rc>='A'&&rc<='Z')||(rc>='a'&&rc<='z')
#define INNUM		rc>='0'&&rc<='9'
#define SPACE		rc==' '
#define INSPECIAL	rc=='+'||rc=='-'||rc=='*'||rc=='/'|| \
					rc=='='||rc=='('||rc==')'||rc=='<'|| \
					rc==';'||rc==':'



const char* RESERVEDWORDS[]={
	"if",
	"then",
	"else",
	"end",
	"repeat",
	"until",
	"read",
	"write",
	"int"
};

typedef enum {
SPECIALCHAR,
IDENTIFIER,
NUMBER,
RESERVEDWORD
} token_type;

typedef struct token{
	token* next;
	char* value;
	token_type type;
} token;

void tokenize(FILE *fp,token* &t);
char* type_name(token_type t);
