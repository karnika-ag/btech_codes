.MODEL SMALL
.STACK 256
.DATA
 
CIRCLEY  DB 0,4,6,7,8,8,9,9,9,9,10,9,9,9,9,8,8,7,6,4,0
;CIRCLE2Y DB 0 ,2,5 ,7,9,10,11,12,12,13,13,14,14,14,14,15,14 ,14,14,14,14,13,12,12,11,10,9,7,5,2,0 
CIRCLE2Y DB  0,2,3,4,6,7,8,8,9,9,9,9,10,9,9,9,9,8,8,7,6,4,3,2,0,0,0 

X1       DW 100
X2       DW 50 
X        DW 26
X3       DW 26
Z        DW ? 
Z1       DW 100
Z2       DW 50
Z3       DW 26
CNT      DW 5
F        DW  ?
.CODE 
MAIN PROC NEAR
MOV AX,@DATA
MOV DS,AX


 
A27: 

CALL CLEAR 
MOV  F,21
CALL DRAWCIRCLE 
MOV  F,5
CALL DRAWSIDE1
MOV  F,22
CALL DRAWBOTTOM1 
MOV  F,25
CALL DRAWCIRCLE2
MOV  F,25
CALL DRAWBOTTOM1 
MOV  F,25
CALL DRAWCIRCLE2
MOV  F,35
CALL DRAWBOTTOM1
MOV  F,15
CALL DRAWROOF2
MOV  F,85 
CALL DRAWROOF3
MOV  F,32
CALL DRAWROOF4
MOV  F,4
CALL DRAWFONT 

ADD Z1,5
ADD Z2,5
ADD Z3,5 
MOV AX,Z1
MOV X1,AX
MOV AX,Z2
MOV X2,AX 
MOV AX,Z3
MOV X,AX
MOV X3,AX 

CALL DELAY
JMP A27 
 
 MOV AX,4C00H
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
    MOV F,31
    RET
    DRAWCIRCLE ENDP 



DRAWCIRCLE2 PROC NEAR
      
      
    MOV BX,00 
    A21:
    
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X
    MOV DX,135 
    SUB DL,CIRCLE2Y[BX]
    INT 10H  
    INC X
    INC BX 
    DEC F
    JNZ A21
    RET
    DRAWCIRCLE2 ENDP
     
     
DRAWBOTTOM1 PROC NEAR 
      
    A22:
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X 
    MOV DX,137
    INT 10H
    INC X
    DEC F
    JNZ A22 
    RET
DRAWBOTTOM1 ENDP  

DRAWSIDE1 PROC NEAR
     
     MOV Z,137
     
    A23:
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X 
    MOV DX,Z
    DEC Z
    INT 10H
    DEC F
    JNZ A23
    RET
DRAWSIDE1 ENDP

DRAWROOF2 PROC NEAR
        
    MOV Z,132    
    A24:
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X3 
    MOV DX,Z
    INT 10H
    SUB Z,2
    INC X3
    DEC F
    JNZ A24
    RET
DRAWROOF2 ENDP      

DRAWROOF3 PROC NEAR
    
    A25:
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X3 
    MOV DX,Z
    INT 10H
    INC X3
    DEC F
    JNZ A25
    RET
DRAWROOF3 ENDP 

DRAWROOF4 PROC NEAR
    
    A26:
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X3 
    MOV DX,Z
    INT 10H
    INC X3 
    INC Z
    DEC F
    JNZ A26
    RET
DRAWROOF4 ENDP 

DRAWFONT PROC NEAR
    
    A28:
    MOV AH,0CH
    MOV AL,05
    MOV BH,00
    MOV CX,X3 
    MOV DX,Z
    INT 10H 
    INC Z 
    DEC F
    JNZ A28
    RET
DRAWFONT ENDP 
 
CLEAR PROC NEAR
    
    
    
    MOV AH,00
    MOV AL, 13h
    INT 10H 
    
    RET
CLEAR ENDP

DELAY PROC NEAR

MOV DX,2
A70 :  
MOV CX,2
A200:
LOOP A200
DEC DX
JNZ A70

RET
DELAY ENDP 
 
END MAIN
