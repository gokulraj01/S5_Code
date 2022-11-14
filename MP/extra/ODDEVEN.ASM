NAME "ODD-EVEN"

MOV WORD PTR [2000H], 1235H
        
        MOV CL, 00H               
        MOV AX, [2000H]
        TEST AX, 0001H  ; even if last bit is 0
        JZ EVEN
        MOV CL, 01H     ; else set flag as odd
EVEN:   MOV [2010H], CL
        HLT