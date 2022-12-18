#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 1024
#define MAX_ARG 10

struct DEFTAB{
    char **data;
    int n;
};

struct NAMTAB{
    char *name;
    int nargs;
    struct DEFTAB *def;
    struct NAMTAB *next;
};

char *line, *label, *instr, *opr;
int sym_n;
struct NAMTAB *namtab = NULL;

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

int getLine(FILE *prog){
    fgets(line, BUF_LEN, prog);
    sym_n = paramCount(line, label, instr, opr);
    // Skip if comment line or blank line
    return sym_n;
}

void defineMacro(FILE *prog){
    struct NAMTAB *n = malloc(sizeof(struct NAMTAB));
    n->name = malloc(24);
    n->nargs = 0;
    strncpy(n->name, label, 24);
    
    // Extract parameters and store for positional replacement
    char **ARGTAB = malloc(sizeof(ARGTAB));
    int i = 0, j = 0;
    ARGTAB[0] = malloc(128);
    while(opr[i] != 0){
        if(opr[i] == ','){
            ARGTAB[n->nargs++][j] = 0;
            j = 0;
        }
        else
            ARGTAB[n->nargs][j] = opr[i];
        i++;
    }
    ARGTAB[n->nargs++][j] = 0;
    
    while(!feof(prog)){
        if(!getLine(prog)) continue;
        if(!strcmp(opr, "MEND"))
            break;
        // Define line by line
        
    }
}

void main(int argc, char **argv){
    line = malloc(BUF_LEN);
    label = malloc(BUF_LEN/2);
    instr = malloc(BUF_LEN/2);
    opr = malloc(BUF_LEN/2);
    
    if(argc >= 2){
        FILE *prog = fopen(argv[1], "r");
        FILE *inter = fopen(argv[2], "w");
        // Process line by line
        while(!feof(prog)){
            if(!getLine(prog)) continue;
            // If macro defnition, load to NAMTAB
            if(strcmp(instr, "MACRO"))
                defineMacro(prog);
            else{
                // If macro call, expand;
                char found = 0;
                for(struct NAMTAB *i = namtab; i->next != NULL; i = i->next){
                    if(strcmp(instr, i->name)){
                        found = 1;
                        expandMacro(line, i, inter);
                        break;
                    }
                }
                // Else, write line as such
                if(!found) fputs(line, inter);
            }
        }
    }
    else
        printf("Invalid Arguments!!\nRun as %s <source code> <intermediate dest>\n", argv[0]);
}
