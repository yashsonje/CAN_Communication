#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);  // Set CS pin

void setup() {
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with 500kbps CAN speed
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
    Serial.println("CAN init ok!");
  } else {
    Serial.println("CAN init failed");
    while (1); // Stay here forever
  }

  CAN.setMode(MCP_NORMAL);  // Set to normal mode to receive
  Serial.println("CAN Receiver Ready");
}

void loop() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    long unsigned int rxId;
    unsigned char len = 0;
    unsigned char rxBuf[8];

    CAN.readMsgBuf(&rxId, &len, rxBuf);

    Serial.print("Received: ");
    for (int i = 0; i < len; i++) {
      Serial.print(rxBuf[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}
