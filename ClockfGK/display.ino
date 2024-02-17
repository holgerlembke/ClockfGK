/*
  Abstraktionsebene für alle Display
*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void setupDisplay() {
#if (displaymode == LCD2004)
  setupLCDLEDControl();
#endif
#if (displaymode == Clock303)
  display303init();
#endif
#if (displaymode == LCD12864)
  display.begin();
  display.rotatedisplay(true);
#endif
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void displayTime(time_t now) {
#if displaymode == LCD2004
  LCDisplayGrossAnzeige(now);
#endif
#if displaymode == Clock303
  LED303Anzeige(now);
#endif
#if (displaymode == LCD12864)
  tm* lt = localtime(&now);
  clockface(lt->tm_hour, lt->tm_min);
#endif
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void displayIP(int mode) {
#if displaymode == LCD2004
  //??????
#endif
#if displaymode == Clock303
  //??????
#endif
#if displaymode == LCD12864
  // localIP-im Stationmodus ist hier noch (unset)
  if (mode != 1) {
    display.print("IP:");
    display.print(WiFi.softAPIP());
  }
  display.println();
#endif
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void displaystartupmode(int mode) {
#if displaymode == LCD2004
  const int row = 2;
  display.setCursor(0, row);
  if (mode == 1) {
    display.print("Start as Clock");
  } else {
    display.print("Start as Config-AP");
  }
#endif
#if displaymode == Clock303
  if (mode == 1) {
    displaytext("CL");
  } else {
    displaytext("AP");
  }
#endif
#if displaymode == LCD12864
  if (mode == 1) {
    display.println("Start as Clock");
  } else {
    display.println("Start as Config-AP");
  }
#endif
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void displayapwaitmessage(int seconds) {
#if displaymode == LCD2004
  const int row = 3;
  if (seconds == -4) {
    display.setCursor(0, row);
    display.print("AP: client connected");
  } else if (seconds == -3) {
    /*
    display.setCursor(0, row);
    display.print("start in Clock Mode");
    */
  } else if (seconds == -2) {
    display.setCursor(0, row);
    display.print("Reboot    ");
  } else if (seconds == -1) {
    display.setCursor(0, row);
    display.print("Wait: halted");
  } else {
    display.setCursor(0, row);
    display.print("Wait: ");
    display.print(seconds);
    display.print("    ");
  }
#endif
#if displaymode == Clock303
  if (seconds == -4) {
    displaytext("APco");
  } else if (seconds == -3) {
    /*
    display.print("start in Clock Mode");
    */
  } else if (seconds == -2) {
    displaytext("BOOT");
  } else if (seconds == -1) {
    displaytext("AP H");
  } else {
    displaytext("AP"+String(seconds));
  }
#endif
#if displaymode == LCD12864
  if (seconds == -4) {
    display.print("\nAP: client connected");
  } else if (seconds == -3) {
    /*
    display.print("start in Clock Mode");
    */
  } else if (seconds == -2) {
    display.print("\n\rReboot");
  } else if (seconds == -1) {
    display.print("\rWait: halted");
  } else {
    display.print("\rWait: ");
    display.print(seconds);
    display.print("    ");
  }
#endif
}




//-