#include "..\lib\lucano_lifting_column.h"
#include <Arduino.h>

uint8_t AS_Speed=       250;            //0-255
uint8_t max_current=    135;
uint8_t PWM_UP=         0;
uint8_t PWM_DOWN=       0;

uint16_t ref_counter = 50;

/*****************************************************************************
 * Function name:     init_lifting_column
 * 
 * Descriptions:      Funktion zur Initalisierung der GPIOs für die Hubsäule 
 * 
 * Stecker:           Ausleger Schere 
 *                    Hubsäule Positive       = Pin 1
 *                    Hubsäule Negativ        = Pin 2
 *                    Endstop Hubsäule        = Pin 3
 *                    GND                     = Pin 4
 *****************************************************************************/
void init_lifting_column(void){
  
  pinMode(PWM_ASP,OUTPUT);
  pinMode(PWM_ASN,OUTPUT);
  digitalWrite(PWM_ASN,LOW);
  digitalWrite(PWM_ASP,LOW);
  
  pinMode(HS_CURRENT,INPUT);
  pinMode(ENDSTOP_HS_PIN,INPUT);
}

/*****************************************************************************
 * Function name:     lift_column
 * 
 * Descriptions:      Funktion zum anheben der Hubsäule  
 *                    Die Funktion beinhaletet eine Anstiegsrampe
 *                    Wenn Hubsäule ausgefahren gibt Funktion eine Eins zurück
 * 
 * Stecker:           Ausleger Schere 
 *                    Hubsäule Positive       = Pin 1
 *                    Hubsäule Negativ        = Pin 2
 *                    Endstop Hubsäule        = Pin 3
 *                    GND                     = Pin 4
 *****************************************************************************/
uint8_t lift_column(void){

  uint16_t analog;
  
  analog = analogRead(HS_CURRENT);  
   
  if(PWM_UP < (AS_Speed - AS_Speed/10)){
    PWM_UP = PWM_UP + (AS_Speed/9);
    analogWrite(PWM_ASP,PWM_UP);
    delay(80);
  } 
  else if(analog>max_current){
    PWM_UP = 0;
    analogWrite(PWM_ASP,PWM_UP);
    return 1;
  }
  return 0;
}

/*****************************************************************************
 * Function name:     retract_column
 * 
 * Descriptions:      Funktion zum absenken der Hubsäule  
 *                    Die Funktion beinhaletet eine Anstiegsrampe
 *                    Wenn Hubsäule eingefahren gibt Funktion eine Eins zurück
 * 
 * Stecker:           Ausleger Schere 
 *                    Hubsäule Positive       = Pin 1
 *                    Hubsäule Negativ        = Pin 2
 *                    Endstop Hubsäule        = Pin 3
 *                    GND                     = Pin 4
 *****************************************************************************/
uint8_t retract_column(void){

  if (ENDSTOP_HS){                                     //Wenn Hubsäule in unterer Endlage
    PWM_DOWN = 0;
    analogWrite(PWM_ASN,PWM_DOWN); 
    return 1;
  }  
  else if (PWM_DOWN < (AS_Speed - AS_Speed/21)){
    PWM_DOWN = PWM_DOWN + (AS_Speed/20);
    analogWrite(PWM_ASN,PWM_DOWN);
    delay(30);
  }
  return 0;
}


/*****************************************************************************
 * Function name:     ref_column
 * 
 * Descriptions:      Funktion zur Referenzfahrt der Hubsäule  
 * 
 * Stecker:           Ausleger Schere 
 *                    Hubsäule Positive       = Pin 1
 *                    Hubsäule Negativ        = Pin 2
 *                    Endstop Hubsäule        = Pin 3
 *                    GND                     = Pin 4
 *****************************************************************************/
uint8_t ref_column(void){

  if(ref_counter){
    lift_column();
    ref_counter = ref_counter - 1;
    delay(20);
  }
  else {
    if(PWM_UP == 0){
      if(retract_column())
        return 1;
      }
      else{
        PWM_UP = 0;
        analogWrite(PWM_ASP,PWM_UP);
        delay(100);
      }
  }
  return 0;
}
