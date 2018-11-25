TITLE VID2 (.EXE)
        .MODEL SMALL
        .STACK 64
        .DATA
STR1    DB 'PAGE1','$'
STR2    DB 'PAGE2','$'
STR3    DB 'PAGE3','$'
STR4    DB 'PAGE4','$'
ARR     DB 5 DUP(?),'$'
PG      DB 00
CNT     DW 0
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX

        MOV ARR,01H
        MOV ARR+1,02H
        MOV ARR+2,03H
        MOV ARR+3,04H
        MOV ARR+4,05H
        LEA SI,ARR
A10:    INC CNT 
        MOV AH,05H
        MOV AL,PG
        INT 10H
        
B10:    CALL CLEAR
        MOV AH,09H
        MOV AL,'*'
        MOV BH,PG
        MOV BL,1EH
        MOV CX,CNT
        INT 10H
        mov ah,10h
        int 16h
    


        INC PG
        CMP PG,05
        JB A10


        MOV AX,4C00H
        INT 21H
MAIN ENDP

CLEAR PROC NEAR
        MOV AX,0600H
        MOV BH,16H
        MOV CX,0000
        MOV DX,184FH
        INT 10H
        RET
CLEAR ENDP

END MAIN
