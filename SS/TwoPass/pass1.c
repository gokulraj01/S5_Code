#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTAB "OPTAB"
#define OPLEN 32
#define SYMLEN 256
#define BUF_LEN 1024
#define WORD_SIZE 3
#define COMMENT_CHAR '.'

struct Op{
    int code;
    char name[24];
};

struct Op **optab;
struct Op **symtab;
int op_n = 0;

void loadOptab(){
    FILE *f = fopen(OPTAB, "r");
    while(!feof(f)){
        struct Op *o = malloc(sizeof(struct Op));
        fscanf(f, "%s\t%d", o->name, &o->code);
        optab[op_n++] = o;
    }
    fclose(f);
}

// Compare op-codes ignoring case and whitespace. 1=same, 0=diff
char opMatch(char *c1, char *c2){
    char a, b;
    int i=0, j=0;
    for(; c1[i] != 0 && c2[j] != 0; i++, j++){
        // Skip leading whitespace
        while(c1[i] == 9 || c1[i] == 32) i++;
        while(c2[j] == 9 || c2[j] == 32) j++;
        a = c1[i]; b = c2[j];
        // To make capital, do c - 'a' + 'A', or c - 32
        if(a >= 'a' && a <= 'z')
            a -= 32;
        if(b >= 'a' && b <= 'z')
            b -= 32;
        if(a != b)
            return 0;
    }
    if(c1[i] == c2[j]) return 1;
    else return 0;
}

int isValidOp(char *op){
    for(int i=0; i<op_n; i++){
        if(opMatch(optab[i]->name, op))
            return optab[i]->code;
    }
    return -1;
}

// Counts and parses params in line and identifies comments and blank lines
char paramCount(char *line, char *lab, char *op, char *opr){
    int i=0, j=0, n=0;
    while((line[i] == 32 || line[i] == 9) && line[i] != 0) i++;
    // If comment or blank, exit
    if(line[i] == 0 || line[i] == 10 || line[i] == '.')
        return 0;
    while(line[i] != 32 && line[i] != 9 && line[i] != 10 && line[i] != 0)
        lab[j++] = line[i++];
    lab[j] = 0;
    j = 0; n++;

    while((line[i] == 32 || line[i] == 9) && line[i] != 0) i++;
    while(line[i] != 32 && line[i] != 9 && line[i] != 10 && line[i] != 0)
        op[j++] = line[i++];
    op[j] = 0;
    j = 0; n++;

    while(line[i] == 32 || line[i] == 9 || line[i] == 10 && line[i] != 0) i++;
    if(line[i] == 0){
        strcpy(opr, op);
        strcpy(op, lab);
        lab[0] = 0;
        return n;
    }
    while(line[i] != 0 && line[i] != 10)
        opr[j++] = line[i++];
    opr[j] = 0;
    j = 0; n++;
    return n;
}

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

int oprSizeEval(char *opr){
    int i = 0;
    // For plain numbers
    int flag = 1;
    while(opr[i] != 0){
        if(opr[i] >= '0' && opr[i] <= '9' || opr[i]=='-');
        else{
            flag = 0; break;
        }
        i++;
    }
    if(flag) return 1;

    // For Specials/ Labels
    // Hex constants
    if(opr[0] == 'X' && opr[1] == '\''){
        i = 2;
        while(opr[i] != '\'' && opr[i] != 0) i++;
        if(i > 8) return 0; // Larger than 3 bytes
        while(opr[--i] != '\''){
            // Add if valid hex
            if((opr[i] >= '0' && opr[i] <= '9') || (opr[i] >= 'A' && opr[i] <= 'F'));
            else return 0;
        }
        return 1;
    }

    // Strings
    if(opr[0] == 'C' && opr[1] == '\''){
        i = 2;
        int k = 0;
        while(opr[i] != '\'' && opr[i] != 0){
            k += 1;
            i++;
        }
        return k;
    }
}

int main(int argc, char **argv){
    int locctr = 0, sym_i = 0;
    optab = malloc(sizeof(optab)*OPLEN);
    symtab = malloc(sizeof(symtab)*SYMLEN);
    // Load OPCodes from file
    loadOptab();
    char *line = malloc(BUF_LEN);
    char *label = malloc(BUF_LEN/2);
    char *operation = malloc(BUF_LEN/2);
    char *operator = malloc(BUF_LEN/2);
    int sym_n, line_n = 0;
    // Read from terminal asm and destination filenames
    if(argc >= 4){
        FILE *prog = fopen(argv[1], "r");
        FILE *objc = fopen(argv[2], "w");
        FILE *symtab_f = fopen(argv[3], "w");
        // Read each lines of program
        while(!feof(prog)){
            fgets(line, BUF_LEN, prog);
            sym_n = paramCount(line, label, operation, operator);
            line_n++;
            // Skip if comment line or blank line
            if(sym_n == 0)
                continue;
            // Is code line. Start parsing.
            // 3 param line
            if(sym_n == 3){
                // Write label into symtab file
                for(int k=0; k<sym_i; k++){
                    if(!strcmp(symtab[k]->name, label)){
                        printf("%d | %s\n[ERROR] At line %d: Duplicate label '%s'\n", line_n, line, line_n, label);
                        return 1;
                    }
                }
                if(strcmp(label, "") != 0){
                    struct Op *sym = malloc(sizeof(struct Op));
                    strcpy(sym->name, label);
                    sym->code = locctr;
                    symtab[sym_i++] = sym;
                }
            }

            printf("--> %d | %s op{%s}\n", line_n, line, operation); // Debug

            // Translate assembler directives
            if(opMatch(operation, "END"))
                continue;
            else if(opMatch(operation, "START"))
                locctr = str2int(operator);
            else if(opMatch(operation, "RESW"))
                locctr += str2int(operator)*WORD_SIZE;
            else if(opMatch(operation, "RESB"))
                locctr += str2int(operator);
            else if(opMatch(operation, "WORD")){
                if(oprSizeEval(operator) > 0)
                    locctr += WORD_SIZE;
                else
                    printf("%d | %s\n[ERROR] At line %d: Invalid Constant -> %s\n", line_n, line, line_n, operator);
            }
            else if(opMatch(operation, "BYTE")){
                int constSize = oprSizeEval(operator);
                printf("%d + %d\n", locctr, constSize);
                if(constSize > 0)
                    locctr += constSize;
                else
                    printf("%d | %s\n[ERROR] At line %d: Invalid Constant -> %s\n", line_n, line, line_n, operator);
            }

            // Translate opcodes
            else{
                int opcode = isValidOp(operation);
                // Write intermediate file
                // printf("%d | %s %s %s\n", line_n, label, operation, operator); // DEBUG
                if(opcode > -1){
                    fprintf(objc, "%d\t%s\t%s\n", locctr, operation, operator);
                    locctr += 3;
                }
                else{
                    printf("%d | %s\n[ERROR] At line %d: Unknown mnemonic '%s'\n", line_n, line, line_n, operation);
                    exit(1);
                }
            }
        }
        // Write symtab to file
        for(int i=0; i<sym_i; i++)
            fprintf(symtab_f, "%s %d\n", symtab[i]->name, symtab[i]->code);
        printf("Pass 1 done!!\n");
    }
    else
        printf("Invalid Arguments!!\nRun as %s <asm code> <intermediate dest> <symtab dest>\n", argv[0]);
    return 0;
}