TITLE BINCAL (.EXE)
        .MODEL SMALL
        .286
        .STACK 64
        .DATA
D1      DB 30H
D2      DB 31H
X       DW 0
Y       DW 0
ASV     DW ?
C1      DB 5 dup(?),'$'
CNT     DB 05H
CNT1    DB ?,'$'
CNT2    DB ?,'$'

DATA1 LABEL BYTE
MSG    DB 'X,Y=','$'
XA      DW ?
YA      DW ?

        .CODE
MAIN PROC FAR       
        MOV AX,@DATA
        MOV DS,AX
        MOV CX,05H
        LEA SI,C1

A20:    MOV AH,01H
        INT 21H
        MOV [SI],AL
        INC SI
        LOOP A20

        DEC SI
        CALL CLEAR

        MOV DX,0204H
        CALL SETCUR
        CALL DISP3
        MOV CNT2,50
        MOV AL,0CDH
     
B40:
        CALL SETCUR
        CALL DISP2
        INC DL
        DEC CNT2
        JNZ B40

        MOV AL,0BAH
        MOV CNT2,20
        DEC DL
B50:    
        CALL SETCUR
        CALL DISP2
        INC DH
        DEC CNT2
        JNZ B50

        MOV AL,0CDH
        MOV CNT2,50
        DEC DH
B60:    CALL SETCUR
        CALL DISP2
        DEC DL
        DEC CNT2
        JNZ B60

        MOV AL,0BAH
        MOV CNT2,20
B70:    CALL SETCUR
        CALL DISP2
        DEC DH
        DEC CNT2
        JNZ B70


        MOV CX,05H
        MOV DX,0E0EH

        ADD DL,09H
        CALL SETCUR
        MOV AL,D1
        CALL DISP

        ADD DL,09H
        CALL SETCUR
        MOV AL,D2
        CALL DISP
        ADD DH,04H
        MOV DL,00H

A10:   
        ADD DL,09H
        CALL SETCUR
        MOV AL,[SI]
        CALL DISP
        DEC SI
        DEC CNT
        JNZ A10

        CALL INIT
        CMP AX,00
        JE A70

      
        MOV DX,0609H
        CALL SETCUR
A80:    CALL PNTR

        CMP BX,01
        JE A70

        MOV AX,X
        CALL CNVRT
        MOV AX,ASV
        MOV XA,AX
        MOV AX,Y
        CALL CNVRT
        MOV AX,ASV
        MOV YA,AX
        CALL ADISP
        JMP A80


A40:    CMP Y,05H
        JE A50
        JMP A70
A50:    CMP X,17H
        JE A60
        JMP A70
       
A60:    MOV DX,0909H
        CALL SETCUR
        MOV AL,D1
        CALL DISP

A70:   ; MOV DX,2000H
       ; CALL SETCUR
        MOV AX,4C00H
        INT 21H

MAIN ENDP

INIT PROC NEAR
        MOV AX,00H
        INT 33H
        CMP AX,00
        JE A30
        MOV AX,01H
        INT 33H
A30:    RET
INIT ENDP

PNTR PROC NEAR
C20:    MOV AX,03H
        INT 33H
        CMP BX,00000001B
        JE C90
        SHR CX,03
        SHR DX,03
        CMP CX,X
        JNE C30
        CMP DX,Y
        JE C20
C30:    MOV X,CX
        MOV Y,DX
C90:    RET
PNTR ENDP

DISP PROC NEAR
        MOV AH,09H
        MOV BH,0
        MOV BL,24H
        MOV CX,01H
        INT 10H
        RET
DISP ENDP
DISP3 PROC NEAR
        MOV AH,09H
        MOV AL,0C9H
        MOV BH,00
        MOV BL,1EH
        INT 10H
        MOV CX,01H
        RET
DISP3 ENDP

DISP2 PROC NEAR
        MOV AH,09H
      ;  MOV AL,0CDH
        MOV BH,00
        MOV BL,1EH
        INT 10H
        MOV CX,01h
        RET
DISP2 ENDP

CNVRT PROC NEAR
        MOV ASV,2020H
        MOV CX,10
        LEA SI,ASV+1
        CMP AX,CX
        JB D20
        DIV CL
        OR AH,30H
        MOV [SI],AH
        DEC SI
D20:    OR AL,30H
        MOV [SI],AL
        RET
CNVRT ENDP

CLEAR PROC NEAR
        MOV AX,0600H
        MOV BH,30
        MOV CX,0000
        MOV DX,184FH
        INT 10H
        RET
CLEAR ENDP

ADISP PROC NEAR
        MOV AX,1300H
        MOV BX,0031H
        LEA BP,DATA1
        MOV CX,10
        MOV DX,0020H
        INT 10H
        RET
ADISP ENDP

SETCUR PROC NEAR
        MOV AH,02H
        MOV BH,00
        INT 10H
        RET
SETCUR ENDP
END MAIN

