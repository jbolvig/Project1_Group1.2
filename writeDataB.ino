// Write data for part B to serial monitor and SD card

void writeDataB()  {

  DateTime now = rtc.now(); //RTC reads current time and date from PC
  
  // Print to serial monitor
  // Print headers
  Serial.println("Date,Time,Humidity,Pressure,Temperature");
  
  // Print date
  Serial.print(now.day(), DEC);
  Serial.print("-");
  Serial.print(now.month(), DEC);
  Serial.print("-");
  Serial.print(now.year(), DEC);
  Serial.print(",");
 
  // print time
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(",");
  
  // print data
  Serial.print(humi, 2);
  Serial.print(",");
  Serial.print(pres, 2);
  Serial.print(",");
  Serial.println(temp, 2);


  // Write data to SD-card
  dataFile = SD.open("dataB.csv", FILE_WRITE); // open file and write to it

  // If dataB.csv is found, write to it
  if (dataFile) {
    // print date
    dataFile.print(now.day());
    dataFile.print("/");
    dataFile.print(now.month());
    dataFile.print("/");
    dataFile.print(now.year());
    dataFile.print(",");

    // print time
    dataFile.print(now.hour());
    dataFile.print(":");
    dataFile.print(now.minute());
    dataFile.print(",");

    // print data
    dataFile.print(humi, 2);
    dataFile.print(",");
    dataFile.print(pres, 2);
    dataFile.print(",");
    dataFile.println(temp, 2);

    // close file
    dataFile.close();
  }

  // If file is not found print error message
  else  {
    Serial.println("Error opening dataB.csv");
  }
  
}
