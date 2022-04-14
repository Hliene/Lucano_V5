#include "..\lib\lucano_drive.h"
#include "..\lib\led_summer.h"
#include "..\lib\lucano_actuator.h"
#include <Arduino.h>

uint32_t  counter_up =0;

/*****************************************************************************
 * Function name:     init_drive
 * 
 * Descriptions:      Funktion zur Initalisierung der GPIOs die für den Antrieb 
 *                    gebraucht werden
 * 
 * Stecker:           Spare 3
 *                    Drive up =   Pin 2
 *                    Drive Down = Pin 3
 *                    
 * Output pins:       D8  = PWM Finger links
 *                    D9  = PWM Finger mitte links
 *                    D10 = PWM Finger mitte rechts
 *                    D11 = PWM Finger rechts
 *                    
 *                    D24 = direction Finger links 
 *                    D25 = direction Finger mitte links 
 *                    D26 = direction Finger mitte rechts
 *                    D27 = direction Finger rechts
 *****************************************************************************/
void init_drive(void){
    
  pinMode(PWM_FL,OUTPUT);
  pinMode(PWM_FML,OUTPUT);
  pinMode(PWM_FMR,OUTPUT);
  pinMode(PWM_FR,OUTPUT);
  pinMode(DIR_FL,OUTPUT);
  pinMode(DIR_FML,OUTPUT);
  pinMode(DIR_FMR,OUTPUT);
  pinMode(DIR_FR,OUTPUT);
  
  digitalWrite(PWM_FL,LOW);
  digitalWrite(PWM_FML,LOW);
  digitalWrite(PWM_FMR,LOW);
  digitalWrite(PWM_FR,LOW);
  
  digitalWrite(DIR_FL,LOW);
  digitalWrite(DIR_FML,LOW);
  digitalWrite(DIR_FMR,LOW);
  digitalWrite(DIR_FR,LOW);
}

/*****************************************************************************
 * Function name:     _drive_UP
 * 
 * Descriptions:      Funktio zur Ansteuerug der Antriebsmotoren um 
 *                    mit dem Lucano hoch zu fahren
 * 
 * Stecker:           Spare 3
 *                    Drive up =   Pin 2
 *                    Drive Down = Pin 3
 *                    
 * Output pins:       D8  = PWM Finger links
 *                    D9  = PWM Finger mitte links
 *                    D10 = PWM Finger mitte rechts
 *                    D11 = PWM Finger rechts
 *                    
 *                    D24 = direction Finger links 
 *                    D25 = direction Finger mitte links 
 *                    D26 = direction Finger mitte rechts
 *                    D27 = direction Finger rechts
 *****************************************************************************/
uint16_t _drive_UP(void){
      
  uint16_t current_FR, current_FMR, current_FML;
      
  digitalWrite(DIR_FL,LOW);
  digitalWrite(DIR_FML,LOW);
  digitalWrite(DIR_FMR,LOW);
  digitalWrite(DIR_FR,HIGH);

  //Serial.println(counter_up);
  current_FR = analogRead(CURRENT_FL);
  current_FMR = analogRead(CURRENT_FMR);
  current_FML = analogRead(CURRENT_FML);

  Serial.print("FR: ");
  Serial.print(current_FR);
  Serial.print("  FMR: ");
  Serial.print(current_FMR);
  Serial.print("  FML: ");
  Serial.println(current_FML);
  
  if(ERROR_FR){
    delay(50);
    if(ERROR_FR){
      _drive_STOP();
      digitalWrite(SUMMER,HIGH);
      delay(200);
      _drive_DOWN();
      analogWrite(PWM_FML,(AntriebSpeed/2));
      analogWrite(PWM_FL,(AntriebSpeed/2));
      delay(2000);
      _drive_STOP();
      digitalWrite(SUMMER,LOW);
      counter_up = 0; 
      return 0;
    }   
  }
  else if((current_FMR < 100) | (current_FML < 100)){//(current_FR > (current_FMR +10) | current_FR > (current_FML +10)){
    analogWrite(PWM_FML,(AntriebSpeed /2));
    analogWrite(PWM_FL,(AntriebSpeed /2));
    analogWrite(PWM_FR,(AntriebSpeed ));
    analogWrite(PWM_FMR,(AntriebSpeed));
    //Serial.println("over current");
    return 1;
    //counter_up = counter_up +1;
  }
  else{   
    analogWrite(PWM_FR,AntriebSpeed);
    delay(10);
    analogWrite(PWM_FMR,AntriebSpeed);
    delay(10);
    analogWrite(PWM_FML,AntriebSpeed-20);
    delay(10);
    analogWrite(PWM_FL,AntriebSpeed-20);
    if(counter_up>3)
      counter_up = counter_up/2;   
  }
  return 2;
}

/*****************************************************************************
 * Function name:     _drive_DOWN
 * 
 * Descriptions:      Funktio zur Ansteuerug der Antriebsmotoren um 
 *                    mit dem Lucano runter zu fahren
 * 
 * Stecker:           Spare 3
 *                    Drive up =   Pin 2
 *                    Drive Down = Pin 3
 *                    
 * Output pins:       D8  = PWM Finger links
 *                    D9  = PWM Finger mitte links
 *                    D10 = PWM Finger mitte rechts
 *                    D11 = PWM Finger rechts
 *                    
 *                    D24 = direction Finger links 
 *                    D25 = direction Finger mitte links 
 *                    D26 = direction Finger mitte rechts
 *                    D27 = direction Finger rechts
 *****************************************************************************/
void _drive_DOWN(void){
  
  digitalWrite(DIR_FL,HIGH);
  digitalWrite(DIR_FML,HIGH);
  digitalWrite(DIR_FMR,HIGH);
  digitalWrite(DIR_FR,LOW);
      
  analogWrite(PWM_FL,(AntriebSpeed));
  delay(50);
  analogWrite(PWM_FML,(AntriebSpeed));
  delay(50);
  analogWrite(PWM_FMR,(AntriebSpeed -100));
  delay(50);
  analogWrite(PWM_FR,(AntriebSpeed -100));
}

/*****************************************************************************
 * Function name:     _attach_to_tree(void)
 * 
 * Descriptions:      Funktio zum Anstetzten den Lucano an dem Baum 
 * 
 * Stecker:           Spare 3
 *                    Drive up =   Pin 2
 *                    Drive Down = Pin 3
 *                    
 * Output pins:       D8  = PWM Finger links
 *                    D9  = PWM Finger mitte links
 *                    D10 = PWM Finger mitte rechts
 *                    D11 = PWM Finger rechts
 *                    
 *                    D24 = direction Finger links 
 *                    D25 = direction Finger mitte links 
 *                    D26 = direction Finger mitte rechts
 *                    D27 = direction Finger rechts
 *****************************************************************************/
void _attach_to_tree(void){

    digitalWrite(DIR_FL,LOW);
    digitalWrite(DIR_FML,HIGH);
    digitalWrite(DIR_FMR,HIGH);
    digitalWrite(DIR_FR,LOW);
        
    analogWrite(PWM_FL,(AntriebSpeed));
    analogWrite(PWM_FML,(AntriebSpeed));
    analogWrite(PWM_FMR,(AntriebSpeed));
    analogWrite(PWM_FR,(AntriebSpeed));
}

/*****************************************************************************
 * Function name:     _remove_from_tree(void)
 * 
 * Descriptions:      Funktion um den Lucano vom Baum zu nehmen 
 * 

 *                    
 * Output pins:       D8  = PWM Finger links
 *                    D9  = PWM Finger mitte links
 *                    D10 = PWM Finger mitte rechts
 *                    D11 = PWM Finger rechts
 *                    
 *                    D24 = direction Finger links 
 *                    D25 = direction Finger mitte links 
 *                    D26 = direction Finger mitte rechts
 *                    D27 = direction Finger rechts
 *****************************************************************************/
void _remove_from_tree(void){

    digitalWrite(DIR_FL,HIGH);
    digitalWrite(DIR_FML,LOW);
    digitalWrite(DIR_FMR,LOW);
    digitalWrite(DIR_FR,HIGH);
        
    analogWrite(PWM_FL,(AntriebSpeed));
    analogWrite(PWM_FML,(AntriebSpeed));
    analogWrite(PWM_FMR,(AntriebSpeed));
    analogWrite(PWM_FR,(AntriebSpeed));
}

/*****************************************************************************
 * Function name:     _drive_STOP
 * 
 * Descriptions:      Funktio um die Antriebsmotoren anzuhalten
 * 
 * Stecker:           Spare 3
 *                    Drive up =   Pin 2
 *                    Drive Down = Pin 3
 *                    
 * Output pins:       D8  = PWM Finger links
 *                    D9  = PWM Finger mitte links
 *                    D10 = PWM Finger mitte rechts
 *                    D11 = PWM Finger rechts
 *                    
 *                    D24 = direction Finger links 
 *                    D25 = direction Finger mitte links 
 *                    D26 = direction Finger mitte rechts
 *                    D27 = direction Finger rechts
 *****************************************************************************/
void _drive_STOP(void){
  
  analogWrite(PWM_FL,0);
  analogWrite(PWM_FML,0);
  analogWrite(PWM_FMR,0);
  analogWrite(PWM_FR,0);
}
