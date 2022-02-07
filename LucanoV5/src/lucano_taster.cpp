#include "..\lib\lucano_taster.h"
#include <Arduino.h>

uint16_t state_BUTTOM_1       = 1;
uint16_t state_BUTTOM_2       = 1;
uint16_t state_BUTTOM_3       = 1;
uint16_t state_BUTTOM_4       = 1;
uint16_t state_ATTACH_TO_TREE = 1;


/*****************************************************************************
 * Function name:     init_Buttons
 * 
 * Descriptions:      Funktion zur Initalisierung der GPIOs für die Taster
 * 
 * Stecker:           Taster 1-2:
 *                    Plus konpf  = Taster 1-2 Pin2
 *                    Minus knopf = Taster 1-2 Pin4 
 *                    Taster 3-4:
 *                    Start konpf       = Taster 3-4 Pin2
 *                    Bestätigungsknopf = Taster 3-4 Pin4                   
 *                    
 * Input Pins:        D28 = BUTTOM_1
 *                    D29 = BUTTOM_2
 *                    D31 = BUTTOM_4
 *                    D30 = BUTTOM_3
 *                    D44 = ATTACH TO TREE
 *****************************************************************************/
void init_Buttons(void){

  pinMode(BUTTOM_1,INPUT);
  pinMode(BUTTOM_2,INPUT);
  pinMode(BUTTOM_3,INPUT);
  pinMode(BUTTOM_4,INPUT);
  pinMode(ATTACH_TREE,INPUT);
}


/*****************************************************************************
 * Function name:     minus_buttom
 * 
 * Descriptions:      Funktio zur Entprellung und einlesen des Minus-Tasters. 
 *                    Der Taster wird entprelt
 *                    Funktion gibt nur einmalig True zurück dann muss der Taster erst wieder losgelassen werden
 * 
 * Stecker:           Taster 1-2
 *                    Plus konpf  = Taster 1-2 Pin2
 *                    Minus knopf = Taster 1-2 Pin4    
 *                    
 * Input Pins:        D28 = BUTTOM_1
 *                    D29 = BUTTOM_2
 *****************************************************************************/
uint8_t minus_buttom(void){

  if(!digitalRead(BUTTOM_1)){                             //Wenn Taster gedrückt      
    state_BUTTOM_1 = (state_BUTTOM_1 << 1);               //Zähler zum Entprellen nach links schiften         
    if(state_BUTTOM_1 == (BUTTOM_LOOPs))                //Wenn anzahl erreicht gebe eine eins zurück
      return 1;                          
  }else 
    state_BUTTOM_1 = 1;                                   //Setzte state wieder auf Eins 
        
  return 0;
}

/*****************************************************************************
 * Function name:     plus_buttom
 * 
 * Descriptions:      Funktio zur Entprellung und einlesen des Plus-Tasters. 
 *                    Der Taster wird entprelt
 *                    Funktion gibt nur einmalig True zurück dann muss der Taster erst wieder losgelassen werden
 * 
 * Stecker:           Taster 1-2
 *                    Plus konpf  = Taster 1-2 Pin2
 *                    Minus knopf = Taster 1-2 Pin4    
 *                    
 * Input Pins:        D28 = BUTTOM_1
 *                    D29 = BUTTOM_2
 *****************************************************************************/
uint8_t plus_buttom(void){

  if(!digitalRead(BUTTOM_2)){                             //Wenn Taster gedrückt
    state_BUTTOM_2 = (state_BUTTOM_2 << 1);               //Zähler zum Entprellen nach links schiften         
    if(state_BUTTOM_2 == (BUTTOM_LOOPs))                //Wenn anzahl erreicht gebe eine eins zurück
      return 1;                          
  }else 
    state_BUTTOM_2 = 1;                                   //Setzte state wieder auf Eins 
        
  return 0;
}

/*****************************************************************************
 * Function name:     confirmation_buttom
 * 
 * Descriptions:      Funktio zur Entprellung und einlesen des Bestätigungs-Tasters. 
 *                    Der Taster wird entprelt
 *                    Funktion gibt nur einmalig True zurück dann muss der Taster erst wieder losgelassen werden
 * 
 * Stecker:           Taster 3-4
 *                    Start konpf       = Taster 3-4 Pin2
 *                    Bestätigungsknopf = Taster 3-4 Pin4    
 *                    
 * Input Pins:        D31 = BUTTOM_4
 *                    D30 = BUTTOM_3
 *****************************************************************************/
uint8_t confirmation_buttom(void){

  if(!digitalRead(BUTTOM_3)){                             //Wenn Taster gedrückt      
    state_BUTTOM_3 = (state_BUTTOM_3 << 1);               //Zähler zum Entprellen nach links schiften         
    if(state_BUTTOM_3 == BUTTOM_LOOPs)                    //Wenn anzahl erreicht gebe eine eins zurück
      return 1;                          
  }else 
    state_BUTTOM_3 = 1;                                   //Setzte state wieder auf Eins 
        
  return 0;
}

/*****************************************************************************
 * Function name:     start_buttom
 * 
 * Descriptions:      Funktio zur Entprellung und einlesen des Start-Tasters. 
 *                    Der Taster wird entprelt
 *                    Funktion gibt nur einmalig True zurück dann muss der Taster erst wieder losgelassen werden
 * 
 * Stecker:           Taster 3-4
 *                    Start konpf       = Taster 3-4 Pin2
 *                    Bestätigungsknopf = Taster 3-4 Pin4    
 *                    
 * Input Pins:        D31 = BUTTOM_4
 *                    D30 = BUTTOM_3
 *****************************************************************************/
uint8_t start_buttom(void){

  if(!digitalRead(BUTTOM_4)){                             //Wenn Taster gedrückt   
    state_BUTTOM_4 = (state_BUTTOM_4 << 1);               //Zähler zum Entprellen nach links schiften 
    if(state_BUTTOM_4 == BUTTOM_LOOPs)                    //Wenn anzahl erreicht gebe eine eins zurück
      return 1;                                
  }else      
    state_BUTTOM_4 = 1;                                   //Setzte state wieder auf Eins 
      
  return 0;
}

/*****************************************************************************
 * Function name:     start_buttom
 * 
 * Descriptions:      Funktio zur Entprellung und einlesen des Start-Tasters. 
 *                    Der Taster wird entprelt
 *                    Funktion gibt nur einmalig True zurück dann muss der Taster erst wieder losgelassen werden
 * 
 * Stecker:           Taster 3-4
 *                    Start konpf       = Taster 3-4 Pin2
 *                    Bestätigungsknopf = Taster 3-4 Pin4    
 *                    
 * Input Pins:        D31 = BUTTOM_4
 *                    D30 = BUTTOM_3
 *****************************************************************************/
uint8_t attach_to_tree_buttom(void){

  if(!digitalRead(ATTACH_TREE)){                             //Wenn Taster gedrückt   
    state_ATTACH_TO_TREE = (state_ATTACH_TO_TREE << 1);               //Zähler zum Entprellen nach links schiften 
    if(state_ATTACH_TO_TREE == BUTTOM_LOOPs)                    //Wenn anzahl erreicht gebe eine eins zurück
      return 1;                                
  }else      
    state_ATTACH_TO_TREE = 1;                                   //Setzte state wieder auf Eins 
      
  return 0;
}

