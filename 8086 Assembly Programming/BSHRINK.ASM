TITLE SHRINK (.EXE)
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
A DB ?,'$'
B DB ?,'$'
C DW 20H,'$'
        .CODE
MAIN PROC FAR       
        MOV AX,@DATA
        MOV DS,AX
        MOV CX,05H

        CALL CLEAR

        MOV DX,0204H
        CALL SETCUR
       
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

        MOV DX,0305H
C20:    CALL SETCUR
C10:    MOV AH,01H
        INT 21H
        CMP AL,0DH
        JE C40
        cmp AL,08H
        JE C60

        CALL CURPOS
          CMP DL,35H
        JB C10
C40:    INC DH
        CMP DH,15H
        JAE C30
        MOV DL,05H
        JMP C20
C60:    DEC DL
        MOV AH,09H
        LEA DX,C
        INT 21H
        CALL CURPOS
        SUB DL,02
        CALL SETCUR
        JMP C10
C30:    MOV DX,1738H
        CALL SETCUR
        MOV AX,4C00H
        INT 21H

MAIN ENDP

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
        MOV CX,01
        RET
DISP2 ENDP


CLEAR PROC NEAR
        MOV AX,0600H
        MOV BH,07
        MOV CX,0000
        MOV DX,184FH
        INT 10H
        RET
CLEAR ENDP
CLEAR1 PROC NEAR
        MOV AX,0601H
        MOV BH,07H
        INT 10H
        RET
CLEAR1 ENDP
        

SETCUR PROC NEAR
        MOV AH,02H
        MOV BH,00
        INT 10H
        RET
SETCUR ENDP

CURPOS PROC NEAR
        MOV AH,03H
        MOV BH,00
        INT 10H
        RET
CURPOS ENDP
END MAIN

