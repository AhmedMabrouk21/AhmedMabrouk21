/*
 * header.h
 *
 * Created: 11/14/2022 1:05:02 PM
 *  Author: AhmedMabrouk
 */ 


#ifndef HEADER_H
#define HEADER_H

#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define SETBIT(REG,BIT)  (REG |= 1 << BIT)
#define CLRBIT(REG,BIT)  (REG &= ~(1 << BIT))
#define TOGBIT(REG,BIT)  (REG ^= 1 << BIT)
#define READBIT(REG,BIT)  ((REG >> BIT) & 1)

#endif