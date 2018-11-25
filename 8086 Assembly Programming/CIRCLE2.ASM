TITLE CIRCLE2(.EXE)
        .MODEL SMALL
        .STACK 64
        .DATA
CIRCLEY  DB 0,4,6,7,8,8,9,9,9,9,10,9,9,9,9,8,8,7,6,4,0
;CIRCLE2Y DB 0 ,2,5 ,7,9,10,11,12,12,13,13,14,14,14,14,15,14 ,14,14,14,14,13,12,12,11,10,9,7,5,2,0 
CIRCLE2Y DB  0,2,3,4,6,7,8,8,9,9,9,9,10,9,9,9,9,8,8,7,6,4,3,2,0,0,0 

X1       DW 300
X2       DW 50 
X        DW 26
X3       DW 26
Z        DW ? 
Z1       DW 100
Z2       DW 50
Z3       DW 26
CNT      DW 5
P       DW  ?
f       dw ?
.CODE 
MAIN PROC NEAR
MOV AX,@DATA
MOV DS,AX


 
A27: 
 mov f,21
CALL CLEAR 

CALL DRAWCIRCLE 
call delay
mov ax,x1
sub ax,42
mov x1,ax
dec cnt
jnz a27
A30: MOV AX,4C00H
 INT 21H
 MAIN ENDP

DRAWCIRCLE PROC NEAR
  
    MOV BX,00 
    A20:
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X1 
    MOV DX,0000
    MOV DL,CIRCLEY[BX]
    ADD DX,140  
    INT 10H  
    
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X1 
    MOV DX,0140
    SUB DL,CIRCLEY[BX] 
    INT 10H
    
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X2 
    MOV DX,0000
    MOV DL,CIRCLEY[BX]
    ADD DX,140  
    INT 10H  
    
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X2 
    MOV DX,0140
    SUB DL,CIRCLEY[BX] 
    INT 10H
         
    INC X1
    INC X2  
    INC BX 
    DEC F
    JNZ A20 
  

    RET
    DRAWCIRCLE ENDP

CLEAR PROC NEAR
        MOV AH,00
        MOV AL,13H
        INT 10H
        RET
CLEAR ENDP
delay PROC NEAR
        MOV DX,1000
        A70:MOV CX,1000
        A80:LOOP A80
        DEC DX
        JNZ A70
        RET
DELAY ENDP
    END MAIN
