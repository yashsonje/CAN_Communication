#include <ESP32-TWAI-CAN.hpp>

#define CAN_TX 5
#define CAN_RX 4

CanFrame rxFrame;

void setup() {
  Serial.begin(115200);
  ESP32Can.setPins(CAN_TX, CAN_RX);
  ESP32Can.setSpeed(ESP32Can.convertSpeed(100));
  
  if (ESP32Can.begin()) {
    Serial.println("CAN bus started on Receiver!");
  } else {
    Serial.println("CAN bus failed on Receiver!");
  }
}

void loop() {
  if (ESP32Can.readFrame(rxFrame, 1000)) {
    Serial.print("Received: ");
    Serial.println(rxFrame.data[0]);
  }
}
