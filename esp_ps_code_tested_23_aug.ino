#include <PS4Controller.h>
#include <ESP32-TWAI-CAN.hpp>

void setup() {
  Serial.begin(115200);

  // Start CAN
  if (!ESP32Can.begin(TWAI_SPEED_500KBPS)) {
    Serial.println("CAN Init Failed!");
    while (1);
  }
  Serial.println("CAN Ready");

  // Connect PS4 Controller (insert your MAC address)
  PS4.begin("3c:8a:1f:09:0b:a6");
  Serial.println("PS4 Bluetooth Started");
}

void loop() {
  if (PS4.isConnected()) {
    uint16_t buttons = 0;
    uint8_t dpadByte = 0;
    buttons |= PS4.Square()   << 0;
    buttons |= PS4.Cross()    << 1;
    buttons |= PS4.Circle()   << 2;
    buttons |= PS4.Triangle() << 3;
    buttons |= PS4.Up()       << 4;
    buttons |= PS4.Down()     << 5;
    buttons |= PS4.Left()     << 6;
    buttons |= PS4.Right()    << 7;
    buttons |= PS4.L1()       << 8;
    buttons |= PS4.R1()       << 9;
    buttons |= PS4.L3()       << 10;
    buttons |= PS4.R3()       << 11;
    buttons |= PS4.Share()    << 12;
    buttons |= PS4.Options()  << 13;
    buttons |= PS4.PSButton() << 14;
    buttons |= PS4.Touchpad() << 15;

    uint8_t lx = PS4.LStickX();
    uint8_t ly = PS4.LStickY();
    uint8_t rx = PS4.RStickX();
    uint8_t ry = PS4.RStickY();

    // Prepare CAN frame
    CanFrame frame;
    frame.identifier = 0x101;
    frame.data_length_code = 8;

    frame.data[0] = buttons & 0xFF;         // Lower byte of buttons
    frame.data[1] = (buttons >> 8) & 0xFF;  // Upper byte
    frame.data[2] = dpadByte;               // Reserved / D-Pad bits if needed
    frame.data[3] = lx;
    frame.data[4] = ly;
    frame.data[5] = rx;
    frame.data[6] = ry;
    frame.data[7] = PS4.L2Value();          // Example: Analog trigger value

    ESP32Can.writeFrame(frame);

    delay(50);  // Adjust based on performance needs
  }
}
