/**
 * @file hal.h
 *
 * @brief This file contains definitions for hardware abstraction
 *
 * @author Thomas Fischl
 * @copyright (c) 2013 Thomas Fischl

* 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef _HAL_
#define _HAL_

#define USART_BAUDRATE 38400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// ******************************** ATmega324P ***********************************
#if defined (__AVR_ATmega324P__)

#define DEFINE_DATAPOINTER uint16_t scriptdata_p = (uint16_t)scriptdata

#define hal_init() DDRC = (1 << PC3); DDRD = (1 << PD4); PORTD = ~(1 << PD4); // all inputs except PC3 and PD4
#define hal_getSwitch() ((PIND & (1 << PD3)) == 0)
#define hal_setLEDred(x) PORTC = (PORTC & ~(1 << PC3)) | ((!x) << PC3)
#define hal_setLEDgreen(x) PORTD = (PORTC & ~(1 << PD4)) | ((!x) << PD4)
#define hal_initUSART() UBRR0L = BAUD_PRESCALE; UBRR0H = (BAUD_PRESCALE >> 8); UCSR0B = (1 << TXEN0);
#define hal_txUSART(x) while (!( UCSRA0 & (1 << UDRE0))); UDR0 = x;

#define flash_readbyte(x) pgm_read_byte(x)

#define	ISP_OUT   PORTB
#define ISP_IN    PINB
#define ISP_DDR   DDRB
#define ISP_RST   PB4
#define ISP_MOSI  PB5
#define ISP_MISO  PB6
#define ISP_SCK   PB7

#define TCCR0 TCCR0B
#define TIMSK TIMSK0

// ******************************** ATmega1284P ***********************************
#elif defined (__AVR_ATmega1284P__)

#define DEFINE_DATAPOINTER uint32_t scriptdata_p = FAR(scriptdata);

#define hal_init() DDRC = (1 << PC3); DDRD = (1 << PD4); PORTD = ~(1 << PD4); // all inputs except PC3 and PD4
#define hal_getSwitch() ((PIND & (1 << PD3)) == 0)
#define hal_setLEDred(x) PORTC = (PORTC & ~(1 << PC3)) | ((!x) << PC3)
#define hal_setLEDgreen(x) PORTD = (PORTC & ~(1 << PD4)) | ((!x) << PD4)
#define hal_initUSART() UBRR0L = BAUD_PRESCALE; UBRR0H = (BAUD_PRESCALE >> 8); UCSR0B = (1 << TXEN0);
#define hal_txUSART(x) while (!( UCSRA0 & (1 << UDRE0))); UDR0 = x;

#define flash_readbyte(x) pgm_read_byte_far(x)

#define	ISP_OUT   PORTB
#define ISP_IN    PINB
#define ISP_DDR   DDRB
#define ISP_RST   PB4
#define ISP_MOSI  PB5
#define ISP_MISO  PB6
#define ISP_SCK   PB7

#define TCCR0 TCCR0B
#define TIMSK TIMSK0
// ****************************** unknown device *********************************
#else 
  #error "MCU not supported by HAL"
#endif


/**
 * @brief Macro to access strings defined in PROGMEM above 64kB
 */
#define FAR(var)                     \
({ uint_farptr_t tmp;                \
   __asm__ __volatile__(             \
       "ldi    %A0, lo8(%1)"  "\n\t" \
       "ldi    %B0, hi8(%1)"  "\n\t" \
       "ldi    %C0, hh8(%1)"  "\n\t" \
       : "=d" (tmp)                  \
       : "p"  (&(var)));             \
   tmp;                              \
})

#endif
