#include "..\lib\lucano_lidar.h"
#include <Arduino.h>

/*****************************************************************************
 * Function name:     init_Lidar
 * 
 * Descriptions:      Funktion zur Initalisierung des Lidar sensors
 *                    Angeschloss über UART
 * 
 * Stecker:           Lidar 1
 *                    5V      = Pin 1
 *                    TX1     = Pin 2
 *                    RX1     = Pin 3
 *                    GND     = Pin 4
 *****************************************************************************/
void init_lidar1(void){
  Serial1.begin(115200); // opens serial port, sets data rate to 115200 bps
}

/*****************************************************************************
 * Function name:     getTFminiData
 * 
 * Descriptions:      Funktion zur Auswertung der Daten des Lidar sensors
 *                    Angeschloss über UART
 * 
 * Stecker:           Lidar 1
 *                    5V      = Pin 1
 *                    TX1     = Pin 2
 *                    RX1     = Pin 3
 *                    GND     = Pin 4
 *****************************************************************************/
void getTFminiData1(int* distance, int* strength) {
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];
  if(Serial1.available())
  { 
    // Serial.println( "tfmini serial available" );
    rx[i] = Serial1.read();
    if(rx[0] != 0x59) {
      i = 0;
    } else if(i == 1 && rx[1] != 0x59) {
      
      i = 0;
    } else if(i == 8) {
      for(j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if(rx[8] == (checksum % 256)) {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
      }
      i = 0;
    } else
    {
      i++;
    }
  } 
}


/*****************************************************************************
 * Function name:     Init_I2C_Lidar
 * 
 * Descriptions:      Funktion zur Initalisierung des Lidar sensors
 *                    Bussystem = I2C 
 *                    Adresse = 0x10
 *                  
 * 
 * Stecker:           I2C
 *                    5V      = Pin 1
 *                    TX1     = Pin 2
 *                    RX1     = Pin 3
 *                    GND     = Pin 4
 *****************************************************************************/
void init_I2C_lidar(void){
  

  
  //Serial1.begin(115200); // opens serial port, sets data rate to 115200 bps
}
