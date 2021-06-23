#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char input[1024];
    printf("Welcome to the number to ASCII art generation program!\n");
    printf("Enter a number that you want to convert to an ASCII art: <no input, just hit Enter>\n");
    fgets(input, 1024, stdin);
    if(input[0] == '\n') {
        perror("Input is empty!");
    }
    printf("Please enter a number: ");
   
    while (scanf("%[^\n]%*c", input) == 1){
      
        int numdigit = strlen(input);
        int error = 0;
        
        for (size_t i = 0; i < strlen(input); i++){
            if(input[i] == ' ') {
                printf("\"%s\" contains more than one input.\n", input);
                error++;
                break;
                
            }else if(input[i] == '\n'){
                perror("Input is empty!");
                error++;
                break;
                
            }else if(isdigit(input[i]) == 0){
                printf("\"%s\" is not a number.\n", input);
                error++;
                break;
            }
            
        }
       if (error == 0){
           printf("Input number is \"%s\". String length is %d.\n", input, numdigit);
           printf("ASCII art:\n");
           for (int i = 0; i < numdigit; i++){
               printf("+--------");
               
           }printf("+\n");
           
           char* zero[6];
           zero[0]=" _/_/_/ ";
           zero[1]="_/    _/";
           zero[2]="_/    _/";
           zero[3]="_/    _/";
           zero[4]="_/    _/";
           zero[5]=" _/_/_/ ";
           
           char* one[6];
           one[0]="   _/   ";
           one[1]=" _/_/   ";
           one[2]="   _/   ";
           one[3]="   _/   ";
           one[4]="   _/   ";
           one[5]=" _/_/_/ ";
           
           char* two[6];
           two[0]="  _/_/  ";
           two[1]=" _/  _/ ";
           two[2]="    _/  ";
           two[3]="   _/   ";
           two[4]="  _/    ";
           two[5]=" _/_/_/ ";
           
           char* three[6];
           three[0]="  _/_/  ";
           three[1]=" _/  _/ ";
           three[2]="    _/  ";
           three[3]="    _/  ";
           three[4]=" _/  _/ ";
           three[5]="  _/_/  ";
           
           char* four[6];
           four[0]="   _/_/ ";
           four[1]="  _/ _/ ";
           four[2]=" _/  _/ ";
           four[3]="_/_/_/_/";
           four[4]="    _/  ";
           four[5]="    _/  ";
           
           char* five[6];
           five[0]="_/_/_/_/";
           five[1]="_/      ";
           five[2]="_/_/_/_/";
           five[3]="      _/";
           five[4]="_/    _/";
           five[5]=" _/_/_/ ";
           
           char* six[6];
           six[0]="     _/ ";
           six[1]="    _/  ";
           six[2]="    _/  ";
           six[3]="  _/ _/ ";
           six[4]=" _/  _/ ";
           six[5]="  _/_/  ";
           
           char* seven[6];
           seven[0]=" _/_/_/ ";
           seven[1]="     _/ ";
           seven[2]="    _/  ";
           seven[3]="    _/  ";
           seven[4]="   _/   ";
           seven[5]="  _/    ";
           
           char* eight[6];
           eight[0]=" _/_/_/ ";
           eight[1]="_/    _/";
           eight[2]=" _/_/_/ ";
           eight[3]=" _/_/_/ ";
           eight[4]="_/    _/";
           eight[5]=" _/_/_/ ";
           
           char* nine[6];
           nine[0]="  _/_/  ";
           nine[1]=" _/  _/ ";
           nine[2]="  _/ _/ ";
           nine[3]="   _/   ";
           nine[4]="   _/   ";
           nine[5]="  _/    ";
           
           for (int i = 0; i < 6; i++){
               for (int j = 0; j < numdigit; j++){
                   if (input[j] == '0'){
                       printf(" %s",zero[i]);
                       continue;
                       
                   }else if (input[j] == '1'){
                       printf(" %s",one[i]);
                       continue;
                    
                   }else if (input[j] == '2'){
                       printf(" %s",two[i]);
                       continue;

                   }else if (input[j] == '3'){
                       printf(" %s",three[i]);
                       continue;
                
                   }else if (input[j] == '4'){
                       printf(" %s",four[i]);
                       continue;
                       
                   }else if (input[j] == '5'){
                       printf(" %s",five[i]);
                       continue;
                       
                   }else if (input[j] == '6'){
                       printf(" %s",six[i]);
                       continue;
                
                   }else if (input[j] == '7'){
                       printf(" %s",seven[i]);
                       continue;
                       
                   }else if (input[j] == '8'){
                       printf(" %s",eight[i]);
                       continue;
                       
                   }else if (input[j] == '9'){
                       printf(" %s",nine[i]);
                       continue;
                   }
                   
               }printf("\n");
               
           }for (int i = 0; i < numdigit; i++){
               printf("+--------");
               
           }printf("+\n");
           
       }
       
       //Print statement differs by input.
       if (error != 0){
           printf("Please enter a number: ");
       }else{
           printf("Enter a number that you want to convert to an ASCII art: ");
       }
           
        
            
        }
    
    

        
    printf("\nThank you for using the ASCII art program!");
    return 0;
}
