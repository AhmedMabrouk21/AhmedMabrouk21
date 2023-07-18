/*
 * LCD_cfg.h
 *
 * Created: 11/17/2022 8:25:23 PM
 *  Author: AhmedMabrouk
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "header.h"

#define LCD_PINS_INIT() DDRA |= 0b11111100;

#define LCD_RS(x) if(x==1) SETBIT(PORTA,2); else CLRBIT(PORTA,2);
#define LCD_EN(x) if(x==1) SETBIT(PORTA,3); else CLRBIT(PORTA,3);
#define LCD_D4(x) if(x==1) SETBIT(PORTA,4); else CLRBIT(PORTA,4);
#define LCD_D5(x) if(x==1) SETBIT(PORTA,5); else CLRBIT(PORTA,5);
#define LCD_D6(x) if(x==1) SETBIT(PORTA,6); else CLRBIT(PORTA,6);
#define LCD_D7(x) if(x==1) SETBIT(PORTA,7); else CLRBIT(PORTA,7);


#endif /* LCD_CFG_H_ */