TITLE BINTODEC (.EXE)
        .MODEL SMALL
        .STACK 64
        .DATA
BIN     DB '1101','$'
DECI    DB 5 DUP(' '),'$'
Z       DW 00H,'$'
X       DW 0AH,'$'
Y       DW 00H
D       DW 01H,'$'
P       DW ?
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        LEA DI,BIN
        LEA SI,DECI+4
        MOV P,02H
        mov y,04h
       
        MOV CX,00H

A60:;    MOV AH,01H
     ;   INT 21H
      ;  CMP AL,0DH
   ;     JE A70
    ;    INC Y
     ;   SUB AL,30H
    ;    MOV [DI],AL
      ;  INC DI
     ;   JMP A60
        

   
A70:    
        LEA DI,BIN
        MOV AX,D
        
A10:    MOV BL,[DI]
        MUL BL
        ADD Z,AX
        MOV AX,D
       
        CMP CX,00H
        JE A50
        MUL P
        
        LOOP A10
A50:    INC CX
        CMP CX,Y
        JE B10
        JMP A10
        MOV CX,00H
B10:    MOV AX,Z
A20:    MOV DX,00
        DIV X
        ADD DX,30H
        MOV [SI],DX
        DEC SI
        DEC SI
        INC CX
        CMP AX,00H
        JNE A20
        INC SI
        INC SI

        
A30:    MOV AH,09H
        LEA DX,[SI]
        INT 21H
        INC SI
        LOOP A30

        MOV AX,4C00H
        INT 21H

MAIN ENDP
END MAIN
