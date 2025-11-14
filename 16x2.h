#include <xc.h>
#define _XTAL_FREQ 4000000

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
#define LCD_PORT PORTD
#define LCD_PORT_DIR TRISD

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear();
void Lcd_Init();
void Lcd_Set_Cursor(char line, char place);
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
//////////////////////////////
void Lcd_Shift_Right();
void Lcd_Shift_Left();

