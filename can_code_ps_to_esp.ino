#include <PS4Controller.h>
#include <ESP32-TWAI-CAN.hpp>

#define CAN_TX_PIN 5
#define CAN_RX_PIN 4
#define CAN_SPEED TWAI_SPEED_500KBPS

uint8_t sendData[8];  
int bytesToSend = 0;

void onConnect() {
  Serial.println("PS4 Controller Connected");
}

void setup() {
  Serial.begin(115200);

  PS4.begin("ac:15:18:d4:e9:3c"); 
  PS4.attach(onConnect);
  Serial.println("Waiting for PS4 Controller...");

  ESP32Can.setPins(CAN_RX_PIN, CAN_TX_PIN);
  if (!ESP32Can.begin(CAN_SPEED)) {
    Serial.println("CAN Init Failed!");
    while (1);
  }

  Serial.println("CAN + PS4 Bridge Ready");
}

void loop() {
  if (PS4.isConnected()) {

    sendData[0] = PS4.LStickX();
    sendData[1] = PS4.LStickY();
    sendData[2] = PS4.RStickX();
    sendData[3] = PS4.RStickY();
    sendData[4] = PS4.L2Value();
    sendData[5] = PS4.R2Value();
    sendData[6] = PS4.Square() ? 1 : 0;
    sendData[7] = PS4.Circle() ? 1 : 0;

    bytesToSend = 8;

    Serial.print("LX: "); Serial.print(sendData[0]);
    Serial.print(" LY: "); Serial.print(sendData[1]);
    Serial.print(" RX: "); Serial.print(sendData[2]);
    Serial.print(" RY: "); Serial.print(sendData[3]);
    Serial.print(" L2: "); Serial.print(sendData[4]);
    Serial.print(" R2: "); Serial.print(sendData[5]);
    Serial.print(" Square: "); Serial.print(sendData[6]);
    Serial.print(" Circle: "); Serial.println(sendData[7]);

    CanFrame txFrame;
    txFrame.identifier = 0x123;
    txFrame.extd = 0;
    txFrame.rtr = 0;
    txFrame.data_length_code = bytesToSend;
    memcpy(txFrame.data, sendData, bytesToSend);

    ESP32Can.writeFrame(txFrame);
  }

  delay(20);
}
