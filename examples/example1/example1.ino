#include <PushButton.h>

//
// Button pins
//
PushButton button1(GPIO_NUM_0);

void onButton1Pressed() {
  Serial.println("Button 1 has been pressed.");
}

void onButton1Released(unsigned int duration) {
  Serial.printf("Button 1 has been released after %zu millis.\n", duration);
}

void setup() {
  // we need serial output for the monitor.
  Serial.begin(115200);

  // My button is grounded so I set them up as INPUT_PULLUP.
  // If the argument is not specified it will begin as INPUT.
  button1.begin(INPUT_PULLUP);

  // Set the callbacks methods.
  // We set button1 to detected press and release events.
  // We could set only one of the events if we do not need one of them.
  button1.setPressedCallback(onButton1Pressed);
  button1.setReleasedCallback(onButton1Released);
}

void loop() {
  // We must call the loop method of each button.
  button1.loop();
}