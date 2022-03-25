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
#include "..\lib\lucano_bluetooth.h"

#include <Arduino.h>


uint16_t delimbing_height = 0;
uint16_t old_delimbing_height = 0;

//Abhängig vom Baumdurchmesser
uint16_t hook_fall_counter;       // 20ms *300/2 = 3s

//height of the Lucano
uint16_t Lucano_height = 0;
uint16_t height_strength = 0;

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
    //Serial.println("IDLE");
    //retract_column();                 //Fals die Schere ausgefahren ist erst einfahren

    _drive_STOP();                      // Raeder muessen stehen bleiben 
    digitalWrite(GREENLED,HIGH);
    digitalWrite(REDLED,LOW);
    
    _actuator(100);

 // <<<<<<<<<<<<<<<<<<<< Adjust the declimbing height>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(plus_buttom() & (delimbing_height < MAX_DELCLIMBING_HEIGT))
        delimbing_height++;
    else if(minus_buttom() & (delimbing_height > MIN_DELCLIMBING_HEIGT)) 
        delimbing_height--;   

    if(old_delimbing_height != delimbing_height)
        Display_delclimbing_height(delimbing_height,"1");

    old_delimbing_height= delimbing_height;

    hook_fall_counter = getTFminiDataI2C();

 //<<<<<<<<<<<<<<<<<<<<<<<Display Batterie Spannung>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    _battery("1");
    //if(_battery())
       // return BATTERIE_EMPTY;

//  <<<<<<<<<<<<<<<<<<<< go to next State >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(BT_CONNECT){
        Display_Page("4");
        page4_text("Attention!","Remote Control","Bluetooth Connected");
        old_baterie_value = DEFALT_BAT_VAL;
        return REMOTE_CONTROL;
    } 

    if (confirmation_buttom()){
        delimbing_height =delimbing_height * cm2m;                                  // Weil der LIDAR Sensor die Werte in Cm ausgibt
        delimbing_height = delimbing_height - DIFF_HEIGT_SISSOR;                    //Anpassung des Abstandes zur Erde
        delay(500);                                                                 //Dela für den nächsten State
        return HOOK_FALL_PROTECTION;
    }

    if(attach_to_tree_buttom())
        return ATTACH_TO_TREE;    

    delay(10);

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
    if(_actuator(512))                 //if(_actuator(512))
        _attach_to_tree();              // Wenn Actuatoren auf 0 Grad Räder bewegen  
    else 
        _drive_STOP();                  //Sonst nicht fahren

    delay(20);


    if(_battery("1"))                   //Ausgabe der Batteriespannung
        return BATTERIE_EMPTY;

    if(digitalRead(ATTACH_TREE))        //Wenn Taster gedrückt dann State weiter durchlaufen
        return ATTACH_TO_TREE;
    else 
        _drive_STOP();                  //Sonst nicht fahren

    return IDLE;                        //Gehe zurück in State IDLE
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

 //<<<<<<<<<<<<<<<<<<<<<<<Display Batterie Spannung>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(_battery("1"))
        return BATTERIE_EMPTY;

//  <<<<<<<<<<<<<<<<<<<< go to next State >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(BT_CONNECT){
        Display_Page("4");
        page4_text("Attention!","Remote Control","Bluetooth Connected");
        old_baterie_value = DEFALT_BAT_VAL;
        return REMOTE_CONTROL;
    } 

 // <<<<<<<<<<<<<<<<<<<<drive the Tree half around>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(hook_fall_counter){
        hook_fall_counter = hook_fall_counter - (_drive_UP());
        delay(20);
    }
    else{ 
        _drive_STOP();       
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

    digitalWrite(REDLED,LOW);
    digitalWrite(GREENLED,HIGH);

    Serial.println("ready_to_start");

 //<<<<<<<<<<<<<<<<<<<<<<<Display Batterie Spannung>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(_battery("1"))
        return BATTERIE_EMPTY;

//  <<<<<<<<<<<<<<<<<<<< go to next State >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(BT_CONNECT){
        Display_Page("4");
        page4_text("Attention!","Remote Control","Bluetooth Connected");
        old_baterie_value = DEFALT_BAT_VAL;
        return REMOTE_CONTROL;
    } 

    if(start_buttom()){
        delay(500);
        sekunde = 0;
        minute = 0;
        return WORK;
    }

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

    digitalWrite(REDLED,LOW);
    digitalWrite(GREENLED,HIGH);

 //<<<<<<<<<<<<<<<<<<<<<<<Display Batterie Spannung>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(_battery("1"))
        return BATTERIE_EMPTY;

    getTF_High_Data(&Lucano_height, &height_strength);
        
    if(Lucano_height < delimbing_height) {
        _drive_UP();
    }
    else{
        _drive_STOP();
        delay(500);
        return DRIVE_BACK;
    }

//  <<<<<<<<<<<<<<<<<<<< go to next State >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if(BT_CONNECT){
        Display_Page("4");
        page4_text("Attention!","Remote Control","Bluetooth Connected");
        old_baterie_value = DEFALT_BAT_VAL;
        return REMOTE_CONTROL;
    } 

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

    _battery("4");

    hook_fall_counter = getTFminiDataI2C();



    if(BT_CONNECT){
        return REMOTE_CONTROL;
        delay(20);
    }

    old_baterie_value = DEFALT_BAT_VAL;
    ref_counter = LOOPS_REF_LIFTING_COLLUM;
    delimbing_height = 0;
    Display_Page("1");
    return IDLE;    
}


/*****************************************************************************
 * Function name:     drive_back
 * 
 * Descriptions:      Funktion der State Maschiene 
 *                    Der Lucano fährt solage runter bis er wieder 90cm über den Boden ist

 * 
 * Variabels:         
 * 
 *                   
 *****************************************************************************/
uint16_t drive_back(void){


    getTF_High_Data(&Lucano_height, &height_strength);                          //Auslesen des LiDARs für die höhe
    
    if(Lucano_height > DRIVE_BACK_HEIGHT) {                                     //fahre runter solange bis der Lucano wieder auf dem Bden ist
        _drive_DOWN();      
    }
    else{
        _drive_STOP();                                                          //Anhalten
        delay(500);                                                             //Eine halbe Sekunde warten
        Display_Page("2");                                                      //Ausgabe der zweiten Seite
        Display_delclimbing_height(delimbing_height,"2");                       //Ausgabe der geastenten höhe
        Display_working_time(sekunde ,minute, "2");                             //Ausgabe der entastugszeit
        delimbing_height = delimbing_height + DIFF_HEIGT_SISSOR;                //Die Höhenanpassung wirder rausnehmen
        delimbing_height = delimbing_height / cm2m;                             //wieder von m auf cm umrechen damit die höhe im idle status wieder neu eingestellt werden kann
        old_baterie_value = DEFALT_BAT_VAL;                                     //Alten Batteriewert neu setzten damit auf der neuen Seite der Batteriestand wieder ausgegeben wird
        return FINISHED;
    }

    if(BT_CONNECT){                                                             //Wenn mit BT verbunden in den "remote control" state gehen
        Display_Page("4");                                                      //Ausgabe der vierten Seite
        page4_text("Attention!","Remote Control","Bluetooth Connected");        //Text für die BT-Verbindung ausgeben 
        old_baterie_value = DEFALT_BAT_VAL;                                     //Alten Batteriewert neu setzten damit auf der neuen Seite der Batteriestand wieder ausgegeben wird
        return REMOTE_CONTROL;  	                                            
    } 

    return DRIVE_BACK;    
}

/*****************************************************************************
 * Function name:     drive_back
 * 
 * Descriptions:      Funktion der State Maschiene 
 *                    Der Lucano fährt solage runter bis er wieder 90cm über den Boden ist

 * 
 * Variabels:         
 * 
 *                   
 *****************************************************************************/
uint16_t finished(void){

    _battery("2");
    hook_fall_counter = getTFminiDataI2C();

    if (confirmation_buttom()){
        Display_Page("1");
        Display_delclimbing_height(delimbing_height,"1");
        old_baterie_value = DEFALT_BAT_VAL;
        ref_counter = LOOPS_REF_LIFTING_COLLUM;
        delay(200);
        return IDLE;
    }

    if(BT_CONNECT){
        Display_Page("4");
        page4_text("Attention!","Remote Control","Bluetooth Connected");
        old_baterie_value = DEFALT_BAT_VAL;
        return REMOTE_CONTROL;
    } 

    delay(20);
    return FINISHED;    
}