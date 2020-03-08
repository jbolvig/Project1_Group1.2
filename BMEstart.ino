// Setup fucntion for BME280 sensor

void BMEstart() {
  Wire.begin();
  mySensor.settings.I2CAddress = 0x76;  //Adjusting I2C address
  
  //Set the daily barometric pressure at sea level in Pa
  mySensor.beginI2C();
  mySensor.setReferencePressure(100580);

  Serial.println("Initializing BME280 sensor..."); //Print to serial monitor

  // Check if BME280 is correctly wired
  if ( !mySensor.beginI2C() ) {
    Serial.println("The sensor did not respond. Please check wiring.");
    while (1); // freeze
  }
  
}


/*
 * Davids gruppe:
void BMESetup() {
  Wire.begin();
  mySensor.setI2CAddress(0x76);
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while (1); //Freeze
  }
}
*/
