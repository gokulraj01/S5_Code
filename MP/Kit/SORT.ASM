; Author: Gokul Raj, 235, R5A
NAME "BUBBLE-SORT"
        MOV AX, 0000H
        MOV BP, 2002H
        MOV CX, [2000H]
        MOV [1500H], CX ; iter variable -> i
        DEC CX
        
ITER1:  MOV SI, 0000H
        MOV [2020H], 01H ; done flag variable  

ITER2:  MOV BX, [SI+BP]
        MOV DX, [SI+BP+2]
        CMP BX, DX
        JB NOSWAP   
    ; swap values if left > right
        MOV [2020H], 00H
        MOV [SI+BP+2], BX
        MOV [SI+BP], DX
NOSWAP: ADD SI, 2
        LOOP ITER2
    
    ; if done, stop iterating    
        CMP [2020H], 01H
        JE STOP
        
        DEC [1500H]
        MOV CX, [1500H]
        JCXZ STOP
        JMP ITER1
STOP:   HLT
