//lcd.h
void Write_CMD_LCD(char);		// Sends a command byte to the LCD

void Buildcgram(char *p,char nb);	// Stores custom character patterns in LCD CGRAM

void Write_DAT_LCD(char);		// Sends a data byte (character) to the LCD

void Write_LCD(char);			// Low-level function to write data/command to LCD

void LCD_Init(void);			// Initializes the LCD in 8-bit mode

void Write_str_LCD(char *);		// Displays a null-terminated string on the LCD

void Write_int_LCD(signed int);	// Displays a signed integer value on the LCD
								// signed int (2 bytes) range: -32768 to 32767

void Write_float_LCD(float f,char );	// Displays a floating-point number on the LCD
										// Second argument specifies digits after decimal point