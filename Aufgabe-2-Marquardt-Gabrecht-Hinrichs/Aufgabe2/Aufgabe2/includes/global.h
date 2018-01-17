/*
 * global.h
 *
 * Created: 12.12.2017 15:03:37
 *  Author: 240747
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>


//IO
//SENSORS
#define HYGROPORT PORTA
#define HYGRODDR DDRA
#define HYGROPIN PA2
#define TEMPPORT PORTB
#define TEMPDDR DDRB
#define TEMPPIN PB2
#define TEMPPININPUT PINB
//BUTTONS
#define BTNPORT PORTA
#define BTNDDR DDRA
#define UPBTN PA0
#define DOWNBTN PA3
#define ENTER PA4
#define CANCEL PA5
//LCD
#define LCDPORT PORTD
#define LCDDDR DDRD
#define LCD_RS_PIN PD2
#define LCD_E_PIN PD3
#define LCD_SHIFT 4
#define LCD_ROWS 2
#define LCD_COLS 16

//DELAYS
//ONEWIRE
#define ONEWIRE_DELAY_A_US 6
#define ONEWIRE_DELAY_B_US 64
#define ONEWIRE_DELAY_C_US 60
#define ONEWIRE_DELAY_D_US 10
#define ONEWIRE_DELAY_E_US 9
#define ONEWIRE_DELAY_F_US 55
#define ONEWIRE_DELAY_G_US 0
#define ONEWIRE_DELAY_H_US 480
#define ONEWIRE_DELAY_I_US 70
#define ONEWIRE_DELAY_J_US 410
//LCD
#define LCD_ENABLE_PULSE_US 3
#define LCD_DATA_DELAY_US 45
#define LCD_COMMAND_DELAY_US 45
#define LCD_CLEAR_DELAY_MS 2
#define LCD_CURSOR_HOME_DELAY_MS 2
#define LCD_EIGHT_BIT_DELAY_1_MS 5
#define LCD_EIGHT_BIT_DELAY_2_US 100

//COMMANDS
//LCD
#define LCD_COMMAND_RS 0
#define LCD_COMMAND_RW 0
#define LCD_CLEAR_DISPLAY_COMMAND 0b00000001
#define LCD_CURSOR_HOME_COMMAND 0b00000010
#define LCD_CURSOR_MOVE_RIGHT_COMMAND 0b00010100
//ENTRY SET
#define LCD_ENTRY_MODE_SET 0x04 // 0b0000.0100
#define LCD_ENTRY_MODE_SET_INCREMENT 0x02 // 0b0000.0010
#define LCD_ENTRY_MODE_SET_DECREMENT 0x00 // 0b0000.0000
#define LCD_ENTRY_MODE_SET_SHIFT 0x01 // 0b0000.0001
#define LCD_ENTRY_MODE_SET_NO_SHIFT 0x00 // 0b0000.0001
//DISPLAY ON OFF CONTROL
#define LCD_DISPLAY_ON_OFF_CONTROL 0x08 // 0b0000.1000
#define LCD_DISPLAY_ON_OFF_CONTROL_DISPLAY_ON 0x04 // 0b0000.0100
#define LCD_DISPLAY_ON_OFF_CONTROL_DISPLAY_OFF 0x00 // 0b0000.0000
#define LCD_DISPLAY_ON_OFF_CONTROL_CURSOR_ON 0x02 // 0b0000.0010
#define LCD_DISPLAY_ON_OFF_CONTROL_CURSOR_OFF 0x00 // 0b0000.0000
#define LCD_DISPLAY_ON_OFF_CONTROL_BLINK_ON 0x01 // 0b0000.0001
#define LCD_DISPLAY_ON_OFF_CONTROL_BLINK_OFF 0x00 // 0b0000.0000
//CURSOR OR DISPLAY SHIFT
#define LCD_CURSOR_DISPLAY_SHIFT 0x10 // 0b0001.0000
#define LCD_CURSOR_DISPLAY_SHIFT_DISPLAY_SHIFT 0x08 // 0b0000.1000
#define LCD_CURSOR_DISPLAY_SHIFT_CURSOR_MOVE 0x00 // 0b0000.0000
#define LCD_CURSOR_DISPLAY_SHIFT_RIGHT_SHIFT 0x04 // 0b0000.0100
#define LCD_CURSOR_DISPLAY_SHIFT_LEFT_SHIFT 0x00 // 0b0000.0000
//FUNCTION SET
#define LCD_FUNCTION_SET 0x20 // 0b0010.0000
#define LCD_FUNCTION_SET_EIGHT_BIT 0x10 // 0b0001.0000
#define LCD_FUNCTION_SET_FOUR_BIT 0x00 // 0b0000.0000
#define LCD_FUNCTION_SET_ONE_LINE 0x00 // 0b0000.0000
#define LCD_FUNCTION_SET_TWO_LINES 0x08 // 0b0000.1000
#define LCD_FUNCTION_SET_TEN_DOTS 0x04 // 0b0000.0100
#define LCD_FUNCTION_SET_EIGHT_DOTS 0x00 // 0b0000.0000
//SET DDRAM
#define LCD_SET_DDRAM 0x80 // 0b1000.0000
#define LCD_DDRAM_FIRST_ROW 0x00 // 0b0000.0000
#define LCD_DDRAM_SECOND_ROW 0x40 // 0b0100.0000
#endif /* GLOBAL_H_ */