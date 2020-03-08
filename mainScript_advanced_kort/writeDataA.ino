// Write data for part A to serial monitor and SD card

void writeDataA()  {

  // Print to serial monitor
  // Print headers
  Serial.println("Pressure,Temperature,Altitude");

  // Print to serial monitor
  Serial.print(pres, 2);
  Serial.print(",");
  Serial.print(temp, 2);
  Serial.print(",");
  Serial.println(alti, 2);


  // Write data to SD-card
  dataFile = SD.open("dataA.csv", FILE_WRITE); // open file and write to it

  // If dataA.csv is found, write to it
  if (dataFile) {
    // print data
    dataFile.print(pres, 2);
    dataFile.print(",");
    dataFile.print(temp, 2);
    dataFile.print(",");
    dataFile.println(alti, 2);

    // close file
    dataFile.close();
  }

  // If file is not found print error message
  else  {
    Serial.println("Error opening dataA.csv");
  }
  
}
