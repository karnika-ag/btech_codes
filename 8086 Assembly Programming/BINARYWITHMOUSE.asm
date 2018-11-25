.MODEL SMALL
.STACK 64
.DATA
SUMP     DB 'SUM = : $'
SUBP     DB 'SUB = : $'
MULP     DB 'MUL = : $'         
DIVRR    DB 'RDR = : $'
DIVQ     DB 'QNT = : $' 
POWR     DB 'POW = : $' 
X1       DB  5
Y1       DB  4 
WIDTH    DB  20
HEIGHT   DB  2

F1X      DB 5,17,5,17,5,17, 5,17
F1Y      DB 8,8,12,12,16,16,20,20

F2X      DB 13,25,13,25,13,25,13,25
F2Y      DB 10,10,14,14,18,18,22,22

CURSX    DB  9,21,9,21,9,21,9,21
CURSY    DB  9,9,13,13,17,17,21,21 
L        DB  8
  
MSG      DB  '0','1','+','-','*','/','^','='
X        DW   ?
Y        DW   ? 
ACTULEN1 DB  0
KBNAME1  DB  21 DUP (' ')
             
ACTULEN2 DB  0
KBNAME2  DB 21 DUP(' ')  
CHS      DB 0
A        DW ?
B        DW ?
FACT     DW 2
R1       DB 16 DUP(?)
R2       DB 16 DUP(?)
F        DB ? 
Z        DB ? 
R11      DW ?
R12      DW ?
CNT      DB ?
S        DB 0 
.CODE

MAIN PROC NEAR

MOV AX,@DATA
MOV DS,AX
MOV ES,AX
CALL DRAW
CALL SETBUTTON
C3:
MOV AX,4C00H
INT 21H
MAIN ENDP

DRAW PROC NEAR
    
    
    MOV AX,0600H
    MOV BH,20H 
    MOV CL,4
    MOV CH,3
    MOV DH,23
    MOV DL,26   
    INT 10H
    
    MOV AX,0600H
    MOV BH,71H 
   
    MOV CL,X1
    MOV CH,Y1
   
    MOV DH,Y1
    ADD DH,HEIGHT
    MOV DL,X1  
    ADD DL,WIDTH 
    INT 10H
           
   ;-------------------------
   
    MOV SI,0000       
   
    A33:      
    MOV AX,0600H
    MOV BH,71H 
    MOV CL,F1X[SI]
    MOV CH,F1Y[SI]  
    MOV DL,F2X[SI]
    MOV DH,F2Y[SI]      
    INT 10H 
    
    
    MOV AX,0200H
    MOV BH,00   
    MOV DH,CURSY[SI]
    MOV DL,CURSX[SI]             
    INT 10H 
    
    MOV AH,02H
    MOV DL,MSG[SI]
    INT 21H  
    
    INC SI
    INC DI  
    
    DEC L
    JNZ A33 
        
    RET
DRAW ENDP     

SETBUTTON PROC NEAR
    PUSHA  
    ;MOUSE INSTALLED
    MOV AX,0000       
    INT 33H        
    MOV AX,01H
    INT 33H   
    A20:
    MOV AX,03H
    INT 33H
    CMP BX,1
    JNE A20
     
    ;DIVIDE BY 8 TO GET CO-ORDINATE
    SHR CX,03
    SHR DX,03        
    MOV X,CX
    MOV Y,DX
    CALL CALCULATION
    JMP A20
    POPA
    RET
SETBUTTON ENDP 
  
CALCULATION PROC NEAR
      PUSHA
      CALL CHOOSE
      
      CMP CHS,1
      JE  A1
      
      CMP CHS,2
      JE  A3
      
      CMP CHS,3
      JE  A6
      
      CMP CHS,4 
      JE A7
      
      CMP CHS,5
      JE A8
      
      CMP CHS,6  
      JE A9
      
      CMP CHS,7 
      JE A10
      
      CMP CHS,8 
      JE  A11
      
      JMP A2
;------STORING VALUE INTO ARRAY---------      
      A1:
      CMP S,00 ;NO INSTRUCTION SO PUT IN 1ST
      JE A5 
      
      MOV BX,0000
      MOV BL,ACTULEN2
      MOV KBNAME2[BX],30H
      INC ACTULEN2 
      CALL DISPLAY12
      JMP A2 
      
      A5: 
      MOV BX,0000
      MOV BL,ACTULEN1
      MOV KBNAME1[BX],30H
      INC ACTULEN1
      CALL DISPLAY11     
      JMP A2 
      
     A3:
      CMP S,00 ;NO INSTRUCTION SO PUT IN 1ST
      JE A4 
      
      MOV BX,0000
      MOV BL,ACTULEN2
      MOV KBNAME2[BX],31H
      INC ACTULEN2 
      CALL DISPLAY12
      JMP A2 
      
      A4: 
      MOV BX,0000
      MOV BL,ACTULEN1
      MOV KBNAME1[BX],31H
      INC ACTULEN1
      CALL DISPLAY11     
      JMP A2 
            
;-------------------------------- 
      
      A6:
      MOV S,'+'
      JMP A2 
      A7:
      MOV S,'-'
      JMP A2
      A8:
      MOV S,'*'
      JMP A2
      A9:
      MOV S,'/'
      JMP A2
      A10:
      MOV S,01
      JMP A2 
            
;CHECKING WHAT TO DO WHEN = KEY IS PRESSED
      
      
      A11: 
      
      CALL CONVERT1
      CALL CONVERT2
      
      CMP S,'+'
      JE SUM1
      CMP S,'-'
      JE SUB1
      CMP S,'*'
      JE MUL1
       CMP S,'/'
      JE DIV1
      CMP S,1
      JE POW1
      JMP A2 
             
      SUM1:
      CALL DOSUM 
      JMP C3
      SUB1:
      CALL DOSUB
      JMP C3
      MUL1:
      CALL DOMUL
      JMP C3
      DIV1:
      CALL DODIV
      JMP C3
      POW1:
      CALL DOPOW
      JMP C3
           
      A2:   
      POPA
      RET
CALCULATION ENDP

CHOOSE PROC NEAR
    
    PUSHA 
;----CLICKED OUTSIDE WINDOW-----
    
    CMP X,5
    JL B1  
    CMP X,25
    JG B1 
    CMP Y,8
    JL B1
    CMP Y1,22
    JG B1
;----CLICKED INSIDE WINDOW 
     
  ;X<=13 FIRST COLUMN
     CMP X,13 
     JLE B5
  ;ELSE X>=17 SECOND COLUMN
     CMP X,17
     JGE B6
  ;------OUTSIDE LIMIT-----   
     JMP B1
  ;----FIRST COLUMN-----
     
     B5: 
     CMP Y,20 ;FOURTH ROW
     JGE B7
     CMP Y,16
     JGE B8
     CMP Y,12
     JGE B9
     CMP Y,8
     JGE B10
     JMP B1
     
     B7:
     MOV CHS,7
     JMP B1
     B8:
     MOV CHS,5
     JMP B1
     B9:
     MOV CHS,3
     JMP B1
     B10:
     MOV CHS,1
     JMP B1
;-----SECOND COLUMN-----
        
    B6:
     CMP Y,20 ;FOURTH ROW
     JGE B11
     CMP Y,16
     JGE B12
     CMP Y,12
     JGE B13
     CMP Y,8
     JGE B14
     JMP B1
     
     B11:
     MOV CHS,8
     JMP B1
     B12:
     MOV CHS,6
     JMP B1
     B13:
     MOV CHS,4
     JMP B1
     B14:
     MOV CHS,2
     JMP B1
         
    B1:  
    POPA
    RET
CHOOSE ENDP

;-------------------------------------       
;SUM SUB DIV MUL PROC         
        
DOSUM PROC NEAR
            
             
            PUSHA
            
            MOV AX,A
            ADD AX,B
            MOV R11,AX  
            
            CALL CLEAR
            CALL CURSOR          
            CALL DISPLAYSUMP 
            CALL DISPLAY1
            
            POPA
            
            RET
DOSUM ENDP  
        
;----------------------------------
                 
DOSUB PROC NEAR
             
            PUSHA
            CALL CLEAR
            CALL CURSOR
            CALL DISPLAYSUBP 
            
            MOV AX,A
            CMP AX,B
            JGE ZZZ
            
            ;B>A
            
            MOV AH,02H
            MOV DL,31
            INT 21H
            
            MOV AX,B 
            SUB AX,A            
            MOV R11,AX
            JMP ABC
            
            ;A>=B
            
            ZZZ:
            SUB AX,B
            MOV R11,AX 
            
            ABC:
            
            CALL DISPLAY1 
                        
            POPA
            
            RET
DOSUB ENDP 
              
;--------------------------------------                 
            
DOMUL PROC NEAR
            
            PUSHA 
            
            MOV AX,A
            MUL B
            MOV R11,AX ;ASSUME DX==0
            
            CALL CLEAR
            CALL CURSOR
            CALL DISPLAYMULP
            CALL DISPLAY1
            
            POPA
            
            RET
DOMUL ENDP 
           

;-------------------------------------------
        
DODIV PROC NEAR
            
            PUSHA 
            
            MOV DX,0000
            MOV AX,A
            DIV B
            MOV R11,AX ;QUOTIENT
            MOV R12,DX ;REMAINDER
            CALL CLEAR
            CALL CURSOR
            CALL DISPLAYDIVQP
            CALL DISPLAY1  
            CALL CLEAR
            CALL CURSOR 
            CALL DISPLAYDIVRP
            CALL DISPLAY2
                       
             POPA
             RET
DODIV ENDP     
  
DOPOW PROC NEAR
    PUSHA 
    MOV CX,B
    MOV AX,A
    MOV DX,00 
    DEC CX
    F1:
    MUL A
    LOOP F1
    MOV  R11,AX
    CALL CLEAR
    CALL CURSOR
    CALL DISPLAYPOWP
    CALL DISPLAY1 
    POPA
    RET
DOPOW ENDP  
                          
;---------------------------------                         
;DISPLAY ALL INFORMATION 
DISPLAY11 PROC NEAR
    PUSHA 
    CALL CLEAR
    CALL CURSOR
    MOV CX,0000
    MOV CL,ACTULEN1
    MOV BX,CX 
    
    MOV KBNAME1[BX],'$'
    MOV  AH,09H
    LEA  DX,KBNAME1
    INT 21H
    POPA
    RET
DISPLAY11 ENDP 

DISPLAY12 PROC NEAR
    PUSHA 
    CALL CLEAR
    CALL CURSOR 
     
    MOV CX,0000
    MOV CL,ACTULEN2
    MOV BX,CX
    
    MOV KBNAME2[BX],'$'
    MOV  AH,09H
    LEA  DX,KBNAME2
    INT 21H
    POPA
    RET
DISPLAY12 ENDP 

DISPLAY1 PROC NEAR
            
            PUSHA              
            
            MOV ACTULEN1,00
            MOV ACTULEN2,00
            MOV S,00  
              
            MOV AX,R11
            MOV DX,00
            MOV CNT,00
            
            A35:
            DIV FACT 
            PUSH DX
            INC CNT  
            MOV DX,00
            CMP AX,00
            JE ABD1
            JMP A35   
            
           
             
            ABD1: 
            MOV SI,0000
            MOV CX,0000
            MOV CL,CNT
            MOV BX,CX
            MOV R1[BX],'$' 
            ABD:
            POP DX 
            ADD DX,30H
            MOV R1[SI],DL
            INC SI
            LOOP ABD
             
            MOV AH,09H
            LEA DX,R1
            INT 21H
            
            POPA
            
            RET
DISPLAY1 ENDP
          
DISPLAY2 PROC NEAR  
            
            PUSHA
            
            MOV AX,R12
            MOV DX,00
            MOV CNT,00
            
            A36:
            DIV FACT 
            PUSH DX
            INC CNT  
            MOV DX,00 
            CMP AX,00
            JE ABDEF
            JMP A36   
             
            ABDEF:
            
            MOV CX,0000
            MOV CL,CNT
            MOV SI,0000 
            MOV BX,CX
            MOV R2[BX],'$'
            ABDE:
            POP DX
            ADD DX,30H
            MOV R2[SI],DL
            INC SI
            LOOP ABDE
             
             MOV AH,09H
             LEA DX,R2
             INT 21H
             
            POPA
            
            RET
DISPLAY2 ENDP 
       
;-----------------------------------
;OUTPUT PROMPT
        
DISPLAYSUMP PROC NEAR 
            
            PUSHA
            
            MOV AX,0900H
            LEA DX,SUMP
            INT 21H 
            
            POPA
            
            RET
            DISPLAYSUMP ENDP 
        
DISPLAYSUBP PROC NEAR 
            
            PUSHA
            
            MOV AX,0900H
            LEA DX,SUBP
            INT 21H 
            
            POPA
            
            RET
            DISPLAYSUBP ENDP
         
DISPLAYMULP PROC NEAR
            
            PUSHA
            
            MOV AX,0900H
            LEA DX,MULP
            INT 21H
            
            POPA
            
            RET
            DISPLAYMULP ENDP
          
DISPLAYDIVQP PROC NEAR  
            
            PUSHA
            
            MOV AX,0900H
            LEA DX,DIVQ
            INT 21H   
            
            POPA
            
            RET
DISPLAYDIVQP ENDP 
         
DISPLAYDIVRP PROC NEAR  
            
            PUSHA            
            MOV AX,0900H
            LEA DX,DIVRR
            INT 21H   
            
            POPA
            
            RET
DISPLAYDIVRP ENDP 
 
DISPLAYPOWP PROC NEAR
    PUSHA 
    
    MOV AX,0900H
    LEA DX,POWR
    INT 21H
    
    POPA
    RET
DISPLAYPOWP ENDP         
;---------------------------------          
;CLEAR SCREEN AND SET CURSOR       
        
CLEAR PROC NEAR
    PUSHA 
    MOV AX,0600H
    MOV BH,34H 
   
    MOV CL,X1
    MOV CH,Y1
   
    MOV DH,Y1
    ADD DH,HEIGHT
    MOV DL,X1  
    ADD DL,WIDTH 
    INT 10H
    POPA
    RET
CLEAR ENDP

CURSOR PROC NEAR
       
        PUSHA
       
        MOV AX,0200H
        MOV BH,00
        MOV DH,Y1
        MOV DL,X1
        INT 10H
       
        POPA       
        RET
CURSOR ENDP 
       
;---------------------------------       
        
CONVERT1 PROC NEAR
           PUSHA
             
           MOV CX,0000
           MOV CL,ACTULEN1  
           MOV F,CL
           DEC CL 
           MOV BX,0000
           MOV AX,0000
                    
           A23:
           
           MOV DX,0000
           MOV DL,KBNAME1[BX]  
           SUB DX,30H  
           MOV Z,DL
           SHL DX,CL
           CMP Z,00 ;ZERO BYPASS
           JE  A27
           ADD AX,DX 
           A27:
           INC BX
           DEC CL
           DEC F
           JNZ A23
            
           MOV A,AX
            
           POPA
           RET
CONVERT1 ENDP 
       
CONVERT2 PROC NEAR
           PUSHA 
           
           MOV CX,0000
           MOV CL,ACTULEN2  
           MOV F,CL 
           DEC CL 
           MOV BX,0000
           MOV AX,0000         
           A29:
           
           MOV DX,0000
           MOV DL,KBNAME2[BX]  
           SUB DX,30H
           MOV Z,DL
           SHL DX,CL 
           CMP Z,00 ;ZERO BYPASS
           JE  A32
           ADD AX,DX 
           A32:
           INC BX
           DEC CL
           DEC F
           JNZ A29
            
           MOV B,AX
            
           POPA
           RET
CONVERT2 ENDP         
        
;------------------

