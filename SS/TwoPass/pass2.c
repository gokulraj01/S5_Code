#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Op{
    char name[24];
    int code;
};

#define OPTAB "optab.txt"
#define OPLEN 6

struct Op **optab;
struct Op **symtab;
int op_n = 0;
int sym_n = 0;

void loadOpCode(){
    FILE *f = fopen(OPTAB, "r");
    while(!feof(f)){
        struct Op *o = malloc(sizeof(struct Op));
        fscanf(f, "%s %d", o->name, &o->code);
        optab[op_n++] = o;
    }
    fclose(f);
}

void loadTable(char *filename, struct Op **table, int *n){
    FILE *f = fopen(filename, "r");
    while(!feof(f)){
        struct Op *o = malloc(sizeof(struct Op));
        fscanf(f, "%s\t%d", o->name, &o->code);
        table[(*n)++] = o;
    }
    fclose(f);
}

void main(int argc, char **argv){
    if(argc > 4){
        FILE *interFile = fopen(argv[1], 'r'); 
        loadSymtab(argv[2]);
        FILE *obj = fopen(argv[3], 'w');
    }
    else
        printf("No input files!!\nRun as %s <intermediate file> <symtab dest> <objcode dest>\n", argv[0]);
}