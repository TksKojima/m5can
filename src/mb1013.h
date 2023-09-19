#ifndef mb1013_H
#define mb1013_H

#include <Arduino.h>

void mb1013_init();
void mb1013_init( int rxPin, int txPin );
void mb1013_loop();
int  mb1013_getVal();



#endif
