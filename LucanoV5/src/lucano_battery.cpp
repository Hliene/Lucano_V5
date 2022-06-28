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

  pinMode(BAT_IN,INPUT);                                                    //analoge input for the batterievalue

}
/*****************************************************************************
 * Function name:       read_battery
 * 
 * Descriptions:        -Funktion zum auslesen der Batteriespannung
 *                      -51V Batterie Voll geladen
 *                      -40V Batterie Entladen
 *                      -Es wird dierekt der Analogepin A13 eingelesen
 *                      -Rückgabewert in % und 10 schritten  
 * 
 * Pin:                 -A13
 *          
 *****************************************************************************/
uint16_t read_battery(void){

    bat_val = (analogRead(BAT_IN) + bat_val*3) / 4;                         //read the analogpin for the Baterievalue

    if(bat_val > BAT_MIN_VALE){                                             //if baterievalue is high enoght 
        bat_val_return = bat_val - BAT_MIN_VALE;                            //edit the batterievalue
        bat_val_return = (bat_val_return*10)/BAT_MAX_VALE;              
    }
    else    
        return 0;   	                                                    //if batterievalue is to low return 0
        
    bat_val_return = bat_val_return *10;                                    //edit the baterie value

    return bat_val_return;                                                  //return the batterievalue
}

/*****************************************************************************
 * Function name:     _battery
 * 
 * Descriptions:      -Funktion zut überprüfung der Batteriespannung gibt einen Fehler 
 *                      zurück wenn die batteriespannung überschritten ist 
 *                    -Gibt gleichzeitig die aktuelle Batteriespannung am Display aus
 * 
 * Values:            Der Übergabewert ist die Seite des Display auf der die 
 *                      Batteriespannung ausgegeben werden soll  
 * 
 * return:            Git eine eins zurück wenn die Batteriespannung unterschritten ist 
 *                      
 *          
 *****************************************************************************/
uint16_t _battery(const char* page){


//  <<<<<<<<<<<<<<<<<<<< read baterie value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    baterie_value = read_battery(); // read Batterie value

    //Serial.println(baterie_value);

    if(old_baterie_value >= baterie_value)
        Display_baterie_value(baterie_value,page);

    old_baterie_value = baterie_value;   

    if(baterie_value)
        return 0;

    return 1;    
}