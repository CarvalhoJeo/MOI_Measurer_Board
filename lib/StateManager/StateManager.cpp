#include <Arduino.h>
#include <StateManager.h>
#include <BoardConstants.h>
#include <ArduinoJson.h>

void StateManager::run(){
    switch (state) {
    case WAIT_FOR_START:
        if(Serial.available() > 0){
            char input = Serial.read();
            if(input == 'X'){
                state = MEASURING;
            }
        }
        break;
    case MEASURING:
        if(digitalRead(TOP_IR_PIN) && !secondSensorDetected){
            firstSensorDetected = true;
            moi_estimator->seenWeightInInitialHeight();
        }else if(firstSensorDetected && digitalRead(BOTTOM_IR_PIN)){
            moi_estimator->seenWeightInFinalHeight();
            secondSensorDetected = true;
        }
        if(firstSensorDetected && secondSensorDetected){
            moi_estimator->calculate();
            state = SEND_VALUES;
        }
        break;
    case SEND_VALUES:
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