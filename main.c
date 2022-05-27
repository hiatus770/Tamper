#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>
#define fileSize 1000
#define arraySize 10
int charAmt = 0; 
// Contains where the file to be ran is
char *fileDir; 
int tape[arraySize];
FILE* ptr; 
FILE* out;
char fl[fileSize];
int ind = 0; 

/* Some useful ascii code values 

10 = \n 
65 = A 
66 = B
67 = C
68 = D 
69 = E
70 = F
71 = G
72 = H
73 = I
74 = J
75 = K
76 = L
77 = M
78 = N
79 = O
80 = P
81 = Q
82 = R
83 = S
84 = T
85 = U
86 = V
87 = W
88 = X
89 = Y
90 = Z

*/ 


// Find the next closing bracket
int findClosingBracket(int start) {
    int i = start;
    int open = 0;
    while (fl[i] != '\0') {
        if (fl[i] == '['){
            open++;
        }
        if (fl[i] == ']') {
            open--;
        }
        if (open == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

// Find the next curly bracket
int findCurlyBracket(int start) {
    int i = start;
    int open = 0;
    while (fl[i] != '\0') {
        if (fl[i] == '{'){
            open++;
        }
        if (fl[i] == '}') {
            open--;
        }
        if (open == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

// Translates char into ascii code
char asciiTranslate(char find){
    for(int i = 0; i < 1000; i++){
        char a = i;
        if (a == find){
            return i;
        }
    }
}

void runCode(int i, int j){
    int lastBracket = 0; 
    while (i < j) {
        if (ind >= arraySize-1){
                ind = 0;
                printf("At end of tape!\n\n\n");
        }
        printf("Index:%d\nChar:%c\n", i, fl[i]); 
        if (fl[i] == '+') {
            printf("Increasing value at index %d by 1\n", ind);
            tape[ind]++;
            printf("Value is now %d\n", tape[ind]);
        }
        if (fl[i] == '-') {
            printf("Decreasing value at index %d by 1\n", ind);
            tape[ind]--;
            printf("Value is now %d\n", tape[ind]);
        }
        if (fl[i] == '>') {
            printf("Increasing index %d by 1\n", ind);   
            ind++;
        }
        if (fl[i] == '<') {
            printf("Decreasing index %d by 1\n", ind);
            ind--;
        }
        if (fl[i] == '.') {
            fprintf(out, "%c", tape[ind]);
        }
        if (fl[i] == ',') {
            // get one char from iostream
            tape[ind] = asciiTranslate(getchar());
        }
        if (fl[i] == '!'){
            fprintf(out, "%d", tape[ind]); 
        }
        if (fl[i] == '[') {
            lastBracket = i; 
            if (tape[ind] != 0){
                runCode(i+1, findClosingBracket(i));
            }
            i = findClosingBracket(i);
        }
        if (fl[i] == ']') {
            printf("Heading back to [\n"); 
            if (tape[ind]!=0){
                i = lastBracket;
            }
        } 
        if (fl[i] == '{'){
            int distance = findCurlyBracket(i)-i;
            int newIndex = 0;
            int num[100]; 
            int cnt = 0; 

            newIndex = atoi(&fl[i+1]); 
            tape[newIndex] = tape[ind]; 

            printf("Number is: %d\n", newIndex);
        }
        // check if fl[i] is any of the letters of the alphabet 
        
        i++; 
    }
}

// The main method 
void main(int argc, char *argv[] )  {  

    printf("Amt of arguments: %d\n", argc); 
    printf("File directory: %s\n", argv[1]);

    fileDir = argv[1];  
    
    // If the input file doesn't exist specify that you need one 
    if (argv[1] == NULL){
       printf("Please enter a file to run\n");
       return;
    }

    // Create new file it doesn't exist
    if (argv[2] == NULL) {
        out = fopen("out", "w");
        printf("Output directory: out\n");

    } else {
        out = fopen(argv[2], "w");
        printf("Output directory: %s\n", argv[2]);
    }

    // Open the file
    ptr = fopen(fileDir, "r"); 

    // Place the file contents into the fl string, fl stands for file contents --> fl 
    int i = 0; 
    while(fscanf(ptr, "%c", &fl[i]) == 1){
        i++;
        charAmt++; 
    }

    // This loops through all the characters in the file 

    runCode(0, charAmt); 

} 
