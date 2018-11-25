title fuction keys using direct video display
;--------------------------------------------------------------
                .model small
                .stack 64
                .data
srow    DB      3
erow    DB      22
scol    DB      10
ecol    DB      70
mode    DB      ? 
char    DB      ?
hor_b   DB      0CDH
ver_b   DB      0BAH
;-----------------------------------------------------------------
        video_seg       segment         at      0B900H
        video_area      DB      1000H  DUP(?)
        video_seg       ENDS
;------------------------------------------------------------------
                .code
          MAIN  proc  far

          mov AX,video_seg
          mov ES,AX
          assume ES:video_seg
          mov AX,@data
          mov DS,AX

          mov AH,0FH
          int 10H
          mov mode,AL

          mov AH,00
          mov AL,03H
          int 10H

          mov AH,05
          mov AL,01
          int 10H

          call clr_screen
          
          call border

          call display

          mov AX,4C00H
          int 21H

      MAIN ENDP
;-----------------------------------------------------------------
                clr_screen      proc    near
                
                mov AH,06H
                mov AL,00
                mov BH,75H
                mov CX,0000H
                mov DX,184FH
                int 10H

                mov AH,06H
                mov AL,00
                mov BH,40
                mov CH,srow
                mov CL,scol
                sub cl,2
                mov DH,erow
                mov DL,ecol
                int 10H

                
                ret
           clr_screen ENDP
;-------------------------------------------------------------------   
               border   proc    near

                push AX
                push BX
                push CX
                push DX
               mov DI,336
               mov CX,63
               mov es:byte ptr[di],0c9h
               add di,2
              B1:
                mov AL,hor_b
                mov AH,75H
                
                mov ES:word ptr[DI],AX
                add DI,2
                LOOP B1  
          mov es:byte ptr[di],0bbh

                mov DI,3696
                mov CX,63
        mov es:byte ptr[di],0c8h
        add di,2
              B2:
                mov AL,hor_b
                mov AH,75H
                
                mov ES:word ptr[DI],AX
                add DI,2
                LOOP B2 
       mov es:byte ptr[di],0bch
                
                mov DI,496
                mov CX,20
              
             B3:
                mov AL,ver_b
                mov AH,75H
                
                mov ES:word ptr[DI],AX
                add DI,160
                LOOP B3  
               
                mov DI,624
                mov CX,20
              B4:
                mov AL,ver_b
                mov AH,75H
                
                mov ES:word ptr[DI],AX
                add DI,160
                LOOP B4  
                
                  
              pop DX
              pop CX
              pop BX
              pop AX

              ret
              
           border ENDP
;-------------------------------------------------------------------
                display     proc      near
                
                mov DL,01
                mov BL,20
                mov DI,500

             D1:
                mov CX,60 
             D10:
                mov AH,10H
                int 16H 
                
                mov char,AL
                cmp AL,0E0H
                je DF0
                cmp AL,0DH
                je DFF0
                
                mov AL,char
                mov AH,47H
                mov ES:word ptr[DI],AX
                add DI,2     
                
                jmp D30
             
             DF0:
                call fun_keys
                inc CX
                jmp D30
             DFF0:
                push BX
                push AX
                push DX
                mov BX,40
		mov AH,00
		mov AL,CL
		mov DL,2
		mul DL
		add BX,AX
		add DI,BX
		pop DX
		pop AX
		pop BX
		mov CX,61

                
             D30:   
                LOOP D10

                add DI,40
                inc DL
                cmp DL,BL
                jle D1

                
                ret

                display ENDP
;-------------------------------------------------------------
            fun_keys    proc    near
                
                
                cmp AH,53H
                jne DF1
                
                mov SI,DI 
                push DX
                mov DX,CX
                push CX
                push AX
                
                mov CX,DX
              DFA:
                mov AX,ES:[DI+2]
                mov ES:[DI],AX
                add DI,2
                LOOP DFA
                
                mov DI,SI
                
                pop AX
                pop CX
                pop DX
                
                jmp Dexit
                
             DF1:
                cmp AH,52H
                jne DF2
                
                push AX
                mov AX,ES:[DI]
                mov AH,11000111B
                mov ES:word ptr[DI],AX
                
                pop AX
                jmp Dexit
                
             DF2:
                cmp AH,4BH
                jne DF3
                
                sub DI,2 
                inc CX
                jmp Dexit
                
             DF3:
                cmp AH,4DH
                jne DF4
                
                add DI,2
                dec CX          
                jmp Dexit
                
             DF4:
                cmp AH,48H
                jne DF5
                
                sub DI,160   
                jmp Dexit
                
             DF5:
                cmp AH,50H
                jne DF6
                
                add DI,160
                jmp Dexit
             
             DF6:
                cmp AH,47H
                jne Dexit
                
                push AX
                mov AX,CX
                push CX
                mov CX,60
                sub CX,AX
                
               DDF:
                 sub DI,2
                 LOOP DDF
                 
                pop CX
                pop AX  
                    
          Dexit:
                
                ret
                
             fun_keys ENDP      

;------------------------------------------------------------
END MAIN
