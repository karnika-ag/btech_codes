
TITLE CAR2 (.EXE)
        .MODEL SMALL
        .386
        .STACK 64
        .DATA
C1      DB ?
C2      DB ?
D1      DB ?
D2      DB ?

A1      DB ?
A2      DB ?
B1      DB ?
B2      DB ?

E1      DB ?
E2      DB ?
F1      DB ?
F2      DB ?

P       DW ?
X       DB 08H
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        MOV AX,1003H
        MOV BL,00
        INT 10H
        mov c1,0ah
        mov c2,01h
        mov d1,0eh
        mov d2,09h
        MOV A1,0EH
        MOV A2,02H
        MOV B1,10H
        MOV B2,03H
A30:    CALL QSCROLL
        MOV AL,03H
        MOV BH,24H
        MOV CX,0c00H
        MOV DX,124FH
        CALL HSCROLL
        
        MOV CH,C1
        Mov cl,c2
        mov dh,d1
        mov dl,d2

        MOV BH,86H
        MOV AL,04H
        CALL HSCROLL

;        MOV CH,A1
 ;       Mov cl,A2
  ;      mov dh,B1
   ;     mov dl,B2

    ;    MOV BH,86H
     ;   MOV AL,04H
      ;  CALL HSCROLL

        MOV P,10
A10:    PUSH P
        MOV P,50
A20:    DEC p
        jnz A20
        POP p
        dec p
        jnz a20

        add c2,X
        add d2,X
      ;  ADD A2,
        MOV C1,CH
        MOV C2,CL
        MOV D1,DH
        MOV D2,DL

        cmp d2,4fh
        jb a30

        
      
       
      
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
