#define PPMHI PORTD |= _BV(PORTD4);
#define PPMLO PORTD &= ~_BV(PORTD4);
//written by doughboy @RCGroups and @multiwii.com 
//8 channel PPM sum using atmega328 @16mhz
//use all 8 channels of your tx receiver on atmega328 based FC
//
//     wiring
//                     +-\/-+
//    Reset->    PC6  1|    |28  PC5 A5  <- SCL*  
//      *RX-> RX PD0  2|    |27  PC4 A4  <- SDA*     
//      *TX-> TX PD1  3|    |26  PC3 A3  <- Trigger*     
//            D2 PD2  4|    |25  PC2 A2  <- Echo*      
//            D3 PD3  5|    |24  PC1 A1    
//   PPMSUM-> D4 PD4  6|    |23  PC0 A0    
//      +5v->    VCC  7|    |22  GND     <-Gnd
//      Gnd->    GND  8|    |21  AREF
//     XTAL->    PB6  9|    |20  AVCC    <-+5v
//     XTAL->    PB7 10|    |19  PB5 D13 <-LED
//      RX5-> D5 PD5 11|    |18  PB4 D12 <-RX4
//      RX6-> D6 PD6 12|    |17  PB3 D11 <-RX3     
//      RX7<- D7 PD7 13|    |16  PB2 D10 <-RX2     
//      RX0-> D8 PB0 14|    |15  PB1 D9  <-RX1  
//                     +----+
//   *I2C_GPS_NAV connections  
//   RX0-RX7 connections to radio receiver, in any order :)
//   PPMSUM goes to throttle pin on FC
//   Make sure to define PPMSUM on MultiWii config.h
//   sample ppmsum entry, move the values around until you get the correct definition
//   #define SERIAL_SUM_PPM THROTTLE,PITCH, YAW, ROLL,AUX1,AUX2,AUX3,AUX4,8,9,10,11

void PpmSum_init() {
  PCICR |= _BV(PCIE0) | _BV(PCIE2); //Pin Change Interrupt 0 and 2
  PCMSK0 |= _BV(PCINT0) | _BV(PCINT1) | _BV(PCINT2) | _BV(PCINT3) | _BV(PCINT4); //interrupt on PB0-PB4
  PCMSK2 |= _BV(PCINT21) | _BV(PCINT22) | _BV(PCINT23); //PD5 - PD6
  TCCR2A = 0;
  TCCR2B |= _BV(CS22) | _BV(CS20); //div 128 prescaler //16mhz/128=125khz =8us per count
  TIMSK2 |= _BV(OCIE2B);
  DDRD |= _BV(PORTD4);  //digital pin 4 output
}

ISR(PCINT0_vect) {
  pwm_in();
}

ISR(PCINT2_vect) {
  pwm_in();
}

ISR(TIMER2_COMPB_vect) {
  PPMLO;
}

void pwm_in() {
    PPMHI;
    TCNT2=0; 
    OCR2B=38; //8*38=3004s PPM SUM pulse  
}
