// Author: Gokul Raj, 235, R5A
// Relocating loader for SIC Object Program

#include <stdio.h>
#include <stdlib.h>

#define BUFF_LEN 1024
#define NAME_SIZE 8
#define WORD_LEN 3

int hex2dec(char *str){
    int op = 0;
    for(int i=0; str[i]!=0; i++){
        if(str[i] >= '0' && str[i] <= '9')
            op = op*16 + str[i] - '0';
        else if(str[i] >= 'A' && str[i] <= 'F')
            op = op*16 + str[i] - 'A' + 10;
    }
    return op;
}

int getTextStart(char *rec){
    int i = 1, j = 0;
    char *snip = malloc(2*WORD_LEN+1);
    while(rec[i] != 0 && i < 2*WORD_LEN+1)
        snip[j++] = rec[i++];
    snip[j] = 0;
    int startAddr = hex2dec(snip);
    // j = 0;
    // while(rec[i] != 0 && j < 2)
    //     snip[j++] = rec[i++];
    // snip[j] = 0;
    // *len = hex2int(snip);
    return startAddr;
}

void main(int argc, char **argv){
    if(argc >= 4){
        FILE *objf = fopen(argv[3], "r");
        char *buff = malloc(BUFF_LEN);
        char i = 0, f = 0;
        // Verify program name of program to load
        while(!feof(objf)){
            fgets(buff, BUFF_LEN, objf);
            // If header, verify program name
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
            // If modification record,
            // go to beginning and find correct Text Record
            else if(buff[0] == 'M'){
                
            }
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
    else
        printf("Invalid file format!!\nRun as %s <prog name> <start addr> <obj code>\n", argv[0]);
}
