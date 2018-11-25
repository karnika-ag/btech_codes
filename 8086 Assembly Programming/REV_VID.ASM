TITLE REVVID (.EXE)
        .MODEL SMALL
        .386
        .STACK 64
        .DATA
PAR     LABEL BYTE
ML      DB 20
ACL     DB ?
KNAME   DB 20 DUP(' ')
LEFTC   EQU 51
BOTS    EQU 23
ATTR    DB 00
COL     DB 05
ROW     DB 00
PROM    DB 'NAME? '

        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        MOV AX,1003H
        MOV BL,00
        INT 10H
        MOV AL,00H
        CALL QSCROLL
A20:    MOV COL,05
        CALL BPROM
        CALL INPUT
        CMP ACL,00
        JE A30
        CALL DNAME
        JMP A20
A30:    MOV AL,00H
        CALL QSCROLL
        MOV AX,4C00H
        INT 21H
MAIN ENDP

BPROM PROC NEAR
        MOV ATTR,71
        LEA BP,PROM
        MOV CX,06
        CALL DISP
        RET
BPROM ENDP

INPUT PROC NEAR
        MOV AH,0AH
        LEA DX,PAR
        INT 21H
        RET
INPUT ENDP

DNAME PROC NEAR
        PUSHA
        MOV AL,ML
        SUB AL,ACL
        MOV COL,AL
        MOV ATTR,17H
        LEA BP,KNAME
        MOVZX CX,ACL
        CALL DISP
        CMP ROW,BOTS
        JAE D30
        INC ROW
        JMP D90
D30:    MOV AL,01H
        CALL QSCROLL
D90:    POPA
        RET
DNAME ENDP

DISP PROC NEAR
        PUSHA
        MOV AH,13H
        MOV AL,01
        MOV BH,00
        MOV BL,ATTR
        MOV DH,ROW
        MOV DL,COL
        INT 10H
        POPA
        RET
DISP ENDP

QSCROLL PROC NEAR
        PUSHA
        MOV AH,06H
        MOV BH,86H
        MOV CX,0000
        MOV DX,184FH
        INT 10H
        POPA
        RET
QSCROLL ENDP
END MAIN

