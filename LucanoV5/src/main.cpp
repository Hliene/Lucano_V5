#include <Arduino.h>
#include "..\lib\lucano_init.h"
#include "..\lib\lucano_display.h"
#include "..\lib\lucano_drive.h"
#include "..\lib\lucano_lidar.h"
#include "..\lib\lucano_lifting_column.h"
#include "..\lib\lucano_taster.h"
#include "..\lib\lucano_timer.h"
#include "..\lib\led_summer.h"
#include "..\lib\lucano_state.h"
#include "..\lib\lucano_battery.h"
#include "..\lib\lucano_scissor.h"
#include "..\lib\lucano_actuator.h"
#include "..\lib\lucano_bluetooth.h"



#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
//#include <evive.h>
#include "..\lib\Dabble.h"



uint16_t state = 0;

/**
 * @brief Notizen 
 * 
 * Testprogramm für alle LiDAR sensoren
 * 
 * 
 * 
 * 
 * Funktion für HS Referencefahrt
 * Display Ausschalten
 * Struct oder Array für die Äste anlegen
 * Lidar Sensoren auf i2C umbauen
 * 
 */




void setup() {

  Dabble.begin(9600);  
  init_ISR_2();
  init_actuator();
  init_drive();
  init_battery();
  init_ledSummer(); 
  init_lucano();
  init_Buttons();
  init_lifting_column();
  init_Display();
  Display_Page("0");
  delay(1000);
  Display_Page("1");
  state = IDLE;
  init_lidar1();
  init_I2C_lidar();
 
}
int i;

void loop() {

//Dabble.processInput();

//delay(1);
  
  switch(state)
    {
      case IDLE:
        state = idle();
        break;

      case ATTACH_TO_TREE:
        state = attach_to_tree();
        break;  

      case HOOK_FALL_PROTECTION:
        state = hook_fall_protection();
        break;

      case READY_TO_START: 
        state = ready_to_start();
        break;

      case WORK: 
        state = work();
        break;

      case DRIVE_BACK:
        state = drive_back();
        break;

      case FINISHED:
        state = finished();
        break;

      case 8:
        
        break;  
      
      case REMOTE_CONTROL:
        Dabble.processInput();

        if(GamePad.isDownPressed()){ 
          _drive_DOWN();
          Serial.println("Drive DOWN");    
          if (ENDSTOP_HS == 0){                           // Wenn sich die Hubsäule während der Fahrt aus der endlage löst
            analogWrite(PWM_ASN,100);
          }
          else 
            analogWrite(PWM_ASN,0);

        }
        else if(GamePad.isUpPressed()){
          _drive_UP();
          Serial.println("Drive UP"); 
          if (ENDSTOP_HS == 0){                           // Wenn sich die Hubsäule während der Fahrt aus der endlage löst
            analogWrite(PWM_ASN,100);
          }
          else 
            analogWrite(PWM_ASN,0);

        }
        else{
          _drive_STOP();
          analogWrite(PWM_ASP,0);
          analogWrite(PWM_ASN,0);
        } 

        //analogWrite(PWM_ASN,0);
        
        state = remote_control();
        break;

      case BATTERIE_EMPTY:
        Serial.println("batterie");
        Display_Page("4");
        page4_text("Attention!","EMPTY BATTERIE","REMOTE CONTROL");
        state = REMOTE_CONTROL;
        break; 
      
      default:
       
        break;
  }

}


