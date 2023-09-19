#include <Arduino.h>

/*
  please add MCP_CAN_LIB to your library first........
  MCP_CAN_LIB file in M5stack lib examples -> modules -> COMMU ->
  MCP_CAN_lib.rar
*/

#include <M5Stack.h>
#include "mcp_can.h"
#include "m5_logo.h"

#include "m5can_app.h"

void setup() {
    M5.begin();
    M5.Power.begin();
    Serial.begin(9600);
    Serial2.begin(9600, SERIAL_8N1, 16, 17);

    M5.Lcd.pushImage(0, 0, 320, 240, (uint16_t *)gImage_logoM5);
    delay(500);
    M5.Lcd.setTextColor(BLACK);
    // M5.Lcd.setTextSize(1);

    Serial.println("Test CAN...");
    
    can_init();
    can_setTestFlag( 0, 1 );
    
}

void loop() {
    if (M5.BtnA.wasPressed()) {
        M5.Lcd.clear();
        M5.Lcd.printf("CAN Test B!\n");
        M5.Lcd.pushImage(0, 0, 320, 240, (uint16_t *)gImage_logoM5);
        can_init();
    }

    can_loop();
    M5.update();
}

