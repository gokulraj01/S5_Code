// Author: Gokul Raj, 235, R5A
// Absolute Loader for SIC Object Program

#include <stdio.h>
#include <stdlib.h>

#define BUFF_LEN 1024
#define NAME_SIZE 8

void main(int argc, char **argv){
    if(argc >= 4){
        FILE *objf = fopen(argv[3], "r");
        char *buff = malloc(BUFF_LEN);
        char i = 0, f = 0;
        // Verify program name of program to load
        while(!feof(objf)){
            fgets(buff, BUFF_LEN, objf);
            if(buff[0] == 'H'){
                while(i < NAME_SIZE && argv[1][i] != 0){
                    if(buff[i+1] != argv[1][i]){
                        f = 1;
                        break;
                    }
                    i++;
                }
                if(f){
                    printf("[ERROR] '%s' not found in '%s'\n", argv[1], argv[3]);
                    exit(0);
                }
                break;
            }
            else continue;
        }
        // Verified. Now load at start addr.
        char *startAddr = malloc(9);
        i = NAME_SIZE+1;
        char max = i+NAME_SIZE-2, j = 0;
        while(buff[i] == '0') i++;
        while(i < max)
            startAddr[j++] = buff[i++];
        startAddr[j] = 0;
        printf("Loading program %s to memory location %s...\n", argv[1], startAddr);
            // Loading syscalls happen here
        printf("Load done!!\n");
    }
    else{
        printf("Invalid file format!!\nRun as %s <prog name> <start addr> <obj code>\n", argv[0]);
    }
}
