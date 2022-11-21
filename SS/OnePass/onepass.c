// Author: Gokul Raj, 235, R5A
// 1-pass assembler for SIC, w/o back reference

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Op{
    char name[16];
    int code;
};

#define OPTAB "OPTAB"
#define OPLEN 32
#define BUF_LEN 1024
#define RECORD_SIZE 60
#define WORD_SIZE 3
#define COMMENT_CHAR '.'

struct Op **optab;
struct Op **symtab;
int op_n = 0;
int sym_n = 0;

char progName[32];
int progLen, startAddr;

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
    for(int i=0; i<op_n; i++){
        if(opMatch(table[i]->name, op))
            return table[i]->code;
    }
    return -1;
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

int str2hex(char *str){
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

void loadOptab(){
    FILE *f = fopen(OPTAB, "r");
    while(!feof(f)){
        struct Op *o = malloc(sizeof(struct Op));
        fscanf(f, "%s\t%d", o->name, &o->code);
        optab[op_n++] = o;
    }
    fclose(f);
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
        if(i > bytes*2+2) return 0; // Larger than specified byte count
        k = bytes*2-1;
        while(opr[--i] != '\''){
            // Add if valid hex
            if((opr[i] >= '0' && opr[i] <= '9') || (opr[i] >= 'A' && opr[i] <= 'F'))
                op[k--] = opr[i];
            else
                return 0;
        }
        while(k >= 0) op[k--] = '0';
        op[bytes*2] = 0;
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

int main(int argc, char **argv){
    int locctr = 0, sym_i = 0;
    optab = malloc(sizeof(optab)*OPLEN);
    symtab = malloc(sizeof(symtab)*OPLEN);
    // Load OPCodes from file
    loadOptab();
    char *line = malloc(BUF_LEN);
    char *label = malloc(BUF_LEN/2);
    char *instr = malloc(BUF_LEN/2);
    char *opr = malloc(BUF_LEN/2);
    int sym_n, line_n = 0;
    int tr_start, tr_curr, tr_len_pos, tr_ind, n, addr;
    char *ins_hexcode, *opr_hexcode;

    // Store program name and length
    char *progName = malloc(BUF_LEN/2);
    int startAddr = 0;

    // Read from terminal asm and destination filenames
    if(argc >= 4){
        FILE *prog = fopen(argv[1], "r");
        FILE *symtab_f = fopen(argv[2], "w");
        FILE *obj = fopen(argv[3], "w");
        // Read each lines of program
        while(!feof(prog)){
            fgets(line, BUF_LEN, prog);
            sym_n = paramCount(line, label, instr, opr);
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
                    if(opMatch(instr, "START")){
                        strcpy(progName, label);
                        // Truncate program name to fixed size
                        int i = 0;
                        while(label[i] != 0 && i < 8) i++;
                        while(i<8) label[i++] = 32;
                        label[i] = 0;
                    }
                    else{
                        // Add symbol to SYMTAB
                        struct Op *sym = malloc(sizeof(struct Op));
                        strcpy(sym->name, label);
                        sym->code = locctr;
                        symtab[sym_i++] = sym;
                    }
                }
            }

            // Translate assembler directives
            if(opMatch(instr, "END")){
                // Finish last record, write end record
                fseek(obj, tr_len_pos, SEEK_SET);
                fprintf(obj, "%s", dec2hex(tr_curr-tr_start, 1));
                fseek(obj, 0, SEEK_END);
                fprintf(obj, "\nE%s", dec2hex(startAddr, 3));
                printf("Pass 2 done!! Object code in '%s'\n", argv[3]);
                break;
            }
            else if(opMatch(instr, "START")){
                locctr = str2hex(opr);
                startAddr = locctr;
                // Write Header Record
                fprintf(obj, "H%s%s%s\n", label, dec2hex(startAddr, 3), dec2hex(progLen, 3));
                // Write 1st Text Record
                fprintf(obj, "T%s   ", dec2hex(startAddr, 3));
                tr_start = tr_curr = startAddr;
                tr_len_pos = ftell(obj)-2;
                tr_ind = 0;
                continue;
            }
            else if(opMatch(instr, "RESW")){
                locctr += str2int(opr)*WORD_SIZE;
                continue;
            }
            else if(opMatch(instr, "RESB")){
                locctr += str2int(opr);
                continue;
            }
            else if(opMatch(instr, "WORD")){
                ins_hexcode = 0;
                opr_hexcode = oprEval(opr, WORD_SIZE, &n);
                if(opr_hexcode > 0){
                    addr = locctr;
                    locctr += WORD_SIZE;
                }
                else
                    printf("%d | %s\n[ERROR] At line %d: Invalid Constant -> %s\n", line_n, line, line_n, opr);
            }
            else if(opMatch(instr, "BYTE")){
                ins_hexcode = 0;
                opr_hexcode = oprEval(opr, 1, &n);
                if(opr_hexcode > 0){
                    addr = locctr;
                    locctr += n/2;
                }
                else
                    printf("%d | %s\n[ERROR] At line %d: Invalid Constant -> %s\n", line_n, line, line_n, opr);
            }

            // Translate opcodes
            else{
                int opcode = getOpCode(instr, optab);
                addr = locctr;
                // Write intermediate file
                if(opcode > -1){
                    ins_hexcode = dec2hex(opcode, 1);
                    opr_hexcode = oprEval(opr, 2, &n);
                    locctr += 3;
                }
                else{
                    printf("%d | %s\n[ERROR] At line %d: Unknown mnemonic '%s'\n", line_n, line, line_n, instr);
                    exit(1);
                }
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
            //printf("Writing...%s%s\n", ins_hexcode, opr_hexcode); //debug
            //printf("tr_start: %x, tr_curr: %x, tr_len_pos: %x, tr_ind: %d, n: %d, addr: %x\n", tr_start, tr_curr, tr_len_pos, tr_ind, n, addr); //debug
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
        // Write name and length to symtab
        fprintf(symtab_f, "%s\t%d\t%d\n", progName, startAddr, locctr-startAddr);
        fseek(obj, 15, SEEK_SET);
        progLen = locctr-startAddr;
        fprintf(obj, "%s", dec2hex(progLen, 3));
        // Write symtab to file
        for(int i=0; i<sym_i; i++)
            fprintf(symtab_f, "%s\t%d\n", symtab[i]->name, symtab[i]->code);
        printf("Assembly for '%s' complete!!\nProgram is %d bytes\n", progName, locctr-startAddr);
    }
    else
        printf("Invalid Arguments!!\nRun as %s <asm code> <symtab dest> <obj dest>\n", argv[0]);
    return 0;
}