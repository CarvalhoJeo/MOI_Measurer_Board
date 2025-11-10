#pragma once

#include <Arduino.h>
#include <MOI_Estimator.h>

enum States{WAIT_FOR_START, MEASURING, SEND_VALUES, RESET};

class StateManager
{
private:
    MOI_Estimator* moi_estimator = new MOI_Estimator();
    States state = WAIT_FOR_START;
    bool firstSensorDetected = false;
    bool secondSensorDetected = false;
public:
    StateManager();

    void run();
};
