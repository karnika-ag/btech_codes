TITLE STRSORT (.EXE)
        .MODEL SMALL
        .STACK 64
        .DATA
TMP     DB 4 DUP(' '),'$'
STR2    DB 'NEHA','$'
STR1    DB 'NISH','$'
STR3    DB 'GAUR','$'
STR4    DB 'VARS','$'
MSG     DB 2 DUP(?),'$'
CNT     DW 01H
CNT2    DW 00H
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        CLD
A40:
A50:    
        MOV CX,4
        LEA DI,STR1
        LEA SI,STR2
        REPE CMPSB
        JNE A10

A10:    
        JG A20
        MOV MSG,'N'
        JMP A60
A20:    MOV MSG,'Y'
        JMP A70

        
A60:    CLD
        MOV CX,04
        LEA SI,STR1
        LEA DI,TMP
        REP MOVSB
        
        MOV CX,04
        LEA SI,STR2
        LEA DI,STR1
        REP MOVSB
        MOV CX,04
        LEA SI,TMP
        LEA DI,STR2
        REP MOVSB


A70:;     INC CNT2
     ;    mov cx,cnt2
      ;   CMP CX,CNT
       ;  JB A50
        ; DEC CNT
     ;    CMP CNT,00H
      ;   JAE A40
A30:    MOV AH,09H
        LEA DX,MSG
        INT 21H
        MOV AH,09H
        LEA DX,STR1
        INT 21H

        MOV AH,09H
        LEA DX,STR2
        INT 21H


        MOV AX,4C00H
        INT 21H

MAIN ENDP
END MAIN
