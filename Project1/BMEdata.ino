// Get data from the BME sensor

void BMEdata()  {

  // Save data from BME 
  humi = mySensor.readFloatHumidity();
  pres = mySensor.readFloatPressure();
  temp = mySensor.readTempC();
  alti = mySensor.readFloatAltitudeMeters();
  
}
