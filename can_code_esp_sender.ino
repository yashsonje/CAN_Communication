#include <ESP32-TWAI-CAN.hpp>

#define CAN_TX 5
#define CAN_RX 4

void setup() {
  Serial.begin(115200);
  ESP32Can.setPins(CAN_TX, CAN_RX);
  ESP32Can.setSpeed(ESP32Can.convertSpeed(100));
  if (ESP32Can.begin()) {
    Serial.println("CAN bus started on Sender!");
  } else {
    Serial.println("CAN bus failed on Sender!");
  }
}

void loop() {
  static uint32_t lastStamp = 0;
  uint32_t now = millis();

  if (now - lastStamp >= 1000) {
    lastStamp = now;

    CanFrame frame = {0};
    frame.identifier = 0x123;
    frame.extd = 0;
    frame.data_length_code = 1;
    frame.data[0] = 0xAB;
    // frame.data[1] = 0xCD;

    ESP32Can.writeFrame(frame);
    Serial.println("Sent CAN Frame: Hello World");
  }
}
