NAME "BUBBLE-SORT"
; init mem with sample data
MOV [2000H], 00AH
MOV [2001H], 000H
MOV [2002H], 0C8H
MOV [2003H], 0ECH
MOV [2004H], 094H
MOV [2005H], 052H
MOV [2006H], 0C9H
MOV [2007H], 009H
MOV [2008H], 02CH
MOV [2009H], 0B2H
MOV [200AH], 09EH
MOV [200BH], 005H
MOV [200CH], 02EH
MOV [200DH], 02FH
MOV [200EH], 09EH
MOV [200FH], 01EH
MOV [2010H], 0B8H
MOV [2011H], 0C1H
MOV [2012H], 0BEH
MOV [2013H], 0C2H
MOV [2014H], 067H
MOV [2015H], 002H
; sample ends

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