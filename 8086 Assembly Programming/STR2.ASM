TITLE STRNG2(.EXE)
        .MODEL SMALL
        .STACK 64
        .DATA
MSG     DB 10 DUP(?),'$'
STR1    DB 'COMPUTER'
STR2    DB 'PUTR'
CNT     DB 0
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
A20:    INC SI
        INC CNT
        MOV AL,[SI]
        CMP CNT,03
        JE A40
        REPNE SCASB
        JE A20

        MOV MSG,'N'
        JMP A50
A40:    MOV MSG,'Y'
A50:    MOV AH,09H
        LEA DX,MSG
        INT 21H

        MOV AX,4C00H
        INT 21H
MAIN ENDP
END MAIN
