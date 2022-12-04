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

// Get a section from any record
int getRecData(char *rec, int start, int len){
    int i = start, j = 0;
    char *snip = malloc(len+1);
    while(rec[i] != 0 && i < len)
        snip[j++] = rec[i++];
    snip[j] = 0;
    int startAddr = hex2dec(snip);
    return startAddr;
}

void relocateLine(char *rec, FILE *f, int startAddr){
    // Remember last pos to return to
    int lastloc = ftell(f);

    // Get location to modify
    int modloc = getRecData(rec, 1, 6);
    int modsize = getRecData(rec, 7, 2);

    // Start at top, read all text records
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(BUFF_LEN);
    while(!feof(f)){
        fgets(buf, BUFF_LEN, f);
        // For each text record, find start addr
        if(buf[0] == 'T'){
            int textloc = getRecData(buf, 1, 6);
            int textlen = getRecData(buf, 7, 2);
            // if modloc is in this text record, modify it
            if(textloc+textlen >= modloc){
                int offset = (modloc-textloc)*2+6;
                int addr = getRecData(buf, , modsize);
                char *newAddr = dec2hex(addr+startAddr, modsize/2);
                for(int i=; )
            }
        }
    }
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
                int modLoc = getRecStart(buff);
                int lastFileLoc = ftell();
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
