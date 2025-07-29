#include "ultrasonic_sensor.hpp"

UltrasonicSensor::UltrasonicSensor(uint8_t trigPin, uint8_t echoPin)
    : trigPin_(trigPin), echoPin_(echoPin) {}

void UltrasonicSensor::begin() {
    pinMode(trigPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
    digitalWrite(trigPin_, LOW);
    delay_ms(30); // Sensor stabilization time
}

float UltrasonicSensor::measureDistance(Unit unit) const {
    long duration = measurePulseDuration();
    if (duration < 0) return -1.0f;

    float distanceCm = duration / 58.2f;
    return (unit == Unit::INCH) ? distanceCm / 2.54f : distanceCm;
}

long UltrasonicSensor::measurePulseDuration() const {
    // Send 10us trigger pulse
    digitalWrite(trigPin_, LOW);
    delay_us(2);
    digitalWrite(trigPin_, HIGH);
    delay_us(10);
    digitalWrite(trigPin_, LOW);

    // Measure duration of HIGH echo signal
    long duration = pulseIn(echoPin_, HIGH, 50000); // Timeout: 50ms
    return (duration == 0) ? -1 : duration;
}

bool UltrasonicSensor::isObjectDetected(float thresholdCm) const {
    float distance = measureDistance(Unit::CENTIMETER);
    return (distance > 0 && distance <= thresholdCm);
}

float UltrasonicSensor::filteredDistance(uint8_t sampleCount, uint16_t delayMs) const {
    float total = 0;
    uint8_t validSamples = 0;

    for (uint8_t i = 0; i < sampleCount; ++i) {
        float d = measureDistance(Unit::CENTIMETER);
        if (d > 0) {
            total += d;
            validSamples++;
        }
        delay_ms(delayMs);
    }

    return (validSamples == 0) ? -1.0f : total / validSamples;
}

void UltrasonicSensor::delay_us(uint32_t delayUs) {
    uint32_t start = micros();
    while ((micros() - start) < delayUs);
}

void UltrasonicSensor::delay_ms(uint32_t delayMs) {
    for (uint32_t i = 0; i < delayMs; ++i) {
        delay_us(1000);
    }
}