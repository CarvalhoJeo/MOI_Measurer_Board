#include <Arduino.h>
#include <StateManager.h>
#include <ArduinoJson.h>

StateManager::StateManager(){
    pinMode(13, OUTPUT);
    pinMode(7, INPUT);
    pinMode(11, INPUT);    
}

void StateManager::run(){
    switch (state) {
    case WAIT_FOR_START:
        digitalWrite(13, LOW);
        if(Serial.available() > 0){
            char input = Serial.read();
            if(input == 'X'){
                state = MEASURING;
            }
        }
        break;
    case MEASURING:
        digitalWrite(13, HIGH);
        if(!digitalRead(pin_top_sensor) && !secondSensorDetected){
            firstSensorDetected = true;
            moi_estimator->seenWeightInInitialHeight();
        }else if(firstSensorDetected && !digitalRead(pin_bottom_sensor)){
            moi_estimator->seenWeightInFinalHeight();
            secondSensorDetected = true;
        }
        if(firstSensorDetected && secondSensorDetected){
            moi_estimator->calculate();
            state = SEND_VALUES;
        }
        break;
    case SEND_VALUES:
        digitalWrite(13, LOW);
        Serial.flush();
        serializeJson(moi_estimator->getJsonData(), Serial);
        state = RESET;
        break;
    case RESET:
        firstSensorDetected = false;
        secondSensorDetected = false;
        Serial.flush();
        state = WAIT_FOR_START;
        break;
    }
}