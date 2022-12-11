// Author: Gokul Raj, 235, R5A
// Absolute Loader for SIC Object Program

#include <stdio.h>
#include <stdlib.h>

#define BUFF_LEN 1024
#define NAME_SIZE 8
#define WORD_LEN 3
#define MEM_DUMP_FILE "memdump.txt"

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
    if(argc >= 3){
        FILE *objf = fopen(argv[2], "r");
        char *buff = malloc(BUFF_LEN);
        char f = 0;
        int startAddr, progLen, currPos, currLen, mempos, i, j;
        // Read whole object program
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
                    printf("[ERROR] '%s' not found in '%s'\n", argv[1], argv[2]);
                    exit(0);
                }
                // Verified. Get metadata, allocate a copy buffer
                printf("Program '%s' found. Loading...\n", argv[1]);
                startAddr = snipAddr(buff, NAME_SIZE+1, WORD_LEN*2);
                progLen = snipAddr(buff, NAME_SIZE+WORD_LEN*2+1, 2*(WORD_LEN+1));
                mem = malloc(progLen*2);
                for(int i=0; i<progLen*2; i++)
                    mem[i]='0';
            }
            // If text record, copy normally
            else if(buff[0] == 'T'){
                currPos = snipAddr(buff, 1, 2*WORD_LEN);
                currLen = snipAddr(buff, 2*WORD_LEN+1, 2)*2;
                mempos = (currPos-startAddr)*2;
                // Copy this record to mem
                i = 2*WORD_LEN+3;
                j = 0;
                while(j < currLen)
                    mem[mempos+(j++)] = buff[i++];
            }
            // Stop reading at end record
            else if(buff[0] == 'E'){
                printf("Loaded to [%x..%x]. Load done!!\n", startAddr, startAddr+progLen-1);
                break;
            }
        }
        // Dump memory to file
        i = 0, currPos = startAddr;
        FILE *memdump = fopen(MEM_DUMP_FILE, "w");
        while(i < 2*progLen){
            fprintf(memdump, "%s %c%c\n", dec2hex(currPos, 2), mem[i], mem[i+1]);
            i += 2;
            currPos ++;
        }
        fclose(memdump);
        fclose(objf);
        printf("Memory dumped to %s...\n", MEM_DUMP_FILE);
    }
    else
        printf("Invalid file format!!\nRun as %s <prog name> <obj code>\n", argv[0]);
}