#include <SPI.h>
#include <mcp_can.h>

const int CAN_CS_PIN = 10;
MCP_CAN CAN(CAN_CS_PIN);

void setup() {
  Serial.begin(115200);

  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("CAN Init OK");
  else {
    Serial.println("CAN Init Failed");
    while (1);
  }

  CAN.setMode(MCP_NORMAL);
}

void loop() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    long unsigned int rxId;
    unsigned char len = 0;
    unsigned char buf[8];

    CAN.readMsgBuf(&rxId, &len, buf);

    // Decode buttons
    uint16_t buttons = buf[0] | (buf[1] << 8);

    bool square   = buttons & (1 << 0);
    bool cross    = buttons & (1 << 1);
    bool circle   = buttons & (1 << 2);
    bool triangle = buttons & (1 << 3);
    bool up       = buttons & (1 << 4);
    bool down     = buttons & (1 << 5);
    bool left     = buttons & (1 << 6);
    bool right    = buttons & (1 << 7);
    bool l1       = buttons & (1 << 8);
    bool r1       = buttons & (1 << 9);
    bool l3       = buttons & (1 << 10);
    bool r3       = buttons & (1 << 11);
    bool share    = buttons & (1 << 12);
    bool options  = buttons & (1 << 13);
    bool ps       = buttons & (1 << 14);
    bool touchpad = buttons & (1 << 15);

    // Joystick values
    uint8_t lx = buf[3];
    uint8_t ly = buf[4];
    uint8_t rx = buf[5];
    uint8_t ry = buf[6];
    uint8_t l2 = buf[7];

    // Serial.print("Buttons: ");
    // Serial.print(square); Serial.print(" ");
    // Serial.print(cross); Serial.print(" ");
    // Serial.print(circle); Serial.print(" ");
    // Serial.print(triangle); Serial.print(" ");
    // Serial.print(up); Serial.print(" ");
    // Serial.print(down); Serial.print(" ");
    // Serial.print(left); Serial.print(" ");
    // Serial.print(right); Serial.print(" ");
    // Serial.print(l1); Serial.print(" ");
    // Serial.print(r1); Serial.print(" ");
    // Serial.print(share); Serial.print(" ");
    // Serial.print(options); Serial.print(" ");
    // Serial.print(ps); Serial.print(" ");
    // Serial.println(touchpad);

    Serial.print("Lx: "); Serial.print(lx);
    Serial.print(" | Ly: "); Serial.print(ly);
    // Serial.print(" | Rx: "); Serial.print(rx);
    // Serial.print(" | Ry: "); Serial.print(ry);
    Serial.print(" | L2: "); Serial.println(l2);
  }
}
