/*
 * one_wire.c
 *
 * Created: 11.12.2017 22:11:02
 *  Author: Matthias Hinrichs
 */
/************************************************************************/
/* Step 1. Initialization
 Step 2. ROM Command (followed by any required data exchange)
 Step 3. DS18S20 Function Command (followed by any required data exchange)                                                                     */
/************************************************************************/

#include <avr/io.h>
#include  <avr/cpufunc.h>
#include "one_wire/one_wire.h"
#include "global.h"
/**
 Setze den Temperaturport als eingang
 */
static inline void set_port_input() {
	TEMPDDR &= ~(1 << TEMPPIN);
}
/**
 Setze den Temperaturport aus ausgang
 */
static inline void set_port_output() {
	TEMPDDR |= (1 << TEMPPIN);
}
/**
 Setze den Temperaturport auf low
 */
static inline void set_temperature_port_down() {
	TEMPPORT &= ~(1 << TEMPPIN);

}

/**
 Setze den Temperaturport auf high
 */
static inline void set_temperature_port_high() {
	TEMPPORT |= (1 << TEMPPIN);
}
/**
 * Reset auf dem Onewire wiedergeben
 */
uint8_t reset() {
	uint8_t read_slave_bit = 0;
	// Bus auf low ziehen und 480us warten
	set_temperature_port_down();
	set_port_output();
	_delay_us(ONEWIRE_DELAY_H_US);
	// Bus loslassen und 70us warten
	set_temperature_port_high();
	_delay_us(ONEWIRE_DELAY_I_US);
	// Buswert lesen und warten bis der zweite 480us-Slot zu Ende ist
	read_slave_bit = (TEMPPININPUT & (1 << TEMPPIN));
	_delay_us(ONEWIRE_DELAY_J_US);
	// Buswert zurueckgeben
	return read_slave_bit;
}
/**
 * \brief Schreibe ein einzelnes bit auf den onewire
 * \param uint8_t bit Bit das geschrieben werden soll
 */
void write_one_bit(uint8_t bit) {
	set_port_output();
	set_temperature_port_down();
	//_delay_us(ONEWIRE_DELAY_A_US);
	if (bit) {
		_delay_us(ONEWIRE_DELAY_A_US); //copy von z63
		set_port_input();
		_delay_us(ONEWIRE_DELAY_B_US);

	} else {
		_delay_us(ONEWIRE_DELAY_C_US);
		set_port_input();
		_delay_us(ONEWIRE_DELAY_D_US);
	}
}
/**
 * \brief Lese ein bit vom onewire. Ein readslot
 * \return 0 wenn kein bit gesendet wurde ansonsten 1
 */
uint8_t read_one_bit() {
	uint8_t read_bit = 0;
	set_port_output();
	set_temperature_port_down();
	_delay_us(ONEWIRE_RESET_SLOT);
	// Test application_note one-wire page 6 of 12 OWReadBit uses delay(A)
	set_port_input();
	_delay_us(ONEWIRE_DELAY_E_US);
	if ((TEMPPININPUT & (1 << TEMPPIN))) {
		read_bit = 1;
	}
	_delay_us(ONEWIRE_DELAY_F_US);
	return read_bit;

}
/**
 * \brief Lese ein byte auf dem onewire
 * \return das gelesene byte
 */
uint8_t read_byte() {
	uint8_t result = 0;
	for (uint8_t i = 0; i < 8; i++) {
		result >>= 1;
		if (read_one_bit()) {
			result |= 0x80;
		}
	}
	return result;
}
/**
 * \breif schreibe ein byte auf dem onewire
 * \param uint8_t byte Byte das geschrieben werden soll
 */
void write_byte(uint8_t byte) {
	for (uint8_t i = 0; i < 8; i++) {
		write_one_bit(byte & 0x01);
		byte >>= 1;
	}
}

uint8_t one_wire_reset() {
	return reset();
}

void one_wire_write_byte(uint8_t data) {
	write_byte(data);
}

uint8_t one_wire_read_bit() {
	return read_one_bit();
}

uint8_t one_wire_read_byte() {
	return read_byte();
}
