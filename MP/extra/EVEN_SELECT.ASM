NAME "EVEN-ARR-SELECT"

MOV WORD PTR [2000H], 0005H
MOV WORD PTR [2002H], 0001H
MOV WORD PTR [2004H], 0002H
MOV WORD PTR [2006H], 000AH
MOV WORD PTR [2008H], 0004H
MOV WORD PTR [200AH], 0005H

; source and destination pointers
        MOV CX, [2000H]
        MOV BX, 0000H
        MOV SI, 2002H
        MOV DI, 2012H

ITER:   MOV AX, [SI]
        TEST AX, 0001H  ; even if last bit is 0
        JNZ ODD
        MOV [DI], AX    ; store even word at di
        ADD DI, 2
        INC BX        
ODD:    ADD SI, 2
        LOOP ITER
        MOV [2010H], BX ; store length of dest arr
        HLT