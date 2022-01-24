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
  
  init_actuator();
  init_drive();
  init_battery();
  init_ledSummer(); 
  init_lucano();
  init_Buttons();
  init_lifting_column();
  init_Display();
  Display_Page_0();
  delay(10000);
  Display_Page_1();
  delay(100);
  state = IDLE;
  init_lidar1();
 // init_ISR_2();
}

void loop() {
  
  switch(state)
    {
      case IDLE:
        state = idle();
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

      case 5:
        
        break;

      case 6:
        
        break;
      
      case 7:
        break;

      case 8:
        
        break; 
      
      default:
        /* TODO: Do we need a default state? */
        break;
  }

}


