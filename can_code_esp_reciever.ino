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
    Serial.printf("Received CAN Frame: ID: 0x%03X, Data: ", rxFrame.identifier);
    for (int i = 0; i < rxFrame.data_length_code; i++) {
      Serial.printf("0x%02X ", rxFrame.data[i]);
    }
    Serial.println();
  }
}
