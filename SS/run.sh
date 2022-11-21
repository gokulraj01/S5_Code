#!/bin/bash
SOURCE_FILENAME="samp2.asm"
INTER_FILENAME="inter"
SYMTAB_FILENAME="symtab"
OBJC_FILENAME="obj"

DEBUG=0

clear
gcc TwoPass/pass1.c -g
if [[ $DEBUG == 1 ]]; then
    echo "run $SOURCE_FILENAME $INTER_FILENAME $SYMTAB_FILENAME" | gdb -q a.out
else
    ./a.out $SOURCE_FILENAME $INTER_FILENAME $SYMTAB_FILENAME
fi

echo ""
gcc TwoPass/pass2.c -g
if [[ $DEBUG == 1 ]]; then
    echo "run $INTER_FILENAME $SYMTAB_FILENAME $OBJC_FILENAME" | gdb -q a.out
else
    ./a.out $INTER_FILENAME $SYMTAB_FILENAME $OBJC_FILENAME
fi

printf "\n-----------\nObject Code\n-----------\n"
cat $OBJC_FILENAME
echo ""