/**
 * PushButton - https://github.com/ArduSpace/PushButton
 * Copyright JuanPedro González 2025
 * MIT Licence (see license.txt)
 */
#include "PushButton.h"

/**
 * Constructor.
 */
PushButton::PushButton(uint8_t pin) : 
  _pin(pin)
{
  // Default pin mode.
  _pinMode = INPUT;
  _lastState = LOW;
  _state = LOW;
  _lastDebounceTime = 0;

  onPressed = NULL;
  onReleased = NULL;
}

/**
 * Begin the button control.
 *
 * We can optionally set the pinMode. The default pinMode will be INPUT.
 */
void PushButton::begin(uint8_t mode) {
  pinMode(_pin, mode);
  _pinMode = mode;

  // Read the button pin to register the last state.
  _state = digitalRead(_pin);
  _lastState = _state;
  _lastDebounceTime = millis();
}

/**
 * Checks if the button is pressed.
 */ 
bool PushButton::isPressed() {
  return (((_pinMode == INPUT_PULLUP) && (_state == LOW)) || ((_pinMode == INPUT) && (_state == HIGH)));
}

/**
 * Gets the millis that have ellapsed since the button was pressed.
 * If the button is not pressed it will return 0.
 */
unsigned int PushButton::pressedMillis() {
  // The button must be pressed, ifnot it shall return 0.
  if (!isPressed())
    return 0;

  // Calculate the millis the button has been pressed.
  return millis() - _press_started_at;
}

/**
 * Helper method which is called when the state of the button changes.
 */
void PushButton::stateChangedEvent(int newState) {
  _state = newState;

  // Check if the button has been released.
  if (((_pinMode == INPUT_PULLUP) && (newState == HIGH)) || ((_pinMode == INPUT) && (newState == LOW))) {
	unsigned int duration = millis() -_press_started_at;
	
    // The button has been released.
    if (onReleased != NULL)
      onReleased(duration);
  } else {
    // The button has been pressed.
    if (onPressed != NULL)
      onPressed();
      
    // Start tracking the time when it was pressed.
    _press_started_at = millis();
  }
}

/**
 * Loop method.
 *
 * This method should be called from the main loop or any other
 * method that gets called from the main loop.
 */ 
void PushButton::loop() {
  int buttonState = digitalRead(_pin);

  // if the button state has changed due to press or bouncing...
  if (buttonState != _lastState) {
    // reset the debouincing timer.
    _lastDebounceTime = millis();
    _lastState = buttonState;
  }
  
  // If enough time has ellpsed since the last change...
  if ((millis() - _lastDebounceTime) > _debounceDelay) {
    if (buttonState != _state) {
      // State has changed.
      stateChangedEvent(buttonState);
    }
  }
}

/**
 * Set the debounce delay in millis.
 */
void PushButton::setDebounceDelay(uint8_t delay) {
  _debounceDelay = delay;
}

/**
 * Sets the callback method when the button gets pressed.
 */
void PushButton::setPressedCallback(void (*function)()) {
  onPressed = function;
}

/**
 * Sets the callback method when the button gets released.
 */
void PushButton::setReleasedCallback(void (*function)(unsigned int)) {
  onReleased = function;
}
