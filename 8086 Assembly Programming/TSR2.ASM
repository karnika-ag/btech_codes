CODE SEGMENT
        ASSUME CS:CODE,DS:CODE,ES:CODE
        ORG 100H
START : JMP BEGIN
        KB_IP DD ?  
       ; KB_CS DW ?
         
		CHAR DB ?
		MSG DB 'YADUVIR SINGH$'
 
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
		MOV AH,09H
		LEA DX,MSG
		INT 21H
                ret
          disp endp

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
