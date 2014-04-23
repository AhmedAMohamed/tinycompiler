#include "scanner.h"

void LinkedList_insert(token * temp);
short is_reserved_word(const char* word);


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

void tokenize(FILE *fp){

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
			ungetc (rc,fp);
			temp->value[i]='\0';
			LinkedList_insert(temp);
		}

		else if(INID){
			token *temp =(token*)malloc(sizeof(token));
			temp->value = (char*)malloc(15*sizeof(char));
			temp->next=NULL;
			int i=0;
			do {
				temp->value[i++]=rc;
				rc = fgetc(fp);
			} while(INID && i<14);
			ungetc (rc,fp);
			temp->value[i]='\0';
			temp->type= is_reserved_word(temp->value)?RESERVEDWORD:IDENTIFIER;
			LinkedList_insert(temp);
		}

		else if(INSPECIAL){
			token *temp =(token*)malloc(sizeof(token));
			temp->value = (char*)malloc(2*sizeof(char));
			temp->value[0] = rc;
			temp->value[1] = '\0';
			temp->type=SPECIALCHAR;
			temp->next=NULL;
			LinkedList_insert(temp);
		}

		else if(INCOMMENT){
			do {
				rc = fgetc(fp);
			} while(!(rc=='}'||ENDOFFILE));
			ungetc (rc,fp);
			continue;
		}

	}
}

void LinkedList_insert(token* temp){
	if(head==NULL){
		head = temp;
		return;
	}
	token *current = head;
	while(current->next!=NULL){
		current = current->next;
	}
	current->next = temp;
}

short is_reserved_word(const char* word){
	int i=0;
	for(;i<sizeof(RESERVEDWORDS)/sizeof(char*);i++){
		if(!strcmp(RESERVEDWORDS[i],word)){
			return 1;
		}
	}
	return 0;
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
