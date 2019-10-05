#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsgs;
struct can_frame canMsgr;
MCP2515 mcp2515(10);


void setup() {
  Serial.begin(115200);
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");

  canMsgs.can_id  = 0x61A;
  canMsgs.can_dlc = 8;
  canMsgs.data[0] = 0x40;
  canMsgs.data[1] = 0x09;
  canMsgs.data[2] = 0x10;
  canMsgs.data[3] = 0x00;
  canMsgs.data[4] = 0x00;
  canMsgs.data[5] = 0x00;
  canMsgs.data[6] = 0x00;
  canMsgs.data[7] = 0x00;
}

void loop() {
  
  if (mcp2515.readMessage(&canMsgr) == MCP2515::ERROR_OK && canMsgr.can_id != 1207 && canMsgr.can_id != 0x242 && canMsgr.can_id != 0x237) {
      
    Serial.print(canMsgr.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsgr.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsgr.can_dlc; i++)  {  // print the data
        
      Serial.print(canMsgr.data[i],HEX);
      Serial.print(" ");

    }

    Serial.println();      
  }

  if(Serial.available() > 0) {
    Serial.read();
    mcp2515.sendMessage(&canMsgs);
    Serial.println("Message Sent!");
  }

}
