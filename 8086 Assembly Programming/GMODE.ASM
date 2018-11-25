TITLE GMODE(.EXE)
        .MODEL SMALL
        .286
        .STACK 64
        .DATA
STRG     DB '1234567890'

        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        MOV AH,0FH
        INT 10H
        PUSH AX
        CALL BMODE
        CALL SCROLL
        CALL DSTR
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
        MOV AH,00H
        MOV AL,12H
        INT 10H
        MOV AH,0BH
        MOV BH,00
        MOV BL,07H
        INT 10H
        RET
BMODE ENDP

SCROLL PROC NEAR
        PUSHA
        MOV AX,0605H
        MOV BH,1110B
        MOV CX,0000H
        MOV DX,044FH
        INT 10H
        POPA
        RET
SCROLL ENDP

DSTR PROC NEAR
        PUSHA
        MOV AX,1301H
        MOV BX,00021H
        LEA BP,STRG
        MOV CX,10
        MOV DX,0815H
        INT 10H
        POPA
        RET
DSTR ENDP

DISP PROC NEAR
        PUSHA
        MOV AX,0A01H
        MOV BH,00
        MOV BL,0100B
        MOV CX,10
        INT 10H
        POPA
        RET
DISP ENDP
END MAIN
