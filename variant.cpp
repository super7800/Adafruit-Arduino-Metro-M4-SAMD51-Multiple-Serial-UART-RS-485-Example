/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[]=
{
  // 0..13 - Digital pins
  // ----------------------
  // 0/1 - SERCOM/UART (Serial1)
  { PORTA, 23, PIO_SERCOM, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH3, TC4_CH1, EXTERNAL_INT_7 }, // RX: SERCOM3/PAD[1] (0u1)
  { PORTA, 22, PIO_SERCOM, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH2, TC4_CH0, EXTERNAL_INT_6 }, // TX: SERCOM3/PAD[0] (1u1)

  // 2..12
  // Digital Low
  { PORTB,  17, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH5, NOT_ON_TIMER,  EXTERNAL_INT_1 }, // d2
  { PORTB,  16, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH4, NOT_ON_TIMER, EXTERNAL_INT_0 }, // d3
  { PORTB,  13, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH1, TC4_CH1, EXTERNAL_INT_13 }, // d4 (4ul)
  { PORTB,  14, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC4_CH0, TC5_CH0, EXTERNAL_INT_14 }, // d5
  { PORTB,  15, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC4_CH1, TC5_CH1, EXTERNAL_INT_15 }, // d6
  { PORTB,  12, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH0, TC4_CH0, EXTERNAL_INT_12 }, // d7 (7ul)

  // Digital High
  { PORTA,  21, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH1, NOT_ON_TIMER, EXTERNAL_INT_5 }, // d8
  { PORTA,  20, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, TCC0_CH0, NOT_ON_TIMER, EXTERNAL_INT_4 }, // d9
  { PORTA,  18, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH2, TC3_CH0, EXTERNAL_INT_2 }, // d10
  { PORTA,  19, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH3, TC3_CH1, EXTERNAL_INT_3 }, // d11
  { PORTA,  17, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH1, TC2_CH1, EXTERNAL_INT_1 }, // d12 (12u1)

  // 13 (LED)
  { PORTA,  16, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH0, TC2_CH0, EXTERNAL_INT_0  }, // d13 (13u1)

  // 14..19 - Analog pins
  // --------------------
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // A0
  { PORTA,  5, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel5, NOT_ON_PWM, TC0_CH1, EXTERNAL_INT_5 }, // A1 (15u1) 
  { PORTA,  6, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel6, TC1_CH0, TC1_CH0, EXTERNAL_INT_6 }, // A2
  { PORTA,  4, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel4, TC0_CH0, TC0_CH0, EXTERNAL_INT_4 }, // A3 (17u1) 
  { PORTB,  8, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel2, TC4_CH0, TC4_CH0, EXTERNAL_INT_8 }, // A4
  { PORTB,  9, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel3, TC4_CH1, TC4_CH1, EXTERNAL_INT_9 }, // A5

  // Extra Analog pins! 20..21
  { PORTB,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel14, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // A6 same as sda
  { PORTB,  3, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel15, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, // A7 same as scl

  // 22..23 I2C pins (SDA/SCL)
  // ----------------------
  { PORTB,  2, PIO_SERCOM_ALT, PIN_ATTR_PWM_F, No_ADC_Channel, TCC2_CH2, NOT_ON_TIMER, EXTERNAL_INT_2 }, // D20 same as sda (22u1)
  { PORTB,  3, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, // D21 same as scl (23u1)

  // 24..26 - SPI pins (ICSP:MISO,SCK,MOSI)
  // ----------------------
  { PORTA,  14, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC3_CH0, TC3_CH0, EXTERNAL_INT_14 }, // d24 (24u)
  { PORTA,  13, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH1, TC2_CH1, EXTERNAL_INT_13 }, // d25 (25u)
  { PORTA,  12, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH0, TC2_CH0, EXTERNAL_INT_12 }, // d26 (26u)

  // 27..28 - RX/TX LEDS (PB06/PA27)
  // --------------------
  { PORTB, 6, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, // used as output only
  { PORTA, 27, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 }, // used as output only

  // 29..31 - USB
  // --------------------
  { PORTB, 7, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, // USB Host enable
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8 }, // USB/DM
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9 }, // USB/DP

  // 32..34 - Secondary SPI
  // ----------------------
  { PORTA,  18, PIO_SERCOM, PIO_SERCOM, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2  }, //same as d10
  { PORTA,  19, PIO_SERCOM, PIO_SERCOM, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3  }, //same as d11
  { PORTA,  17, PIO_SERCOM, PIO_SERCOM, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1  }, //same as d12

  // 35 - Secondary SPI cs
  { PORTA,  16, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0  }, //same as d10

  // 36 (AREF)
  { PORTA, 3, PIO_ANALOG, PIN_ATTR_ANALOG, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, // DAC/VREFP

  // ----------------------
  // 37 - 38 Alternate use of A0 and A1 (DAC output)
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // DAC/VOUT[0]
  { PORTA,  5, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 }, // DAC/VOUT[1]

  // 39 - LED #13 duplicate placeholder
  { PORTA,  16, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH0, TC2_CH0, EXTERNAL_INT_0  },

  // 40 - Internal NeoPixel
  { PORTB, 22, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, // used as output only

  // ----------------------
  // 41 - 46 QSPI (SCK, CS, IO0, IO1, IO2, IO3)
  { PORTB, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 }, //41
  { PORTB, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 }, //42
  { PORTA, 8, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI }, //43
//  { PORTA, 9, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9 },
//  { PORTB,  8, PIO_ANALOG, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel2, TC4_CH0, TC4_CH0, EXTERNAL_INT_8 },
  { PORTA, 9, PIO_COM, PIN_ATTR_PWM_E, No_ADC_Channel, TC0_CH1, NOT_ON_TIMER, EXTERNAL_INT_9 }, //44
  { PORTA, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 }, //45
  { PORTA, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 }, //46
  
  // 47 - 54 added by super7800.
  { PORTB, 31, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 }, //47
  { PORTB, 23, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, //48
  { PORTA, 7, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, //49
  { PORTA, 15, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7 }, //50
  { PORTB, 0, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0 }, //51
  { PORTB, 1, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1 }, //52
  { PORTB, 4, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4 }, //53
  { PORTB, 5, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 }, //54
  
  { PORTA,  4, PIO_SERCOM_ALT, (PIN_ATTR_ANALOG|PIN_ATTR_PWM_E), ADC_Channel4, TC0_CH0, TC0_CH0, EXTERNAL_INT_4 }, // A3 (55u1)
  { PORTB,  13, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH1, TC4_CH1, EXTERNAL_INT_13 }, // d4 (56ul)
  { PORTB,  12, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH0, TC4_CH0, EXTERNAL_INT_12 }, // d7 (57ul)
  { PORTA,  17, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH1, TC2_CH1, EXTERNAL_INT_1 }, // d12 (58u1)
  { PORTA,  16, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH0, TC2_CH0, EXTERNAL_INT_0  }, // d13 (59u1)
  { PORTA,  5, PIO_SERCOM_ALT, PIN_ATTR_ANALOG, ADC_Channel5, NOT_ON_PWM, TC0_CH1, EXTERNAL_INT_5 }, // A1 (60u1)
} ;

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TCC3, TCC4, TC0, TC1, TC2, TC3, TC4, TC5 } ;
const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM+TC_INST_NUM] = { TCC0_GCLK_ID, TCC1_GCLK_ID, TCC2_GCLK_ID, TCC3_GCLK_ID, TCC4_GCLK_ID, TC0_GCLK_ID, TC1_GCLK_ID, TC2_GCLK_ID, TC3_GCLK_ID, TC4_GCLK_ID, TC5_GCLK_ID } ;


// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;

// sercom 3  pins 1 and 0
Uart Serial1( &sercom3, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX ) ;

void SERCOM3_0_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM3_1_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM3_2_Handler()
{
  Serial1.IrqHandler();
}
void SERCOM3_3_Handler()
{
  Serial1.IrqHandler();
}

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

// Sercom 1 pins 13 and 12
Uart Serial3( &sercom1, PIN_SERIAL3_RX, PIN_SERIAL3_TX, PAD_SERIAL3_RX, PAD_SERIAL3_TX ) ;

void SERCOM1_0_Handler()
{
  Serial3.IrqHandler();
}
void SERCOM1_1_Handler()
{
  Serial3.IrqHandler();
}
void SERCOM1_2_Handler()
{
  Serial3.IrqHandler();
}
void SERCOM1_3_Handler()
{
  Serial3.IrqHandler();
}

// Sercom 0 pins A3 and A1
Uart Serial4( &sercom0, PIN_SERIAL4_RX, PIN_SERIAL4_TX, PAD_SERIAL4_RX, PAD_SERIAL4_TX ) ;

void SERCOM0_0_Handler()
{
  Serial4.IrqHandler();
}
void SERCOM0_1_Handler()
{
  Serial4.IrqHandler();
}
void SERCOM0_2_Handler()
{
  Serial4.IrqHandler();
}
void SERCOM0_3_Handler()
{
  Serial4.IrqHandler();
}

// Sercom 2 pins 26 and 25
Uart Serial5( &sercom2, PIN_SERIAL5_RX, PIN_SERIAL5_TX, PAD_SERIAL5_RX, PAD_SERIAL5_TX ) ;

void SERCOM2_0_Handler()
{
  Serial5.IrqHandler();
}
void SERCOM2_1_Handler()
{
  Serial5.IrqHandler();
}
void SERCOM2_2_Handler()
{
  Serial5.IrqHandler();
}
void SERCOM2_3_Handler()
{
  Serial5.IrqHandler();
}

// Sercom 5 pins 20 and 21
Uart Serial6( &sercom5, PIN_SERIAL6_RX, PIN_SERIAL6_TX, PAD_SERIAL6_RX, PAD_SERIAL6_TX ) ;

void SERCOM5_0_Handler()
{
  Serial6.IrqHandler();
}
void SERCOM5_1_Handler()
{
  Serial6.IrqHandler();
}
void SERCOM5_2_Handler()
{
  Serial6.IrqHandler();
}
void SERCOM5_3_Handler()
{
  Serial6.IrqHandler();
}
