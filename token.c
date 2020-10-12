#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <ctype.h>


#define MAX_TOKEN_LENGTH 250
#define MAX_LENGTH_LINE 5000


int isValid (char strg []) {
	int i;
	int valid =  1;
	if (isalpha(strg[0]) == 0) {
		valid = 0; 
	}
	for (i = 1; strg[i] != '\0'; i++) {
		if ((isalpha(strg[i]) == 0) && (isdigit(strg[i]) == 0) && (strg[i] != '_')) {
			valid = 0;  
		}
	} 
	return valid; 
}

int read_token (token *theToken, FILE *theFile) {
	char st[MAX_TOKEN_LENGTH];
	int argNum;
	int literalNum;
	char temp[MAX_LENGTH_LINE];
    
	//removeSemicolons(theFile);
	//rewind(theFile);

	if (fscanf(theFile,"%s", st) == EOF) {
		return -1;
	} 
		else if (st[0] == ';') {
		fgets(temp, MAX_LENGTH_LINE, theFile);
		return read_token(theToken, theFile);
	}	else if (strncmp(st,"defun", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = DEFUN;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (strncmp(st,"return", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = RETURN;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (strncmp(st, "+", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = PLUS;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st, "-", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type =  MINUS;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (strncmp(st, "*", MAX_TOKEN_LENGTH) == 0) {
		theToken -> type = MUL;
		strcpy((theToken -> str), st);  
		return 0;
	}       else if (strncmp(st, "/", MAX_TOKEN_LENGTH) == 0) {
		theToken -> type = DIV;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (strncmp(st, "%", MAX_TOKEN_LENGTH) == 0) {
		theToken -> type = MOD;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st, "and", MAX_TOKEN_LENGTH) == 0) {
		theToken -> type = AND;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (strncmp(st ,"or", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = OR;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st ,"not", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = NOT;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st ,"lt", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = LT;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (strncmp(st ,"le", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = LE;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (strncmp(st ,"eq", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = EQ;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st ,"ge", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = GE;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (strncmp(st ,"gt", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = GT;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st ,"if", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = IF;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (strncmp(st ,"else", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = ELSE;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st ,"endif", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = ENDIF;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st ,"drop", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = DROP;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st ,"dup", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = DUP;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st ,"swap", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = SWAP;
		strcpy((theToken -> str), st);  
		return 0;
	}	else if (strncmp(st ,"rot", MAX_TOKEN_LENGTH) == 0) { 
		theToken -> type = ROT;
		strcpy((theToken -> str), st); 
		return 0;
	}	else if (sscanf(st,"arg%d", &argNum) == 1) {
		if ((argNum >= 1) && (argNum <= 20)) {
			theToken -> type = ARG;
			theToken -> arg_no = argNum;
			strcpy((theToken -> str), st); 	
			return 0;
		} else { 
			theToken -> type = BROKEN_TOKEN;
			strcpy((theToken -> str), st); 		
			return 0;
		}
	}	else if (sscanf(st,"0x%X", &literalNum) == 1) {
		theToken -> type = LITERAL;
		theToken -> literal_value = literalNum;
		strcpy((theToken -> str), st); 		
		return 0;
	}	else if (sscanf(st,"%d", &literalNum) == 1) {
		theToken -> type = LITERAL;
		theToken -> literal_value = literalNum;
		strcpy((theToken -> str), st); 		
		return 0;
	}	else if  (isValid(st)) {
		theToken -> type = IDENT;
		strcpy((theToken -> str), st); 		
		return 0;
	}	else {
		theToken -> type = BROKEN_TOKEN;
		strcpy((theToken -> str), st); 		
		return 2;
	}
}

// Extra functions which you may wish to define and use , or not

	const char *token_type_to_string (int type) {
		char *a = malloc(sizeof(char) * 250);
		switch (type) {
			case (0) : 
			strcat(a, "DEFUN");
			case (1) : 
			strcat(a, "IDENT");
			case (2) : 
			strcat(a, "RETURN");	
			case (3) : 
			strcat(a, "PLUS");
			case (4) : 
			strcat(a, "MINUS");
			case (5) : 
			strcat(a, "MUL");
			case (6) :
			strcat(a, "DIV");
			case (7) :
			strcat(a, "MOD");
			case (8) :
			strcat(a, "AND");
			case (9) :
			strcat(a, "OR");
			case (10) :
			strcat(a, "NOT");
			case (11) : 
			strcat(a, "LT");
			case (12) :
			strcat(a, "LE");
			case (13) : 
			strcat(a, "EQ");
			case (14) :
			strcat(a, "GE");
			case (15) : 
			strcat(a, "GT");
			case (16) : 
			strcat(a, "IF");
			case (17) : 
			strcat(a, "ELSE");
			case (18) : 
			strcat(a, "ENDIF");
			case (19) : 
			strcat(a, "DROP");
			case (20) : 
			strcat(a, "DUP");
			case (21) : 
			strcat(a, "SWAP");
			case (22) : 
			strcat(a, "ROT");
			case (23) : 
			strcat(a, "ARG");
			case (24) : 
			strcat(a, "LITERAL");
			case (25) : 
			strcat(a, "BROKEN_TOKEN");
			default : 
			printf("Invalid token type input\n");

		}
		free(a); 
		return  a; 
	}


	void print_token (token *theToken) {
		if (((theToken -> type) != 25)) {		
		printf("type: %d\n", (theToken -> type)); 
		printf("Value of Token = %s\n", (theToken-> str));
	  }
	}






