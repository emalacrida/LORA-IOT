/**
   E32-TTL-100 Transceiver Interface

  need series a 4.7k Ohm resistor between .
  UNO/NANO(5V mode)                E32-TTL-100
     --------*                      *------
    | D7     | <------------------> | M0   |
    | D8     | <------------------> | M1   |
    | A0     | <------------------> | AUX  |
    | D10(Rx)| <---> 4.7k Ohm <---> | Tx   |
    | D11(Tx)| <---> 4.7k Ohm <---> | Rx   |
     --------*                      *------
*/
#include <SoftwareSerial.h>

#define M0_PIN  7
#define M1_PIN  8
#define AUX_PIN A0
#define SOFT_RX 10
#define SOFT_TX 11

SoftwareSerial softSerial(SOFT_RX, SOFT_TX);  // RX, TX

// Module parameters values setup

byte head = 0xC0;        // C0 > permanent save   C2 > temporary save

byte addH = 0xFF;        // 00H - FFH
byte addL = 0xFF;        // 00H - FFH

// Speed byte
byte uart_parity = 0x00;
// 00xx xxxx 8N1*  > 00H
// 01xx xxxx 8O1   > 40H
// 10xx xxxx 8E1   > 80H
// 11xx xxxx 8N1   > D0H
byte uart_baud = 0x18;
// xx00 0xxx 1200  > 00H
// xx00 1xxx 2400  > 08H
// xx01 0xxx 4800  > 10H
// xx01 1xxx 9600* > 18H
// xx10 0xxx 19200 > 20H
// xx10 1xxx 38400 > 28H
// xx11 0xxx 57600 > 30H
// xx11 1xxx 115200 > 38H
byte air_rate = 0x00;
// xxxx x000 0.3K  > 00H
// xxxx x001 1.2K  > 01H
// xxxx x010 2.4K* > 02H
// xxxx x011 4.8K  > 03H
// xxxx x100 9.6K  > 08H
// xxxx x101 19.2K > 09H
// xxxx x110 19.2K > 0AH
// xxxx x111 19.2K > 0BH

// Channel 3 MSB rfu set to 0 (00-1F 410M+channel*1M)
byte channel = 0x17;
/*
xxx0 0000 410MHz  > 00H Ch 00
xxx0 0001 411MHz  > 01H Ch 01
xxx0 0010 415MHz  > 05H Ch 05
xxx1 0111 433MHz* > 17H CH 1A - 23
xxx1 1111 441MHz  > 1FH Ch 1F - 31
*/
// Options

byte fixed_trans = 0x00;
// 0xxx xxxx trasparent tx mode
// 1xxx xxxx fixed tx mode
byte io_drive_mode = 0x00;
// x0xx xxxx rx-tx-aux open collector
// x1xx xxxx tx-aux push-pull rx open collector
int wake_up_time = 0x00;
// xx00 0xxx 250ms*
// xx00 1xxx 500ms
// xx01 0xxx 750ms
// xx01 1xxx 1000ms
// xx10 0xxx 1250ms
// xx10 1xxx 1500ms
// xx11 0xxx 1750ms
// xx11 1xxx 2000ms
byte fec = 0x04;
// xxxx x0xx
// xxxx x1xx
byte tx_power = 0x00;
// xxxx xx00 20dBm*
// xxxx xx01 17dBm
// xxxx xx10 14dBm
// xxxx xx11 10dBm

// setup string construction

byte velocita = uart_parity | uart_baud | air_rate;
byte canale = channel;
byte opzioni = fixed_trans | wake_up_time | fec | tx_power;
uint8_t command_buf[8] = { head, head, head, addH, addL, velocita, canale, opzioni};

void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);

  // Lettura della configurazione salvata.


}

void loop() {
  Serial.print(command_buf[1], HEX);
  Serial.print(command_buf[2], HEX);
  Serial.print(command_buf[3], HEX);
  Serial.print(command_buf[5], HEX);
  Serial.print(command_buf[6], HEX);
  Serial.print(command_buf[7], HEX);
  Serial.println(command_buf[8], HEX);
  /*Serial.print(" ");
    Serial.print(indirizzo, HEX);
    Serial.print(" ");
    Serial.print(velocita, BIN);
    Serial.print(" ");
    Serial.print(canale, BIN);
    Serial.print(" ");
    Serial.println(opzioni, BIN);*/
  delay(1000);
}

void SwitchMode(MODE_TYPE mode)
{
  if (!chkModeSame(mode))
  {
    WaitAUX_H();

    switch (mode)
    {
      case MODE_0_NORMAL:
        // Mode 0 | normal operation
        digitalWrite(M0_PIN, LOW);
        digitalWrite(M1_PIN, LOW);
        break;
      case MODE_1_WAKE_UP:
        digitalWrite(M0_PIN, HIGH);
        digitalWrite(M1_PIN, LOW);
        break;
      case MODE_2_POWER_SAVIN:
        digitalWrite(M0_PIN, LOW);
        digitalWrite(M1_PIN, HIGH);
        break;
      case MODE_3_SLEEP:
        // Mode 3 | Setting operation
        digitalWrite(M0_PIN, HIGH);
        digitalWrite(M1_PIN, HIGH);
        break;
      default:
        return ;
    }

    WaitAUX_H();
    delay(10);
  }
}


