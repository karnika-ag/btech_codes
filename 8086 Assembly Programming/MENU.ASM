TITLE MENU (.EXE)
        .MODEL SMALL
        .386
        .STACK 64
        .DATA
TOPROW  EQU 08
BOTROW  EQU 15
LEFCOL EQU 26
ATTRIB  DB  ?
ROW     DB  00
SHADOW  DB  19 DUP(0DBH)
MENU    DB  0C9H, 17 DUP(0CDH),0BBH
        DB  0BAH,' ADD RECORDS     ',0BAH
        DB  0BAH,' DELETE RECORDS  ',0BAH
        DB  0BAH,' ENTER ORDERS    ',0BAH
        DB  0BAH,' PRINT REPORTS   ',0BAH
        DB  0BAH,' UPDATE ACCOUNTS ',0BAH
        DB  0BAH,' VIEW RECORDS    ',0BAH
        DB  0C8H, 17 DUP(0CDH),0BCH
PRMPT   DB  'TO SELECT AN ITEM ,USE <UP/DOWN ARROW>'
        DB  ' AND PRESS <ENTER>. '
        DB  13,10,'PRESS <ESC> TO EXIT '
        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        CALL CLEAR
        MOV ROW,BOTROW+4
A20:    CALL BMENU
        MOV ROW,TOPROW+1
        MOV ATTRIB,16H
        CALL DISP
        CALL INPUT
        CMP AL,1BH
        JNE A20
        MOV AX,0600H
        CALL CLEAR
A10:    MOV AX,4C00H
        INT 21H
MAIN ENDP

BMENU PROC NEAR
        PUSHA
        MOV AX,1301H
        MOV BX,0060H
        LEA BP,SHADOW
        MOV CX,19
        MOV DH,TOPROW+1
        MOV DL,LEFCOL+1
B20:    INT 10H
        INC DH
        CMP DH,BOTROW+2
        JNE B20
        MOV ATTRIB,71H
        MOV AX,1300H
        MOVZX BX,ATTRIB
        LEA BP,MENU
        MOV CX,19
        MOV DH,TOPROW
        MOV DL,LEFCOL
B30:    INT 10H
        ADD BP,19
        INC DH
        CMP DH,BOTROW+1
        JNE B30
        MOV AX,1301H
        MOVZX BX,ATTRIB
        LEA BP,PRMPT
        MOV CX,79
        MOV DH,BOTROW+4
        MOV DL,00
        INT 10H
        POPA
        RET
BMENU ENDP

INPUT PROC NEAR
        PUSHA
C20:    MOV AH,10H
        INT 16H
        CMP AH,50H
        JE C30
        CMP AH,48H
        JE C40
        CMP AL,0DH
        JE C90
        CMP AL,1BH
        JE A10
        JMP C20
C30:    MOV ATTRIB,71H
        CALL DISP
        call clear1
        INC ROW
        CMP ROW,BOTROW-1
        JBE C50
        MOV ROW,TOPROW+1
        JMP C50
C40:    MOV ATTRIB,71H
        CALL DISP
        DEC ROW
        CMP ROW,TOPROW+1
        JAE C50
        MOV ROW,BOTROW-1
C50:    MOV ATTRIB,17H
        CALL DISP
        JMP C20
C90:    POPA
        RET
INPUT ENDP

DISP PROC NEAR
        PUSHA
        MOVZX AX,ROW
        SUB AX,TOPROW
        IMUL AX,19
        LEA SI,MENU+1
        ADD SI,AX
        MOV AX,1300H
        MOVZX BX,ATTRIB
        MOV BP,SI
        MOV CX,17
        MOV DH,ROW
        MOV DL,LEFCOL+1
        INT 10H
        POPA
        RET
DISP ENDP

CLEAR PROC NEAR
        PUSHA
        MOV AX,0600H
        MOV BH,61H
        MOV CX,0000
        MOV DX,184FH
        INT 10H
        POPA
        RET
CLEAR ENDP
CLEAR1 PROC NEAR
        MOV AX,0605H
        MOV BH,17H
        MOV CX,0101
        MOV DX,0606H
        INT 10H
        MOV AH,02H
        MOV BH,00
        MOV DX,0101
        INT 10H
        MOV CX,06
E10:    MOV AH,01H
        INT 21H
        LOOP E10
        RET
END MAIN




