/*
 * LCD.c
 *
 * Created: 11/17/2022 6:29:26 PM
 *  Author: AhmedMabrouk
 */ 


#include "LCD.h"
#include "LCD_cfg.h"

/*****************************************************************************
* Function Name: LCD_init
* Purpose      : initialize LCD to work in 4-bit mode - clear lcd - cursor off
* Parameters   : void
* Return value : void
*****************************************************************************/
void LCD_init(void) {
	LCD_PINS_INIT();
	LCD_write_command(0x3);
	_delay_ms(4);
	LCD_write_command(0x3);
	_delay_ms(4);
	LCD_write_command(0x3);
	_delay_ms(4);
	LCD_write_command(0x2);
	LCD_write_command(0x28);
	LCD_write_command(0x1);
	LCD_write_command(0x6);
	LCD_write_command(0xc);
	_delay_ms(20);
}


/*****************************************************************************
* Function Name: LCD_write_command
* Purpose      : Send command to LCD
* Parameters   : cmd
* Return value : void
*****************************************************************************/
void LCD_write_command(uint8_t data) {
	LCD_RS(0);
	LCD_D7(READBIT(data,7));
	LCD_D6(READBIT(data,6));
	LCD_D5(READBIT(data,5));
	LCD_D4(READBIT(data,4));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
	
	LCD_D7(READBIT(data,3));
	LCD_D6(READBIT(data,2));
	LCD_D5(READBIT(data,1));
	LCD_D4(READBIT(data,0));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
}

/*****************************************************************************
* Function Name: LCD_write_char
* Purpose      : Write character to LCD
* Parameters   : char
* Return value : void
*****************************************************************************/
void LCD_write_char(uint8_t data) {
	LCD_RS(1);
	LCD_D7(READBIT(data,7));
	LCD_D6(READBIT(data,6));
	LCD_D5(READBIT(data,5));
	LCD_D4(READBIT(data,4));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
	
	LCD_D7(READBIT(data,3));
	LCD_D6(READBIT(data,2));
	LCD_D5(READBIT(data,1));
	LCD_D4(READBIT(data,0));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
}


/*****************************************************************************
* Function Name: LCD_write_string
* Purpose      : Write string to LCD
* Parameters   : Address of first char in string, length of string
* Return value : void
*****************************************************************************/
void LCD_write_string(uint8_t *data) {
	
	uint8_t i;

	for(i = 0; (data[i] != '\0'); i++) {
		LCD_write_char(data[i]);
	}
	
}


/*****************************************************************************
* Function Name: LCD_write_number
* Purpose      : Write number to LCD
* Parameters   : number
* Return value : void
*****************************************************************************/
void LCD_write_number(uint32_t data) {
	
	int8_t flag = 0, i;
	uint8_t str[10];
	
	for(i = 0; data >= 1 ; i++) {
		str[i] = data%10;
		data = data/10;
	}
	
	flag = i-1;
	
	for(i = flag; i >= 0; i--) {
		LCD_write_char(str[i]+48);
	}
	
}