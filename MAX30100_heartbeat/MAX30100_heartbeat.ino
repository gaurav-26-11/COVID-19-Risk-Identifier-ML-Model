//including required libraries for I2C and MAX30100 sensor
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"           

//variable for LM35 temperature sensor
const int sensor = A0;
float tempc;
float vout;

//delay for MAX30100 sensor
#define REPORTING_PERIOD_MS     1000


//defining name for PulseOximeter
PulseOximeter pox;
//defining name for flag variable for timer
uint32_t tsLastReport = 0;



void setup()
{
  //Initialising Serial output monitor of arduino to output at 115200 baud rate
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");


  //checking whether sensor heartbeat sensor is properly working or not
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  //initalising oximeter setting of hatbeat sensor
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);


}

void loop()
{

  //commanding the MAX30100 heartbeat sensor to update its values with a fresh value
  pox.update();


  //here we are checking whether 1 seconds after printing last value is passed or not
  //If yes, then print the current values
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

    //reading output of temperature sensor and converting it into celcius level
    vout = analogRead(sensor); 
    tempc = (vout * 500) / 1023;


    //Printing values like heartbeat, blood oxygen and body temperature in Serial monitor
    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print('\t');
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.print("%");
    Serial.print('\t');
    Serial.print("Temperature: ");
    Serial.print(tempc);
    Serial.println("*C");
    Serial.println();

    //updating the flag variable with current values of time
    tsLastReport = millis();
  }
}
