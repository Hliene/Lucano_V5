#include "..\lib\lucano_battery.h"
#include "..\lib\lucano_display.h"
#include <Arduino.h>


uint16_t bat_val = 0;
uint16_t bat_val_return = 0;
uint16_t baterie_value = 0;
uint16_t old_baterie_value = 100;

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

/*****************************************************************************
 * Function name:     _battery
 * 
 * Descriptions:      Funktion zut überprüfung der Batteriespannung 
 * 
 * return:            Git eine eins zurück wenn die Batteriespannung unterschritten ist 
 *                      
 *          
 *****************************************************************************/
uint16_t _battery(const char* page){


//  <<<<<<<<<<<<<<<<<<<< read baterie value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    baterie_value = read_battery(); // read Batterie value

    //Serial.println(baterie_value);

    if(old_baterie_value != baterie_value)
        Display_baterie_value(baterie_value,page);

    old_baterie_value = baterie_value;   

    if(baterie_value)
        return 0;

    return 1;    
}