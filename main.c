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
	token* next;
	char* value;
	token_type type;
} token;


void LinkedList_insert(token* &t,token * temp);

void tokenize(FILE *fp,token* &t){

	char rc;

	while(1){
		rc = fgetc(fp);
		if(ENDOFFILE)
			break;

		else if(SPACE)
			continue;

		else if(INNUM){
			token *temp =(token*)malloc(sizeof(token));
			temp->value = (char*)malloc(10*sizeof(char));
			temp->type=NUMBER;
			temp->next=NULL;
			int i=0;
			do {
				temp->value[i++]=rc;
				rc = fgetc(fp);
			} while(INNUM && i<9);
			temp->value[i]='\0';
			LinkedList_insert(t,temp);
		}

		else if(INID){
			token *temp =(token*)malloc(sizeof(token));
			temp->value = (char*)malloc(15*sizeof(char));
			temp->type=IDENTIFIER;
			temp->next=NULL;
			int i=0;
			do {
				temp->value[i++]=rc;
				rc = fgetc(fp);
			} while(INID && i<14);
			temp->value[i]='\0';
			LinkedList_insert(t,temp);
		}

		else if(INSPECIAL){
			token *temp =(token*)malloc(sizeof(token));
			temp->value = (char*)malloc(2*sizeof(char));
			temp->value[0] = rc;
			temp->value[1] = '\0';
			temp->type=SPECIALCHAR;
			temp->next=NULL;
			LinkedList_insert(t,temp);
		}

		else if(INCOMMENT){
			do {
				rc = fgetc(fp);
			} while(rc!='}');
			continue;
		}

	}
}

void LinkedList_insert(token* &t,token * temp){
	if(t==NULL){
		t = temp;
		return;
	}
	token *current=t;
	while(current->next!=NULL){
		current = current->next;
	}
	current->next = temp;
}

char* type_name(token_type t){
	char *ret =(char*)malloc(20*sizeof(char));
	ret[19]='\0';
	switch(t){
		case SPECIALCHAR:	strcpy(ret,"special character"); break;
		case IDENTIFIER:	strcpy(ret,"Identifier"); break;
		case NUMBER:		strcpy(ret,"Number"); break;
		case RESERVEDWORD:	strcpy(ret,"Reserved word"); break;
	}
	return ret;
}

int main(){
	FILE *fp = fopen("mytest.tiny","r");
	token *t=NULL;
	tokenize(fp,t);
	printf("Name\tType\r\n");
	printf("---------------\r\n");
	while(t!=NULL){
		printf("%s\t%s\r\n",t->value,type_name(t->type));
		t=t->next;
	}
	char rc;
	scanf("%c",&rc);
}