#ifndef SCANNER_H
#define SCANNER_H

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

typedef enum {
SPECIALCHAR,
IDENTIFIER,
NUMBER,
RESERVEDWORD
} token_type;

typedef struct token{
	struct token* next;
	char* value;
	token_type type;
} token;

token *head;

void tokenize(FILE *fp);
char* type_name(token_type t);

#endif/*SCANNER_H*/
