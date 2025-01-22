# Adafruit-Arduino-Metro-M4-SAMD51-Multiple-Serial-UART-RS-485-Example
Example of having 6 UART active on a single board.

These work as-is without the need for additional modification if you are using the metro M4. This file also defines all the pins not normally broken out.

Files provided are the variant.h and variant.cpp files, some basic basic example code, and the physical connections i used. For RS-485 MODBUS ETC you likely will need a driver.

Shows how to edit the variant.h and variant.cpp files for a metro m4 board. this would also work for the grand central m4, ETC, but will just need different pin definitions.

Essentially, you add to the variant.h

// Serial2
#define PIN_SERIAL2_RX       (56ul) // SERCOM4.1

#define PIN_SERIAL2_TX       (57ul) // SERCOM4.0

#define PAD_SERIAL2_TX       (UART_TX_PAD_0)

#define PAD_SERIAL2_RX       (SERCOM_RX_PAD_1)

for every additional serial you wish to create. Then, at the bottom you add

extern Uart Serial2;

for every additional serial. Youll notice the 56ul, 57ul. These are created in the variant.cpp. In the variant.cpp, i recommend creating new pin lines, i.e. 

  { PORTA,  4, PIO_SERCOM_ALT, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel4, TC0_CH0, TC0_CH0, EXTERNAL_INT_4 }, // A3 (55u1)
  
  { PORTB,  13, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH1, TC4_CH1, EXTERNAL_INT_13 }, // d4 (56ul)
  
  { PORTB,  12, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH0, TC4_CH0, EXTERNAL_INT_12 }, // d7 (57ul)
  
  { PORTA,  17, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH1, TC2_CH1, EXTERNAL_INT_1 }, // d12 (58u1)
  
  { PORTA,  16, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH0, TC2_CH0, EXTERNAL_INT_0  }, // d13 (59u1)
  
  { PORTA,  5, PIO_SERCOM_ALT, PIN_ATTR_ANALOG, ADC_Channel5, NOT_ON_PWM, TC0_CH1, EXTERNAL_INT_5 }, // A1 (60u1)

instead of modifying the existing lines. Adding instead of modifying helps ensure libraries still work fine. Instead of the usual PIO_ANALOG, PIO_DIGITAL, ETC instead use the
appropriate PIO_SERCOM or PIO_SERCOM_ALT case depending. If you dont know which, you can just test it both ways until it works.

At the bottom of the variant.cpp file add this for each additional serial

// Sercom 4 pins 7 and 4
Uart Serial2( &sercom4, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX ) ;

void SERCOM4_0_Handler()
{
  Serial2.IrqHandler();
}
void SERCOM4_1_Handler()
{
  Serial2.IrqHandler();
}
void SERCOM4_2_Handler()
{
  Serial2.IrqHandler();
}
void SERCOM4_3_Handler()
{
  Serial2.IrqHandler();
}
