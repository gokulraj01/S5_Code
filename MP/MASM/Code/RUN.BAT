@ECHO OFF
MASM %1.ASM %1.OBJ;

IF EXIST %1.OBJ LINK %1.OBJ;
IF NOT EXIST %1.OBJ GOTO :ERR1

IF NOT EXIST %1.EXE GOTO :ERR2

:START
    CLS
    %1.EXE
    DEL %1.OBJ
    DEL %1.EXE
    GOTO :EOF

:ERR1
    ECHO Assembly failed...
    GOTO :EOF

:ERR2
    ECHO Linking failed...
    GOTO :EOF

:EOF