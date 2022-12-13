#include <stdio.h>
#include <stdlib.h>

char bitCheck(char *hex, int pos){
    char map[][4] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    int len = -1;
    while(hex[++len] != 0);
    if(pos > 4*len-1) return 0;
    else{
        int hexpos = pos/4;
        int bitpos = pos%4;
        char c = hex[hexpos];
        if(c >= '0' && c <= '9') c -= '0';
        else if(c >= 'A' && c <= 'F') c = c+10-'A';
        if(map[c][bitpos] == '0') return 0;
        else return 1;
    }
}

void main(){
    char a[] = "1234";
    for(int n=0; n<16; n++)
        // printf("%d bit of %s is %d\n", n, a, bitCheck(a, n));
        printf("%d ", bitCheck(a, n));
}