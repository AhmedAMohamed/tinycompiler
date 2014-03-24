#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"


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