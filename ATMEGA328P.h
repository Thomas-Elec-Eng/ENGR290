/*ENGR 290 Team 5
The point of this header file is to define all addresses needed to control
This includes GPIO, UART and ADC*/

#ifndef _ATMEGA328P_H_
#define _ATMEGA328P_H_

#include <stdint.h>

/*  General information in case others don't know
    the volatile key work is to make sure the compiler doesn't make a short cut and has to read the pin address again
    This is very useful for inputs
    
    uin8_t is an unsigned 8 bit integer; the * afterwards is because this is a pointer to a register
    
    the * before volatile make it so the variable reads/writes into the memory instead of modifying the memory address */
// GPIO
#define MCUCR (*(volatile uint8_t *)0x55) //Page 72 of datasheet  MCU Control Register
#define IVCE  0
#define IVSEL 1
#define PUD   4 //global pull-ups disabler. 1 means everything is disabled
#define BODSE 5 //Read only
#define BODS  6 //Read only

#define PINB  (*(volatile uint8_t *)0x23) //Page 72 of datasheet   Read only
#define DDRB  (*(volatile uint8_t *)0x24) //Page 72 of datasheet   Set if port is Read or Write
#define PORTB (*(volatile uint8_t *)0x25) //Page 72 of datasheet  Read or write
#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7

#define PINC    (*(volatile uint8_t *)0x26) //Page 73 of datasheet   Read only
#define DDRC    (*(volatile uint8_t *)0x27) //Page 73 of datasheet   Set if port is Read or Write
#define PORTC   (*(volatile uint8_t *)0x28) //Page 73 of datasheet  Read or write
#define PC0     0
#define PC1     1
#define PC2     2
#define PC3     3
#define PC4     4
#define PC5     5
//BIT 6 IS RESET, DO NOT USE
//BIT 7 UNUSED

#define PIND    (*(volatile uint8_t *)0x29) //Page 73 of datasheet   Read only
#define DDRD    (*(volatile uint8_t *)0x2A) //Page 73 of datasheet   Set if port is Read or Write
#define PORTD   (*(volatile uint8_t *)0x2B) //Page 73 of datasheet  Read or write
#define PD0     0
#define PD1     1
#define PD2     2
#define PD3     3
#define PD4     4
#define PD5     5
#define PD6     6
#define PD7     7

//UART
#define UDR0    (*(volatile uint8_t *)0xC6)  //USART I/O data register
#define UBRR0H  (*(volatile uint8_t *)0xC5)  //USART baud rate register high; bit 4 to bit 7 are empty and lead to nothing
#define UBRR0L  (*(volatile uint8_t *)0xC4)  //USART baud rate register low

#define UCSR0C  (*(volatile uint8_t *)0xC2)
#define UCPOL0  0 //Clock Polarity; only for Synchronous mode
#define UCSZ00  1 //Character size  See Table 19-7 for clarification
#define UCPHA0  1 //SPI mode
#define UCSZ01  2 //Character size  See Table 19-7 for clarification
#define UDORD0  2 //SPI mode
#define USBS0   3 //Stop bit select; 0 means 1 bit, 1 means 2 bits
#define UPM00   4 //Parity Mode
#define UPM01   5 //Parity Mode
#define UMSEL00 6 //USART Mode Select See Table 19-4; Async: 0
#define UMSEL01 7 //USART Mode Select See Table 19-4; Async: 0

#define UCSR0B  (*(volatile uint8_t *)0xC1)
#define TXB80   0 //Transmit Data bit 8; this is only for when operating in 9 bit mode
#define RXB80   1 //Receive Data bit 8; this is only for when operating in 9 bit mode
#define UCSZ02  2 //Character size  See Table 19-7 for clarification
#define TXEN0   3 //Transmit Enable
#define RXEN0   4 //Receiver Enable
#define UDRIE0  5 //USART Data Register Empty Interrupt Enable
#define TXCIE0  6 //TX Complete Interrupt Enable
#define RXCIE0  7 //RX Complete Interrupt Enable

#define UCSR0A  (*(volatile uint8_t *)0xC0)
#define MPCM0   0 //Multi-processor Communication Mode
#define U2X0    1 //Double transmission speed (doubles the BAUD rate if set 1, only works for asynchonous)
#define UPE0    2 //USART Parity Error
#define DOR0    3 //Data OverRun
#define FE0     4 //Frame Error
#define UDRE0   5 //USART Data Register Empty; when UDR0 is empty flag
#define TXC0    6 //USART Transmit complete; when no new data is is present in transmit buffer (UDR0)
#define RXC0    7 //USART Receive complete; unread data flag

//ADC
#define ADMUX   (*(volatile uint8_t *)0x7C) //ADC Multiplexer Selection Register; Page 217 of datasheet
#define MUX0    0 //Analog Channel Selection Bits, Table 23-4
#define MUX1    1 //Analog Channel Selection Bits, Table 23-4
#define MUX2    2 //Analog Channel Selection Bits, Table 23-4
#define MUX3    3 //Analog Channel Selection Bits, Table 23-4
//BIT 4 UNUSED
#define ADLAR   5 //ADC Left adjust result. 0 seems more easily readable
#define REFS0   6 //Voltage Reference Selection, Table 23-3
#define REFS1   7 //Voltage Reference Selection, Table 23-3

#define ADCSRA  (*(volatile uint8_t *)0x7A) //ADC Control and Status Register A; Page 218 of datasheet
#define ADPS0   0 //ADC Prescaler Select bits, Table 23-5
#define ADPS1   1 //ADC Prescaler Select bits, Table 23-5
#define ADPS2   2 //ADC Prescaler Select bits, Table 23-5
#define ADIE    3 //ADC Interrupt Enable
#define ADIF    4 //ADC Interrupt flag
#define ADATE   5 //ADC Auto Trigger Enable
#define ADSC    6 //ADC Start Conversion
#define ADEN    7 //ADC Enable

#define ADCH    (*(volatile uint8_t *)0x79) //ADC Data Register Higher
#define ADCL    (*(volatile uint8_t *)0x78) //ADC Data Register Lower

#define ADCSRB  (*(volatile uint8_t *)0x7B) //ADC Control and Status Register B; Page 220 of datasheet
#define ADTS0   0 //ADC Auto Trigger Source, Table 23-6
#define ADTS1   1 //ADC Auto Trigger Source, Table 23-6
#define ADTS2   2 //ADC Auto Trigger Source, Table 23-6
//BIT 3 UNUSED
//BIT 4 UNUSED
//BIT 5 UNUSED
#define ACME    6 //Analog Comparator Multiplexer Input, See table 22-1 at page 202
//BIT 7 UNUSED

#endif //_ATMEGA328P_H_
