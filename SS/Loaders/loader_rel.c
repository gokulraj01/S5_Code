// Author: Gokul Raj, 235, R5A
// Relocating loader for SIC Object Program

#include <stdio.h>
#include <stdlib.h>

#define BUFF_LEN 1024
#define NAME_SIZE 8
#define WORD_LEN 3

char *mem = NULL;

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

char* dec2hex(int n, int bytes){
    bytes = bytes*2;
    char symmap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char *op = malloc(bytes+1);
    int pos = bytes-1, rem;
    while(n > 0){
        rem = n%16;
        n /= 16;
        op[pos--] = symmap[rem];
    }
    while(pos >= 0) op[pos--] = '0';
    op[bytes] = 0;
    return op;
}

int snipAddr(char *rec, int offset, int len){
    int i = offset, j = 0;
    char *snip = malloc(len+1);
    while(rec[i] != 0 && j < len)
        snip[j++] = rec[i++];
    snip[j] = 0;
    int addr = hex2dec(snip);
    return addr;
}

void main(int argc, char **argv){
    if(argc >= 4){
        FILE *objf = fopen(argv[3], "r");
        char *buff = malloc(BUFF_LEN);
        char f = 0;
        int startAddr, progLen, relAddr, currPos, currLen, mempos, i;
        // Verify program name of program to load
        while(!feof(objf)){
            fgets(buff, BUFF_LEN, objf);
            // If header, verify program name
            if(buff[0] == 'H'){
                i = 0;
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
                // Verified. Get metadata, allocate a copy buffer
                startAddr = snipAddr(buff, NAME_SIZE+1, WORD_LEN*2);
                progLen = snipAddr(buff, NAME_SIZE+WORD_LEN*2+1, 2*(WORD_LEN+1));
                relAddr = hex2dec(argv[2]);
                mem = malloc(progLen*2);
                printf("Start at %d with len %d, memsize %d\nRel to %d", startAddr, progLen, progLen*2, relAddr);
            }
            // If text record, copy normally
            else if(buff[0] == 'T'){
                currPos = snipAddr(buff, 1, 2*WORD_LEN);
                currLen = snipAddr(buff, 2*WORD_LEN+1, 2);
                mempos = (currPos-startAddr)*2;
                // Copy this record to mem
                i = 2*WORD_LEN+3;
                while(buff[i] != '\n')
                    mem[mempos+i] = buff[i++];

                printf("Currpos: %d, Currlen: %d, mempos: %d, start: %d\n", currPos, currLen, mempos, startAddr);
                
            }
            // If modification record,
            // go to beginning and find correct Text Record
            else if(buff[0] == 'M'){
                int modAddr = snipAddr(buff, 1, 2*WORD_LEN); 
                int modLen = snipAddr(buff, 2*WORD_LEN+1, 2);
                mempos = (modAddr - startAddr)*2+1;
                int oldAddr = snipAddr(mem, mempos, modLen);
                char *newAddr = dec2hex(oldAddr+relAddr, 2);
                i = 0;
                while(newAddr[i] != 0)
                    mem[mempos+i] = newAddr[i++];
                printf("Modify %d at %d\n", modLen, modAddr);
            }
        }
        // Dump mem to file
        i = 0, currPos = relAddr;
        FILE *memdump = fopen("memdump.txt", "w");
        while(i <= 2*progLen){
            printf("Dump %s %c%c\n", dec2hex(relAddr, 2), mem[i++], mem[i++]);
            getchar();
            fprintf(memdump, "%s %c%c\n", dec2hex(relAddr, 2), mem[i++], mem[i++]);
        }
        fclose(memdump);
        fclose(objf);
    }
    else
        printf("Invalid file format!!\nRun as %s <prog name> <start addr> <obj code>\n", argv[0]);
}
