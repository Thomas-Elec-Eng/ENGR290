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

// sample main just to test if output is accurate to distance perception 

// int main(void) {
//     USART_Init();
//     ADC_init();
    
//     char string[10];
    
//     while(1) {
//         uint16_t adc_val = Read_ADC(1); // Read from analog pin A1 (ADC1)
        
//         // Threshold Logic based on targets
//         if (adc_val == 6) {
//             
//             USART_Transmit_more("Object not recognizable too close OR too far\r\n");
//         } 
//         else if (adc_val < 400) {
//             
//             USART_Transmit_more("Object closer than 20cm\r\n");
//         } 
//         else {
//             // beyod 20 cm but not soo far it cannot be detected
//             USART_Transmit_more("Object beyond 20cm but closer than 35cm\r\n");
//         }
        
//         _delay_ms(500); 
//     }
// }



int main(){
  USART_Init();
  ADC_init();
  char string[6];
  //USART_Transmit_more("IR range finder test raw value");
  while(true){
    USART_Transmit_more("\nPass ");
    //USART_Transmit_more(int_to_char(195));
    sprintf(string, "%d", Read_ADC(1));
    USART_Transmit_more(string);
   _delay_ms(500); // Slow down output stream for readability

  }
}
