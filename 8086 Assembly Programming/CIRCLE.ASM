TITLE CIRCLE(.EXE)
        .MODEL SMALL
        .STACK 64
        .DATA
CNT DB 10
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
       ; CALL CLEAR
        MOV AX,0013H
        INT 10H
        MOV DX,50
        MOV CX,60

A10:    MOV AH,0CH
        MOV AL,03
        MOV BH,00
        INT 10H
        SUB DX,01
      ;  ADD CX,01
        MOV AH,0CH
        INT 10H
       ; SUB DX,01
        ADD CX,01
        MOV AH,0CH
        INT 10H
        MOV AH,0CH
        INT 10H
        SUB DX,01
        ADD CX,01
        MOV AH,0CH
        INT 10H
       ; SUB DX,01
        ADD CX,01
        MOV AH,0CH
        INT 10H
        
     ;   MOV AH,10H
      ;  INT 16H
       ; CMP AL,1BH
       ; JE A20
        DEC CNT
       CMP CNT,00H
        JNE A10
A20:    MOV AX,4C00H
        INT 21H
MAIN ENDP
CLEAR PROC NEAR
        MOV AX,0600H
        MOV BH,24h
        MOV CX,0000
        MOV DX,184FH
        INT 10H
        RET
CLEAR ENDP
        END MAIN

