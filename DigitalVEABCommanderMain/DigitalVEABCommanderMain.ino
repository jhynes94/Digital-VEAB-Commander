#include <SPI.h>
#include "LCD_Functions.h"

#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

Adafruit_MCP4725 dac1;
Adafruit_MCP4725 dac2;

Adafruit_ADS1015 ads1015;  //0x48

int16_t ADC1, ADC2;

void setup(void) 
{
  Serial.begin(9600);

  dac1.begin(0x60);
  dac2.begin(0x61);
  ads1015.begin();

  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);


  lcdBegin(); // This will setup our pins, and initialize the LCD
  updateDisplay(); // with displayMap untouched, SFE logo
  setContrast(50); // Good values range from 40-60

  delay(500);
  clearDisplay(WHITE);
  updateDisplay();
}

uint16_t VEAB1 = 0;
uint16_t VEAB2 = 4095;
uint16_t idacv = 0;

void loop(void) 
{
  ADC1 = ads1015.readADC_SingleEnded(0);
  ADC2 = ads1015.readADC_SingleEnded(1);

  dac1.setVoltage(idacv, false);
  dac2.setVoltage(idacv, false);

  Serial.println(ADC1);
  Serial.println(ADC2);
  Serial.println(idacv);
  
  //map(value, fromLow, fromHigh, toLow, toHigh)
  uint16_t Voltage1 = map(VEAB1, 0, 4096, 0, 10);
  uint16_t Voltage2 = map(VEAB2, 0, 4096, 0, 10);

  updateDisplay2(Voltage1, Voltage2);

  delay(2000);
}

void setVEAB(){
  VEAB1 += 100;
  VEAB2 -= 100;
  if(VEAB1 > 4095 || VEAB2 < 0){
    VEAB1=0;
    VEAB2 = 4095;
  }
}




//  Serial.println(LCD_WIDTH); = 84
//  Serial.println(LCD_HEIGHT); = 48
void updateDisplay2(uint16_t data1, uint16_t data2){
  
  char DataString1[10];
  char DataString2[10];
  itoa(data1, DataString1, 10);
  itoa(data2, DataString2, 10);
    
  clearDisplay(WHITE);
  updateDisplay();
  setStr(DataString1, 0, 10, BLACK);
  setStr(DataString2, 0, 20, BLACK);

  // setRect takes six parameters (x0, y0, x1, y0, fill, bw)
  setRect(10, 10, 80, 10, 1, BLACK);
  setRect(10, 20, 80, 20, 1, BLACK);

  setRect(10, 10, 10+map(VEAB1, 0, 4096, 0, 70), 16, 1, BLACK);
  setRect(10, 20, 10+map(VEAB2, 0, 4096, 0, 70), 26, 1, BLACK);
  updateDisplay();
}
