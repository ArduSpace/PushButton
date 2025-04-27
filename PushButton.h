/**
 * PushButton - https://github.com/ArduSpace/PushButton
 * Copyright JuanPedro González 2025
 * MIT Licence (see license.txt)
 */
#ifndef __PUSHBUTTON_H__
#define __PUSHBUTTON_H__

#include <Arduino.h>

class PushButton {
  public:
    // Constructor
    PushButton(uint8_t pin);

    void begin(uint8_t mode = INPUT);
    
	bool isPressed();
	unsigned int pressedMillis();
	void setDebounceDelay(uint8_t delay);
	
    void loop();
	
    // Setter methods for callback functions
    void setPressedCallback(void (*onPressed)());
    void setReleasedCallback(void (*onReleased)(unsigned int));
    
  private:
    uint8_t _pin;
    uint8_t _pinMode;
    int _lastState;
    int _state;
    unsigned long _lastDebounceTime;
    uint8_t _debounceDelay = 20;
    unsigned long _press_started_at;

    // Callbacks
    void (*onPressed)();
    void (*onReleased)(unsigned int);
    
    // Helper methods
    void stateChangedEvent(int newState);
};

#endif