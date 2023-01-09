STACK SEGMENT STACK
STACK ENDS

DATA SEGMENT
    PROMPT1 DB "Enter n1: $"
    PROMPT2 DB "Enter n2: $"
    MSG DB "Difference is: $"
    ERMSG DB "Not a number!!",13, 10, "$"
    CRLF DB 10,13,"$"

    NUM DW 0
    N1 DW ?
    N2 DW ?
    SUM DW ?
    TEN DB 10
DATA ENDS

PRINT MACRO LOC
    MOV DX, OFFSET LOC
    MOV AH, 09H
    INT 21H
ENDM

EXIT MACRO
    MOV AH, 4CH
    INT 21H
ENDM

GETINT MACRO LOC
LOCAL ITER, ERR, DONE
        MOV NUM, 0000H  ; init buffer
ITER:   MOV AH, 01H
        INT 21H
        CMP AL, 13      ; end if new line
        JE DONE
        CMP AL, '0'     ; sanitize input
        JB ERR
        CMP AL, '9'
        JA ERR
        SUB AL, '0'
        CBW             ; fill AH with 0s
        MOV BX, AX      ; store input ascii to BL
        MOV AX, NUM
        MUL WORD PTR TEN
        ADD AX, BX
        MOV NUM, AX
        JMP ITER
ERR:    PRINT CRLF
        PRINT ERMSG
        EXIT
DONE:   MOV AX, NUM
        MOV LOC, AX
ENDM

SHOWINT MACRO LOC
LOCAL MD, OP
        MOV CX, 0
; push digts to stack
        MOV AX, LOC
        MOV BX, 10
MD:     MOV DX, 0
        DIV BX
        PUSH DX
        INC CX
        CMP AX, 0
        JA MD
; pop digits and write as ascii
OP:     POP DX
        ADD DX, 48
        MOV AH, 02H
        INT 21H
        LOOP OP
ENDM

CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    MOV AX, DATA    ; Initialize Data Segment
    MOV DS, AX

    PRINT PROMPT1
    GETINT N1

    PRINT PROMPT2
    GETINT N2

    MOV AX, N1
    SUB AX, N2
    MOV SUM, AX
    PRINT MSG
    SHOWINT SUM
    PRINT CRLF

    EXIT
CODE ENDS
END START