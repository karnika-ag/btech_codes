TITLE PERSVIEW (.EXE)
.MODEL SMALL

.STACK 64
.DATA
X1 DW 50
Y1 DW 50
C DW 100
D DW 100
F DW ?  

.CODE
MAIN PROC NEAR
    MOV AX,@DATA
    MOV DS,AX
    MOV ES,AX
    
    
    
    
    MOV AH,00 
    MOV AL,12H
    MOV BH,71H
    INT 10H

    CALL DRAW1
    CALL DRAW2
   
    
    
    MOV aX,4C00H
    INT 21H
    MAIN ENDP  

DRAW1 PROC NEAR

       PUSHA 
       MOV AH,0CH
       MOV AL,04
       MOV CX,50
       MOV DX,450
       
       A20:
       
       INT 10H
       DEC DX
       CMP DX,50
       JGE A20
       
       
       MOV CX,150
       MOV DX,450
       
       A22:
       
       INT 10H
       DEC DX
       CMP DX,150
       JGE A22
       
       MOV CX,250
       MOV DX,450
       A23:
       
       INT 10H          
       DEC DX
       CMP DX,250
       JGE A23 
       
       MOV CX,350
       MOV DX,450
       A24:
       INT 10H          
       DEC DX
       CMP DX,350
       JGE A24
    
       POPA
       RET
DRAW1 ENDP 

DRAW2 PROC NEAR
       PUSHA    
       
       MOV AH,0CH
       MOV AL,08H
       MOV CX,00
       MOV DX,450
       
       A21:
       INT 10H
       INC CX
       CMP CX,550
       JLE A21
       
       POPA
       RET
DRAW2 ENDP
END MAIN
    
