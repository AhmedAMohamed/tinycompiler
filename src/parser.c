#include "stdio.h"

#include "scanner.h"

short exp (){
	return 1;
}

short match(const char* ch){
	token* temp = get_next_token();
	if(!strcmp(temp->value,ch)){
		return 1;
	}
	set_next_token(temp);
	return 0;
}

short factor(){
	token* temp = get_next_token();
	printf("factor : %s\n",temp->value);
	if(temp->type==NUMBER){
		return 1;
	}
	set_next_token(temp);
	return 0;
}

short add_op(){
	token* temp = get_next_token();
	printf("add_op : %s\n",temp->value);
	if(temp->type==ADD_OP || temp->type==SUB_OP){
		return 1;
	}
	set_next_token(temp);
	return 0;
}

short assig_op(){
	token* temp = get_next_token();
	printf("assig_op : %s\n",temp->value);
	if(temp->type==ASSIG_OP){
		return 1;
	}
	set_next_token(temp);
	return 0;
}

short assign_stmt(){
	if(factor() && assig_op() && factor()) {
		return 1;
	}
	return 0;
}

short statement(){
	if(assign_stmt())
		return 1;
	return 0;
}

short stmt_sequence(){
	token* temp = get_next_token();
	printf("stmt_seq : %s\n",temp->value);
	if(match(";")){
		temp = get_next_token();
	}
	else{
		return 0;	
	}
	if(statement()){
		return 1;
	}
	set_next_token(temp);
	return 0;
}

short program(void){
	return stmt_sequence();
}

