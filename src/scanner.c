#include "scanner.h"

void LinkedList_insert(token * temp);
short is_reserved_word(const char* word);

token *next_token;

token * get_next_token(){
	token * temp = next_token;
	next_token = next_token->next;
	return temp;
}

void set_next_token(token * t){
	next_token = t;
}

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

token_type get_special_char(const char* ch){
	if(!strcmp(ch,"=")) return ASSIG_OP;
	if(!strcmp(ch,";")) return SPECIALCHAR;
	return IDENTIFIER;
}

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
			temp->type=get_special_char(temp->value);
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
	token *temp =(token*)malloc(sizeof(token));
	temp->value = "eof";
	temp->type= _EOF;
	temp->next=NULL;
	LinkedList_insert(temp);
	next_token = head;
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
	switch(t){
		case SPECIALCHAR:	return "special character";
		case IDENTIFIER:	return "Identifier";
		case ASSIG_OP:		return "Assign Operat";
		case NUMBER:		return "Number";
		case RESERVEDWORD:	return "Reserved word";
		default:		return "Unknown";
	}
}
