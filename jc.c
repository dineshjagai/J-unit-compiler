#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <ctype.h>
#include "token.h"
#include "stack.h"
#include "compiler.h" 


int main (int argc, char *argv[]) {
   FILE  *file_asm;
   FILE *fileN;
   token *token1; 
   char jName[250];
   int i;

   token1 =  (token*) malloc(sizeof(token));  
   Stack S1 = init_stack();
   Stack S2  = init_stack();  
   int counter = 0; 

   fileN = fopen(argv[1], "r");   

   strcpy(jName, argv[1]);
   int length = (strlen(jName) + 3);
   char asmName[length]; 
   for (i = 0; i < length; i++) {
      if (jName[i] == '.') {
         asmName[i] = jName[i];
         asmName[i + 1] = 'a';
         asmName[i + 2] = 's';
         asmName[i + 3] = 'm';
         asmName[i + 4] = 0;
         break;
      }
    else {

    asmName[i] = jName[i];
    }
   }  


    file_asm = fopen(asmName, "w");

   if (fileN == NULL) {
   printf ("Could not open file \n");
   	}  else  {
   fprintf(file_asm,".CODE\n");     
   while ((read_token(token1, fileN) != -1)) { 	
        compiler (token1, file_asm, S1, S2, &counter); 

   }
}







fclose(fileN);
fclose(file_asm);
free(token1);
return 0;
}

