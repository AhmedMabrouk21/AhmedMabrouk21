/*
 * KEYPAD.h
 *
 * Created: 11/18/2022 12:25:35 AM
 *  Author: AhmedMabrouk
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "header.h"

void KEYPAD_init(void);
int8_t KEYPAD_read(void);

#define INIT_KEYPAD_PINS() DDRC = 0xf0; PORTC = 0xff;

#define K0() READBIT(PINC,0)
#define K1() READBIT(PINC,1)
#define K2() READBIT(PINC,2)
#define K3() READBIT(PINC,3)
#define K4(x) if(x == 1) SETBIT(PORTC,4); else CLRBIT(PORTC,4);
#define K5(x) if(x == 1) SETBIT(PORTC,5); else CLRBIT(PORTC,5);
#define K6(x) if(x == 1) SETBIT(PORTC,6); else CLRBIT(PORTC,6);
#define K7(x) if(x == 1) SETBIT(PORTC,7); else CLRBIT(PORTC,7);

#endif /* KEYPAD_H_ */