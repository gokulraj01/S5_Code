NAME "ARRAY-ADDITION"
; initialize count and base index
        MOV CX, [2000H]
        MOV BP, 2002H

; clear registers
        MOV SI, 0000H     
        MOV AX, 0000H
        MOV DX, 0000H

; loop until array end
ITER:   ADD AX, [SI+BP]
        JNC SKIP
        INC DX
SKIP:   ADD SI, 2
        LOOP ITER

; store results       
        MOV [3000H], DX
        MOV [3002H], AX
        HLT
