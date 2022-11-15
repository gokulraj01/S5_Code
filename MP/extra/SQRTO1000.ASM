NAME "SQR-UPTO-1000"
        MOV SI, 2002H   ; arr dest ptr
        MOV CX, 0001H   ; for arr length and n
        
ITER:   MOV AX, CX
        MUL CX
        CMP AX, 3E8H     ; compare square to 1000
        JA  STOP
        INC CX          ; next number
        
        MOV [SI], AX    ; store current result
        ADD SI, 2
        JMP ITER

STOP:   DEC CX
        MOV [2000H], CX ; store length
        HLT
