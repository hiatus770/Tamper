#include <stdio.h>  
#include <string.h> 
#define fileSize 1000
#define arraySize 100
int charAmt = 0; 
// Contains where the file to be ran is
char *fileDir; 
int tape[arraySize];
FILE* ptr; 
char fl[fileSize];
int ind = 0; 

/* Some useful ascii code values 

10 = \n 
97 = a 
65 = A 

*/ 

void main(int argc, char *argv[] )  {  

    printf("Amt of arguments: %d\n", argc); 
    printf("File directory: %s\n", argv[1]);

    fileDir = argv[1];  
    ptr = fopen(fileDir, "r"); 

    // Place the file contents into the fl string, fl stands for file contents --> fl 
    int i = 0; 
    while(fscanf(ptr, "%c", &fl[i]) == 1){
        i++;
        charAmt++; 
    }

    // This loops through all the characters in the .tam file 
    i = 0; 
    while(i < charAmt){
        //printf("%c", fl[i]);  
        if (fl[i] == '>'){
            if (ind+1 >= arraySize){
                ind = 0;
            } else {
                ind++; 
            } 
        }
        if (fl[i] == '<'){
            if (ind-1 < 0){
                ind = arraySize-1; 
            } else {
                ind--; 
            }
        }
        if (fl[i] == '+'){
            tape[ind]++; 
        }
        if (fl[i] == '-'){
            tape[ind]--; 
        }
        if (fl[i] == '.'){
            printf("%i", tape[ind]);
        }
        if (fl[i] == ','){
            printf("%c", tape[ind]); 
        }
        i++;
        printf("Index: %d\n", ind);
    }

    // char find = 'A'; 
    // for(int i = 0; i < 100; i++){
    //     char a = i;
    //     if (a == find){
    //         printf("Found %c at %d", find, a); 
    //     }
    // }

    
  


} 
