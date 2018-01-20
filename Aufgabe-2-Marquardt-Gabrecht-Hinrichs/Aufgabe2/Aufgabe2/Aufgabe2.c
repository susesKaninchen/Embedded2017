/*
 * Aufgabe2.c
 *
 * Created: 11.12.2017 22:06:28
 *  Author: Matthias Hinrichs
 */

#include <avr/io.h>
#include <avr/interrupt.h>		// interrupts
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "lcd/lcd.h"
#include "adc/adc.h"
#include "adc/hygro.h"
#include "one_wire/ds18s20.h"
#include "clock/clock.h"

#define UP PA0
#define DOWN PA3
#define ENTER PA4
#define CANCEL PA5

#define IDLE 0
#define MENUE_TIME 1
#define MENUE_TIME_EDIT_H 2
#define MENUE_TIME_EDIT_M 3
#define MENUE_DISPLAY 4
#define MENUE_DISPLAY_TIME 5
#define MENUE_DISPLAY_TIME_TEMP 6
#define MENUE_DISPLAY_TIME_TEMP_LF 7

#define DISPLAY_TIME 10
#define DISPLAY_TIME_TEMP 11
#define DISPLAY_TIME_TEMP_LF 12
#define DEBUG 1

uint8_t volatile menue_state = IDLE;
uint8_t volatile display_state = MENUE_DISPLAY_TIME;
uint8_t volatile enter_was_pressed = 0;
uint8_t volatile up_was_pressed = 0;
uint8_t volatile down_was_pressed = 0;
uint8_t volatile key_was_pressed = 0;
uint8_t volatile IOInterruptEnabled = 1;
volatile uint8_t Lastbutton =0;

extern volatile uint8_t hours;
extern volatile uint8_t minutes;
extern volatile uint8_t seconds;

volatile uint8_t clock_flag = 1;
volatile uint8_t temp_flag = 1;
volatile uint8_t temp_counter = 0;
volatile uint8_t hygro_flag = 1;
volatile uint8_t hygro_counter = 0;
extern volatile uint8_t clock_blink_flag;


// Prototypes
void timer1Init (void);
void init(void);

int main(void){
	init();
	while(1)
	{
		if (clock_flag)
		{
			clock_flag = 0;
			clock_display(1,2,0);
		}
		if (temp_flag)
		{
			temp_flag = 0;
			temp_display(2,2);
		}
		if (hygro_flag)
		{
			hygro_flag = 0;
			hygro_display(2,9);
		}
	}
}

void init(void)
{
	cli();
	lcd_init();
	adc_init();
	timer1Init();
	sei();
}

void timer1Init(void)
{
	TCCR1A = 0x00;
	TCCR1B |= ((1<<WGM12)|(1<<CS12)); // CTC ON, Prescaler 1024
	// Timer 1,0s
	// 1 * 8.000.000 / 256 = 31250
	OCR1A = 31250;
	// Interrupt aktivieren
	TIMSK1 |= (1<<OCIE1A);
	// Zaehlregister auf 0
	TCNT1 = 0x00;
}

ISR (TIMER1_COMPA_vect)
{
	clock_blink_flag ^= 1;
	temp_counter++;
	hygro_counter++;
	seconds++;
	if (seconds == 60)
	{
		seconds = 0;
		minutes++;
		if (minutes == 60)
		{
			minutes = 0;
			hours++;
			if (hours == 24)
			{
				hours = 0;
			}
		}
	}
	clock_flag = 1;
	if (temp_counter == 9)
	{
		temp_counter = 0;
		temp_flag = 1;
	}
	if (hygro_counter == 5)
	{
		hygro_counter = 0;
		hygro_flag = 1;
	}
}
