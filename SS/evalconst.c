#include <stdio.h>
#include <stdlib.h>

int str2int(char *str){
    int op = 0; char neg = 0;
    for(int i=0; str[i]!=0; i++){
        if((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
            if(str[i] == '-')
                neg = 1;
            else
                op = op*10 + str[i] - '0';
    }
    if(neg) op *= -1;
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

// Evaluate the operator to corersponding hex code
char* oprEval(char *opr, int bytes, int *n){
    int i = 0, k;
    *n = bytes*2;
    // For plain numbers
    int flag = 1;
    while(opr[i] != 0){
        if(opr[i] >= '0' && opr[i] <= '9' || opr[i]=='-');
        else{
            flag = 0;
            break;
        }
        i++;
    }
    if(flag)
        return dec2hex(str2int(opr), bytes);

    // For Specials/ Labels
    // Hex constants
    char *op = malloc(1024);
    if(opr[0] == 'X' && opr[1] == '\''){
        i = 2;
        while(opr[i] != '\'' && opr[i] != 0) i++;
        if(i > bytes*2+2) return 0; // Larger than 3 bytes
        k = bytes*2-1;
        while(opr[--i] != '\''){
            // Add if valid hex
            if((opr[i] >= '0' && opr[i] <= '9') || (opr[i] >= 'A' && opr[i] <= 'F'))
                op[k--] = opr[i];
            else
                return 0;
        }
        while(k >= 0) op[k--] = '0';
        op[6] = 0;
        return op;
    }

    // Strings
    if(opr[0] == 'C' && opr[1] == '\''){
        i = 2;
        k = 0;
        while(opr[i] != '\'' && opr[i] != 0){
            char *t = dec2hex(opr[i++], 1);
            op[k++] = t[0];
            op[k++] = t[1];
        }
        *n = k;
        return op;
    }
}

void main(){
    int a = 128, n;
    printf("%d in hex is %x or %s\n", a, a, dec2hex(a, 3));
    printf("STR test: %s\n", oprEval("C'abcdefghijklmn'", 2, &n));
    printf("HEX test: %s\n", oprEval("X'8A'", 2, &n));
    printf("DEC test: %s\n", oprEval("1256", 2, &n));
}