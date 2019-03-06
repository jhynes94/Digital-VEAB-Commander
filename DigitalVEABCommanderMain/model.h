#include <Arduino.h>
#include "view.h"

#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

Adafruit_MCP4725 dac1;
Adafruit_MCP4725 dac2;

Adafruit_ADS1015 ads1015;  //0x48

//uint16_t ADC1, ADC2;

class Model
{
  public:
   uint16_t VEAB1 = 10;
   uint16_t VEAB2 = 10;
   uint16_t VEAB_MODE = 1;

   Model(){
      dac1.begin(0x60);
      dac2.begin(0x61);
      ads1015.begin();
   };

   void switchMode(){
    if(VEAB_MODE == 1){
      VEAB_MODE = 2;
    }
    else if(VEAB_MODE == 2){
      VEAB_MODE = 1;
    }
    InputToLCD(map(VEAB1, 0, 20, 0, 4095), map(VEAB2, 0, 20, 0, 4095), VEAB_MODE);
   }
   
   void incrementVEAB(){
    if(VEAB_MODE == 1){
      VEAB1++;
    }
    else if(VEAB_MODE == 2){
      VEAB2++;
    }
    writeVEAB(VEAB_MODE, map(VEAB1, 0, 20, 0, 4095));
   };
   void decrementVEAB(){
    if(VEAB_MODE == 1){
      VEAB1--;
    }
    else if(VEAB_MODE == 2){
      VEAB2--;
    }
    writeVEAB(VEAB_MODE, map(VEAB1, 0, 20, 0, 4095));
   };

   //Value must be between 0-4095
   void writeVEAB(uint16_t numberVEAB, uint16_t value){
    if(numberVEAB == 1){
      dac1.setVoltage(value, false);
    }
    else if(numberVEAB == 2){
      dac2.setVoltage(value, false);
    }

    InputToLCD(map(VEAB1, 0, 20, 0, 4095), map(VEAB2, 0, 20, 0, 4095), numberVEAB);
   };

   void readData(){
    //ADC1 = ads1015.readADC_SingleEnded(0);
    //ADC2 = ads1015.readADC_SingleEnded(1);

    //Serial.println(ADC1);
    //Serial.println(ADC2);
   };
};
