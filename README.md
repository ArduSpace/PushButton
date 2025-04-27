# PushButton Arduino Library
A simple library for push buttons on Arduino projects.

## Usage
We must include the library file.

    #include <PushButton.h>
 
We can then declare the *PushButton* specifying the pin wherethe button is located. For example, GPIO0.

    PushButton button1(GPIO_NUM_0);

Inside the ***setup*** method we will call the *begin* method. Here we can specify the *pinMode*. If no argument is specified it will use *INPUT* by default.

    button1.begin(INPUT_PULLUP);
 
 Then we can set the callback methods for the event we want to listen for.
 ### Released event
 The released event signature does not return enything but will have a parameter which will tell us for how muchtime (in millis) the button has been pressed before being released. A sample callback method would be:

    void onButton1Released(unsigned int duration) {
      Serial.printf("Button 1 has been released after %zu millis.\n", duration);
    }

...and we would set it up in the ***setup*** method:

    button1.setReleasedCallback(onButton1Released);

 ### Pressed event
 The pressed event signature does not have arguments and neither returns anything. The method would be something like:
 

    void onButton1Pressed() {
      Serial.println("Button 1 has been pressed.");
    }
...and we would set it up in the ***setup*** method:

    button1.setPressedCallback(onButton1Pressed);

### Loop method
For the code to work we must call the ***loop()*** method from the main loop.

    button1.loop();

## Set the debouncing delay
The default debouncing delay is 20 millis.
If you wish to change the value you can set it through ***setDebouncingDelay***. For example, if we wish to set it to 50 millis:

    button1.setDebouncingDelay(50);

 ## Other methods.
 The *PushButton* class has some other methods that could come in handy.
 One of this methods is ***isPressed()*** which will return true if the button is pressed. For example, we could check if another button is also pressed to do soething when multiple buttons get pressed.
 
 Another usefull method is ***pressedMillis()*** which will return how much time a button has been pressed. We can use this method, for exaple, if we want to call a methd if a button has been pressed form more than a given number of millis.
