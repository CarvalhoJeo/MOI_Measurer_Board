#include <MOI_Estimator.h>
#include <Arduino.h>

MOI_Estimator::MOI_Estimator() {
}

void MOI_Estimator::seenWeightInFinalHeight() {
    timeSeenInFinalHeight = millis(); 
    weightPassed = true;
}

void MOI_Estimator::seenWeightInInitialHeight() {
    timeSeenInInitialHeight = millis(); 
    weightPassed = false;
}

float MOI_Estimator::getFreefallTime() {
    fallTime = (timeSeenInFinalHeight - timeSeenInInitialHeight) / 1000.0;
    return fallTime;
}

float MOI_Estimator::calculateAceleration() {
    weightAceleration = (2*distanceBetweenSensors)/(getFreefallTime()*getFreefallTime());
    return weightAceleration;
}

float MOI_Estimator::calculatePulleyAngularAceleration(){
    pulleyAngularAceleration = calculateAceleration() / pulleyRadius;
    return pulleyAngularAceleration;
}

float MOI_Estimator::calculateForcesInWeight(){
    forcesInWeight = mass*(gAceleration-weightAceleration);
    return forcesInWeight;
}

float MOI_Estimator::calculateTorqueInPulley(){
    torqueInPulley = calculateForcesInWeight()*pulleyRadius;
    return torqueInPulley;
}

float MOI_Estimator::calculateTotalMOI(){
    totalMOI = calculateTorqueInPulley()/calculatePulleyAngularAceleration();
}

float MOI_Estimator::calculateObjectMOI(){
    objectMOI = forcesInWeight*pulleyRadius;
}

void MOI_Estimator::calculate(){
    calculateTotalMOI();
}

JsonDocument MOI_Estimator::getJsonData(){
    JsonDocument json;
    json["distanceTraveled"] = distanceBetweenSensors;
    json["timeTraveled"] = fallTime;
    json["mass"] = mass;
    json["pulleyRadius"] = pulleyRadius;
    json["weightAceleration"] = weightAceleration;
    json["pulleyAngularAceleration"] = pulleyAngularAceleration;
    json["forcesInWeight"] = forcesInWeight;
    json["torqueInPulley"] = torqueInPulley;
    json["totalMOI"] = totalMOI;
    json["platformMOI"] = platformMOI;
    json["objectMOI"] = objectMOI;
    return json;
}
