// Setup fucntion for RTC

void RTCstart() {

  Serial.println("Initializing RTC..."); //Print to serial monitor
  
  //Check if RTC is correctly wired
  if ( !rtc.begin() ) {
    Serial.println("The RTC did not respond. Please check wiring.");
    while (1);  //freeze
  }

  // Run the following line once during initial setup! Then comment out the line and upload again
  // If not the RTC will not use the current time but the time of the upload
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Set RTC to current time and date

}


/*
 * Davids gruppe
 void RTCbegin() {
    // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  rtc.begin();
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
}
 */
