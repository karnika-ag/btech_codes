CODE SEGMENT
        ASSUME CS:CODE,DS:CODE,ES:CODE
        ORG 100H
START : JMP BEGIN
        KB_IP DD ?
TM      DW ?,'$'
X       DB 0AH
P       DW ?
HRS      DB ?,'$'
MN      DB ?,'$'
SC      DB ?,'$'
HA      DB 3 DUP(' '),'$'
MA      DB 3 DUP(' '),'$'
SA      DB 3 DUP(' '),'$'
CNT     Dw ?
BEEP    DW 007H,'$'
              CHAR DB ?
               
 
KB:
		MOV AX,CS
        MOV DS,AX
        MOV ES,AX
        jmp f10
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
      ;  PUSHA
        MOV AH,02H
        MOV BH,00
        MOV DX,0500H
        INT 10H
      ;  POPA
        RET
SETCUR ENDP
          disp proc near

        mov bl,x
        MOV Cnt,500
       
A10:     MOV AH,2CH
        INT 21H
        MOV HRS,CH
        MOV MN,CL
        MOV SC,DH
       
        MOV P,300
A40:    PUSH P
        MOV P,300
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
      ret
disp ENDP

f10:                IN AL,60H
		CMP AL,01
		JNE KB_END
                call disp
                jmp kb_end

KB_END :	 
		 
JMP DWORD PTR CS:KB_IP
 
BEGIN:
        MOV AX,CS
        MOV DS,AX
        MOV ES,AX
   
        MOV AH,35H
        MOV AL,09H
        INT 21H
 
       MOV WORD PTR KB_IP,BX
        MOV WORD PTR KB_IP+2,ES
 
        MOV AH,25H
        MOV AL,09H
        MOV DX,OFFSET KB
        INT 21H
 
        MOV AH,31H
        MOV DX,OFFSET BEGIN
        INT 21H
 
CODE ENDS
END START
