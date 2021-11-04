; Begin reserved section: do not change ANYTHING in reserved section!
; The ONLY exception to this is that you MAY change the .FILL values for
; Option, Value1 and Value2. This makes it easy to initialize the values in the
; program, so that you do not need to continually re-enter them. This
; makes debugging easier as you need only change your code and re-assemble.
; Your test value(s) will already be set.
;------------------------------------------------------------------------------
; Author: Fritz Sieker
;
; Description: Tests the implementation of a simple string library and I/O
;

            .ORIG x3000
            BR Main
Functions
            .FILL Test_pack         ; (option 0)
            .FILL Test_unpack       ; (option 1)
            .FILL Test_printCC      ; (option 2)
            .FILL Test_strlen       ; (option 3)
            .FILL Test_strcpy       ; (option 4)
            .FILL Test_strcat       ; (option 5)
            .FILL Test_strcmp       ; (option 6)

; Parameters and return values for all functions
Option      .FILL 0                 ; which function to call
String1     .FILL x4000             ; default location of 1st string
String2     .FILL x4100             ; default location of 2nd string
Result      .BLKW 1                 ; space to store result
Value1      .FILL 0                 ; used for testing pack/unpack
Value2      .FILL 0                 ; used for testing pack/unpack
lowerMask   .FILL 0x00FF            ; mask for lower 8 bits
upperMask   .FILL 0xFF00            ; mask for upper 8 bits

Main        LEA R0,Functions        ; get base of jump table
            LD  R1,Option           ; get option to use, no error checking
            ADD R0,R0,R1            ; add index of array
            LDR R0,R0,#0            ; get address to test
            JMP R0                  ; execute test

Test_pack   
            LD R0,Value1            ; load first character
            LD R1,Value2            ; load second character
            JSR pack                ; pack characters
            ST R0,Result            ; save packed result
End_pack    HALT                    ; done - examine Result

Test_unpack 
            LD R0,Value1            ; value to unpack
            JSR unpack              ; test unpack
            ST R0,Value1            ; save upper 8 bits
            ST R1,Value2            ; save lower 8 bits
End_unpack  HALT                    ; done - examine Value1 and Value2

Test_printCC    
            LD R0,Value1            ; get the test value
            .ZERO R1                ; reset condition codes
            JSR printCC             ; print condition code
End_printCC HALT                    ; done - examine output

Test_strlen 
            LD R0,String1           ; load string pointer
            GETS                    ; get string
            LD R0,String1           ; load string pointer
            JSR strlen              ; calculate length
            ST R0,Result            ; save result
End_strlen  HALT                    ; done - examine memory[Result]

Test_strcpy 
            LD R0,String1           ; load string pointer
            GETS                    ; get string
            LD R0,String2           ; R0 is dest
            LD R1,String1           ; R1 is src
            JSR strcpy              ; copy string
            PUTS                    ; print result of strcpy
            NEWLN                   ; add newline
End_strcpy  HALT                    ; done - examine output

Test_strcat 
            LD R0,String1           ; load first pointer
            GETS                    ; get first string
            LD R0,String2           ; load second pointer
            GETS                    ; get second string
            LD R0,String1           ; dest is first string
            LD R1,String2           ; src is second string
            JSR strcat              ; concatenate string
            PUTS                    ; print result of strcat
            NEWLN                   ; add newline
End_strcat  HALT                    ; done - examine output

Test_strcmp 
            LD R0,String1           ; load first pointer
            GETS                    ; get first string
            LD R0,String2           ; load second pointer
            GETS                    ; get second string
            LD R0,String1           ; dest is first string
            LD R1,String2           ; src is second string
            JSR strcmp              ; compare strings
            JSR printCC             ; print result of strcmp
End_strcmp  HALT                    ; done - examine output

;------------------------------------------------------------------------------
; End of reserved section
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; on entry R0 contains first value, R1 contains second value
; on exit  R0 = (R0 << 8) | (R1 & 0xFF)

pack        ; fill in your code, ~11 lines of code
		AND R2, R2, #0	
		ADD R2, R2, #8		; R2 = counter = 8
Double
		ADD R0, R0, R0	
		ADD R2, R2, #-1
		BRp Double		; shift R0 left 8 times
		LD R2, lowerMask 	; R2 = 0x00FF mask
		AND R1, R1, R2 		; R1 = [8:0] of R1
		NOT R0, R0
		NOT R1, R1
		AND R0, R1, R0
		NOT R0, R0 		; R0 = R0 | R1
		RET

;------------------------------------------------------------------------------
; on entry R0 contains a value
; on exit  (see instructions)

unpack      ; fill in your code, ~14 lines of code
		LD R1, lowerMask
		AND R1, R0, R1		; R1 = [8:0] of R0
		LD R2, upperMask
		AND R0, R2, R0		; Clear [15:9] of R0
		
		AND R4, R4, #0		; Clear R4 ; counter
		ADD R4, R4, #8		; Counter = #8
		AND R2, R2, #0		; Clear R2
		ADD R2, R2, #1		; R2 = src mask
		ADD R3, R2, #0		; R3 = dst mask
ShiftLoop
		ADD R2, R2, R2
		ADD R4, R4, #-1
		BRp ShiftLoop		; R2 left shifted 8 bits
IsSet
		AND R4, R2, R0		; R4 = is bit set?
		BRz Shift
		ADD R0, R3, R0		; If set, add at dst mask
Shift
		ADD R3, R3, R3		; shift dst mask
		ADD R2, R2, R2		; shift src mask
		BRp IsSet		; if src mask isn't at msb, go to IsSet
		AND R4, R2, R0		; R4 = is bit set?
		LD R2, lowerMask
		AND R0, R2, R0		; clear [15:9] of R0
		RET

;------------------------------------------------------------------------------
; on entry R0 contains value
; on exit  (see instructions)

StringNEG   .STRINGZ "NEGATIVE\n"   ; output strings
StringZERO  .STRINGZ "ZERO\n"
StringPOS   .STRINGZ "POSITIVE\n"

printCC     ; fill in your code, ~11 lines of code
		ADD R2, R7, #0 ;Save addy
		ADD R1, R0, #0 ; Save to diff reg
		LEA R0, StringNEG
		ADD R1, R1, #0
		BRn Print
		LEA R0, StringZERO
		ADD R1, R1, #0
		BRz Print
		LEA R0, StringPOS
Print
		TRAP X22 ; PUTS
		ADD R7, R2, #0 ; restore addy
		ADD R0, R1, #0
		RET
;------------------------------------------------------------------------------
; size_t strlen(char *s)
; on entry R0 points to string
; on exit  (see instructions)

strlen      ; fill in your code, ~7 lines of code
		AND R1, R1, #0 ;clear R1 the counter
		LDR R2, R0, #0
		BRz Done
Repeat
		ADD R1, R1, #1 ;inc counter
		ADD R0, R0, #1 ;move to next char/ set cc
		LDR R2, R0, #0
		BRnp Repeat
Done
		ADD R0, R1, #0
            	RET

;------------------------------------------------------------------------------
; char *strcpy(char *dest, char *src)
; on entry R0 points to destination string, R1 points to source string
; on exit  (see instructions)

String   .STRINGZ "\n"

strcpy      ; fill in your code, ~8 lines of code
		ADD R2, R0, #0 ; Load pointer
LoadChar
		LDR R3, R1, #0 ; Load src char into R3
		STR R3, R0, #0 ; Put char into dest slot
		ADD R1, R1, #1 ; inc src pointer
		ADD R0, R0, #1 ; inc dst pointer
		ADD R3, R3, #0 ; load char into cc
		BRnp LoadChar	; check if null pointer
		ADD R0, R2, #0 ; R0 points to dest string char[0]
            	RET

;------------------------------------------------------------------------------
; char *strcat(char *dest, char *src)
; on entry R0 points to destination string, R1 points to source string
; on exit  (see instructions)

strcat_RA   .BLKW 1                 ; space for return address
strcat_dest .BLKW 1                 ; space for dest
strcat_src  .BLKW 1                 ; space for src

strcat      ST R7,strcat_RA         ; save return address
            ST R0,strcat_dest       ; save dest
            ST R1,strcat_src        ; save src

            ; fill in your code, ~5 lines of code
            ; HINT: call strlen and strcpy
		JSR  strlen
		LD R0,strcat_dest       ; restore dest
		ADD R0, R0, R1
		LD R1,strcat_src       ; restore src
		JSR strcpy

            LD R0,strcat_dest       ; restore dest
            LD R7,strcat_RA         ; restore return address
            RET

;------------------------------------------------------------------------------
; int strcmp(char *s1, char *s2)
; on entry R0 points to first string, R1 points to second string
; on exit  (see instructions)

strcmp      ; fill in your code, ~12 lines of code
Compare
		LDR R2, R0, #0 ; Load char at R0 into R2
		LDR R3, R1, #0 ; Load char at R1 into R3
		BRz End		; is R1 pointing at null char?
		ADD R0, R0, #1 ; inc s1 pointer
		ADD R1, R1, #1 ; inc s2 pointer
		NOT R3, R3	; negate second char
		ADD R3, R3, #1 
		ADD R2, R2, R3 ; Find diff between char values
		BRz Compare
End
		ADD R0, R2, #0 ; Load diff into R0
            	RET

;------------------------------------------------------------------------------
            .END
