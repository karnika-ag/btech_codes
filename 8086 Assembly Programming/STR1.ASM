TITLE STR1 (.EXE)
        .MODEL SMALL
        .386
        .STACK 64
        .DATA
ST1    DB '1234567890','$'
ST2    DB 10 DUP(' '),'$'
IND     EQU 24
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        CLD
        MOV CX,10
        LEA SI,ST2
        LEA DI,ST1
        REP MOVSW
        CALL CLEAR
        CALL SETCUR
        CALL DISP
        MOV AX,4C00H
        INT 21H
MAIN ENDP

CLEAR PROC NEAR
        MOV AX,0600H
        MOV BH,61H
        MOV CX,0000
        MOV DX,184FH
        INT 10H
        RET
CLEAR ENDP

SETCUR PROC NEAR
        MOV AH,02H
        MOV BH,00
        MOV DX,1000H
        ADD DL,IND
        INT 10H
        RET
SETCUR ENDP

DISP PROC NEAR
        MOV AX,1300H
        MOV BX,0016H
        LEA BP,ST1
        MOV CX,10
        MOV DX,1000H
        ADD DL,IND
        INT 10H
        RET
DISP ENDP
END MAIN
