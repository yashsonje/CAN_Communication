#include <ESP32-TWAI-CAN.hpp>


#define CAN_TX 5
#define CAN_RX 4


void setup() {
  Serial.begin(115200);

  // Set the CAN TX and RX pins
  ESP32Can.setPins(CAN_TX, CAN_RX);

  // Set CAN speed to 500 Kbps using correct method
  ESP32Can.setSpeed(ESP32Can.convertSpeed(500));  // 500 kbps

  // Start CAN communication
  if (ESP32Can.begin()) {
    Serial.println("CAN bus started on ESP32!");
  } else {
    Serial.println("CAN bus failed to start!");
  }
}

void loop() {
  static uint8_t counter = 1;
  static uint32_t lastSend = 0;

  if (millis() - lastSend > 100) {
    lastSend = millis();

    // Create a CAN frame
    CanFrame frame = {0};
    frame.identifier = 0x100;         // CAN ID
    frame.extd = 0;                   // Standard frame
    frame.data_length_code = 1;       // 1 byte
    frame.data[0] = counter;

    // Send the frame
    ESP32Can.writeFrame(frame);
    Serial.print("Sent: ");
    Serial.println(counter);

    counter++;
    if (counter > 100) counter = 1;  // Restart after 100
  }
}
