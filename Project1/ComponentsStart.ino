// Setup function for BME, RTC and SD card

void ComponentsStart()  {

  // Setup BME
  Wire.begin();
  mySensor.settings.I2CAddress = 0x76;  //Adjusting I2C address

  //Set the daily barometric pressure at sea level in Pa
  mySensor.beginI2C();
  mySensor.setReferencePressure(dailyPressurePa);

  Serial.println(F("Initializing BME280 sensor...")); //Print to serial monitor

  // Check if BME280 is correctly wired
  if ( !mySensor.beginI2C() ) {
    Serial.println(F("The sensor did not respond. Please check wiring."));
    while (1); // freeze
  }


  // Setup RTC
  Serial.println(F("Initializing RTC...")); //Print to serial monitor

  //Check if RTC is correctly wired
  if ( !rtc.begin() ) {
    Serial.println(F("The RTC did not respond. Please check wiring."));
    while (1);  //freeze
  }

  // Run the following line once during initial setup! Then comment out the line and upload again
  // If not the RTC will not use the current time but the time of the upload
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Set RTC to current time and date


  // Setup SD
  Serial.println(F("Initializing SD card...")); //Print to serial monitor

  // Check if SD is correctly wired
  if ( !SD.begin() ) {
    Serial.println(F("The SD card did not respond. Please check wiring."));
    while (1); //freeze
  }

}
