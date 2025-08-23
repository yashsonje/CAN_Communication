#include <FlexCAN_T4.h>

// Create CAN object for CAN1 (Teensy 4.1 has CAN1, CAN2, CAN3)
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize CAN1 at 500 kbps (same as ESP32)
  Can1.begin();
  Can1.setBaudRate(500000);

  Serial.println("Teensy CAN Receiver Ready");
}

void loop() {
  CAN_message_t msg;

  if (Can1.read(msg)) {
    Serial.print("CAN ID: 0x");
    Serial.print(msg.id, HEX);
    Serial.print("  DLC: ");
    Serial.print(msg.len);
    Serial.print("  Data: ");

    for (uint8_t i = 0; i < msg.len; i++) {
      Serial.print(msg.buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    // Decode PS4 data
    if (msg.id == 0x101 && msg.len == 8) {
      uint16_t buttons = msg.buf[0] | (msg.buf[1] << 8);
      uint8_t dpad     = msg.buf[2];
      uint8_t lx       = msg.buf[3];
      uint8_t ly       = msg.buf[4];
      uint8_t rx       = msg.buf[5];
      uint8_t ry       = msg.buf[6];
      uint8_t l2       = msg.buf[7];

      Serial.println("---- PS4 Data ----");
      Serial.print("Buttons: 0x");
      Serial.println(buttons, HEX);
      Serial.print("D-Pad: ");
      Serial.println(dpad, DEC);
      Serial.print("LX: "); Serial.println(lx);
      Serial.print("LY: "); Serial.println(ly);
      Serial.print("RX: "); Serial.println(rx);
      Serial.print("RY: "); Serial.println(ry);
      Serial.print("L2: "); Serial.println(l2);
      Serial.println("------------------");
    }
  }
}
