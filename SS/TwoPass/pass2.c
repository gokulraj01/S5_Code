// Author: Gokul Raj, 235, R5A
// 2-pass assembler for SIC | Pass 2
// Intermediate File --> Object Code

#include <stdio.h>
#include <stdlib.h>

struct Op{
    char name[16];
    int code;
};

#define OPTAB "OPTAB"
#define OPLEN 32
#define BUF_LEN 1024
#define RECORD_SIZE 60

struct Op **optab;
struct Op **symtab;
int op_n = 0;
int sym_n = 0;
char progName[32];
int progLen, startAddr;

void loadOptab(){
    FILE *f = fopen(OPTAB, "r");
    while(!feof(f)){
        struct Op *o = malloc(sizeof(struct Op));
        fscanf(f, "%s\t%x", o->name, &o->code);
        optab[op_n++] = o;
    }
    fclose(f);
}

void loadSymtab(char *filename){
    FILE *f = fopen(filename, "r");
    fscanf(f, "%s\t%d\t%d", progName, &startAddr, &progLen);
    printf("Running Pass 2 for '%s' | Start: %x, Length: %d bytes\n", progName, startAddr, progLen);
    while(!feof(f)){
        struct Op *o = malloc(sizeof(struct Op));
        fscanf(f, "%s\t%d", o->name, &o->code);
        symtab[sym_n++] = o;
    }
    fclose(f);
}

void parseParam(char *line, char *addr, char *instr, char *opr){
    // Read Address
    int i = 0, k = 0;
    while(line[i]!=0 && line[i]!='\n' && line[i]!='\t')
        addr[k++] = line[i++];
    addr[k] = 0;
    // Read Instruction
    k = 0;
    if(line[i] != 0 && line[i] != 32) i++;
    while(line[i]!=0 && line[i]!='\n' && line[i]!='\t')
        instr[k++] = line[i++];
    instr[k] = 0;
    // Read Operator
    k = 0;
    if(line[i] != 0 && line[i] != 32) i++;
    while(line[i]!=0 && line[i]!='\n' && line[i]!='\t')
        opr[k++] = line[i++];
    opr[k] = 0;
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

// Compare op-codes ignoring case and whitespace. 1=same, 0=diff
char opMatch(char *c1, char *c2){
    char a, b;
    int i=0, j=0;
    if(c1 == 0 || c2 == 0)
        return 0;
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

int getOpCode(char *op, struct Op **table){
    printf("Iter!!");
    for(int i=0; i<op_n; i++){
        if(opMatch(table[i]->name, op))
            return table[i]->code;
    }
    return -1;
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

    // If all fails, it is a label
    int labelloc = getOpCode(opr, symtab);
    if(labelloc > -1)
        return dec2hex(labelloc, bytes);
    else{
        printf("[ERROR] Invalid label '%s' -- Filling 0's\n", opr);
        // NOTE: Workaround for invalid label
        return dec2hex(0, bytes);
    }
}

void main(int argc, char **argv){
    if(argc == 4){
        FILE *interFile = fopen(argv[1], "r");
        FILE *obj = fopen(argv[3], "w");

        optab = malloc(sizeof(optab)*OPLEN);
        symtab = malloc(sizeof(optab)*OPLEN);
        char *line = malloc(BUF_LEN);
        char *ins = malloc(256);
        char *opr = malloc(256);
        char *addr_s = malloc(256);
        char *ins_hexcode, *opr_hexcode;
        int addr, n, tr_start, tr_curr, tr_len_pos, tr_ind;

        loadOptab();
        loadSymtab(argv[2]);

        // Truncate program name to fixed size
        int i = 0;
        while(progName[i] != 0 && i < 8) i++;
        while(i<8) progName[i++] = 32;
        progName[i] = 0;

        // Write Header Record
        fprintf(obj, "H%s%s%s\n", progName, dec2hex(startAddr, 3), dec2hex(progLen, 3));
        // Write 1st Text Record
        fprintf(obj, "T%s   ", dec2hex(startAddr, 3));
        tr_start = tr_curr = startAddr;
        tr_len_pos = ftell(obj)-2;
        tr_ind = 0;

        // Read each line of intermediate file
        while(!feof(interFile)){
            fgets(line, BUF_LEN, interFile);
            // NOTE: Fix for potential trailing new line
            if(line[0] == 0) break;
            parseParam(line, addr_s, ins, opr);
            addr = str2int(addr_s);

            // Evaluate Operand
            // BYTE and WORD have no opcode.
            if(opMatch(ins, "BYTE")){
                ins_hexcode = 0;
                opr_hexcode = oprEval(opr, 1, &n);
            }
            else if (opMatch(ins, "WORD")){
                ins_hexcode = 0;
                opr_hexcode = oprEval(opr, 3, &n);
            }
            // The rest are valid opcodes
            else{
                ins_hexcode = dec2hex(getOpCode(ins, optab), 1);
                opr_hexcode = oprEval(opr, 2, &n);
            }
            
            // NOTE: Workaround for missed instruction size 
            int offset = 0;
            if(n == 4) offset = 6;
            else offset = n;
            
            // Cannot write in current record, make new one
            if(tr_ind+offset > RECORD_SIZE || tr_curr != addr){
                // End current Record
                fputc('\n', obj);
                fseek(obj, tr_len_pos, SEEK_SET);
                fprintf(obj, "%s", dec2hex(tr_curr-tr_start, 1));
                fseek(obj, 0, SEEK_END);
                // Start new record
                tr_ind = 0;
                fprintf(obj, "T%s   ", dec2hex(addr, 3));
                tr_start = addr;
                tr_len_pos = ftell(obj)-2;
            }
            // Write to same text record
            tr_curr = addr;
            tr_ind += n;
            tr_curr += n/2;
            if(ins_hexcode == 0)
                fprintf(obj, " %s", opr_hexcode);
            else{
                fprintf(obj, " %s%s", ins_hexcode, opr_hexcode);
                tr_ind += 2;
                tr_curr ++;
            }
            line[0] = 0;
        }
        // Finish last record, write end record
        fseek(obj, tr_len_pos, SEEK_SET);
        fprintf(obj, "%s", dec2hex(tr_curr-tr_start, 1));
        fseek(obj, 0, SEEK_END);
        fprintf(obj, "\nE%s", dec2hex(startAddr, 3));
    }
    else
        printf("Invalid Arguments!!\nRun as %s <intermediate file> <symtab dest> <objcode dest>\n", argv[0]);
}