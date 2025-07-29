#include <Arduino.h>
#include"ultrasonic_sensor.hpp"

#define TRIG_PIN 6
#define ECHO_PIN 7

UltrasonicSensor sensor(TRIG_PIN, ECHO_PIN);

void setup() {
    Serial.begin(9600);
    sensor.begin();
}

void loop() {

  float distance = sensor.measureDistance(Unit::CENTIMETER);

  if (distance > 0) {
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
  } else {
      Serial.println("Measurement failed");
  }

  delay(500);
}

