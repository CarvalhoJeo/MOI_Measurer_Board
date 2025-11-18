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
    int pin_top_sensor = 7;
    int pin_bottom_sensor = 11;

public:
    StateManager();

    void run();
};
