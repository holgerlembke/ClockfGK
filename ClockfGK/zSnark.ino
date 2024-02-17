/* 

    Pfff. Ich weiß. 

    Es ist die philosophische Frage, an welcher Stelle ich globale Variablen definiere.

    C-Style ist, sie erst dort zu definieren, wo sie wirklch gebraucht werden. Adruino-Style ist, sie im ersten Sketch
    (ganz links) in einem Block zu deklarieren.

    Kann man so oder so machen. Ich finde den C-Style angenehmer. Resultat ist diese blöde Lösung. Ach je.


    nach: The Hunting of the Snark (An Agony in Eight Fits) 
*/

//********************************************************************************************************************************
void loopAsStation() {
  WifiMonitor();
  ZeitManagement();
}

//********************************************************************************************************************************
void loopAsAccesspoint() {
  static int apuser = 0;
  const int maxwaittime = 30;

  if (webserver != NULL) {
    webserver->handleClient();
    dnsserver->processNextRequest();
  }

  static uint32_t ticker = 0;
  static int secondscounter = 0;
  if (millis() - ticker > 1000) {
    ticker = millis();

    int apusertemp = WiFi.softAPgetStationNum();
    if (apuser != apusertemp) {
      apuser = apusertemp;
      Serial.print("AP-User: ");
      Serial.print(apuser);
      Serial.println();
    }
    if (apusertemp > 0) {
      displayapwaitmessage(-1);
      secondscounter = 0;
    } else {
      displayapwaitmessage(maxwaittime - secondscounter);
      if (secondscounter >= maxwaittime) {
        byte startmode = 1;
        displayapwaitmessage(-2);
        ESP.rtcUserMemoryWrite(0, (uint32_t *)&startmode, sizeof(startmode));
        ESP.restart();  // reset() or .restart();
      } else {
        secondscounter++;
      }
    }
  }
}

//