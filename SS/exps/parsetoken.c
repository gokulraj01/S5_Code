#include <stdio.h>

void main(){
    char buf[] = "LABEL MYLABEL WORD X'122";
    char tokens[100][10];

    int i = 0, j = 0, k = 0;
    int next_token = 0;
    while(buf[i] != 0){
        if(buf[i] == ' ' || buf[i] == '\t'){
            if(!next_token){
                next_token = 1;
                tokens[j][k] = 0;
                k = 0;
                j++;
            }
        }
        else{
            next_token = 0;
            tokens[j][k++] = buf[i];
        }
        i++;
    }
    tokens[j][k] = 0;
    printf("Got %d tokens...\n", j+1);
    printf("Tokens are ");
    for(int i=0; i<j+1; i++)
        printf("[%s] ", tokens[i]);
    putchar('\n');
}