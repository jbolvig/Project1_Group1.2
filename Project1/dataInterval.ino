// Check if part A or B is running and check if it's time to record a measurement

void dataInterval()  {
  
  currentMillis = millis(); // Check the current time since start

  // Activate either part A or B based on number of button pushes
  // If button hasn't been pressed turn LED's off
  if ( buttonPushCounter == 0 ) {
    // Turn LEDs off
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, LOW);
  }

  // If button has been pressed once, run mode A
  if ( buttonPushCounter == 1 ) {
    // Turn LED A on and LED B off
    digitalWrite(ledPinA, HIGH);
    digitalWrite(ledPinB, LOW);

    // Change measureInterval to 2.5 sec
    measureInterval = 2500;
    // Check if it's time to measure, if it is take a measurement
    if ( currentMillis - prevMillisData >= measureInterval )  {
      prevMillisData = currentMillis;       // Save the time for this measurement
      Serial.println(F("Mode A running"));  // Print that mode A is running
      BMEdata();                            // Take the measurement
      writeDataA();                         // Write data A to serial monitor and SD card
    }
  }

  // If button has been pressed twice, run mode B
  if ( buttonPushCounter == 2 ) {
    // Turn LED B on and LED A off
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, HIGH);  

    // Check if it's nighttime
    if ( timeHour < 6 ) {
      // Change measureInterval to 10 min
      measureInterval = 600000;
      // Check if it's time to measure
      if ( currentMillis - prevMillisData >= measureInterval ) {
        prevMillisData = currentMillis;       // Save the time for this measurement
        Serial.println(F("Mode B running"));  // Print that mode B is running
        BMEdata();                            // Take the measurement
        writeDataB();                         // Write data B to serial monitor and SD card
      }
    }

    // If it's daytime
    else  {
      // Change measureInterval to 5 min
      measureInterval = 300000;
      // Check if it's time to measure
      if ( currentMillis - prevMillisData >= measureInterval ) {
        prevMillisData = currentMillis;       // Save the time for this measurement
        Serial.println(F("Mode B running"));  // Print that mode A is running
        BMEdata();                            // Take the measurement
        writeDataB();                         // Write data B to serial monitor and SD card
      }
    }
  }

  // If button has been pressed more than twice, turn data gathering off and reset buttonPushCounter to 0
  if ( buttonPushCounter > 2 ) {
    // Turn LEDs off
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, LOW);
    Serial.println(F("Data gathering turned off"));
    Serial.println(F("Press once to start mode A and twice to start mode B"));
    buttonPushCounter = 0;
  }
  
}
