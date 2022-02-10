#include "..\lib\lucano_lidar.h"
#include <TFMPI2C.h>  // TFMini-Plus I2C Library v1.7.2
#include <Wire.h>     // Arduino standard I2C/Two-Wire Library
#include <Arduino.h>


TFMPI2C tfmP;         // Create a TFMini-Plus I2C object

// Initialize data variables
int16_t tfDist = 0;       // Distance to object in centimeters
int16_t tfFlux = 0;       // Signal strength or quality of return signal
int16_t tfTemp = 0;       // Internal temperature of Lidar sensor chip


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
 * Function name:     getTF_High_Data
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
void getTF_High_Data(int* distance, int* strength) {
  static int i = 0; // war vorher char
  int j = 0;        //war vorher char 
  int checksum = 0;
  static int rx[9];
  while(Serial1.available())
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
  
  tfmP.recoverI2CBus();

  Wire.begin();               // Called in previous function.
  Wire.setClock(1000000);      // Set I2C bus speed to 'Fast plus' if

  printf( "System reset: ");
  if( tfmP.sendCommand( SOFT_RESET, 0))
  {
   // printf( "passed.\r\n");
  }
  else tfmP.printReply();  // This response and 'printStatus()' are for

  printf( "Firmware version: ");
    if( tfmP.sendCommand( GET_FIRMWARE_VERSION, 0))
    {
     //   printf( "%1u.",  tfmP.version[ 0]); // print three single numbers
       // printf( "%1u.",  tfmP.version[ 1]); // each separated by a dot
       // printf( "%1u\n", tfmP.version[ 2]);
    }
    else tfmP.printReply();

  printf( "Data-Frame rate: ");
    if( tfmP.sendCommand( SET_FRAME_RATE, FRAME_500))
    {
       // printf( "%2uHz.\n", FRAME_1000);
    }
    else tfmP.printReply();

    delay(500);            // And wait for half a second.
}

/*****************************************************************************
 * Function name:     getTFminiData
 * 
 * Descriptions:      Funktion zur Auswertung der Daten des Lidar sensors
 *                    Angeschloss über UART
 * 
 * Stecker:           I2C
 *                    5V      = Pin 1
 *                    SDA     = Pin 2
 *                    SCL     = Pin 3
 *                    GND     = Pin 4
 *****************************************************************************/
int getTFminiDataI2C(void) {

    tfmP.getData( tfDist, tfFlux, tfTemp); // Get a frame of data

    if( tfmP.status == TFMP_READY)         // If no error...
      return tfDist;     
    else
    {
        tfmP.printFrame();                 // Display error and data frame
        if( tfmP.status == TFMP_I2CWRITE)  // If I2C error...
        {
            tfmP.recoverI2CBus();          // recover hung bus.
        }
    }
return 0;
}


/**
 * @brief  Asterkennung für Lidar ist aber noch nicht ganz fertig
 *  * 
 * distance =getTFminiDataI2C();

   if(distance <= 40 && distance > 0 ) {                                  //Wenn Ast näher als 40cm ist
    branch_thinkness = branch_thinkness+1;              //Zähler für Ast stärke
    if(distance <= branch_distance)                     //Ermittel des geringsten abstand zum Ast, wenn nicht der kleinste abstand genommen wird ist der Wert zu hoch
      branch_distance = distance;                       //Speichern des Abstandes
    }
    else if(branch_thinkness > 25)                         //Wenn Ast vollständig gemessen zähle "branch_detactet" hoch um die Asterkennung zu entprellen
      branch_detactet = 1;


if(branch_detactet){
  Serial.print("Aststaeke = ");
  Serial.println(branch_thinkness);
  Serial.print("Astdistance = ");
  Serial.println(branch_distance);
  branch_thinkness = 0;
  branch_detactet = 0;
  branch_distance = 41;
}
 * 
 */