TITLE DNAME (.EXE)
        .MODEL SMALL
        .386
        .STACK 64
        .DATA
PARLIST LABEL BYTE
MLEN    DB    20
ALEN    DB    ?
KNAME   DB    21 DUP(' ')
MSG     DB    'NAME? ','$'
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        CALL CLEAR
A20:    MOV DX,0000
        CALL SETCUR
        CALL INPUT
        CALL CLEAR
        CMP ALEN,00
        JE A30
        CALL CENTER
        CALL DISP
        JMP A20
A30:    MOV AX,4C00H
        INT 21H
MAIN ENDP

INPUT PROC NEAR
        PUSH AX
        PUSH DX
        MOV AH,09H
        LEA DX,MSG
        INT 21H
        MOV AH,0AH
        LEA DX,PARLIST
        INT 21H
        POP DX
        POP AX
        RET
INPUT ENDP

CENTER PROC NEAR
        MOVZX BX,ALEN
        MOV KNAME[BX],07
        MOV KNAME[BX+1],'$'
        MOV DL,ALEN
        SHR DL,1
        NEG DL
        ADD DL,40
        MOV DH,12
        CALL SETCUR
        RET
CENTER ENDP

DISP PROC NEAR
        MOV AH,09H
        LEA DX,KNAME
        INT 21H
        RET
DISP ENDP

CLEAR PROC NEAR
        PUSHA
        MOV AX,0600H
        MOV BH,24
        MOV CX,0000
        MOV DX,184FH
        POPA
        RET
CLEAR ENDP

SETCUR PROC NEAR
        MOV AH,02H
        MOV BH,00
        INT 10H
        RET
SETCUR ENDP
END MAIN
