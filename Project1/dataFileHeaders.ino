// Create data files on SD card for part A and part B with respective headers

void dataFileHeaders()  {

  //Create dataA.csv on SD card
  dataFile = SD.open("dataA.csv", FILE_WRITE);

  // If dataA.csv is available, write to it
  if (dataFile) {
    Serial.println(F("File dataA.csv created"));
    dataFile.println(F("Pressure,Temperature,Altitude"));
    dataFile.close();
  }
  
  // If dataA.csv is not available, print error message
  else {
    Serial.println(F("Failed to open dataA.csv"));
  }

  //Create dataB.csv on SD card
  dataFile = SD.open("dataB.csv", FILE_WRITE);

  // If dataB.csv is available, write to it
  if (dataFile) {
    Serial.println(F("File dataB.csv created"));
    dataFile.println(F("Date,Time,Humidity,Pressure,Temperature"));
    dataFile.close();
  }
  
  // If dataB.csv is not available, print error message
  else {
    Serial.println(F("Failed to open dataB.csv"));
  }
  
}
