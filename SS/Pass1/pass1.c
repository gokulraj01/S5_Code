#include <stdio.h>
#include <stdlib.h>

#define OPTAB "optab.txt"
#define OPLEN 6
#define BUF_LEN 1024
#define WORD_SIZE 3
#define COMMENT_CHAR '.'

struct Op{
    int code;
    char name[10];
};

struct Op **optab;
int op_n = 0;

void loadOpCode(){
    FILE *f = fopen(OPTAB, "r");
    while(!feof(f)){
        struct Op *o = malloc(sizeof(struct Op));
        fscanf(f, "%s %d", o->name, &o->code);
        optab[op_n++] = o;
    }
    fclose(f);
}

// Compare op-codes ignoring case and whitespace. 1=same, 0=diff
char opMatch(char *c1, char *c2){
    char a, b;
    for(int i=0, j=0; c1[i] != 0 && c2[j] != 0; i++, j++){
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
    return 1;
}

int isValidOp(char *op){
    for(int i=0; i<op_n; i++){
        if(opMatch(optab[i]->name, op))
            return optab[i]->code;
    }
    return -1;
}

// Counts params in line and identifies comments and blank lines
char paramCount(char *line){
    int i=0, n=0;
    // Skip initial whitespaces
    while(line[i] == 9 || line[i] == 32 || line[i] == 0) i++;
    // 1st non blank is '.' then it's comment. Skip.
    if(line[i] == COMMENT_CHAR)
        return 0;
    // Is code line. Then count params.
    else{
        while(line[i] != 0){
            if(line[i] == 32 || line[i] == 9)
                n++;
            i++;
        }
    }
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

void main(int argc, char **argv){
    int locctr = 0;
    optab = malloc(sizeof(optab)*OPLEN);
    // Load OPCodes from file
    loadOpCode();
    char *line = malloc(BUF_LEN);
    char *label = malloc(BUF_LEN/2);
    char *operator = malloc(BUF_LEN/2);
    char *operation = malloc(BUF_LEN/2);
    int sym_n, line_n = 0;
    // Read from terminal asm and destination filenames
    if(argc >= 4){
        FILE *prog = fopen(argv[1], "r");
        FILE *objc = fopen(argv[2], "w");
        FILE *symtab = fopen(argv[3], "w");
        // Read each lines of program
        while(!feof(prog)){
            fgets(line, BUF_LEN, prog);
            sym_n = paramCount(line);
            // Skip if comment line or blank line
            if(sym_n == 0)
                continue;
            // Is code line. Start parsing.
            line_n++;
            // 2 param line (ie. no label)
            if(sym_n == 1)
                sscanf(line, "%s %s", operation, operator);
            // 3 param line
            else if(sym_n == 2){
                sscanf(line, "%s %s %s", label, operation, operator);
                // Write label into symtab file
                fprintf(symtab, "%s %d\n", label, locctr);
            }
            // Format invalid
            else{
                printf("Sym_n: %d\n", sym_n);
                printf("%d | %s\n[ERROR] At line %d: Invalid format\n", line_n, line, line_n);
                break;
            }

            // Translate assembler directives
            if(opMatch(operation, "START"))
                locctr = str2int(operator);
            else if(opMatch(operation, "RESW"))
                locctr += str2int(operator)*WORD_SIZE;
            else if(opMatch(operation, "RESB"))
                locctr += str2int(operator);
            else if(opMatch(operation, "WORD"))
                locctr += WORD_SIZE;
            else if(opMatch(operation, "BYTE"))
                locctr += 1;
            // Translate opcodes
            else{
                int opcode = isValidOp(operation);
                // Write intermediate file
                if(opcode > -1){
                    fprintf(objc, "%x\t%s\n", opcode, operator);
                }
                else
                    printf("%d | %s\n[ERROR] At line %d: Unknown mnemonic '%s'\n", line_n, line, line_n, operation);
            }
        }
    }
    else
        printf("No input files!!\nRun as %s <asm code> <obj dest> <symtab dest>\n", argv[0]);
}