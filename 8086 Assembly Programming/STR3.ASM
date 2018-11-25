TITLE STRNG3(.EXE)
        .MODEL SMALL
        .STACK 64
        .DATA
MSG     DB 10 DUP(?),'$'
STR1    DB 'COMPUTER','$'
STR2    DB 'PUTE'
STR3    DB 'ABCD'
CNT     DB 0
beep    dw 007,'$'
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        
        LEA SI,STR2
        CLD
A10:
        MOV AL,[SI]
        MOV CX,8
        LEA DI,STR1
        REPNE SCASB
        JE A20
A20:    DEC DI
        MOV CX,4
        LEA SI,STR3
        REP MOVSB

        MOV AH,09H
        LEA DX,STR1
        INT 21H
         mov ah,09h
         lea dx,beep
         int 21h
        MOV AX,4C00H
        INT 21H
MAIN ENDP
END MAIN
