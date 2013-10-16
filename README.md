I2C_GPS_NAV_v2_2_PPMSUM
=======================

I2C-GPS-NAV firmware plus PPMSUM, 8 channel RX signals to PPMSUM multiplexer 

Based on I2C-GPS-NAV code by eosbandi
http://code.google.com/p/i2c-gps-nav/

This version adds my PPMSUM interrupt routine to multiplex the 8 channels from RX into one PPM sum signal line
to be connected to throttle pin on flight controller. Now you are really getting the most out of your 
Arduino Pro Mini board.

ASCII Wiring Diagram ;)
-----------------------

                      
                      +-\/-+
     Reset->    PC6  1|    |28  PC5 A5  <- SCL*  
       *RX-> RX PD0  2|    |27  PC4 A4  <- SDA*     
       *TX-> TX PD1  3|    |26  PC3 A3  <- Trigger*     
             D2 PD2  4|    |25  PC2 A2  <- Echo*      
             D3 PD3  5|    |24  PC1 A1    
    PPMSUM-> D4 PD4  6|    |23  PC0 A0    
       +5v->    VCC  7|    |22  GND     <-Gnd
       Gnd->    GND  8|    |21  AREF
      XTAL->    PB6  9|    |20  AVCC    <-+5v
      XTAL->    PB7 10|    |19  PB5 D13 <-LED
       RX5-> D5 PD5 11|    |18  PB4 D12 <-RX4
       RX6-> D6 PD6 12|    |17  PB3 D11 <-RX3     
       RX7<- D7 PD7 13|    |16  PB2 D10 <-RX2     
       RX0-> D8 PB0 14|    |15  PB1 D9  <-RX1  
                      +----+
     *I2C_GPS_NAV connections  
     RX0-RX7 connections to radio receiver, in any order :)
     PPMSUM goes to throttle pin on FC
     Make sure to define PPMSUM on MultiWii config.h
     sample ppmsum entry, move the values around until you get the correct definition
     #define SERIAL_SUM_PPM THROTTLE,PITCH, YAW, ROLL,AUX1,AUX2,AUX3,AUX4,8,9,10,11
