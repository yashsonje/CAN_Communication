#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 10;  // D10 UNO / D53 MEGA
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);

  while (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ)) {
    Serial.println("CAN Init Failed. Retrying...");
    delay(100);
  }

  Serial.println("CAN Init Success");
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    long unsigned int id;
    unsigned char len = 0;
    unsigned char buf[8];

    CAN.readMsgBuf(&id, &len, buf);

    Serial.print("ID: ");
    Serial.print(id, HEX);
    Serial.print(" Data: ");

    for (int i = 0; i < len; i++) {
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
