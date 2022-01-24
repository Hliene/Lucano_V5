#include "..\lib\lucano_timer.h"
#include "..\lib\lucano_lidar.h"

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//Variablen für den Lidar1 um Aeste zu erkennen 
int distance = 0;
int strength = 0;
int branch_thinkness = 0;
int branch_detactet = 0;
int branch_distance = 0;


/*****************************************************************************
 * Function name:     init_ISR_2
 * 
 * Descriptions:      Funktion zur Initalisierung des Timer 2 Interrupts
 *                    Timer wird auf 1ms gesetzt                
 * 
 *****************************************************************************/
void init_ISR_2(void){
  TCCR2A = (1<<WGM01);                // CTC Modus
  TCCR2B = (1<<CS10) | (1<<CS12);;    // Timer mode with 1024 prescler
  OCR2A = 125;                        // Wert für das match Register =>125 ist ca. alle 1ms  
  TIMSK2 |= (1<<OCIE2A);              // Compare Interrupt erlauben  
  sei();
}


/*****************************************************************************
 * Function name:     ISR (TIMER2_COMPA_vect)
 * 
 * Descriptions:      Interrupt zum auslesen der Lidar-Sensors zur Asterkennung 
 *                    
 * 
 *****************************************************************************/
ISR (TIMER2_COMPA_vect)
{
  /*
    getTFminiData1(&distance, &strength);                 //Einlesen des aktuellen Wertes des Lidar Sensors  
    
    if(distance <= 40) {                                  //Wenn Ast näher als 40cm ist
      branch_thinkness = branch_thinkness+1;              //Zähler für Ast stärke
      if(distance <= branch_distance)                     //Ermittel des geringsten abstand zum Ast, wenn nicht der kleinste abstand genommen wird ist der Wert zu hoch
        branch_distance = distance;                       //Speichern des Abstandes
    }
    else if(branch_thinkness > 5)                         //Wenn Ast vollständig gemessen zähle "branch_detactet" hoch um die Asterkennung zu entprellen
      branch_detactet = 1;
    */  
}
