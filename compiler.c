#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <ctype.h>
#include "token.h"
#include "stack.h"
int boolFuct = 0;
int count1 = 0; 

 void compiler (token *the_token, FILE *file_asm, Stack S1, Stack S2, int *counter)  { 
    int num, cnum, hconst, pos;
    char lab1[100], lab2[100], lab3[100]; 
    int temp, temp1;    


   switch(the_token->type)  {
      case (DEFUN) : 
      boolFuct = 1;

     // print .falign
      //call read token and read it
      //name oif functino
      //prolouge 
      break;
      case (IDENT) :
      if (boolFuct) {
      	fprintf(file_asm,".FALIGN\n");
      	fprintf(file_asm,"%s\n", the_token -> str);
      	fprintf(file_asm,"\tADD R6 R6 #-3\n");
      	fprintf(file_asm,"\tSTR R7 R6 #1\n");
      	fprintf(file_asm,"\tSTR R5 R6 #0\n");
      	fprintf(file_asm,"\tADD R5 R6 #0\n");
      	boolFuct = 0;
      }
      else { 
      	fprintf(file_asm,"\tJSR %s\n",the_token -> str);

      }

       break;
      case (RETURN) :  
      	fprintf(file_asm,"\tLDR R0 R6 #0\n");
      	fprintf(file_asm,"\tSTR R0 R5 #2\n");
      	fprintf(file_asm,"\tADD R6 R5 #0\n");
      	fprintf(file_asm,"\tLDR R5 R6 #0\n");
		   fprintf(file_asm,"\tLDR R7 R6 #1\n");
      	fprintf(file_asm,"\tADD R6 R6 #2\n");
      	fprintf(file_asm, "\tRET\n");             //epilouge
         break;
      case (PLUS)  :
         fprintf(file_asm,"\tLDR R1 R6 #0\n");
         fprintf(file_asm,"\tLDR R2 R6 #1\n"); 
         fprintf(file_asm,"\tADD R1 R1 R2\n");
         fprintf(file_asm,"\tADD R6 R6 #1\n");
         fprintf(file_asm,"\tSTR R1 R6 #0\n");
         break; 
      case (MINUS)  :
         fprintf(file_asm,"\tLDR R1 R6 #0\n");
         fprintf(file_asm,"\tLDR R2 R6 #1\n"); 
         fprintf(file_asm,"\tSUB R1 R1 R2\n");
         fprintf(file_asm,"\tADD R6 R6 #1\n");
         fprintf(file_asm,"\tSTR R1 R6 #0\n"); 
         break;      
      case (MUL) : 
         fprintf(file_asm,"\tLDR R1 R6 #0\n");
         fprintf(file_asm,"\tLDR R2 R6 #1\n"); 
         fprintf(file_asm,"\tMUL R1 R1 R2\n");
         fprintf(file_asm,"\tADD R6 R6 #1\n");
         fprintf(file_asm,"\tSTR R1 R6 #0\n"); 
         break;      
      case (DIV) :
         fprintf(file_asm,"\tLDR R1 R6 #0\n");
         fprintf(file_asm,"\tLDR R2 R6 #1\n"); 
         fprintf(file_asm,"\tDIV R1 R1 R2\n");
         fprintf(file_asm,"\tADD R6 R6 #1\n");
         fprintf(file_asm,"\tSTR R1 R6 #0\n");
         break;      
      case (MOD) :
         fprintf(file_asm,"\tLDR R1 R6 #0\n");
         fprintf(file_asm,"\tLDR R2 R6 #1\n"); 
         fprintf(file_asm,"\tMOD R1 R1 R2\n");
         fprintf(file_asm,"\tADD R6 R6 #1\n");
         fprintf(file_asm,"\tSTR R1 R6 #0\n"); 
         break;
      case (AND) :
         fprintf(file_asm,"\tLDR R1 R6 #0\n");
         fprintf(file_asm,"\tLDR R2 R6 #1\n"); 
         fprintf(file_asm,"\tAND R1 R1 R2\n");
         fprintf(file_asm,"\tADD R6 R6 #1\n");
         fprintf(file_asm,"\tSTR R1 R6 #0\n"); 
         break;      
      case (OR) :
         fprintf(file_asm,"\tLDR R1 R6 #0\n");
         fprintf(file_asm,"\tLDR R2 R6 #1\n"); 
         fprintf(file_asm,"\tOR R1 R1 R2\n");
         fprintf(file_asm,"\tADD R6 R6 #1\n");
         fprintf(file_asm,"\tSTR R1 R6 #0\n"); 
         break;      
      case (NOT) :
         fprintf(file_asm,"\tLDR R1 R6 #0\n");
         fprintf(file_asm,"\tNOT R1 R1\n");
         fprintf(file_asm,"\tADD R6 R6 #1\n");
         fprintf(file_asm,"\tSTR R1 R6 #0\n"); 
         break; 

      case (LT) :
         sprintf(lab1, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab2, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab3, "%s%d", "SKIPEND", *counter);
         *counter = *counter + 1;

         fprintf(file_asm, "\tLDR R1 R6 #0\n");
         fprintf(file_asm, "\tLDR R2 R6 #1\n");
         fprintf(file_asm, "\tCMP R1 R2\n");
         fprintf(file_asm, "\tBRn %s\n", lab1);
         fprintf(file_asm, "\tBRzp %s\n",lab2); 

         fprintf(file_asm, "\t%s\n", lab1);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #1\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\tBRnzp %s\n", lab3);

         fprintf(file_asm, "\t%s\n", lab2);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #0\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\t%s\n", lab3);
         break;      
      case (LE) :
         sprintf(lab1, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab2, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab3, "%s%d", "SKIPEND", *counter);
         *counter = *counter + 1;

         fprintf(file_asm, "\tLDR R1 R6 #0\n");
         fprintf(file_asm, "\tLDR R2 R6 #1\n");
         fprintf(file_asm, "\tCMP R1 R2\n");
         fprintf(file_asm, "\tBRnz %s\n", lab1);
         fprintf(file_asm, "\tBRp %s\n",lab2); 

         fprintf(file_asm, "\t%s\n", lab1);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #1\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\tBRnzp %s\n", lab3);

         fprintf(file_asm, "\t%s\n", lab2);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #0\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\t%s\n", lab3);
         break;         
      case (EQ) :	
      	 sprintf(lab1, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab2, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab3, "%s%d", "SKIPEND", *counter);
         *counter = *counter + 1;

         fprintf(file_asm, "\tLDR R1 R6 #0\n");
         fprintf(file_asm, "\tLDR R2 R6 #1\n");
         fprintf(file_asm, "\tCMP R1 R2\n");
         fprintf(file_asm, "\tBRz %s\n", lab1);
         fprintf(file_asm, "\tBRnp %s\n",lab2); 

         fprintf(file_asm, "\t%s\n", lab1);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #1\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\tBRnzp %s\n", lab3);

         fprintf(file_asm, "\t%s\n", lab2);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #0\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\t%s\n", lab3);
         break;      
      case (GE) :
      	 sprintf(lab1, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab2, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab3, "%s%d", "SKIPEND", *counter);
         *counter = *counter + 1;

         fprintf(file_asm, "\tLDR R1 R6 #0\n");
         fprintf(file_asm, "\tLDR R2 R6 #1\n");
         fprintf(file_asm, "\tCMP R1 R2\n");
         fprintf(file_asm, "\tBRzp %s\n", lab1);
         fprintf(file_asm, "\tBRn %s\n",lab2); 

         fprintf(file_asm, "\t%s\n", lab1);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #1\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\tBRnzp %s\n", lab3);

         fprintf(file_asm, "\t%s\n", lab2);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #0\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\t%s\n", lab3);
         break;       
      case (GT) : 
      	 sprintf(lab1, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab2, "%s%d", the_token -> str, *counter);
         *counter = *counter + 1;
         sprintf(lab3, "%s%d", "SKIPEND", *counter);
         *counter = *counter + 1;

         fprintf(file_asm, "\tLDR R1 R6 #0\n");
         fprintf(file_asm, "\tLDR R2 R6 #1\n");
         fprintf(file_asm, "\tCMP R1 R2\n");
         fprintf(file_asm, "\tBRp %s\n", lab1);
         fprintf(file_asm, "\tBRnz %s\n",lab2); 

         fprintf(file_asm, "\t%s\n", lab1);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #1\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\tBRnzp %s\n", lab3);

         fprintf(file_asm, "\t%s\n", lab2);
         fprintf(file_asm, "\tADD R6 R6 #1\n");
         fprintf(file_asm, "\tCONST R0 #0\n");
         fprintf(file_asm, "\tSTR R0 R6 #0\n");
         fprintf(file_asm, "\t%s\n", lab3);
         break;
      
      case (IF) :
      	  fprintf(file_asm, "\tADD R6 R6 #1\n");
      	  fprintf(file_asm, "\tLDR R0 R6 #-1\n");
      	  fprintf(file_asm, "\tBRz ELSE%d\n", count1);
      	  push(S1, count1);
      	  push(S2, count1);
           /*
            printf("top val of if stack when IF is called =");
            print_stack(S1); 
            printf("top val of elseif stack when IF is called =");
            print_stack(S2); 
            */
      	  count1++; 
         break;
      
      case (ELSE) :           
      	  temp = pop(S2);
      	  fprintf(file_asm, "\tJMP ENDIF%d\n", temp);
      	  fprintf(file_asm, "\tELSE%d\n", temp);
           /*
            printf("top val of if stack when ELSE is called =");
            print_stack(S1); 
            printf("top val of elseif stack when ELSE is called =");
            print_stack(S2);  
            */
         break;
      
      case (ENDIF) : 
         if (S2-> top  == NULL) {
           // print_stack(S1); 
            fprintf(file_asm, "\tENDIF%d\n",pop(S1));            
         } else {
            /*
            printf("top val of if stack when ELSE is called =");
            print_stack(S1); 
            printf("top val of elseif stack when ELSE is called =");
            print_stack(S2);  
           */
      	 temp = S1 -> top -> num;
      	 temp1 =  S2 -> top -> num;
      //  push(S1,temp);
      //	 push(S2,temp);
      	 if (temp != temp1) {      	 	
      	 	fprintf(file_asm,"\tENDIF%d\n",pop(S1));
      	 } else {
      	 	temp = pop(S1);
      	 	temp1 = pop(S2);
      	 	fprintf(file_asm,"\tENDIF%d\n", temp);
      	 	fprintf(file_asm,"\tELSE%d\n", temp1);
      	 }
      }
          break;
      
      case (DROP) :
         fprintf(file_asm,"\tADD R6 R6 #1\n");
         break;
      
      case (DUP) :
         fprintf(file_asm,"\tLDR R1 R6 #0\n");
         fprintf(file_asm,"\tADD R6 R6 #-1\n");
         fprintf(file_asm,"\tSTR R1 R6 #0\n");  
         break;

      case (SWAP) :
         fprintf(file_asm, "\tLDR R1 R6 #0\n");
         fprintf(file_asm, "\tLDR R2 R6 #1\n");
         fprintf(file_asm, "\tSTR R2 R6 #0\n");
         fprintf(file_asm, "\tSTR R1 R6 #1\n");
         break; 

      
      case (ROT) :
         fprintf(file_asm, "\tLDR R1 R6 #0\n");
         fprintf(file_asm, "\tLDR R2 R6 #1\n");
         fprintf(file_asm, "\tLDR R3 R6 #2\n");
         fprintf(file_asm, "\tSTR R1 R6 #1\n");
         fprintf(file_asm, "\tSTR R2 R6 #2\n");
         fprintf(file_asm, "\tSTR R3 R6 #0\n");
         break;
        
        
      
      case (ARG) :
         pos = ((the_token -> arg_no) + 2);
         fprintf(file_asm, "\tLDR R1 R5 #%d\n", pos); 
         fprintf(file_asm, "\tADD R6 R6 #-1\n"); 
         fprintf(file_asm, "\tSTR R1 R6 #0\n");
         break;

      
      case (LITERAL) :
         num = (the_token -> literal_value);
         cnum  = (0x00FF) & (num);
         hconst = (0xFF00) & (num);
         hconst = hconst >> 8;

         fprintf(file_asm, "\tCONST R4 #%d\n", cnum);
         fprintf(file_asm, "\tHICONST R4 #%d\n", hconst);
         fprintf(file_asm, "\tADD R6 R6 #-1\n"); 
         fprintf(file_asm, "\tSTR R4 R6 #0\n");
         break;

      
      case (BROKEN_TOKEN) : 
     	free(S1);
     	free(S2);
      free(the_token); 
      exit(1);
      break;
      
      default : printf("Invalid Type\n"); 

   }
   
}

