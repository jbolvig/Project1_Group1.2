// Counts the number of pushes on button with debounce

void buttonPush() {
  
  int reading = digitalRead(buttonPin); // Read current state of button into a local variable

  // If the state of button has changed due to noise or pressing, reset debounce timer
  if ( reading != lastButtonState ) {
    lastDebounceTime = millis();
  }

  // Check if the reading of state of button has been there for longer than the debounce delay
  if ( (millis() - lastDebounceTime) > debounceDelay )  {

    // If button state has changed
    if ( reading != buttonState ) {
      buttonState = reading;          // Change buttonState to the new reading

      // If the new button state is HIGH our buttonPushCounter increments by 1
      // because button is alway LOW unless we press it
      if ( buttonState == HIGH )  {
        buttonPushCounter++;
      }
    } 
  }

  // Save the reading as lastButtonState for new loop
  lastButtonState = reading;
  
}
