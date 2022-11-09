NAME "BIT-MANIPULATION"

MOV W.[2000H], 1122H
MOV W.[2002H], 3344H

MOV DX, [2000H]
MOV BX, [2002H]

; AND operation
MOV AX, DX
AND AX, BX
MOV [2004H], AX  

; OR operation
MOV AX, DX
OR AX, BX
MOV [2006H], AX

; NOT operation
MOV AX, DX
NOT AX
MOV [2008H], AX

; XOR operation
MOV AX, DX
XOR AX, BX
MOV [200AH], AX

HLT