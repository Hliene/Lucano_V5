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
void Display_delclimbing_height(uint16_t delclimbing_height, const char* page){
  Serial2.print("page");
  Serial2.print(page);
  Serial2.print(".t3.txt="); 
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
void Display_baterie_value(uint16_t baterie_value, const char* page){
  Serial2.print("page"); 
  Serial2.print(page); 
  Serial2.print(".j0.val="); 
  Serial2.print(baterie_value);
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);

  Serial2.print("page");
  Serial2.print(page); 
  Serial2.print(".t1.txt=");  
  Serial2.write(0x22);            //"
  Serial2.print(baterie_value); 
  Serial2.write(0x25);            //%
  Serial2.write(0x22);            //"
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);
}

/*****************************************************************************
 * Function name:     Dispaly_Page
 * 
 * Descriptions:      Funktion zum Aufrufen der vierten Display Seite
 * 
 * Stecker:           I2C_Display:
 *                    Pin1  = 5V
 *                    Pin2  = D21
 *                    Pin3  = D20
 *                    Pin4  = GND
 *                    
 *****************************************************************************/
void Display_Page(const char* page){
  Serial2.print("page ");
  Serial2.print(page);  
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);
}



/*****************************************************************************
 * Function name:     page4_text
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
void page4_text(const char* text1, const char* text2, const char* text3){

  Serial2.print("page4.t2.txt="); 
  Serial2.write(0x22);            //"
  Serial2.print(text1); 
  Serial2.write(0x22);            //"
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);

  Serial2.print("page4.t3.txt="); 
  Serial2.write(0x22);            //"
  Serial2.print(text2); 
  Serial2.write(0x22);            //"
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);

    Serial2.print("page4.t4.txt="); 
  Serial2.write(0x22);            //"
  Serial2.print(text3); 
  Serial2.write(0x22);            //"
  Serial2.write(0xFF); 
  Serial2.write(0xFF); 
  Serial2.write(0xFF);
}