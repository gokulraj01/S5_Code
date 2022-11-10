NAME "32BIT-MULTIPLIER"
;           [2000..1]  [2002..3]
;         X [2004..5]  [2006..7]
;           ____________________
; [2010..11][2012..13][2014..15][2016..17]

; PRELOAD MEMORY
MOV W.[2000H], 1122H
MOV W.[2002H], 3344H
MOV W.[2004H], 5566H
MOV W.[2006H], 7788H
         
         
        MOV DI, 2010H

        ; low  *  low
        MOV AX, [2002H]
        MUL WORD PTR [2006H]
        MOV [DI+6], AX
        MOV [DI+4], DX
        
        ; high * low
        MOV AX, [2000H]
        MUL WORD PTR [2006H]
        ADD [DI+4], AX
        MOV [DI+2], DX
        JNC SKIP1
        INC WORD PTR [DI+2]
        
        ; high * high
SKIP1:  MOV AX, [2002H]
        MUL WORD PTR [2004H]
        ADD [DI+4], AX
        JNC SKIP2
        INC WORD PTR [DI+2]
        SKIP2: ADD [DI+2], DX
        JNC SKIP3
        INC WORD PTR [DI]
        
        ; low  * high
SKIP3:  MOV AX, [2000H]
        MUL WORD PTR [2004H]
        ADD [DI+2], AX
        JNC SKIP4
        INC WORD PTR [DI]
SKIP4:  ADD [DI], DX
        
        HLT