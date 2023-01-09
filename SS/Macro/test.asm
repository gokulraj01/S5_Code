SUM     MACRO A,B
        LDA A
        ADD B
MEND

PROG    START 1000
        LDA 100
        SUM 100,200
        STA 300
END     1000