#include "..\lib\lucano_state.h"
#include "..\lib\lucano_init.h"
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
//#include <Dabble.h>


uint16_t delimbing_height = 0;
uint16_t old_delimbing_height = 0;

//Abhängig vom Baumdurchmesser
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
    //retract_column();                 //Fals die Schere ausgefahren ist erst einfahren

    _drive_STOP();                      // Raeder muessen stehen bleiben 
    digitalWrite(GREENLED,HIGH);
    digitalWrite(REDLED,LOW);

 // <<<<<<<<<<<<<<<<<<<< Adjust the declimbing height>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(plus_buttom() & (delimbing_height < MAX_DELCLIMBING_HEIGT))
        delimbing_height++;
    else if(minus_buttom() & (delimbing_height > MIN_DELCLIMBING_HEIGT)) 
        delimbing_height--;   

    if(old_delimbing_height != delimbing_height)
        Display_delclimbing_height(delimbing_height);

    old_delimbing_height= delimbing_height;

   
 //<<<<<<<<<<<<<<<<<<<<<<<Display Batterie Spannung>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    _battery();
    //if(_battery())
        //return BATTERIE_EMPTY;

//  <<<<<<<<<<<<<<<<<<<< go to next State >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(BT_CONNECT)
        return REMOTE_CONTROL;

    if (confirmation_buttom())
        return HOOK_FALL_PROTECTION;

    if(attach_to_tree_buttom())
        return ATTACH_TO_TREE;    

    delay(15);

    return IDLE;
}

/*****************************************************************************
 * Function name:     attach_to_tree
 * 
 * Descriptions:      Funktion um den Lucano an den Bau zu setzten 
 * 
 *                    
 *****************************************************************************/
uint16_t attach_to_tree(void){
  
// Actuatoren auf 0 Grad setzten 
    if(_actuator(512))
        _attach_to_tree();          // Wenn Actuatoren auf 0 Grad Räder bewegen  
    else 
        _drive_STOP();              //Sonst nicht fahren

    delay(20);



//  <<<<<<<<<<<<<<<<<<<< go to next State >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 //   if(BT_CONNECT)
  //      return REMOTE_CONTROL;    
    
    if(attach_to_tree_buttom())     //Wenn Taster gedrückt dann State weiter durchlaufen
        return ATTACH_TO_TREE;
    else 
        _drive_STOP();              //Sonst nicht fahren

    return IDLE;                    //Gehe zurück in State IDLE
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
    if(((hook_fall_counter & BLINK_FREQ) == BLINK_FREQ))
        digitalWrite(GREENLED,LOW);
    else 
        digitalWrite(GREENLED,HIGH);   

    //  <<<<<<<<<<<<<<<<<<<< go to next State >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //if(BT_CONNECT)
    //    return REMOTE_CONTROL;   

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

 //<<<<<<<<<<<<<<<<<<<<<<<Display Batterie Spannung>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   // if(_battery())
   //     return BATTERIE_EMPTY;

//  <<<<<<<<<<<<<<<<<<<< go to next State >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //if(BT_CONNECT)
    //    return REMOTE_CONTROL;   

    if(start_buttom())
        return WORK;

    delay(20);

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

 //<<<<<<<<<<<<<<<<<<<<<<<Display Batterie Spannung>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   // if(_battery())
   //     return BATTERIE_EMPTY;

    digitalWrite(REDLED,LOW);

    Serial.println("work");


delay(500);
/*
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
*/ 
    //  <<<<<<<<<<<<<<<<<<<< go to next State >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //if(BT_CONNECT)
    //    return REMOTE_CONTROL;   

    return WORK;
}

/*****************************************************************************
 * Function name:     remote_control
 * 
 * Descriptions:      Funktion der State Maschiene 

 * 
 * Variabels:         
 * 
 *                   
 *****************************************************************************/
uint16_t remote_control(void){

    digitalWrite(REDLED,HIGH);
    digitalWrite(GREENLED,HIGH);

    Display_Page_4();
    page4_txt2();


/*
    Dabble.processInput();

    if(GamePad.isDownPressed()){ 
        _drive_DOWN();    
        // Serial.println("down"); 
        //delay(900);
        if (ENDSTOP_HS == 0){                           // Wenn sich die Hubsäule während der Fahrt aus der endlage löst
            analogWrite(PWM_ASN,100);
        }
    //delay(300);
    }
    else if(GamePad.isUpPressed()){
        _drive_UP(); 
        if (ENDSTOP_HS == 0){                           // Wenn sich die Hubsäule während der Fahrt aus der endlage löst
            analogWrite(PWM_ASN,100);
        }
    //delay(300);
    }
    else{
        _drive_STOP();
        analogWrite(PWM_ASN,0);
        analogWrite(PWM_ASP,0);
    } 
*/

    

    while(BT_CONNECT){
        //return REMOTE_CONTROL;
        delay(200);
    }

    Display_Page_1();
    return IDLE;    
}
