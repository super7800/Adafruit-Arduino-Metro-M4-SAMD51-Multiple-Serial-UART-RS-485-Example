/*********************************************************************************************************************
Multiple (6) RS485 UART Example Code.
Firmware Rev. 1.1
super7800 2025

Do whatever you want with this, idc, not a software engineer, dont care about liscence. This code worked great for me.
Will it work great for you? Dunno.

For a adafruit metro m4 using a samd51j19a. Mine is on a custom board.
*********************************************************************************************************************/

#include <Arduino.h>

/*********************************************************************************************************************
Hardware Definitions
*********************************************************************************************************************/

// Interface A. Uses SERCOM 5. Serial 6.
#define RE1 42 // PB11
#define DE1 41 // PB10
#define SerialPort1 Serial6
#define DI1 52 // PB01

// Interface B. Uses SERCOM 0. Serial 4.
#define RE2 6
#define DE2 5
#define SerialPort2 Serial4
#define DI2 51 // PB00

// Interface C. Uses SERCOM 4. Serial 2.
#define RE3 50 // PA15
#define DE3 24
#define SerialPort3 Serial2
#define DI3 47 // PB31

// Interface D. Uses SERCOM 2. Serial 5.
#define RE4 11
#define DE4 10
#define SerialPort4 Serial5
#define DI4 A0

// Interface E. Uses SERCOM 1. Serial 3.
#define RE5 2
#define DE5 3
#define SerialPort5 Serial3
#define DI5 53 // PB04

// Interface F. Uses SERCOM 3. Serial 1.
#define RE6 8
#define DE6 9
#define SerialPort6 Serial1
#define DI6 54 // PB05

const uint16_t RE_PINS[6] = {RE1, RE2, RE3, RE4, RE5, RE6};
const uint16_t DE_PINS[6] = {DE1, DE2, DE3, DE4, DE5, DE6};
const uint16_t DI_PINS[6] = {DI1, DI2, DI3, DI4, DI5, DI6};
HardwareSerial* SERIAL_PORTS[6] = { &SerialPort1, &SerialPort2, &SerialPort3, &SerialPort4, &SerialPort5, &SerialPort6 };

/*********************************************************************************************************************
Configuration Settings
*********************************************************************************************************************/

// Port Settings
uint16_t BAUD_RATE[6] = {19200, 19200, 19200, 19200, 19200, 19200};

/*********************************************************************************************************************
Main Setup Function
*********************************************************************************************************************/

void setup() {

  Serial.begin(115200);
  while (!Serial) { ; }

  // Configure Pinmodes
  for (int x = 0; x <= 5; x++) {
    pinMode (RE_PINS[x], OUTPUT);
    pinMode (DE_PINS[x], OUTPUT);
    pinMode (DI_PINS[x], INPUT);
    SERIAL_PORTS[x]->begin(BAUD_RATE[x]);
  }

}

void loop() {
  
  static unsigned long lastMillis = 0;

  // Example: every 2 seconds, do a read from port 0 at address 85, register 0x0101
  // Then do a write to port 0 at address 85, register 0x0102 with some test value
  if (millis() - lastMillis >= 2000) {
    lastMillis = millis();

   for (int x = 0; x <=5; x++) {

      Serial.print("\n--- Demonstration on Port ");
      Serial.print(x);
      Serial.println(" ---");

      // 1) Read register 0x0101 from slave address 85
      int readVal = transmitRecieveHandler(x, 85, 0x0101, -1);

      if (readVal < 0) {
        Serial.print("Read Error: code = ");
        Serial.println(readVal);
      }
        
      else {
        Serial.print("Read Success: value = ");
        Serial.println(readVal);
      }
    }
  }
}

/*********************************************************************************************************************
Control the RS-485 DE/RE
*********************************************************************************************************************/

static inline void rs485SetTransmit(uint8_t port, bool txOn) {
  // half-duplex driver:
  // DE=HIGH => driver enabled
  // RE=HIGH => receiver disabled (active low)
  if (txOn) {
    digitalWrite(DE_PINS[port], HIGH);
    digitalWrite(RE_PINS[port], HIGH);
  }
  else {
    digitalWrite(DE_PINS[port], LOW);
    digitalWrite(RE_PINS[port], LOW);
  }
}

/*********************************************************************************************************************
Standard Modbus CRC16
*********************************************************************************************************************/

uint16_t modbusCRC(const uint8_t *buf, size_t len) {
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; i++) {
    crc ^= buf[i];
    for (int b = 0; b < 8; b++) {
      if (crc & 0x0001) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

/*********************************************************************************************************************
Read the response (typical ~7 bytes for 1 reg).
Return the number of bytes read.
*********************************************************************************************************************/

int readSerialResponse(uint8_t port, uint8_t *resp, int maxLen, unsigned long overallTimeoutMs = 500) {
  unsigned long startTime = millis();
  int count = 0;

  while ((millis() - startTime) < overallTimeoutMs) {
    // If there's data available, read it
    if (SERIAL_PORTS[port]->available()) {
      resp[count++] = (uint8_t)SERIAL_PORTS[port]->read();
      // Restart the timeout counter each time we successfully read a byte
      startTime = millis();
      if (count >= maxLen) {
        break;  // Avoid overrun
      }
    }
  }
  return count;
}

/*********************************************************************************************************************
Universal Read/Write Handler
 - If DATA == -1 => read 1 register (function code 0x04)
 - Otherwise => write 1 register (function code 0x06) with value = DATA
Returns:
  - For read: the 16-bit register value on success, or negative on error
  - For write: the DATA written on success, or negative on error
*********************************************************************************************************************/
int transmitRecieveHandler(uint8_t port, uint16_t ADDRESS, uint16_t REGISTER, int16_t DATA) {
  // Prepare the Modbus frame
  uint8_t req[8];
  uint8_t funcCode;
  if (DATA == -1) {
    // READ: Function code 0x04 (read input register)
    funcCode = 0x04;
    req[0] = ADDRESS;
    req[1] = funcCode;
    req[2] = (REGISTER >> 8) & 0xFF;
    req[3] = (REGISTER & 0xFF);
    req[4] = 0x00;  // number of registers hi
    req[5] = 0x01;  // number of registers lo
    uint16_t crc = modbusCRC(req, 6);
    req[6] = (uint8_t)(crc & 0xFF);
    req[7] = (uint8_t)(crc >> 8);
  } else {
    // WRITE: Function code 0x06 (write single holding register)
    funcCode = 0x06;
    req[0] = ADDRESS;
    req[1] = funcCode;
    req[2] = (REGISTER >> 8) & 0xFF;
    req[3] = (REGISTER & 0xFF);
    // Split DATA into 2 bytes
    req[4] = (DATA >> 8) & 0xFF;
    req[5] = (DATA & 0xFF);
    uint16_t crc = modbusCRC(req, 6);
    req[6] = (uint8_t)(crc & 0xFF);
    req[7] = (uint8_t)(crc >> 8);
  }

  // Enable driver & transmit
  rs485SetTransmit(port, true);
  delayMicroseconds(100); // small gap
  SERIAL_PORTS[port]->write(req, 8);
  SERIAL_PORTS[port]->flush();
  rs485SetTransmit(port, false);

  // Read response
  uint8_t resp[32];
  int got = readSerialResponse(port, resp, sizeof(resp), 500);
  if (got == 0) {
    return -2; // no response
  }

  // Typical valid read response is 7 bytes for 1 register: [Addr, func, 2, DataHi, DataLo, CRCLo, CRCHi]
  // Typical valid write response is 8 bytes: [Addr, func, RegHi, RegLo, DataHi, DataLo, CRCLo, CRCHi]
  // Quick checks:
  if (got < 5) {
    return -3; // too few bytes for any valid modbus
  }

  // Check for correct address and function code
  if (resp[0] != ADDRESS) {
    return -4; // address mismatch
  }
  // If there's an exception, the function code might have 0x80 set
  if ((resp[1] & 0x7F) != funcCode) {
    return -5; // function mismatch or exception
  }

  // Check CRC
  if (got >= 4) {
    uint16_t respCRC = (resp[got - 1] << 8) | resp[got - 2];
    uint16_t calcCRC = modbusCRC(resp, got - 2);
    if (respCRC != calcCRC) {
      return -6; // CRC error
    }
  }

  // If it was a READ
  if (DATA == -1) {
    // Expecting something like: [Addr, 0x04, 0x02, dataHi, dataLo, CRCLo, CRCHi]
    if (got < 7) {
      return -7; // incomplete for a read
    }
    if (resp[1] == funcCode && resp[2] == 2) {
      // Parse the data
      int16_t rawVal = (resp[3] << 8) | resp[4];
      return rawVal;
    } else {
      return -8; // unexpected read format
    }
  }
  else {
    // WRITE
    // Expecting echo of [Addr, 0x06, RegHi, RegLo, DataHi, DataLo, CRCLo, CRCHi]
    if (got < 8) {
      return -9; // incomplete for a write
    }
    // Optionally validate that the register and data match
    if (resp[2] == req[2] && resp[3] == req[3] && resp[4] == req[4] && resp[5] == req[5]) {
      // Looks good
      return DATA; // Return the value we wrote as success
    } else {
      return -10; // mismatch in the echoed data
    }
  }
}
