#include <PS4Controller.h>
#include <ESP32-TWAI-CAN.hpp>

void setup() {
  Serial.begin(115200);

  // Start CAN bus
  if (!ESP32Can.begin(TWAI_SPEED_500KBPS)) {
    Serial.println("CAN Init Failed!");
    while (1)
      ;
  }
  Serial.println("CAN Ready");

  // Connect to PS4 controller (Insert your PS4 MAC address)
  PS4.begin("ac:15:18:d4:e9:3c");
  Serial.println("PS4 Bluetooth Started");
}

void loop() {
  if (PS4.isConnected()) {
    uint16_t buttons = 0;

    // Pack digital buttons
    buttons |= PS4.Square() << 0;
    buttons |= PS4.Cross() << 1;
    buttons |= PS4.Circle() << 2;
    buttons |= PS4.Triangle() << 3;
    buttons |= PS4.Up() << 4;
    buttons |= PS4.Down() << 5;
    buttons |= PS4.Left() << 6;
    buttons |= PS4.Right() << 7;
    buttons |= PS4.L1() << 8;
    buttons |= PS4.R1() << 9;
    buttons |= PS4.L3() << 10;
    buttons |= PS4.R3() << 11;
    buttons |= PS4.Share() << 12;
    buttons |= PS4.Options() << 13;
    buttons |= PS4.PSButton() << 14;
    buttons |= PS4.Touchpad() << 15;

    // Joystick values (mapped to 0–255)
    uint8_t lx = PS4.LStickX();
    uint8_t ly = PS4.LStickY();
    uint8_t rx = PS4.RStickX();
    uint8_t ry = PS4.RStickY();
    uint8_t l2 = PS4.L2Value();  // You can also include R2Value if needed

    // Prepare CAN frame
    CanFrame frame;
    frame.identifier = 0x101;
    frame.data_length_code = 8;

    frame.data[0] = buttons & 0xFF;         // Lower 8 bits of buttons
    frame.data[1] = (buttons >> 8) & 0xFF;  // Upper 8 bits
    frame.data[2] = 0;                      // Reserved or D-Pad byte (if needed later)
    frame.data[3] = lx;
    frame.data[4] = ly;
    frame.data[5] = rx;
    frame.data[6] = ry;
    frame.data[7] = l2;

    ESP32Can.writeFrame(frame);

    // Debug print
    Serial.print("Buttons: ");
    Serial.print(buttons, BIN);
    Serial.print(" | LX: ");
    Serial.print(lx);
    Serial.print(" | LY: ");
    Serial.print(ly);
    Serial.print(" | RX: ");
    Serial.print(rx);
    Serial.print(" | RY: ");
    Serial.print(ry);
    Serial.print(" | L2: ");
    Serial.println(l2);

    delay(5);  // Lower delay for smoother performance
  }
}
