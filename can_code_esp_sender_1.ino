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
  static uint8_t counter = 1;
  static uint32_t lastSend = 0;

  if (millis() - lastSend > 100) {
    lastSend = millis();

    CanFrame frame = {0};
    frame.identifier = 0x123;
    frame.extd = 0;
    frame.data_length_code = 2;
    // frame.data[0] = "Hii..."
    frame.data[0] = counter;
    
    ESP32Can.writeFrame(frame);
    Serial.print("Sent: ");
    Serial.println(counter);

    counter++;
    if (counter > 255) counter = 1;  // restart at 1
  }
}
