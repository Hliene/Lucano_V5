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

uint16_t millisekunden = 0 ;
uint16_t sekunde = 0;
uint16_t minute = 0;


/*****************************************************************************
 * Function name:     init_ISR_2
 * 
 * Descriptions:      Funktion zur Initalisierung des Timer 2 Interrupts
 *                    Timer wird auf 1ms gesetzt                
 * 
 *****************************************************************************/
void init_ISR_2(void){



  TCCR2A = ((TCCR2A & 0b11111111) | (1<<WGM01));    //Set the CTC mode   
  OCR2A = 249;          //Value for ORC0A for 1ms
  TCCR2B = ((TCCR2B & 0b11111000) | 0x05);        //Timer 1 Teiler 8
  TIMSK2|=(1<<OCIE0A);   //Set the interrupt request
  sei(); //Enable interrupt
 

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
//getTF_High_Data(&distance,&strength);
  millisekunden++;
  if(millisekunden == 500)
  {
    sekunde++;
  //  Serial.println("da");
    
    millisekunden = 0;
    if(sekunde == 60)
    {
      minute++;
      sekunde = 0;
    }

  }


}

