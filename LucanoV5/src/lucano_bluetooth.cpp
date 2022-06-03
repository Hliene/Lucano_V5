#include <Arduino.h>
#include "..\lib\lucano_bluetooth.h"

String  inputString     = "";           // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void init_bluetooth(void){
  Serial3.begin(38400);
}

uint16_t _readSerial(void){
    
    while (Serial3.available()) {
        char inChar =Serial3.read();
        inputString += inChar;
        if (inChar == '>') {
            stringComplete = true;
        }
    }
    return 0;
}

uint16_t _read_Bluetooth(void){

    _readSerial();

    if(stringComplete){
        if(inputString == "<Drive Up>"){
            inputString = "";
            stringComplete = false;
            return DRIVE_UP;
        }
        else if(inputString == "<Drive Down>"){
            inputString = "";
            stringComplete = false;
            return DRIVE_DOWN;
        }
        else{
            inputString = "";
            stringComplete = false;
            return DRIVE_STOP;
        }
    }
    //return 0;
}    



