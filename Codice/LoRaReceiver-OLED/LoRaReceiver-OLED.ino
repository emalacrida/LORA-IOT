#include <SPI.h>
#include <LoRa.h>
#include "SSD1306.h"

SSD1306  display(0x3c, 4, 15);

//OLED pins to ESP32 GPIOs via this connection:
//OLED_SDA -- GPIO4
//OLED_SCL -- GPIO15
//OLED_RST -- GPIO16


// WIFI_LoRa_32 ports

// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)

#define SS      18
#define RST     14
#define DI0     26
#define BAND    433E6


void setup() {
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH);

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  Serial.begin(115200);
  while (!Serial); //if just the the basic function, must connect to a computer
  delay(1000);

  Serial.println("LoRa Receiver");
  display.drawString(5, 5, "LoRa Receiver");
  display.display();
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(BAND)) {
    display.drawString(5, 25, "Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initial OK!");
  display.drawString(5, 25, "LoRa Initializing OK!");
  display.display();

  // Serial.println("LoRa Dump Registers");
  // LoRa.dumpRegisters(Serial);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packets
    Serial.print("Received packet. ");
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.drawString(1, 0, "Received packet: ");
    display.display();

    // read packet
    while (LoRa.available()) {
      String data = LoRa.readString();
      Serial.print(data);
      display.drawString(1, 15, data);
      display.display();
    }

    // print RSSI and SNS of packet
    Serial.print(" with RSSI ");
    Serial.print(LoRa.packetRssi());
    Serial.print(" / SNS ");
    Serial.println(LoRa.packetSnr());
    display.drawString(1, 30, "RSSI:  ");
    display.drawString(35, 30, (String)LoRa.packetRssi());
    display.drawString(55, 30, "/ SNR:  ");
    display.drawString(90, 30, (String)LoRa.packetSnr());
    display.display();
  }
}
