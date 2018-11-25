TITLE TIMING (.EXE)
        .MODEL SMALL
        .286
        .STACK 64
        .DATA
TM      DW ?,'$'
X       DB 0AH
P       DW ?
HRS      DB ?,'$'
MN      DB ?,'$'
SC      DB ?,'$'
HA      DB 3 DUP(' '),'$'
MA      DB 3 DUP(' '),'$'
SA      DB 3 DUP(' '),'$'
CNT     DB ?
BEEP    DW 007H,'$'
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX

        MOV AH,09H
        LEA DX,BEEP
        INT 21H

        mov bl,x
        MOV Cnt,50
       
A10:     MOV AH,2CH
        INT 21H
        MOV HRS,CH
        MOV MN,CL
        MOV SC,DH
       
        MOV P,1000
A40:    PUSH P
        MOV P,1000
A30:    DEC p
        jnz A30
        POP p
        dec p
        jnz a40

        CALL CLEAR
        CALL SETCUR
           LEA SI,HA+2
           MOV AL,HRS
           CBW
           CALL CNVRT
        MOV AH,09H
        LEA DX,HA
        INT 21H

         LEA SI,HA+2
        MOV AL,MN
        CBW
        CALL CNVRT
        MOV AH,09H
        LEA DX,HA
        INT 21H
         LEA SI,HA+2
        MOV AL,SC
        CBW
        CALL CNVRT
        MOV AH,09H
        LEA DX,HA
        INT 21H
         dec cnt
        JNZ A10
  ;      INC SI
   ;     LEA SI,HA
    ;    MOV CNT,02H
;    MOV AH,09H
    ;    LEA DX,[SI]
     ;   INT 21H
      ;  DEC CNT
      ;  JNZ A30
        

        MOV AX,4C00H
        INT 21H
MAIN ENDP
CLEAR PROC NEAR
        MOV AX,0600H
        MOV BH,07H
        MOV CX,0000
        MOV DX,184FH
        INT 10H
        RET
CLEAR ENDP

CNVRT PROC NEAR
A70:    DIV BL
        ADD AH,30H
        MOV [SI],AH
        DEC SI
        MOV AH,00H
        CMP AL,00H
        JNE A70
        INC SI
        RET
CNVRT ENDP
SETCUR PROC NEAR
        PUSHA
        MOV AH,02H
        MOV BH,00
        MOV DX,0500H
        INT 10H
        POPA
        RET
SETCUR ENDP
END MAIN

