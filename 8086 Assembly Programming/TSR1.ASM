TITLE TSR1(.COM)
CODESEG SEGMENT PARA
        ASSUME CS:CODESEG
        ORG 100H
       ; JMP BINIT
BEGIN:  JMP BINIT
SAV     DD ?
MSG     DB 'NEHA','$'
DUR     DW 100H
ATEST:  PUSH AX
        PUSH CX
        IN AL,60H
        CMP AL,01
        JNE AEXIT
        MOV AH,09H
        LEA DX,MSG
        INT 21H
AEXIT:  POP CX             
        POP AX
        JMP CS:SAV
BINIT:  CLI
        MOV AH,35H
        MOV AL,09H
        INT 21H
        MOV WORD PTR SAV,BX
        MOV WORD PTR SAV+2,ES
        MOV AH,25H
        MOV AL,09H
        MOV DX,OFFSET ATEST
        INT 21H
        MOV AH,31H
        MOV DX,OFFSET BINIT
        STI
        INT 21H
CODESEG ENDS
        END BEGIN
