.MODEL SMALL

.STACK 64
.DATA
X1 DW 50
Y1 DW 50
C DW 100
D DW 100
F DW ?  
CUBE  DB '   CUBE   '
      DB ' TOP VIEW ' 
      DB ' SIDE VIEW'
.CODE
MAIN PROC NEAR
    MOV AX,@DATA
    MOV DS,AX
    MOV ES,AX
    
    
    
    
    MOV AH,00 
    MOV AL,12H
    MOV BH,24H
    INT 10H
    CALL INFO
    CALL DRAW1
    CALL DRAW2
    CALL DRAW5
    
    
    MOV CX,4C00H
    INT 21H
    MAIN ENDP  

DRAW1 PROC NEAR

       PUSHA
       MOV F,100
       MOV X1,50
       MOV Y1,50 
       
       MOV AH,0CH
       MOV AL,08H
       A20:
       
       MOV CX,X1
       MOV DX,Y1
       INT 10H
       ADD DX,100
       INT 10H
       ADD CX,50
       SUB DX,50
       INT 10H          
       ADD DX,100
       INT 10H
       ADD CX,200
       INT 10H
       SUB DX,100
       INT 10H
       ADD CX,200
       INT 10H 
       ADD DX,100
       INT 10H
         
       INC X1
       DEC F
       JNZ A20
       POPA
       RET
       DRAW1 ENDP
DRAW2 PROC NEAR
       PUSHA    
       
       MOV X1,50
       MOV Y1,50
       
       MOV F,100
       MOV AH,0CH
       MOV AL,08H
       
       A21:
      
       MOV CX,X1
       MOV DX,Y1
       INT 10H
       ADD CX,100
       INT 10H 
       ADD DX,50
       ADD CX,50
       INT 10H  
       SUB CX,100
       INT 10H
       ADD CX,200
       INT 10H
       ADD CX,100
       INT 10H 
       ADD CX,100
       INT 10H
       ADD CX,100
       INT 10H 
       
       INC Y1
       DEC F
       JNZ A21 
       POPA
       RET
DRAW2 ENDP

DRAW5 PROC NEAR
       PUSHA    
       
       MOV X1,50
       MOV Y1,50
       
       MOV F,50 
       MOV AH,0CH
       MOV AL,08H
       A25:
       
       MOV CX,X1
       MOV DX,Y1
       INT 10H
       ADD CX,100
       INT 10H  
       ADD DX,100
       INT 10H         
       SUB CX,100
       INT 10H 
    
       INC Y1 
       INC X1
       DEC F
       JNZ A25 
       POPA
       RET
DRAW5 ENDP      

INFO PROC NEAR
    
    
    
    MOV AX,1301H
    MOV BH,00
    MOV BL,24H
    LEA BP,CUBE
    MOV CX,10
    MOV DH,3
    MOV DL,0
    MOV F,3
    A1:
    INT 10H 
    ADD BP,10
    ADD DL,15
    DEC F
    JNZ A1
     RET
 INFO ENDP   
END MAIN    
            
