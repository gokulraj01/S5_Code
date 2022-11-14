NAME "PRIME"
;MOV WORD PTR [2000H], 299BH
MOV WORD PTR [2000H], 1234H

; find approximate sqrt(x) by repeated subtraction
        MOV AX, [2000H]
        MOV CX, 0000H
        MOV BX, 0001H
ITER1:  SUB AX, BX
        ADD BX, 2
        INC CX
        CMP AX, 0
        JG ITER1

; compare until sqrt(x) in CX
        MOV BX, [2000H]
ITER2:  MOV DX, 0000H
        MOV AX, BX
        DIV CX
        CMP DX, 00H
        JE NOTPRI
        DEC CX
        CMP CX, 0001H
        JA ITER2
; reaching here means, prime
        MOV [2010H], 01H  
        HLT
NOTPRI: MOV [2010H], 00H
        HLT       
                

