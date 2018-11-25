TITLE DVD (.EXE)
        .MODEL SMALL
        .STACK 64
VIDSEG SEGMENT AT 0B900H
VIDAREA DB 1000H DUP(?)
VIDSEG ENDS
.286
        .CODE
MAIN PROC FAR
        MOV AX,VIDSEG
        MOV ES,AX
        ASSUME ES:VIDSEG
        MOV AH,0FH
        INT 10H
        PUSH AX
        PUSH BX
        MOV AX,0003H
        INT 10H
        MOV AX,0501H
        INT 10H
;        CALL DISP
        MOV AH,10H
        INT 16H
        MOV AH,05H
        POP BX
        MOV AL,BH
        INT 10H
        POP AX
        MOV AH,00H
        INT 10H
        MOV AX,4C00H
        INT 21H
MAIN ENDP
END MAIN
