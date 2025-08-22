#include <FlexCAN_T4.h>
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;

void setup() {
  Serial.begin(115200);
  can1.begin();
  can1.setBaudRate(500000);
}

void loop() {
  CAN_message_t msg;
  if (can1.read(msg)) {
    Serial.print("Teensy Received ID: 0x");
    Serial.print(msg.id, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < msg.len; i++) {
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    Serial.println();
  }
}
