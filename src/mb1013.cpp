#include <mb1013.h>

const int mb1013_bps = 9600;
int sensVal = 0;

void mb1013_init(){ //Serial2のデフォルトのシリアルピンRx16,Tx17を使う場合
    Serial2.begin(mb1013_bps); 
}

//シリアルピンを指定して使う場合
void mb1013_init( int rxPin, int txPin ){
    Serial2.begin(mb1013_bps, SERIAL_8N1, rxPin, txPin);    
}


void mb1013_loop(){
  static int cnt = 0;
  static char getChar;
  static char getChars[5];
  //static unsigned long prev_ms = 0;

  while (Serial2.available() > 0) {
    getChar = Serial2.read();

    if( getChar == 'R' ){
      cnt = 0;
    }
    getChars[cnt] = getChar;

    int getVal = 0;
    if( cnt >= 5){
      getVal += (int)(getChars[1] - '0') * 1000;
      getVal += (int)(getChars[2] - '0') * 100;
      getVal += (int)(getChars[3] - '0') * 10;
      getVal += (int)(getChars[4] - '0') * 1;

    //   Serial.print( millis() - prev_ms );
    //   Serial.print( ": " );
    //   Serial.println(getVal);
    //  prev_ms = millis();
       sensVal = getVal;

    }
    cnt++;
    
  }
}


int mb1013_getVal(){

    return sensVal;

}