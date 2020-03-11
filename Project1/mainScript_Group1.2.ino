/* Main script for project 1 in course 41030 - Design of Mechatronics

   Important! Enter daily barometric pressure in dailyPressurePa on line 28. The unit should be Pa
   This is for the calculation of the altitude in mode A

   Authors:
   Group 1.2 consisting of:
   s183640 Signe Hald Lundby
   s173817 Jonas Bolvig Hansen
   s183660 Joakim Wiben Gundersen
   s173889 Mathies Augustin Olrik Nielsen

   Hand in date: 11-03-2020
*/

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
float dailyPressurePa = 100220;
float humi;
float pres;
float temp;
float alti;

// Defining pins for button and LEDs
const int buttonPin = 7;
const int ledPinA = 2;
const int ledPinB = 4;

// Defining variables to count pushes of button
int buttonState = 0;                    // Current sate of button
int lastButtonState = 0;                // Last state of button
int buttonPushCounter = 0;              // Counter for number of presses

// Defining variables for debounce
unsigned long lastDebounceTime = 0;     // Last time button state switched
unsigned long debounceDelay = 50;       // Debounce time

// Defining variables for keeping track of time
int timeHour;                           // Variable to store hour of day
unsigned long prevMillisData = 0;       // Last time data was taken
unsigned long currentMillis;            // Current time since the program started
unsigned long measureInterval;          // Time interval for measurements


void setup() {
  Serial.begin(9600);   // Setting baud rate

  ComponentsStart();    // Starting BME, RTC and SD
  Serial.println(F("Initialization complete"));

  // Defining pins as input and output for button and LED
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(buttonPin, INPUT);

  dataFileHeaders();    // Create data files on SD card

  // Start with LEDs turned off
  digitalWrite(ledPinA, LOW);
  digitalWrite(ledPinB, LOW);

  // Print start message
  Serial.println(F("Ready to use. Press once to start mode A and twice to start mode B"));
}


void loop() {

  DateTime now = rtc.now();   // RTC reads current time and date
  timeHour = now.hour();      // Saves the hour

  // Count number of pushes on button
  buttonPush();

  // Check which mode is running and if it's time to record a measurement
  // When swithcing to mode A the first measurement is taken after 2.5 sec
  // When swithcing to mode B the first measurement is taken after 5 min at daytime and 10 min at nighttime
  dataInterval();

}
