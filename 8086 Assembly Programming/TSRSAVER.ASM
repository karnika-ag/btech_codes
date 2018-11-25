CODE SEGMENT
        ASSUME CS:CODE,DS:CODE,ES:CODE
        ORG 100H
START : JMP BEGIN
        KB_IP DD ?  
       ; KB_CS DW ?
         
		CHAR DB ?
                
ARR     DB 5 DUP(?),'$'
C1      DB 0
C2      DB ?
D1      DB ?
D2      DB ?
P       DW ?
 
KB:
		MOV AX,CS
        MOV DS,AX
        MOV ES,AX 
		IN AL,60H
		CMP AL,01
		JNE KB_END
                call disp
                jmp kb_end
disp proc near
        LEA SI,ARR
        MOV ARR,01H
;        INC SI

        MOV ARR+1,24H
 ;       INC SI
        MOV ARR+2,36H
  ;      INC SI
        MOV ARR+3,23H
   ;     INC SI
        MOV ARR+4,41H
    ;    INC SI



        LEA SI,ARR
A20:    CALL QSCROLL
        MOV BH,[SI]
        MOV AL,0DH
        MOV CX,0505H
        MOV DX,1348H
        CALL HSCROLL
        MOV P,1000
A10:    PUSH P
        MOV P,1000
A30:    DEC p
        jnz A30
        POP p
        dec p
        jnz a10
        INC SI
        INC C1
;        MOV AH,07H
;        INT 10H
        CMP C1,05H
        JNE A20

        ret
        disp ENDP

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
