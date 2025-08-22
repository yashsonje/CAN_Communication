#include <ESP32-TWAI-CAN.hpp>

CanFrame CAN;

#define tx 21
#define rx 22
void setup() {
  Serial.begin(115200);
  if (!CAN.begin(500000)) {
    Serial.println("CAN Init Failed");
    while (1);
  }
  Serial.println("CAN Bus Ready");
}

void loop() {
  CAN_frame_t tx = { .identifier = 0x100, .data_length_code = 2, .data = { 0xAB, 0xCD } };
  if (CAN.write(tx)) Serial.println("Sent 0x100 AB CD");
  delay(500);

  CAN_frame_t rx;
  if (CAN.read(rx)) {
    Serial.print("Got ID 0x"); Serial.print(rx.identifier, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < rx.data_length_code; i++) {
      Serial.printf("%02X ", rx.data[i]);
    }
    Serial.println();
  }
}
