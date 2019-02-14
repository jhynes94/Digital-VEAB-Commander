#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

Adafruit_MCP4725 dac1;
Adafruit_MCP4725 dac2;

Adafruit_ADS1015 ads1015;

int16_t ADC1, ADC2;
int idacv;

void setup(void) 
{
  Serial.begin(9600);

  dac1.begin(0x60);
  dac2.begin(0x61);
  ads1015.begin();
}


void loop(void) 
{
  ADC1 = ads1015.readADC_SingleEnded(0);
  ADC2 = ads1015.readADC_SingleEnded(1);

  Serial.println("ADC1: " + ADC1);
  Serial.println("ADC1: " + ADC2);

  idacv = 0;
  
  dac2.setVoltage(idacv, false);
}
