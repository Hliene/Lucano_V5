#include "..\lib\lucano_actuator.h"




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
uint8_t actuator(uint16_t extent){

  uint16_t newextent, feedback1, feedback2, feedback3, feedback4, mean_feedback;

  newextent = extent + UPPLER_LIMIT;

  //delay(200);
  feedback1 = (analogRead(FB1) + UPPLER_LIMIT);
  feedback2 = (analogRead(FB2) + UPPLER_LIMIT);
  feedback3 = (analogRead(FB3) + UPPLER_LIMIT);
  feedback4 = (analogRead(FB4) + UPPLER_LIMIT);

  mean_feedback = (feedback1 + feedback2) /2;// + feedback3 + feedback4) / 4;
/*
  Serial.print("mean feedback = ");
  Serial.print(mean_feedback);
*/
  if (mean_feedback > newextent){
   
    //Serial.print("  up  ");

    digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);

    if(feedback1 < newextent)
      feedback1 = UPPLER_LIMIT;
    if(feedback2 < newextent)
      feedback2 = UPPLER_LIMIT;  
    if(feedback3 < newextent)
      feedback3 = UPPLER_LIMIT;
    if(feedback4 < newextent)
      feedback4 = UPPLER_LIMIT;  
  /*  
    Serial.print("  FB1 = "); 
    Serial.print(feedback1); 
    Serial.print("  FB2 = "); 
    Serial.print(feedback2); 
    Serial.print("  FB3 = "); 
    Serial.print(feedback3); 
    Serial.print("  FB4 = "); 
    Serial.println(feedback4); 

*/
    if(_actuator(newextent, feedback1, PWM1) & _actuator(1024-extent, feedback2, PWM2))// & _actuator(extent, feedback3, PWM3) & _actuator(1024-extent, feedback4, PWM4))//& _actuator(extent, feedback3, PWM3)
      return 1;
    }
    else if (mean_feedback < newextent){

  //  Serial.print("  down  ");

    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);

    if(feedback1 > newextent)
      feedback1 = UPPLER_LIMIT;
    if(feedback2 > newextent)
      feedback2 = UPPLER_LIMIT;  
    if(feedback3 > newextent)
      feedback3 = UPPLER_LIMIT;
    if(feedback4 > newextent)
      feedback4 = UPPLER_LIMIT;  

 /*   Serial.print("  FB1 = "); 
    Serial.print(feedback1); 
    Serial.print("  FB2 = "); 
    Serial.print(feedback2); 
    Serial.print("  FB3 = "); 
    Serial.print(feedback3); 
    Serial.print("  FB4 = "); 
    Serial.println(feedback4);
*/
    if(_actuator(newextent, feedback1, PWM1) & _actuator(1024-extent, feedback2, PWM2))// & _actuator(extent, feedback3, PWM3) & _actuator(1024-extent, feedback4, PWM4))//& _actuator(extent, feedback3, PWM3)
      return 1;
  }
  else{
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,LOW);
  }
  return 0;
}

/*****************************************************************************
 * Function name:     _actuator
 * 
 * Descriptions:      Funktion zur Ansterung der Actuatoren
 *                    Wenn Positin erreicht gibt funktion 1 zurück
 *                    sonst eine 0
 * 
 * Stecker:           Actuator 1 - 6
 *                    5V      = Pin 1
 *                    FB1     = Pin 2
 *                    OUTP    = Pin 3
 *                    OUTN    = Pin 4
 *                    GND     = Pin 5
 * 
 * Übergabeparamter:  extent    = gewünschte position des Actuators
 *                    feedback  = aktuelle position des Actuators 
 *                    pin       = PWM Pin des Actuators
 *                    
 *****************************************************************************/
uint8_t _actuator(uint16_t extent, uint16_t feedback, uint16_t pin){

  if(feedback < (extent - UPPLER_LIMIT))
    analogWrite(pin,ANALOG);
  
  else if(feedback > (extent + UPPLER_LIMIT))
    analogWrite(pin,ANALOG);
  
  else if(feedback < (extent - LOWER_LIMIT))
    analogWrite(pin,ANALOG/2);
  
  else if(feedback > (extent + LOWER_LIMIT))
    analogWrite(pin,ANALOG/2);
  
  else{
    analogWrite(pin,0);
    return 1;
  } 
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
/*uint8_t _actuator1(uint16_t extent){

  if(feedback1 < (extent - UPPLER_LIMIT))
    analogWrite(PWM1,ANALOG);
  
  else if(feedback1 > (extent + UPPLER_LIMIT))
    analogWrite(PWM1,ANALOG);
  
  else if(feedback1 < (extent - LOWER_LIMIT))
    analogWrite(PWM1,ANALOG/2);
  
  else if(feedback1 > (extent + LOWER_LIMIT))
    analogWrite(PWM1,ANALOG/2);
  
  else{
    analogWrite(PWM1,0);
    return 1;
  } 
  return 0;  
}
*/
/*****************************************************************************
 * Function name:     _actuator2
 * 
 * Descriptions:      Funktion zur Ansterung des ersten Actuators 
 *                    Wenn Positin erreicht gibt funktion 1 zurück
 *                    sonst eine 0
 * 
 * Stecker:           Actuator 2
 *                    5V      = Pin 1
 *                    FB2     = Pin 2
 *                    OUT1    = Pin 3
 *                    OUT2    = Pin 4
 *                    GND     = Pin 5
 *                    
 * Output pins:       D3  = PWM 2
 *                    D22 = direction OUT 
 *                    D23 = direction IN 
 *                      
 * Input pins:        A1  = Sen1B
 *                    A10 = FB1
 *****************************************************************************/
/*uint8_t _actuator2(uint16_t extent){

  if(feedback2 > (extent + UPPLER_LIMIT))
    analogWrite(PWM2,ANALOG);
  
  else if(feedback2 < (extent - UPPLER_LIMIT))
    analogWrite(PWM2,ANALOG);
  
  else if(feedback2 > (extent + LOWER_LIMIT))
    analogWrite(PWM2,ANALOG/2);
  
  else if(feedback2 < (extent - LOWER_LIMIT))
    analogWrite(PWM2,ANALOG/2);

  else{
    analogWrite(PWM2,0);
    return 1;
  }   
  return 0;  
}
*/

/*****************************************************************************
 * Function name:     _actuator3
 * 
 * Descriptions:      Funktion zur Ansterung des dritten Actuators 
 *                    Wenn Positin erreicht gibt funktion 1 zurück
 *                    sonst eine 0
 * 
 * Stecker:           Actuator 3
 *                    5V      = Pin 1
 *                    FB3     = Pin 2
 *                    OUT1    = Pin 3
 *                    OUT2    = Pin 4
 *                    GND     = Pin 5
 *                    
 * Output pins:       D4  = PWM 3
 *                    D22 = direction OUT 
 *                    D23 = direction IN 
 *                      
 * Input pins:        A2  = Sen2A
 *                    A9 = FB3
 *****************************************************************************/
/*uint8_t _actuator3(uint16_t extent){

   uint16_t newextent;
   
  feedback3 = analogRead(FB3);
  newextent = extent +130;  
  //Serial.println(feedback1);
  feedback3 = feedback3 +130;
  
  if(feedback3 < (newextent-130)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM3,ANALOG*0.7);
  }
  else if(feedback3 > (newextent+130)){
    digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM3,ANALOG*0.7);
  }
  else if(feedback3 < (newextent-40)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM3,ANALOG/2);
  }
  else if(feedback3 > (newextent+40)){
    digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM3,ANALOG/2);
  }
  else if(feedback3 < (newextent-30)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM3,ANALOG/2);
  }
  else if(feedback3 > (newextent+30)){
     digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM3,ANALOG/2);
  }
  else{
    analogWrite(PWM3,0);
    return 1;
  } 
  return 0;  
}
*/
/*****************************************************************************
 * Function name:     _actuator4
 * 
 * Descriptions:      Funktion zur Ansterung des ersten Actuators 
 *                    Wenn Positin erreicht gibt funktion 1 zurück
 *                    sonst eine 0
 * 
 * Stecker:           Actuator 3
 *                    5V      = Pin 1
 *                    FB3     = Pin 2
 *                    OUT1    = Pin 3
 *                    OUT2    = Pin 4
 *                    GND     = Pin 5
 *                    
 * Output pins:       D5  = PWM 4
 *                    D22 = direction OUT 
 *                    D23 = direction IN 
 *                      
 * Input pins:        A4  = Sen2B
 *                    A8 = FB4
 *****************************************************************************/
/*uint8_t _actuator4(uint16_t extent){

  uint16_t newextent;
  
  feedback4 = analogRead(FB4);
  newextent = extent +130;    
  //Serial.println(feedback3);
  feedback4 = feedback4 +130;

  if(feedback4 > (newextent+130)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM4,ANALOG);
  }
  else if(feedback4 < (newextent-130)){
    digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM4,ANALOG);
  }
  else if(feedback4 > (newextent+40)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM4,ANALOG/2);
  }
  else if(feedback4 < (newextent-40)){
    digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM4,ANALOG/2);
  }
  else if(feedback4 > (newextent+20)){
    digitalWrite(DIRECTION1,LOW);
    digitalWrite(DIRECTION2,HIGH);
    analogWrite(PWM4,ANALOG/2);
  }
  else if(feedback4 < (newextent-20)){
     digitalWrite(DIRECTION1,HIGH);
    digitalWrite(DIRECTION2,LOW);
    analogWrite(PWM4,ANALOG/2);
  }
  else{
    analogWrite(PWM4,0);
    return 1;
  }   
  return 0;  
}
*/