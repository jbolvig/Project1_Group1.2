// Get data from the BME sensor

void BMEdata()  {

  // Save data from BME 
  humi = mySensor.readFloatHumidity();
  pres = mySensor.readFloatPressure();
  temp = mySensor.readTempC();
  alti = mySensor.readFloatAltitudeMeters();
  
}




/*
 * Davids gruppe
 
void BMEReadings() {
// These lines of code are to make continuos sensor readings from the BME280.
  temperature = mySensor.readTempC();
  pressure = mySensor.readFloatPressure();
  humidity = mySensor.readFloatHumidity();

// These lines of code are to show the us in the console, that the sensor works. 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" degrees C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
}
 */
