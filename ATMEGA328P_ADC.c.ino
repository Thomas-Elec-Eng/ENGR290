/*ENGR 290 TEAM 5
ADC control*/
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
//#include "ATMEGA328P_UART.c"

void ADC_init(){
  ADMUX = (0<<REFS1)|(0<<REFS0)|(0<<ADLAR); // 010- ----
  ADCSRA = (1<<ADEN); // 1--- ----
  ADCSRA|=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); // ADC clock prescaler
}

uint16_t Read_ADC(uint8_t sel){
  ADMUX = (ADMUX & 0xF0)|(sel&0x0F);
  //DDRC = (0<<sel);
  ADCSRA |= (1<<ADSC);
  USART_Transmit_more("Waiting ");
  while (ADCSRA & (1<<ADSC));
  USART_Transmit_more("No More ");
  uint16_t low  = ADCL;
  uint16_t high = ADCH;
  return (high << 8) | low;
}

int main(void) {
    USART_Init();
    ADC_init();
    
    DDRB |= (1 << PB3);
    PORTB |= (1 << PB3);
    
    char string[40];
    
    while(1) {
        uint16_t adc_val = Read_ADC(1); // Read sensor on pin A1
      
        if (adc_val >= 610) {
            PORTB &= ~(1 << PB3);  // Set pin HIGH (LED ON)
            sprintf(string, "\r\nADC: %d -> <= 16cm (LED ON) ", adc_val);
        }
        else  {
            PORTB |= (1 << PB3); // Set pin LOW (LED OFF)
            sprintf(string, "\r\nADC: %d -> >= 49cm (LED OFF)", adc_val);
        }
        
        USART_Transmit_more(string);
        _delay_ms(200);
    }
}

// int main(){
//   USART_Init();
//   ADC_init();
//   char string[6];
//   //USART_Transmit_more("IR range finder test raw value");
//   while(true){
//     USART_Transmit_more("\nPass ");
//     //USART_Transmit_more(int_to_char(195));
//     sprintf(string, "%d", Read_ADC(1));
//     USART_Transmit_more(string);
//    _delay_ms(500); // Slow down output stream for readability

//   }
// }
