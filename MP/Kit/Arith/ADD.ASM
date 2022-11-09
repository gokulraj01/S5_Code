NAME "ADDITION"
        MOV CX, 0000H
        MOV AX, [2000H]
        ADD AX, [2002H]
        JNC SKIP
        INC CX
SKIP:   MOV [2004H], CX
        MOV [2006H], AX
        HLT