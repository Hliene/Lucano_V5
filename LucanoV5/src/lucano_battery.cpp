#include "..\lib\lucano_battery.h"
#include <Arduino.h>


uint16_t bat_val = 0;
uint16_t bat_val_return = 0;

/*****************************************************************************
 * Function name:     init_battery
 * 
 * Descriptions:      Funktion zur Initalisierung des Pins zum Einlesen der Bateriespannung
 * 
 * Pin:               A13
 *                    
 *****************************************************************************/
void init_battery(void){

  //Bateriespanung
  pinMode(BAT_IN,INPUT);

}
/*****************************************************************************
 * Function name:     read_battery
 * 
 * Descriptions:      Funktion zum auslesen der Batteriespannung
 *                    51V Batterie Voll geladen
 *                    40V Batterie Entladen
 *                    Rückgabewert in % und 10 schritten  
 * 
 * Pin:               A13
 *          
 *****************************************************************************/
uint16_t read_battery(void){

    bat_val = (analogRead(BAT_IN) + bat_val*3) / 4;

   // Serial.println(bat_val);

    if(bat_val > BAT_MIN_VALE){ 
        bat_val_return = bat_val - BAT_MIN_VALE; 
        bat_val_return = (bat_val_return*10)/BAT_MAX_VALE; 
    }
    else    
        return 0;
        
    bat_val_return = bat_val_return *10;   

    return bat_val_return;
}