#include "ultrasonic_sensor.hpp"

UltrasonicSensor::UltrasonicSensor(uint8_t trigPin, uint8_t echoPin)
    : trigPin_(trigPin), echoPin_(echoPin) {}

void UltrasonicSensor::begin() {

}

float UltrasonicSensor::measureDistance(Unit unit) const {
    return 2.2;
}

long UltrasonicSensor::measurePulseDuration() const {
    return 25;
}

bool UltrasonicSensor::isObjectDetected(float thresholdCm) const {
    return false;
}

float UltrasonicSensor::filteredDistance(uint8_t sampleCount, uint16_t delayMs) const {
    return 2.2;
}
