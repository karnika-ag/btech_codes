TITLE SAVER (.EXE)
        .MODEL SMALL
        .386
        .STACK 64
        .DATA
ARR     DB 5 DUP(?),'$'
C1      DB 0
C2      DB ?
D1      DB ?
D2      DB ?
P       DW ?
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        LEA SI,ARR
        MOV ARR,01H
;        INC SI

        MOV ARR+1,24H
 ;       INC SI
        MOV ARR+2,36H
  ;      INC SI
        MOV ARR+3,23H
   ;     INC SI
        MOV ARR+4,41H
    ;    INC SI



        LEA SI,ARR
A20:    CALL QSCROLL
        MOV BH,[SI]
        MOV AL,0DH
        MOV CX,0505H
        MOV DX,1348H
        CALL HSCROLL
        MOV P,1000
A10:    PUSH P
        MOV P,1000
A30:    DEC p
        jnz A30
        POP p
        dec p
        jnz a10
        INC SI
        INC C1
;        MOV AH,07H
;        INT 10H
        CMP C1,05H
        JNE A20

        MOV AX,4C00H
        INT 21H
MAIN ENDP

QSCROLL PROC NEAR
        MOV AX,0600H
        MOV BH,17H
        MOV CX,0000
        MOV DX,184FH
        INT 10H
        RET
QSCROLL ENDP

HSCROLL PROC NEAR
        MOV AH,06H
        INT 10H
        RET
HSCROLL ENDP
END MAIN

