; Recitation 10
; Author: <Alissa Morgan>
; Date:   <10/8/21>
; Email:  <alissaam@colostate.edu>
; Class:  CS270
; Description: copies least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000

                JSR copy           ; call function
                HALT

; Parameter and return value
; Try changing Param's .BLKW 1 to .FILL xNNNN where N is a hexadecimal value or #NNNN
; where N is a decimal value, this can save you time by not having to set these 
; values in the simulator every time you run your code. This is the only change 
; you should make to this section.
Param           .BLKW 1              ; space to specify parameter
Result          .BLKW 1              ; space to store result

; Constants, the use of One and Eight is optional
One             .FILL #1             ; the number 1   
Eight           .FILL #8             ; the number 8
Mask            .FILL x00ff          ; mask top bits

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------
copy                           		; Copy bits 7:0 to 15:8
                                     	; ~20 lines of assembly code
 
                LD R0,Param          	; load pattern
                ADD R1, R0, #0       	; copy R0 into R1
		LD R2, Mask		; R0 = x00ff
		AND R1, R1, R2		; clear bits 15:8
		LD R2, One		; R2 = #1 (source mask)
		LD R3, One		; R3 = #1 (dest mask)
		LD R4, Eight		; R4 = #8 (counter)
shift_loop
		ADD R3, R3, R3		; Left shift
		ADD R4, R4, #-1		; dec counter
		BRp shift_loop		; repeat 8 times
		LD R4, Eight		; R4 = #8 (counter)
copy_loop
		AND R5, R0, R2		; is LS bit set in param?		
		BRz do			; if doesn't hit, skip to shifts
		ADD R1, R3, R1		; add bit in dest mask to result
do
		ADD R2, R2, R2		; shift src mask left
		ADD R3, R3, R3		; shift dest mask left
		ADD R4, R4, #-1		; dec counter
		BRp copy_loop		; repeat 8 times
                ST R1,Result         	; store result
                RET
;--------------------------------------------------------------------------
               .END

