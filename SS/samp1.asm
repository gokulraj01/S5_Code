CODE    START   1000
        LDA     12
TESTSTR BYTE    C'HELLO WORLD, GOOD DAY'

. Comment line eg
ADLINE  ADD     X'8A'
        STA     2000
        JSUB    TESTLAB
        END     1000

TESTLAB LDB     100
        STB     277
        RSUB