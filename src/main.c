#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"


int main(int argc,char* argv[]){
	if(argc!=2)
	{
		printf("Error in args\n");
		return 0;
	}
	FILE *fp = fopen(argv[1],"r");
	tokenize(fp);
	printf("\e[1;31m");
	printf("Name\tType\r\n");
	printf("---------------\r\n");
	printf("\e[0m");
	while(head!=NULL){
		printf("%s\t%s\r\n",head->value,type_name(head->type));
		head=head->next;
	}
}
