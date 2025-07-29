#ifndef ULTRASONIC_SENSOR_HPP
#define ULTRASONIC_SENSOR_HPP

#include <Arduino.h>

/**
 * @brief Units for distance measurement
 */
enum class Unit {
    CENTIMETER,
    INCH
};

/**
 * @class UltrasonicSensor
 * @brief Class for interfacing with the SRF04 ultrasonic distance sensor
 */
class UltrasonicSensor {
public:
    /**
     * @brief Constructor
     * @param trigPin GPIO pin used to trigger the sensor
     * @param echoPin GPIO pin used to read the echo signal
     */
    UltrasonicSensor(uint8_t trigPin, uint8_t echoPin);

    /**
     * @brief Initializes the GPIO pins
     */
    void begin();

    /**
     * @brief Measures distance using the sensor
     * @param unit Unit of distance (default is centimeters)
     * @return Distance in specified unit. Returns -1.0 if measurement fails.
     */
    float measureDistance(Unit unit = Unit::CENTIMETER) const;

    /**
     * @brief Detects if an object is within a specified distance
     * @param thresholdCm Threshold distance in centimeters
     * @return true if an object is within threshold, false otherwise
     */
    bool isObjectDetected(float thresholdCm) const;

    /**
     * @brief Returns a filtered (averaged) distance over multiple samples
     * @param sampleCount Number of samples to take
     * @param delayMs Delay between each sample in milliseconds
     * @return Averaged distance in centimeters. Returns -1.0 if all samples are invalid.
     */
    float filteredDistance(uint8_t sampleCount = 5, uint16_t delayMs = 50) const;

private:
    uint8_t trigPin_;
    uint8_t echoPin_;

    /**
     * @brief Sends trigger pulse and measures echo duration
     * @return Echo duration in microseconds. Returns -1 if timeout occurs.
     */
    long measurePulseDuration() const;

    /**
     * @brief Custom blocking delay function for microseconds
     * @param delayUs Desired delay time in microseconds
     */
    static void delay_us(uint32_t delayUs);

    /**
     * @brief Custom blocking delay function for milliseconds
     * @param delayMs Desired delay time in milliseconds
     */
    static void delay_ms(uint32_t delayMs);
};

#endif // ULTRASONIC_SENSOR_HPP