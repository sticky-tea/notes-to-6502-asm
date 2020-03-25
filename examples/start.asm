  .inesprg 1
  .ineschr 1
  .inesmap 0
  .inesmir 2

  .rsset $0000

frames .rs 1

  .bank 0
  .org $C000

RESET:
    SEI          
    CLD          
    LDX #$40  
    STX $4017    
    LDX #$FF  
    TXS          
    INX          
    STX $2000   
    STX $2001    
    STX $4010   

vblankwait1:       
  BIT $2002
  BPL vblankwait1

clrmem:
  LDA #$00
  STA $0000, x
  STA $0100, x
  STA $0200, x
  STA $0400, x
  STA $0500, x
  STA $0600, x
  STA $0700, x
  LDA #$FE
  STA $0300, x
  INX
  BNE clrmem
   
vblankwait2:      
  BIT $2002
  BPL vblankwait2
Load:

  LDA #%10000000   
  STA $2000

  LDA #%00000000
  STA frames

  JSR music
ForeverLoop:
  JMP ForeverLoop