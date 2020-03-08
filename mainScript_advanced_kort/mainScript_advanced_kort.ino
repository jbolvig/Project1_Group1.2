// Main script for project 1

// Including libraries
#include <Wire.h>
#include "SparkFunBME280.h"
#include <SD.h>
#include <RTClib.h>

// Defining components
BME280 mySensor;
RTC_DS1307 rtc;
File dataFile;

// Defining global variables
float humi;
float pres;
float temp;
float alti;

// Defining pins for button and LEDs
const int buttonPin = 7;
const int ledPinA = 2;
const int ledPinB = 4;

// Defining variables to count pushes of button
int buttonState = 0;        // Current sate of button
int lastButtonState = 0;    // Last state of button
int buttonPushCounter = 0;  // Counter for number of presses

// Defining variables for debounce
unsigned long lastDebounceTime = 0;   // Last time button state switched
unsigned long debounceDelay = 50;     // Debounce time

// Defining variables for keeping track of time
int timeHour;                           // Variable to store hour of day
unsigned long prevMillisData = 0;       // Last time data was taken
unsigned long currentMillis;            // Current time since the program started
unsigned long measureInterval;          // Time interval for measurements
//const long intervalA = 2500;          // Interval for measurements for mode A
//const long intervalBDay = 300000;     // Interval for measurements for mode B at daytime
//const long intervalBNight = 600000;   // Interval for measurements for mode B at nighttime


void setup() {
  Serial.begin(57600);  // Setting baud rate
  BMEstart();           // Starting BME280
  RTCstart();           // Starting RTC
  SDstart();            // Starting SD
  buttonStart();        // Defining button and LED
  dataFileHeaders();    // Create data files and headers

  // Start with LEDs turned off
  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinB, LOW);

  // Print start message
  Serial.println(" ");
  Serial.println("Ready to use. Press once to start mode A and twice to start mode B");
  Serial.println(" ");

  // Print buttonState at start for check
  Serial.print("buttonState ");
  Serial.println(buttonState);
}


void loop() {

  DateTime now = rtc.now();   // RTC reads current time and date
  timeHour = now.hour();      // Saves the hour


  // Count number of pushes on button with debounce
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
        // Print number of pushes for check
        Serial.print("Button pushed. Nr. of pushes: ");
        Serial.println(buttonPushCounter);
      }
    }
  }

  // Save the reading as lastButtonState for new loop
  lastButtonState = reading;

  // Check the current time since start
  currentMillis = millis();

  // Activate either part A or B based on number of button pushes
  // If button hasn't been pressed, ask user to press it once or twice to select mode A or B
  if ( buttonPushCounter == 0 ) {
    // Turn LEDs off
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, LOW);
    Serial.println("Ready to use. Press once to start mode A and twice to start mode B");
  }

  // If button has been pressed once, run mode A
  if ( buttonPushCounter == 1 ) {
    // Turn LED A on and LED B off
    digitalWrite(ledPinA, HIGH);
    digitalWrite(ledPinB, LOW);
    Serial.println("Mode A initiated");

    // Change measureInterval to 2.5 sec
    measureInterval = 2500;
    // Check if it's time to measure, if it is take a measurement
    if ( currentMillis - prevMillisData >= measureInterval )  {
      prevMillisData = currentMillis; // Save the time for this measurement
      BMEdata();                      // Take the measurement
      writeDataA();                   // Write data A to serial monitor and SD card
    }
  }

  // If button has been pressed twice, run mode B
  if ( buttonPushCounter == 2 ) {
    // Turn LED B on and LED A off
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, HIGH);
    Serial.println("Mode B initiated");

    // Check if it's nighttime
    if ( timeHour < 6 ) {
      // Change measureInterval to 10 min
      measureInterval = 600000;
      // Check if it's time to measure
      if ( currentMillis - prevMillisData >= measureInterval ) {
        prevMillisData = currentMillis; // Save the time for this measurement
        BMEdata();                      // Take the measurement
        writeDataB();                   // Write data B to serial monitor and SD card
      }
    }

    // If it's daytime
    else  {
      // Change measureInterval to 5 min
      measureInterval = 300000;
      // Check if it's time to measure
      if ( currentMillis - prevMillisData >= measureInterval ) {
        prevMillisData = currentMillis; // Save the time for this measurement
        BMEdata();                      // Take the measurement
        writeDataB();                   // Write data B to serial monitor and SD card
      }
    }
  }

  // If button has been pressed more than twice, turn data gathering off and reset buttonPushCounter to 0
  if ( buttonPushCounter > 2 ) {
    buttonPushCounter = 0;
    // Turn LEDs off
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, LOW);
    Serial.println("Data gathering turned off");
  }

}
