STACK SEGMENT
STACK ENDS

COUNT EQU 100

DATA SEGMENT
      MSG DB "Enter a string: $"
      SUC DB "Palindrome!$"
      FAL DB "Not palindrome!$"
      BUF DB 100 DUP(?)
      LEN DW 0
DATA ENDS

EXIT MACRO
      MOV AH, 4CH
      INT 21H
ENDM

PRINT MACRO POS
      PUSH DX
      PUSH AX
      MOV DX, OFFSET POS
      MOV AH, 09H
      INT 21H
      POP AX
      POP DX
ENDM

CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACK
START:
      MOV AX, DATA
      MOV DS, AX
      PRINT MSG
      MOV SI, 0
      MOV BP, OFFSET BUF
ITER: MOV AH, 01H
      INT 21H
      CMP AL, 13
      JE DONE
      MOV [BP+SI], AL
      INC SI
      JMP ITER

DONE: MOV AX, SI
      MOV cx, 2
      DIV cx
      MOV BX, AX
      MOV CX, AX
      MOV DI, 0
COPY: MOV AL, [BP+DI]
      CBW
      PUSH AX
      INC DI
      LOOP COPY

      CMP DX, 0
      JE EVN
      INC DI
      MOV CX, BX
EVN:  POP AX
      CMP AL, [BP+DI]
      JNE NP
      INC DI
      LOOP EVN
      PRINT SUC
      JMP STOP
NP:   PRINT FAL
STOP: EXIT
CODE ENDS
END START
