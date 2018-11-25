TITLE MOUSE1 (.EXE)
        .MODEL SMALL
        .386
        .STACK 64
        .DATA
LD EQU 14
X  DW  0
Y  DW  0
ASV DW  ?
DATA1 LABEL BYTE
XMSG DB 'X='
YMSG DB 'Y='
XA  DW ?
    DB ' '
YA  DW ?


        .CODE
MAIN PROC FAR
        MOV AX,@DATA
        MOV DS,AX
        MOV ES,AX
        CALL CLEAR
        CALL INIT
        CMP AX,00
        JE A90

A20:    CALL PNTR
        CMP BX,01
        JE A80
        MOV AX,X
        CALL DISP
        CALL CNVRT
        MOV AX,ASV
        MOV XA,AX
        MOV AX,Y
        CALL CNVRT
        MOV AX,ASV
        MOV YA,AX
        CALL DISP
        JMP A20

A80:    MOV AX,02H
        INT 33H
A90:    CALL CLEAR
        MOV AX,4C00H
        INT 21H
MAIN ENDP

INIT PROC NEAR
        MOV AX,00H
        INT 33H
        CMP AX,00
        JE B90
        MOV AX,01H
        INT 33H
B90:    RET
INIT ENDP

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
        MOV AX,1300H
        MOV BX,0031H
        LEA BP,DATA1
        MOV CX,LD
        MOV DX,0020H
        INT 10H
        RET
DISP ENDP

CLEAR PROC NEAR
        MOV AX,0600H
        MOV BH,30H
        MOV CX,00
        MOV DX,184FH
        INT 10H
        RET
CLEAR ENDP
END MAIN
