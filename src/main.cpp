#include <Arduino.h>
#include <StateManager.h>

StateManager* state_manager;

void setup() {
  Serial.begin(9600);
  state_manager = new StateManager();
}

void loop() {
  state_manager->run();
}
