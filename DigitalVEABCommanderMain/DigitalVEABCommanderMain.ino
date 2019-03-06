#include <SPI.h>
#include "model.h"


int16_t LCD_LED = 8, rightButton = 2, leftButton = 4, middleButton = 3;

Model VEAB;

void setup(void) 
{
  Serial.begin(9600);

  Serial.println("Hello from STM");
  
  pinMode(LCD_LED, OUTPUT);
  digitalWrite(LCD_LED, HIGH);

  pinMode(leftButton, INPUT);
  pinMode(middleButton, INPUT);
  pinMode(rightButton, INPUT);
  
  //attachInterrupt(digitalPinToInterrupt(rightButton), increment, FALLING);
  //attachInterrupt(digitalPinToInterrupt(middleButton), decrement, FALLING);

  setupLCD();
}


void loop() {
  
  if(digitalRead(leftButton) == LOW){
    VEAB.switchMode();
    delay(500);
  }
  else if(digitalRead(rightButton) == LOW){
    VEAB.incrementVEAB();
    delay(500);
  }
  else if(digitalRead(middleButton) == LOW){
    VEAB.decrementVEAB();
    delay(500);
  }
}
