#include <SPI.h>
#include "LCD_Functions.h"

#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

Adafruit_MCP4725 dac1;
Adafruit_MCP4725 dac2;

Adafruit_ADS1015 ads1015;  //0x48

int16_t ADC1, ADC2;
int16_t LCD_LED = 8, rightButton = 4, leftButton = 2, middleButton = 3;

void setup(void) 
{
  Serial.begin(9600);

  dac1.begin(0x60);
  dac2.begin(0x61);
  ads1015.begin();

  pinMode(LCD_LED, OUTPUT);
  digitalWrite(LCD_LED, HIGH);

  pinMode(rightButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(middleButton, INPUT);

  lcdBegin(); // This will setup our pins, and initialize the LCD
  setContrast(60); // Good values range from 40-60
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

  if(digitalRead(rightButton) == HIGH){
    VEAB1 += 100;
  }
  if(digitalRead(leftButton) == HIGH){
    VEAB1 -= 100;
  }

  updateDisplay2(VEAB1, VEAB2);

  delay(1000);
}

//  Serial.println(LCD_WIDTH); = 84
//  Serial.println(LCD_HEIGHT); = 48
void updateDisplay2(uint16_t data1, uint16_t data2){
  
  //map(value, fromLow, fromHigh, toLow, toHigh)
  uint16_t Voltage1 = map(data1, 0, 4095, 0, 10);
  uint16_t Voltage2 = map(data2, 0, 4095, 0, 10);
  
  char DataString1[10];
  char DataString2[10];
  itoa(Voltage1, DataString1, 10);
  itoa(Voltage2, DataString2, 10);
    
  clearDisplay(WHITE);
  updateDisplay();
  setStr(DataString1, 0, 10, BLACK);
  setStr(DataString2, 0, 20, BLACK);

  // setRect takes six parameters (x0, y0, x1, y0, fill, bw)
  setRect(14, 10, 84, 10, 1, BLACK);
  setRect(14, 20, 84, 20, 1, BLACK);

  setRect(14, 10, 14+map(data1, 0, 4095, 0, 70), 16, 1, BLACK);
  setRect(14, 20, 14+map(data2, 0, 4095, 0, 70), 26, 1, BLACK);
  updateDisplay();
}
