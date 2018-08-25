/* ===================================================
 *  LORA ESP32 OLED develompent Board
 *  internal connecion for  SX1276 433MHz
 *  LoRa_IRQ     GPIO26
 *  LoRa_MOSI    GPIO27
 *  LoRa_MISO    GPIO19
 *  LoRa_RST     GPIO14
 *  LoRa_CS      GPIO18
 *  LoRa_SCK     GPIO5
 *  
 *  LED          GPIO25
 *  
 *  OLED display internal  connections
 *  OLED_RST     GPIO16
 *  OLED_SDA     GPIO4
 *  OLED_SCL     GPIO15
 *  
 *==================================================== 
 */



#include <SPI.h>
#include <LoRa.h>

#define LoRa_CS  18             // LORA CS pin
#define LoRa_RST 14             // LORA reset pin
#define LoRa_IRQ 26             // LORA IRQ pin

int counter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");

  LoRa.setPins(LoRa_IRQ, LoRa_RST, LoRa_CS);

//  LoRa.setTxPower(17);                     // 2 - 17
  /*
  LoRa.setSpreadingFactor(spreadingFactor);     // 6 - 12
  LoRa.setSignalBandwidth(signalBandwidth);     // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3, 41.7E3, 62.5E3, 125E3, and 250E3
  

*/
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
