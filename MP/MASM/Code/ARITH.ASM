STACK SEGMENT STACK
STACK ENDS

DATA SEGMENT
    CRLF DB 10, 13, "$"
    PR1 DB "Enter n1: $"
    PR2 DB "Enter n2: $"
    ERMSG DB "Error!$"

    SUM DB "Sum is: $"
    DIF DB "Difference is: $"
    PRO DB "Product is: $"
    DVQ DB "Quotient is: $"
    DVR DB "Remainder is: $"

    N1 DW ?
    N2 DW ?
    NUM DW ?
    TEN DW 10
DATA ENDS

PRINT MACRO LOC
    PUSH DX
    PUSH AX
    MOV DX, OFFSET LOC
    MOV AH, 09H
    INT 21H
    POP AX
    POP DX
ENDM

EXIT MACRO
    MOV AH, 09H
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
    MOV AX, DATA
    MOV DS, AX

    PRINT PR1
    GETINT N1
    PRINT PR2
    GETINT N2

    ; Sum
    MOV AX, N1
    MOV BX, N2
    ADD AX, BX
    PRINT SUM
    SHOWINT AX
    PRINT CRLF

    ; Difference
    MOV AX, N1
    SUB AX, BX
    PRINT DIF
    SHOWINT AX
    PRINT CRLF

    ; Product
    MOV AX, N1
    MUL BX
    PRINT PRO
    SHOWINT AX
    PRINT CRLF

    ; Division
    MOV AX, N1
    DIV BX
    PRINT DVQ
    SHOWINT AX
    PRINT CRLF
    PRINT DVR
    SHOWINT DX
    PRINT CRLF

    EXIT
CODE ENDS
END START