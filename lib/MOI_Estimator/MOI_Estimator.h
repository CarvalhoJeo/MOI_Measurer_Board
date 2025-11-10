#pragma once

#include <ArduinoJson.h>

class MOI_Estimator {
private:
    float timeSeenInInitialHeight;
    float timeSeenInFinalHeight; 
    float weightAceleration;
    float pulleyAngularAceleration;
    float totalMOI;
    float objectMOI;
    float forcesInWeight;
    float torqueInPulley;
    float fallTime;
    bool weightPassed = false;
    const float pulleyRadius = 0.015;
    const float distanceBetweenSensors = 0.25;
    const float mass = 5;
    const float platformMOI = 231;
    const float gAceleration = 9.81;
    float getFreefallTime();
    float calculateAceleration();
    float calculatePulleyAngularAceleration();
    float calculateForcesInWeight();
    float calculateTorqueInPulley();
    float calculateTotalMOI();
    float calculateObjectMOI();
public:
    MOI_Estimator();
    JsonDocument getJsonData();
    void seenWeightInInitialHeight();
    void seenWeightInFinalHeight();
    void calculate();
};