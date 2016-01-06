/*
  Source Code for Simple and Smart Air Purifier System
  Written by Aaron Kow
  Licence: MIT Licence
*/

#include "iot_config.h"
#include "dust_config.h"

aws_iot_setup aws_iot;
dust_setup dust_sensor;

int measurePin = 4;
int ledPower = 12;
int relayPin = 13;
float result;


void setup() {
  pinMode(ledPower, OUTPUT);
  pinMode(relayPin, OUTPUT);
  aws_iot.config();
}

void loop() {
  // set dust density result
  result = dust_sensor.init(measurePin, ledPower);

  // AWS IoT MQTT for real-time data monitoring
  aws_iot.data(result);

  // if dust density more than 0.25 mg/m3, turn on air filter
  if (result > 0.25){    
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }
  
  delay(1000);
}