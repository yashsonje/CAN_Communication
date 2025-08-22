#include <ESP32-TWAI-CAN.hpp>

#define CAN_TX 5
#define CAN_RX 4

void setup() {
  Serial.begin(115200);
  ESP32Can.setPins(CAN_TX, CAN_RX);
  ESP32Can.setSpeed(ESP32Can.convertSpeed(500));  // 500 kbps

  if (ESP32Can.begin()) {
    Serial.println("ESP32 CAN Started");
  } else {
    Serial.println("CAN Init Failed");
  }
}

void loop() {
  CanFrame frame = {0};
  frame.identifier = 0x100;     // Standard 11-bit ID
  frame.extd = 0;
  frame.data_length_code = 2;
  frame.data[0] = 0xA1;
  frame.data[1] = 0xB2;

  ESP32Can.writeFrame(frame);
  Serial.println("Frame sent");

  delay(1000);
}
