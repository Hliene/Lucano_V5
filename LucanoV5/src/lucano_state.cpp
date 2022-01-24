#include "..\lib\lucano_state.h"
#include "..\lib\lucano_display.h"
#include "..\lib\lucano_taster.h"
#include "..\lib\lucano_battery.h"
#include "..\lib\led_summer.h"
#include "..\lib\lucano_drive.h"
#include "..\lib\lucano_lifting_column.h"
#include "..\lib\lucano_scissor.h"
#include "..\lib\lucano_actuator.h"
#include "..\lib\lucano_lidar.h"
#include "..\lib\lucano_timer.h"
#include <Arduino.h>


uint16_t delimbing_height = 0;
uint16_t old_delimbing_height = 0;
uint16_t baterie_value = 0;
uint16_t old_baterie_value = 100;

uint16_t hook_fall_counter = 300;       // 20ms *300/2 = 3s

/*****************************************************************************
 * Function name:     idle
 * 
 * Descriptions:      Funktion der State Maschiene 
 *                    Grüne LED anschalten
 *                    Einstellung der Entastungshöhe
 *                    Ausgabe der Batteriespanung
 *                    Bestätitigung der Entastungshöhe und Sprung in State Hook fall Protection
 * 
 * Variabels:         delimbing_height // Entastungshöhe
 *                    battery_vale     // Batteriespannung in %  
 * 
 *                    
 *****************************************************************************/
uint16_t idle(void)
{
    //retract_column();               //Fals die Schere ausgefahren ist erst einfahren

    digitalWrite(GREENLED,HIGH);
 // <<<<<<<<<<<<<<<<<<<< Adjust the declimbing height>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(plus_buttom() & (delimbing_height < MAX_DELCLIMBING_HEIGT))
        delimbing_height++;
    else if(minus_buttom() & (delimbing_height > MIN_DELCLIMBING_HEIGT)) 
        delimbing_height--;   

    if(old_delimbing_height != delimbing_height)
        Display_delclimbing_height(delimbing_height);

    old_delimbing_height= delimbing_height;

//  <<<<<<<<<<<<<<<<<<<< read baterie value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    baterie_value = read_battery(); // read Batterie value

    if(old_baterie_value != baterie_value)
        Display_baterie_value(baterie_value);

    old_baterie_value = baterie_value;   

//  <<<<<<<<<<<<<<<<<<<< go to State HOOK_FALL_PROTECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    if (confirmation_buttom())
        return HOOK_FALL_PROTECTION;

    delay(15);

    return IDLE;
}

/*****************************************************************************
 * Function name:     hook_fall_protection
 * 
 * Descriptions:      Funktion der State Maschiene 
 *                    Fahre halbe Umdrehung um Baum
 *                    grüne LED Blinkt
 * 
 *                    
 * 
 * Variabels:         hook_fall_counter     //anzahl der Schleifendurläufe abhängig wie die der Baum ist 
 * 
 *                    
 *****************************************************************************/
uint16_t hook_fall_protection(void){
/**
 * @brief 
 * wenn hook_fall_counter == NULL, dann lese den Sensor für Baumdicke aus und setzte hook_fall_counter
 */

    //Serial.println("hookFallProtektion");
 // <<<<<<<<<<<<<<<<<<<<Blink green LED>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(((hook_fall_counter & 0b01000000) == 0b01000000))
        digitalWrite(GREENLED,LOW);
    else 
        digitalWrite(GREENLED,HIGH);   
        
 // <<<<<<<<<<<<<<<<<<<<drive the Tree half around>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(hook_fall_counter){
        hook_fall_counter = hook_fall_counter - (_drive_UP());
        delay(20);
    }
    else{ 
        _drive_STOP();       
       // ref_scissor();
        if (ref_column())
            return READY_TO_START;                    //Go to next state         
    }   
    return HOOK_FALL_PROTECTION;
}

/*****************************************************************************
 * Function name:     ready_to_start
 * 
 * Descriptions:      Funktion der State Maschiene 

 * 
 * Variabels:         
 * 
 *                    
 *****************************************************************************/
uint16_t ready_to_start(void){

    digitalWrite(REDLED,HIGH);

    Serial.println("ready_to_start");







    //  <<<<<<<<<<<<<<<<<<<< read baterie value >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    baterie_value = read_battery(); // read Batterie value

    if(old_baterie_value != baterie_value)
        Display_baterie_value(baterie_value);

    old_baterie_value = baterie_value;  

    if(start_buttom())
        return WORK;

    delay(100);

    return READY_TO_START;
}

/*****************************************************************************
 * Function name:     work
 * 
 * Descriptions:      Funktion der State Maschiene 

 * 
 * Variabels:         
 * 
 *                    
 *****************************************************************************/
uint16_t work(void){

  

    digitalWrite(REDLED,LOW);

    getTFminiData1(&distance, &strength); 

    if(distance <= 40) {                                  //Wenn Ast näher als 40cm ist
      branch_thinkness = branch_thinkness+1;              //Zähler für Ast stärke
      if(distance <= branch_distance)                     //Ermittel des geringsten abstand zum Ast, wenn nicht der kleinste abstand genommen wird ist der Wert zu hoch
        branch_distance = distance;                       //Speichern des Abstandes
    }
    else if(branch_thinkness > 5)                         //Wenn Ast vollständig gemessen zähle "branch_detactet" hoch um die Asterkennung zu entprellen
      branch_detactet = 1;


    if(branch_detactet){
        Serial.print("branch distance = ");
        Serial.println(branch_distance);
        Serial.print("branch thikness = ");
        Serial.println(branch_thinkness);
        branch_detactet = 0;
        branch_thinkness = 0;
        branch_distance = 41;

    }
    delayMicroseconds(500); 

    //Serial.print(branch_detactet);
   // Serial.println(branch_distance);
 




    return WORK;
}


