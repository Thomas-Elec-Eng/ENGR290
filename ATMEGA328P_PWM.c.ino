/*ENGR 290 TEAM 5
Ultrasonic Control HCSR04*/

#include "ATMEGA328P.h"
#include "ATMEGA328P_UART.c"

#define ISR(vector) void vector (void) __attribute__ ((signal, used, externally_visible)); void vector (void)

//Global variable
volatile uint16_t pulse_start = 0;
volatile uint16_t pulse_end = 0;
volatile bool pulse_ready = false; 

void delay_us(uint16_t us){
  TCCR0A = 0x00;        
  TCCR0B = (1<<CS01);   //0.5us
  TCNT0 = 0;
  //SREG &= ~(1<<I);
  //USART_Transmit_more("DelayUS ");
  while(true){
    if(TCNT0>(us*2)){
      break;
    }
  }
  TCCR0B = 0x00;        //turn off clock input to counter
  //SREG |= (1<<I);
}

void delay_ms(uint16_t ms){
  while(ms > 0){
    delay_us(125);
    delay_us(125);
    delay_us(125);
    delay_us(125);
    delay_us(125);
    delay_us(125);
    delay_us(125);
    delay_us(125);
    ms--;
  }
}

void HCSR04_init(){
  DDRB |= (1<<PB5); //output Trigger
  PORTB &= ~(1<<PB5);
  DDRD &= ~(1<<PD3); //input echo
  PORTD &= ~(1<<PD3);

  TCCR1A = 0x00;
  TCCR1B = (1<<CS11);

  EICRA |= (1<<ISC10);
  EIMSK |= (1<<INT1);

  SREG |= (1<<I);
}

void trigger_sensor(){
  pulse_ready = false;
  USART_Transmit_more("Trigger ");
  PORTB |= (1<<PB5);
  delay_us(10);
  PORTB &= ~(1<<PB5);
  USART_Transmit_more("AfterDelay ");
}

uint16_t getdistance_mm(){
  uint16_t duration;
  if(pulse_end >= pulse_start){
    duration = pulse_end - pulse_start;
  } else {
    duration = 65535 - pulse_start + pulse_end;
  }
  uint32_t distance = ((uint32_t)duration * 86) / 1000;
  return (uint16_t)distance;
}

ISR(INT1_vect){
  //USART_Transmit_more("Interrupt\n ");
  if(PIND & (1<<PD3)){
    pulse_start = TCNT1;
  } else {
    pulse_end = TCNT1;
    pulse_ready = true;
  }
}

int main(){
  HCSR04_init();
  USART_Init();
  //USART_Transmit_more("Counter0 actived, giving raw values");
  char string[16];
  while(true){
    trigger_sensor();
    uint32_t timeout = 20000000;
    while (!pulse_ready && timeout >0 ){
      timeout--;
    }
    USART_Transmit_more("AfterTimeout\n");
    if(pulse_ready){
      USART_Transmit_more("\rUltrasonic distance value (mm): ");
      sprintf(string, "%d", getdistance_mm());
      USART_Transmit_more(string);
    } else {
      USART_Transmit_more("Sensor Error: Line Timeout\n");
    }
    delay_ms(60);
  }
}
