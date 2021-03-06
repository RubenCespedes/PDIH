;[]-----------------------------------------------------------------[]
;|      H_PSBH.ASM -- huge pointer routines                          |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

; calls to these routines are generated by the compiler to perform
; arithmetic operations on proteced/fast huge pointers.

_TEXT           SEGMENT BYTE PUBLIC 'CODE'
                ASSUME  CS:_TEXT
;
;       dx:ax   left hand pointer
;       cx:bx   right hand pointer
;
                public  N_PSBH@
                public  F_PSBH@

N_PSBH@:        push    si
                mov     si, cx
                mov     cx, offset __AHSHIFT
                shr     dx, cl
                shr     si, cl
                sub     ax, bx
                sbb     dx, si
                pop     si
                ret

F_PSBH@:        push    si
                mov     si, cx
                mov     cx, offset __AHSHIFT
                shr     dx, cl
                shr     si, cl
                sub     ax, bx
                sbb     dx, si
                pop     si
                retf
_TEXT           ENDS

extrn   __AHSHIFT:far
                END

