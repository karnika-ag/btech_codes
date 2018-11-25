TITLE CAR (.EXE)
        .MODEL SMALL
        .386
        .STACK 64
        .DATA
C1      DB ?
C2      DB ?
D1      DB ?
D2      DB ?
P       DW ?
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        CALL QSCROLL
        MOV AX,1003H
        MOV BL,00
        INT 10H
        MOV AL,03H
        MOV BH,24H
        MOV CX,0E00H
        MOV DX,164FH
        CALL HSCROLL
        MOV P,00H
        
A10:    MOV AH,13H
        MOV AL,02H
        MOV BH,00
        MOV BL,17H
        MOV CX,04H
        MOV DX,0D01H
        INT 10H
       ; JB A10
      
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
