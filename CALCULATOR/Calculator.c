/*
 * LCD_PROJECT.c
 *
 * Created: 11/17/2022 2:33:23 PM
 * Author : AhmedMabrouk
 */ 

#include "header.h"
#include "LCD.h"
#include "LCD_cfg.h"
#include "KEYPAD.h"

uint8_t CALC_get_data(void);
float GET_CALCULATION(float, uint8_t, float);
float STRING_TO_FLOAT(uint8_t *);
uint8_t GET_DECIMAL_PLACES(float);

int main(void)
{
	
	LCD_init();
	KEYPAD_init();
	uint8_t KEY_DATA, op[10], counter, number[10], i, maxNums;
	float nums[10];
	float result;
	
	
    while (1) 
    {	
		counter = 0;
		result = 0;
		
		while(1) {
			
			i=0;
			
			while (1) {
				KEY_DATA = CALC_get_data();
				if (((KEY_DATA >= '0') && (KEY_DATA <= '9')) || (KEY_DATA == '.'))  {
					LCD_write_char(KEY_DATA);
					number[i] = KEY_DATA;
					i++;
				} else {
					break;
				}
			}
						
			nums[counter] = STRING_TO_FLOAT(number);
			
			for (i=0; i < (sizeof(number)/sizeof(number[0])); i++) {
				number[i] = 0;
			}
						
			if ((KEY_DATA == '+') || (KEY_DATA == '-') || (KEY_DATA == '*') || (KEY_DATA == '/')) {
				LCD_write_char(KEY_DATA);
				op[counter] = KEY_DATA;
			} else if ((KEY_DATA == '=')) {
				maxNums = counter;
				LCD_write_command(0xc0);
				LCD_write_char(KEY_DATA);
				break;
			}
			counter++;
		}
		
		for (i = 0; (i < maxNums) ; i++) {
			if ((op[i] == '*') || (op[i] == '/')) {
				nums[i+1] = GET_CALCULATION(nums[i],op[i],nums[i+1]);
				op[i] = '+';
				if ( op[i-1] == '-' ) {
					op[i] = '-';
				}
				nums[i] = 0;
			}
		}
	
		result = nums[0];
	
		for (i = 0; (i < maxNums) ; i++) {
			result = GET_CALCULATION(result,op[i],nums[i+1]);
		}
		
		if (result < 0) {
			if (result == (int32_t)result) {
				result = (-1) * result;
				LCD_write_char('-');
				if ((result < 1) && (result > 0)) {
					LCD_write_char('0');
				}
				LCD_write_number(result);
			} else {
				result = (-1) * result;
				LCD_write_char('-');
				if ((result < 1) && (result > 0)) {
					LCD_write_char('0');
				}
				LCD_write_number(result);
				LCD_write_char('.');
				if (((result-(uint32_t)result)*1000) < 10) {
					LCD_write_char('0');
					LCD_write_char('0');
				} else if (((result-(uint32_t)result)*1000) < 100) {
					LCD_write_char('0');
				}
				LCD_write_number((result-(uint32_t)result)*1000);
			}
		} else {
			if (result == (uint32_t)result) {
				if ((result < 1) && (result > 0)) {
					LCD_write_char('0');
				}
				LCD_write_number(result);
			} else {
				if ((result < 1) && (result > 0)) {
					LCD_write_char('0');
				}
				LCD_write_number(result);
				LCD_write_char('.');
				if (((result-(uint32_t)result)*1000) < 10) {
					LCD_write_char('0');
					LCD_write_char('0');
				} else if (((result-(uint32_t)result)*1000) < 100) {
					LCD_write_char('0');
				}
				LCD_write_number((result-(uint32_t)result)*1000);
			}
		}
				
		while(1) {
			KEY_DATA = CALC_get_data();
			if (KEY_DATA == '.') {
				LCD_write_command(1);
				break;
			}
		}
		
    }
	
}


uint8_t CALC_get_data(void) {
	
	uint8_t key;
	
	while(KEYPAD_read() == -1){}
	key = KEYPAD_read();
	while(KEYPAD_read() != -1){}
	return key;
}


float GET_CALCULATION(float a, uint8_t op, float b) {
	
	switch (op) {
		case '+' : return (a + b);
		case '-' : return (a - b);
		case '*' : return (a * b);
		case '/' : return (a / b);
		default  : break;
	}
	
	return 0;
}


float STRING_TO_FLOAT(uint8_t *str) {
	uint8_t i=0, dec_flag = 0, dec_start = 0;
	uint32_t num=0, dec=0;
	
	while (str[i] != '\0') {
		if ((str[i] >= '0') && (str[i] <= '9')) {
			num = num*10 + str[i] -'0';
			i++;
			} else if (str[i] == '.') {
			dec_flag = 1;
			break;
		}
	}
	
	i++;
	dec_start = i;
	
	if (dec_flag == 1) {
		while (str[i] != '\0') {
			if ((str[i] >= '0') && (str[i] <= '9')) {
				dec = dec*10 + str[i] -'0';
				i++;
			}
		}
	}
	
	return (num+(float)dec/pow(10,i-dec_start));
}
