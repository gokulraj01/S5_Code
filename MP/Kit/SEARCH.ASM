; Author: Gokul Raj, 235, R5A
NAME "LINEAR-SEARCH"
        MOV AX, [3000H]
        MOV BP, 2002H
        MOV CX, [2000H]
        MOV SI, 0000H
; iterate until end of array        
ITER:   CMP AX, [SI+BP]
        JE FOUND
        ADD SI, 2
        LOOP ITER
; not found, so store 0 and end        
        MOV [3002H], 00H
        MOV [3003H], 00H
        HLT
; when found, store location and end   
FOUND:  ADD BP, SI
        MOV [3002H], BP
        HLT
