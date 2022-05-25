
void LCD_cmd(unsigned char cmd);

void LCD_Init (void);

void LCD_write(unsigned char data);

void LCD_write_String(char *Str);

void Cursor_Pos(unsigned char row , unsigned char pos);

void OUT( unsigned char  hundreds , unsigned char tens , unsigned char units);
