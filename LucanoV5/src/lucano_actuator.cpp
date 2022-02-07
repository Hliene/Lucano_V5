#include "..\lib\lucano_actuator.h"


uint16_t feedback1 = 0;
uint16_t feedback2 = 0;
uint16_t feedback3 = 0;
uint16_t feedback4 = 0;
uint16_t feedback5 = 0;
uint16_t feedback6 = 0;

/*****************************************************************************
 * Function name:     init_actuator
 * 
 * Descriptions:      Funktion zur Initalisierung der GPIOs die für die Actuatoren
 * 
 * Stecker:           Actuator 1-6 
 *  
 * Output pins:       D2  = PWM 1
 *                    D3  = PWM 2
 *                    D4  = PWM 3
 *                    D5  = PWM 4
 *                    D6  = PWM 5
 *                    D7  = PWM 6
 *                    D22 = direction OUT 
 *                    D23 = direction IN 
 *                      
 * Input pins:        A0  = Sen1A
 *                    A1  = Sen1B
 *                    A2  = Sen2A
 *                    A3  = Sen2B
 *                    A4  = Sen3A
 *                    A5  = Sen3B
 *                    
 *                    A6  = FB6
 *                    A7  = FB5
 *                    A8  = FB4
 *                    A9  = FB3
 *                    A10 = FB2
 *                    A11 = FB1
 *****************************************************************************/
void init_actuator(void){
  // outputs
  pinMode(DIRECTION1,OUTPUT);
  pinMode(DIRECTION2,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(PWM3,OUTPUT);
  pinMode(PWM4,OUTPUT);
  pinMode(PWM5,OUTPUT);
  pinMode(PWM6,OUTPUT);
  
  digitalWrite(DIRECTION1,LOW);
  digitalWrite(DIRECTION2,LOW);
  digitalWrite(PWM1,LOW);
  digitalWrite(PWM2,LOW);
  digitalWrite(PWM3,LOW);
  digitalWrite(PWM4,LOW);
  digitalWrite(PWM5,LOW);
  digitalWrite(PWM6,LOW);

//inputs
  pinMode(FB1,INPUT);
  pinMode(FB2,INPUT);
  pinMode(FB3,INPUT);
  pinMode(FB4,INPUT);
  pinMode(FB5,INPUT);
  pinMode(FB6,INPUT);

  pinMode(SEN1A,INPUT);
  pinMode(SEN1B,INPUT);
  pinMode(SEN2A,INPUT);
  pinMode(SEN2B,INPUT);
  pinMode(SEN3A,INPUT);
  pinMode(SEN3B,INPUT);
}


/*****************************************************************************
 * Function name:     _actuator
 * 
 * Descriptions:      Funktion zur Ansterung aler Actuatoren
 * 

 *****************************************************************************/
uint8_t _actuator(uint16_t extent){

  if(_actuator1(extent) & _actuator2(1024-extent))
    return 1;

  return 0;
}

/*****************************************************************************
 * Function name:     _actuator1
 * 
 * Descriptions:      Funktion zur Ansterung des ersten Actuators 
 *                    Wenn Positin erreicht gibt funktion 1 zurück
 *                    sonst eine 0
 * 
 * Stecker:           Actuator 1
 *                    5V      = Pin 1
 *                    FB1     = Pin 2
 *                    OUT1    = Pin 3
 *                    OUT2    = Pin 4
 *                    GND     = Pin 5
 *                    
 * Output pins:       D2  = PWM 1
 *                    D22 = direction OUT 
 *                    D23 = direction IN 
 *                      
 * Input pins:        A0  = Sen1A
 *                    A11 = FB1
 *****************************************************************************/
uint8_t _actuator1(uint16_t extent){

   uint16_t newextent;
   
  feedback1 = analogRead(FB1);
  newextent = extent +130;  
  Serial.println(feedback1);
  feedback1 = feedback1 +130;
  
  if(feedback1 < (newextent-130)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM1,ANALOG);
  }
  else if(feedback1 > (newextent+130)){
    digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM1,ANALOG);
  }
  else if(feedback1 < (newextent-40)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM1,ANALOG/2);
  }
  else if(feedback1 > (newextent+40)){
    digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM1,ANALOG/2);
  }
  else if(feedback1 < (newextent-10)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM1,ANALOG/2);
  }
  else if(feedback1 > (newextent+10)){
     digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM1,ANALOG/2);
  }
  else{
    analogWrite(PWM1,0);
    return 1;
  } 
  return 0;  
}

/*****************************************************************************
 * Function name:     _actuator2
 * 
 * Descriptions:      Funktion zur Ansterung des ersten Actuators 
 *                    Wenn Positin erreicht gibt funktion 1 zurück
 *                    sonst eine 0
 * 
 * Stecker:           Actuator 2
 *                    5V      = Pin 1
 *                    FB1     = Pin 2
 *                    OUT1    = Pin 3
 *                    OUT2    = Pin 4
 *                    GND     = Pin 5
 *                    
 * Output pins:       D3  = PWM 1
 *                    D22 = direction OUT 
 *                    D23 = direction IN 
 *                      
 * Input pins:        A1  = Sen1A
 *                    A10 = FB1
 *****************************************************************************/
uint8_t _actuator2(uint16_t extent){

  uint16_t newextent;
  
  feedback2 = analogRead(FB2);
  newextent = extent +130;    
  Serial.println(feedback2);
  feedback2 = feedback2 +130;

  //Serial.println(feedback2);
  if(feedback2 > (newextent+130)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM2,ANALOG);
  }
  else if(feedback2 < (newextent-130)){
    digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM2,ANALOG);
  }
  else if(feedback2 > (newextent+40)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM2,ANALOG/2);
  }
  else if(feedback2 < (newextent-40)){
    digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM2,ANALOG/2);
  }
  else if(feedback2 > (newextent+10)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM2,ANALOG/2);
  }
  else if(feedback2 < (newextent-10)){
     digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM2,ANALOG/2);
  }
  else{
    analogWrite(PWM2,0);
    return 1;
  }   
  return 0;  
}
