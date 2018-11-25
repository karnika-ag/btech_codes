TITLE CHSORT (.EXE)
        .MODEL SMALL
        .STACK 64
        .DATA
TMP     DB ' ','$'
TMP2     DB ' ','$'

STR1    DB 'BACD','$'
MSG     DB 2 DUP(?),'$'
CNT     DW 01H
CNT2    DW 00H
PTR1     DW ?
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        MOV CX,03
        
        CLD
        LEA DI,STR1
        INC DI
        MOV PTR1,DI
        dec DI
        MOV SI,PTR1
A40:       MOV CNT2,00
       LEA DI,STR1
        INC DI
        MOV PTR1,DI
        dec DI
        MOV SI,PTR1

        
A50:    MOV AL,[DI]
        CMP AL,[SI]
        JNE A10

A10:    
        JG A20
        MOV MSG,'N'
        JMP A60
A20:    MOV MSG,'Y'
        JMP A70

        
A60:    CLD
        
        MOV AL,[DI]
        MOV AH,[SI]
        MOV [SI],AL
        MOV [DI],AH
       
A70:    INC SI
        INC DI
        INC CNT2
        CMP CX,CNT2
        Ja A80
        JMP A50
A80:    DEC CX
        CMP CX,00H
        Je A30
        JMP A40

A30:    MOV AH,09H
        LEA DX,MSG
        INT 21H
B10:    MOV AH,09H
        LEA DX,STR1
        INT 21H

        MOV AX,4C00H
        INT 21H

MAIN ENDP
END MAIN
