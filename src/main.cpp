#include <Arduino.h>
#include <BoardConstants.h>
#include <StateManager.h>

StateManager* state_manager;

void setup() {
  pinMode(TOP_IR_PIN, INPUT);
  pinMode(BOTTOM_IR_PIN, INPUT);
  Serial.begin(9600);
  state_manager = new StateManager();
}

void loop() {
  state_manager->run();
}
