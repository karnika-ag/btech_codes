TITLE DPIX(.EXE)
        .MODEL SMALL
        .STACK 64
        .286
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        MOV AH,0FH
        INT 10H
        PUSH AX
        CALL BMODE
        CALL DISP
        MOV AH,10H
        INT 16H
        POP AX
        MOV AH,00H
        INT 10H
        MOV AX,4C00H
        INT 21H
MAIN ENDP

BMODE PROC NEAR
        MOV AX,0012H
        INT 10H
        MOV AH,0BH
        MOV BX,0007H
        INT 10H
        RET
BMODE ENDP

DISP PROC NEAR
        PUSHA
        MOV BX,00
        MOV CX,64
        MOV DX,70
C20:    MOV AH,0CH
        MOV AL,BL
        INT 10H
        INC CX
        CMP CX,576
        JNE C20
        MOV CX,64
        INC BL
        INC DX
        CMP DX,280
        JNE C20
        POPA
        RET
DISP ENDP
END MAIN
