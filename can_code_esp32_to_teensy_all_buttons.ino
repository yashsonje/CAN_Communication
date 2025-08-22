#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t msg;

void setup() {
  Serial.begin(115200);

  can1.begin();
  can1.setBaudRate(500000);
  Serial.println("Teensy CAN Receiver Ready");
}

void loop() {                                                                   
  if (can1.read(msg)) {
    if (msg.id == 0x101 && msg.len == 8) {
      // Unpack button bits
      uint16_t buttons = msg.buf[0] | (msg.buf[1] << 8);
      
      // Unpack joystick and L2 values
      uint8_t lx = msg.buf[3];
      uint8_t ly = msg.buf[4];
      uint8_t rx = msg.buf[5];
      uint8_t ry = msg.buf[6];
      uint8_t l2 = msg.buf[7];

      Serial.print("Buttons: ");
      Serial.print(buttons, BIN);
      
      Serial.print(" | LX: "); Serial.print(lx);
      Serial.print(" | LY: "); Serial.print(ly);
      Serial.print(" | RX: "); Serial.print(rx);
      Serial.print(" | RY: "); Serial.print(ry);
      Serial.print(" | L2: "); Serial.println(l2);

      // Example: Check if Circle is pressed (bit 2)
      if (buttons & (1 << 2)) {
        Serial.println("Circle Pressed!");
        
      }
    }
  }
}
 