// Setup fucntion for SD card

void SDstart()  {

  Serial.println("Initializing SD card..."); //Print to serial monitor
  
  // Check if SD is correctly wired
  if ( !SD.begin() ) {
    Serial.println("The SD card did not respond. Please check wiring.");
    while (1); //freeze
  }

}


/*
 * Davids gruppe
void SDBegin() {

  File myFile;

  int pinCS = 10;

  Serial.print("Initializing SD card...,");
  pinMode(pinCS, OUTPUT);

  SD.begin(10);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}
 */
