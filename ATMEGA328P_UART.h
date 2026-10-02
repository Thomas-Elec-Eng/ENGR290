//ENGR 290 Team 5 UART functions

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR ((F_CPU / (BAUD * 16UL)) - 1)

#include <avr/io.h>

void USART_Init(){
/*Set baud rate */
UBRR0H = (unsigned char)(UBRR>>8);
UBRR0L = (unsigned char)UBRR;
//Enable receiver and transmitter 
UCSR0B = (1<<RXEN0)|(1<<TXEN0); //---1 1---
// Set frame format: 8data, 2stop bit
UCSR0C = (0<<UMSEL00)|(1<<USBS0)|(3<<UCSZ00); //00-- 111-
}

void USART_Transmit(unsigned char data){
// Wait for empty transmit buffer 
while (!(UCSR0A & (1<<UDRE0)));
// Put data into buffer, sends the data 
UDR0 = data;
}

unsigned char USART_Receive(void){
// Wait for data to be received
while (!(UCSR0A & (1<<RXC0)));
// Get and return received data from buffer
return UDR0;
}

void USART_Transmit_more(char message[]){
  for (int i=0; message[i]!= '\0'; i++){
    USART_Transmit(message[i]);
  }
}

//Testing code
//int main(){
//	USART_Init();
//	//char hello[] = "Hello World";
//  USART_Transmit_more("Hello World");
//	while (true)
//    {
//        unsigned char received_char = USART_Receive();
//        USART_Transmit(received_char);
//    }
//  return 0;
//}
