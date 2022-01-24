#include "..\lib\lucano_display.h"
#include <Arduino.h>
#include <SoftwareSerial.h>  


//SoftwareSerial NextionSerial(21, 20);

/*****************************************************************************
 * Function name:     init_Display
 * 
 * Descriptions:      Funktion zur Initalisierung des Nextion Displays
 * 
 * Stecker:           I2C_Display:
 *                    Pin1  = 5V
 *                    Pin2  = D21
 *                    Pin3  = D20
 *                    Pin4  = GND
 *                    
 *****************************************************************************/
void init_Display(void){
  //NextionSerial.begin(9600);
  Serial2.begin(9600);
  delay(100);
}

/*****************************************************************************
 * Function name:     Dispaly_Page_0
 * 
 * Descriptions:      Funktion zum Aufrufen der ersten Display Seite
 * 
 * Stecker:           I2C_Display:
 *                    Pin1  = 5V
 *                    Pin2  = D21
 *                    Pin3  = D20
 *                    Pin4  = GND
 *                    
 *****************************************************************************/
void Display_Page_0(void){
  Serial2.write("page 0"); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);
}

/*****************************************************************************
 * Function name:     Dispaly_Page_1
 * 
 * Descriptions:      Funktion zum Aufrufen der ersten Display Seite
 * 
 * Stecker:           I2C_Display:
 *                    Pin1  = 5V
 *                    Pin2  = D21
 *                    Pin3  = D20
 *                    Pin4  = GND
 *                    
 *****************************************************************************/
void Display_Page_1(void){
  Serial2.print("page 1"); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);
}

/*****************************************************************************
 * Function name:     Dispaly_delclimbing_height
 * 
 * Descriptions:      Funktion zur Ausgabe der Entanstungshöhe
 *                    Uebergabewert ist die Entastungshoehe in Metern
 * 
 * Stecker:           I2C_Display:
 *                    Pin1  = 5V
 *                    Pin2  = D21
 *                    Pin3  = D20
 *                    Pin4  = GND
 *                    
 *****************************************************************************/
void Display_delclimbing_height(uint16_t delclimbing_height){
  Serial2.print("page1.t3.txt="); 
  Serial2.write(0x22);                    //"
  Serial2.print(delclimbing_height);  
  Serial2.write(0x2E);                    //.
  Serial2.write(0x30);                    //0
  Serial2.write(0x6D);                    //m
  Serial2.write(0x22);                    //"
  Serial2.write(0xFF);              
  Serial2.write(0xFF); 
  Serial2.write(0xFF);
}

/*****************************************************************************
 * Function name:     Dispaly_baterie_value
 * 
 * Descriptions:      Funktion zur Ausgabe der Batteriespannung
 *                    Uebergabewert ist Batteriespannung in Prozent
 * 
 * Stecker:           I2C_Display:
 *                    Pin1  = 5V
 *                    Pin2  = D21
 *                    Pin3  = D20
 *                    Pin4  = GND
 *                    
 *****************************************************************************/
void Display_baterie_value(uint16_t baterie_value){
  Serial2.print("page1.j0.val="); 
  Serial2.print(baterie_value);
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);

  Serial2.print("page1.t1.txt="); 
  Serial2.write(0x22);            //"
  Serial2.print(baterie_value); 
  Serial2.write(0x25);            //%
  Serial2.write(0x22);            //"
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);
}