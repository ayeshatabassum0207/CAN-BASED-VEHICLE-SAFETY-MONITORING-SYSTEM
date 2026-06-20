/* defines.h */		// Header file containing commonly used bit manipulation macros

#ifndef __DEFINES_H__	// Check whether the header file is already included
#define __DEFINES_H__	// Define header guard macro


#define SETBIT(WORD,BITPOS)            (WORD|=(1<<BITPOS))		// Set the bit at BITPOS in WORD

#define CLRBIT(WORD,BITPOS)            (WORD&=~(1<<BITPOS))		// Clear the bit at BITPOS in WORD

#define CPLBIT(WORD,BITPOS)            (WORD^=(1<<BITPOS))		// Toggle the bit at BITPOS in WORD

#define WRITEBIT(WORD,BITPOS,BIT)      (BIT?SETBIT(WORD,BITPOS):CLRBIT(WORD,BITPOS))	// Write BIT value (0 or 1) to BITPOS

#define READBIT(WORD,BITPOS)           ((WORD>>BITPOS)&1)		// Read the bit value at BITPOS

#define READWRITEBIT(WORD,WBIT,RBIT)   (WORD=((WORD&~(1<<WBIT))|(((WORD>>RBIT)&1)<<WBIT)))	// Copy bit value from RBIT position to WBIT position

#define WRITEUNIBBLE(WORD,BITPOS,BYTE) (WORD=(WORD&~(0x0000000F<<BITPOS))|((BYTE>>4)<<BITPOS))	// Write upper nibble of BYTE to WORD at BITPOS

#define WRITELNIBBLE(WORD,BITPOS,BYTE) (WORD=(WORD&~(0x0000000F<<BITPOS))|((BYTE&0X0F)<<BITPOS))	// Write lower nibble of BYTE to WORD at BITPOS

#define READNIBBLE(WORD,BITPOS)        ((WORD>>BITPOS)&0x0000000F)	// Read a 4-bit nibble from WORD at BITPOS

#define WRITEBYTE(WORD,BITPOS,BYTE)    (WORD=(WORD&~(0x000000FF<<BITPOS))|(BYTE<<BITPOS))	// Write BYTE to WORD starting at BITPOS

#define READBYTE(WORD,BITPOS)          ((WORD>>BITPOS)&0x000000FF)	// Read a byte from WORD starting at BITPOS


#endif		// End of header guard