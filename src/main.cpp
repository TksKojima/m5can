#include <Arduino.h>

/*
  please add MCP_CAN_LIB to your library first........
  MCP_CAN_LIB file in M5stack lib examples -> modules -> COMMU ->
  MCP_CAN_lib.rar
*/

#include <M5Stack.h>
#include "mcp_can.h"

#include "m5can_app.h"

TFT_eSprite sprite(&M5.Lcd);

int can_tx_test = 0;
int can_show_mode = 0;


void M5_setup(){
    M5.begin();
    M5.Power.begin();
    
    sprite.setTextColor(GREEN);
    sprite.setColorDepth(8);
    sprite.setTextSize(1);
    sprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
    delay(5);

}

void M5_loop_BtnA(){
    static int prevBtnA = 0;
    if (M5.BtnA.isPressed() && prevBtnA == 0 ) {

        can_tx_test++;
        if( can_tx_test >= 2 ){ can_tx_test = 0; }

    }
    prevBtnA = M5.BtnA.isPressed();

}

void M5_loop_BtnB(){
    static int prevBtnB = 0;
    if (M5.BtnB.isPressed() && prevBtnB == 0 ) {

        can_show_mode++;
        if( can_show_mode >= 3 ){ can_show_mode = 0; }

    }    
    prevBtnB = M5.BtnB.isPressed();
    
}

void M5_loop_BtnC(){
    static int prevBtnC = 0;
    if (M5.BtnC.wasPressed()) {


    }
}


void M5_loop(){

    M5_loop_BtnA();
    M5_loop_BtnB();
    M5_loop_BtnC();

    sprite.fillScreen(BLACK);
    sprite.setCursor(0, 0);

    sprite.printf("Can Tx Test Msg (press A): %d", can_tx_test);
    if( can_tx_test != 0 ){  sprite.printf(" TestMsg sending");
    }else{                   sprite.printf(" No TestMsg"); }
    sprite.printf("\n");

    sprite.printf("Can Show Mode   (press B): %d", can_show_mode);
    if( can_show_mode == 0 ){ sprite.printf(" No show"); }
    if( can_show_mode == 1 ){ sprite.printf(" show LCD");}
    if( can_show_mode == 2 ){ sprite.printf(" show LCD & Serial"); }     
    sprite.printf("\n");

    M5_CanShowLCD( &sprite );

    sprite.pushSprite(0, 0); 
    
}


void setup() {

    M5_setup();
    Serial.begin(9600);
    can_init();
    
}


void loop() {

    M5.update(); 

    M5_loop();
    can_setTestFlag( can_tx_test , can_show_mode );

    unsigned char tempData[] = { 10,11,12,13,14,15,16,17,18 };
    canTxbuf_set( 131, 7, 131, tempData, 1 );

    can_loop();

}


