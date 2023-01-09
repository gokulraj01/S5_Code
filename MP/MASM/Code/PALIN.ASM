STACK SEGMENT STACK
STACK ENDS

COUNT EQU 100

DATA SEGMENT
    PROMPT  DB "Enter a string: $"
    SUCCESS DB "Palindrome!!",10,13,"$"
    FAILURE DB "NOT palindrome!!",10,13,"$"
;10
    BUF DB COUNT DUP(?)
    BUFLEN DW 0
DATA ENDS

PRINT MACRO LOC
    MOV DX, OFFSET LOC
    MOV AH, 09H
    INT 21H
ENDM
;20
EXIT MACRO
    MOV AH, 4CH
    INT 21H
ENDM

INPUT MACRO LOC, LEN
LOCAL ITER, E
ITER: MOV BP, LOC    ; initialize base and index of buffer
      MOV SI, 0
      MOV AH, 01H    ; input a charecter
      INT 21H
      CMP AL, 13
      JEQ E
      MOV [BP+SI], AL
      INC SI
      CMP SI, COUNT
      JB ITER
E:    MOV LEN, SI
ENDM
;40
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACK
START:
      MOV AX, DATA
      MOV DS, AX

      PRINT PROMPT
      INPUT BUF, BUFLEN
    
ITER: MOV BP, BUF      ; push letters to stack
      MOV SI, 0
      MOV AL, [BP+SI]
      CBW
      PUSH AX
      INC SI
      CMP SI, BUFLEN
      JB ITER

NXTC:	MOV BP, BUF
      MOV SI, 0
      POP AX
      CMP AL, [BP+SI]
      JNE NP
      INC SI
      CMP SI, BUFLEN
      JB NXTC
	
	PRINT SUCCESS    ; reached here =>palindrome
      JMP STOP
      
NP:   PRINT FAILURE
      
STOP: EXIT
CODE ENDS
END START
