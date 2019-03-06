#include <Arduino.h>
#include "LCD_Functions.h"


//  Serial.println(LCD_WIDTH); = 84
//  Serial.println(LCD_HEIGHT); = 48
void InputToLCD(uint16_t data1, uint16_t data2, uint16_t mode){
  
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

  if(mode == 1){
    setStr("VEAB 1", 25, 30, BLACK);
  }
  if(mode == 2){
    setStr("VEAB 2", 25, 30, BLACK);
  }

  
  //float x = 1.203;
  //char DataString3[10];
  //ftoa(x, DataString3, 10);
  
  updateDisplay();
}


void setupLCD(){
  lcdBegin(); // This will setup our pins, and initialize the LCD
  setContrast(60); // Good values range from 40-60
  clearDisplay(WHITE);
  updateDisplay();
  InputToLCD(2040, 2040, 1);
}
