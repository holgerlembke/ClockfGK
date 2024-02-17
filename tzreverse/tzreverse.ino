/*

   TZ - Reverse

   Which TZ has what Country?

   Baut die wunderbae Liste im Form...

*/


//***************************************************************************************************************
void setup() {
  delay(5000);
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  delay(5000);

  Serial.print(F("\n\nTZ - Reverse "));
  Serial.print(__DATE__);
  Serial.print(F(" "));
  Serial.print(__TIME__);
  Serial.println();

  tzreverse();
}

//***************************************************************************************************************
void loop() {
  delay(1000);
}
