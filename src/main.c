#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "parser.h"


int main(int argc,char* argv[]){
	if(argc!=2)
	{
		printf("Error in args\n");
		return 0;
	}
	FILE *fp = fopen(argv[1],"r");
	tokenize(fp);
	printf("\e[1;31m");
	printf("Name\tType\n");
	printf("---------------\n");
	printf("\e[0m");
	while(head!=NULL){
		printf("%s\t%s\n",head->value,type_name(head->type));
		head=head->next;
	}
	printf("scanner Terminated\n");
	printf("parser is starting\n");
	if(program()){
		printf("syntax ok\n");
		printf("Compilation finished\n");
	}else{
		printf("syntax error\n");
		printf("Compilation terminated\n");
	}
}
