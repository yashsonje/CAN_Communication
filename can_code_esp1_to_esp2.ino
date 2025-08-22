#include <ESP32-TWAI-CAN.hpp>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!ESP32Can.begin(TWAI_SPEED_500KBPS)) {
    Serial.println("CAN init failed");
    while (1);
  }

  Serial.println("CAN Receiver Ready");
}

void loop() {
  CanFrame rxFrame;
  if (ESP32Can.readFrame(rxFrame)) {
    Serial.print("Received ID: ");
    Serial.println(rxFrame.identifier, HEX);
    Serial.print("Data: ");
    for (int i = 0; i < rxFrame.data_length_code; i++) {
      Serial.print(rxFrame.data[i]);  // Corrected here
      Serial.print(" ");
    }
    Serial.println();
  }
}

