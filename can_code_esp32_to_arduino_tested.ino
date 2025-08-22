#include <SPI.h>
#include <mcp_can.h>

const int CAN_CS_PIN = 10;
MCP_CAN CAN(CAN_CS_PIN);

void setup() {
  Serial.begin(115200);
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN Init OK");
  } else {
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

    uint8_t buttonByte = buf[0];

    bool square   = buttonByte & (1 << 0);
    bool cross    = buttonByte & (1 << 1);
    bool circle   = buttonByte & (1 << 2);
    bool triangle = buttonByte & (1 << 3);

    Serial.print("Square: "); Serial.print(square);
    Serial.print(" | Cross: "); Serial.print(cross);
    Serial.print(" | Circle: "); Serial.print(circle);
    Serial.print(" | Triangle: "); Serial.println(triangle);
  }
}
