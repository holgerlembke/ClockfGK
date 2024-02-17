// nicht direkt aufrufen

#if displaymode == LCD2004

//*********************************************************************************************************************
const byte PinLCDBacklightLED = 15;

//*********************************************************************************************************************
void setupLCDLEDControl() {
  pinMode(PinLCDBacklightLED, OUTPUT);
  // digitalWrite(PinLCDBacklightLED, HIGH);
  display.begin();
  display.backlight();
  display.noAutoscroll();

  display.setCursor(0, 0);
  display.print("clockLCD2004 Uhr");
  display.setCursor(0, 1);
  display.print(__DATE__);
  display.print(" ");
  display.print(__TIME__);

  setLCDLEDHelligkeit(60);
}

//*********************************************************************************************************************
void setLCDLEDHelligkeit(int helligkeit) {
  static int hell = -1;

  if (helligkeit != hell) {
    analogWrite(PinLCDBacklightLED, helligkeit);
    hell = helligkeit;
  }
}

const int8_t unknown = 42;

//*********************************************************************************************************************
//*********************************************************************************************************************
int8_t charmapused[8];
void initcharmap() {
  for (int i = 0; i < 8; i++) {
    charmapused[i] = unknown;
  }
}

//*********************************************************************************************************************
byte charmapfreelevel() {
  byte c = 0;
  for (int i = 0; i < 8; i++) {
    if (charmapused[i] == unknown) {
      c++;
    }
  }
  return c;
}

//*********************************************************************************************************************
char id2char(int8_t id, bool addhuebscher) {
  byte charmap[][8] = {             // __attribute__((packed)) benötigt?
                        { 0b11000,  // 0
                          0b11000,
                          0b11000,
                          0b11000,
                          0b11000,
                          0b11000,
                          0b11000,
                          0b11000 },
                        { 0b00011,  // 1
                          0b00011,
                          0b00011,
                          0b00011,
                          0b00011,
                          0b00011,
                          0b00011,
                          0b00011 },
                        { 0b11111,  // 2
                          0b11111,
                          0b11111,
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00000 },
                        { 0b00000,  // 3
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00000,
                          0b11111,
                          0b11111,
                          0b11111 },
                        { 0b00000,  // 4
                          0b00000,
                          0b00000,
                          0b01110,
                          0b01110,
                          0b01110,
                          0b00000,
                          0b00000 },
                        { 0b00000,  // 5
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00011,
                          0b00011,
                          0b00011 },
                        { 0b00011,  // 6
                          0b00011,
                          0b00011,
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00000 },
                        { 0b00000,  // 7
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00000,
                          0b11000,
                          0b11000,
                          0b11000 },
                        { 0b11000,  // 8
                          0b11000,
                          0b11000,
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00000,
                          0b00000 }
  };

  // abs()
  int8_t aid = (id < 0) ? -id : id;

  // haben wir so einen Zeichen?
  for (int i = 0; i < 8; i++) {
    if (charmapused[i] == aid) {
      return i;
    };
  }

  // Nein, also anlegen
  if ((id >= 0) || (addhuebscher)) {
    for (int i = 0; i < 8; i++) {
      if (charmapused[i] == unknown) {
        charmapused[i] = aid;
        display.createChar(i, charmap[aid]);
        return i;
      };
    }
  }

  // OK, kein Platz in der Zeichenlisten
  return unknown;
}

//*********************************************************************************************************************
//*********************************************************************************************************************
void LCDisplayGrossAnzeige(time_t now) {  // no forward
  const byte e = ' ';                     // empty
  const char dt = (char)0b10100101;

  // negative sind Verschönerungselemente, wenn Platz, ansonsten e
  const int8_t digits[10][4][3] = {
    // 0
    { { 1, 2, 0 },
      { 1, e, 0 },
      { 1, e, 0 },
      { 1, 3, 0 } },
    // 1
    { { e, e, 0 },
      { e, e, 0 },
      { e, e, 0 },
      { e, e, 0 } },
    // 2
    { { 6, 2, 0 },
      { -5, 3, 0 },
      { 1, e, e },
      { 1, 3, 7 } },
    // 3
    { { 6, 2, 0 },
      { e, 3, 0 },
      { e, e, 0 },
      { 5, 3, 0 } },
    // 4
    { { 1, e, 0 },
      { 1, 3, 0 },
      { e, e, 0 },
      { e, e, 0 } },
    // 5
    { { 1, 2, 8 },
      { 1, 3, -7 },
      { e, e, 0 },
      { 5, 3, 0 } },
    // 6
    { { 1, 2, 8 },
      { 1, 3, -7 },
      { 1, e, 0 },
      { 1, 3, 0 } },
    // 7
    { { 6, 2, 0 },
      { e, e, 0 },
      { e, e, 0 },
      { e, e, 0 } },
    // 8
    { { 1, 2, 0 },
      { 1, 3, 0 },
      { 1, e, 0 },
      { 1, 3, 0 } },
    // 9
    { { 1, 2, 0 },
      { 1, 3, 0 },
      { e, e, 0 },
      { 5, 3, 0 } }
  };

  const String wota[] = { "So", "Mo", "Di", "Mi", "Do", "Fr", "Sa" };

  initcharmap();

  // !! Zeiger auf einen statischen Buffer, andere Zeitaufrufe überschreiben die Buffer
  tm* lt = localtime(&now);

  // nur, wenn sich was geändert hat
  static byte lastmin = 100;
  if (lastmin == lt->tm_min) {
    return;
  }
  lastmin = lt->tm_min;
  byte lasthour = lt->tm_hour;

  byte anzeige[4];
  anzeige[3] = lt->tm_min % 10;
  anzeige[2] = lt->tm_min / 10;
  anzeige[1] = lt->tm_hour % 10;
  anzeige[0] = lt->tm_hour / 10;

  // ein Mal am Tag das Display löschen...
  static int tag = -1;
  // Display löschen
  if (lt->tm_yday != tag) {
    tag = lt->tm_yday;
    display.clear();
  }

  // Zeichentabelle füllen, erst alle primären Zeichen
  bool hatverschoenerung = false;
  for (byte row = 0; row < 4; row++) {
    for (byte item = 0; item < 4; item++) {
      for (byte col = 0; col < 3; col++) {
        int8_t id = digits[anzeige[item]][row][col];
        if (id >= 0) {
          if (id != e) {
            char c = id2char(id, false);
            if (c == unknown) {
              Serial.println("Panic: Character Buffer Overrun");
            }
          }
        } else {
          hatverschoenerung = true;
        }
      }
    }
  }

  // Verschönerungen hinzufügen
  if ((hatverschoenerung) && (charmapfreelevel() > 0)) {
    // schleife wie vor, nur jetzt auch negative eintragen und keine überlaufmeldung
    for (byte row = 0; row < 4; row++) {
      for (byte item = 0; item < 4; item++) {
        for (byte col = 0; col < 3; col++) {
          int8_t id = digits[anzeige[item]][row][col];
          if (id != e) {
            char c = id2char(id, true);
          }
        }
      }
    }
  }

  // aus der gefüllten Tabelle heraus Text ausgeben
  for (byte row = 0; row < 4; row++) {
    display.setCursor(0, row);
    for (byte item = 0; item < 4; item++) {
      for (byte col = 0; col < 3; col++) {
        int8_t id = digits[anzeige[item]][row][col];
        if (id == e) {
          display.print(' ');
        } else {
          char c = id2char(id, false);
          if (c == unknown) {
            display.print(' ');
          } else {
            display.print(c);
          }
        }
      }
      if (item == 1) {
        if ((row == 1) || (row == 2)) {
          display.print(dt);
        } else {
          display.print(" ");
        }
      }
    }
  }

  const byte dateofs = 16;

  display.setCursor(dateofs, 0);
  display.print(lt->tm_year + 1900);

  display.setCursor(dateofs, 1);
  if (lt->tm_mon < 9) {
    display.print("   ");
  } else {
    display.print("  ");
  }
  display.print(lt->tm_mon + 1);

  display.setCursor(dateofs - 1, 2);
  if (lt->tm_mday < 10) {
    display.print(" ");
  }
  display.print(wota[lt->tm_wday]);
  display.print(" ");
  display.print(lt->tm_mday);

  enum sasustate_t { fetch,
                     wait1,
                     wait2 };
  static sasustate_t sasustate = fetch;

  static byte sasuhour = 255;
  static byte sasuminute = 255;
  static bool istsonnenaufgang = false;

  //State-Engines sind die Lösung aller Probleme
  switch (sasustate) {
    case fetch:
      {
        holeNaechstenSonnenAufgangUntergang(now, sasuhour, sasuminute, istsonnenaufgang);
        if (istsonnenaufgang) {
          setLCDLEDHelligkeit(60);
        } else {
          setLCDLEDHelligkeit(80);
        }
        sasustate = wait1;
        break;
      }
    case wait1:
      {
        if ((sasuhour == lasthour) && (sasuminute == lastmin)) {
          sasustate = wait2;
        }
        break;
      }
    case wait2:
      {
        if ((sasuhour != lasthour) || (sasuminute != lastmin)) {
          sasustate = fetch;
        }
        break;
      }
  }

  if (sasuhour != 255) {
    display.setCursor(dateofs - 2, 3);
    const char ph = 0b01011110;  // Pfeil hoch
    const char pr = 0b01110110;  // Pfeil runter
    if (istsonnenaufgang) {
      display.print(ph);
    } else {
      display.print(pr);
    }
    if (sasuhour < 10) {
      display.print("0");
    }
    display.print(sasuhour);
    display.print(":");
    if (sasuminute < 10) {
      display.print("0");
    }
    display.print(sasuminute);
  }

  /** /
  // Anzeige des Charmap-Dingens-Frei-Level
  display.setCursor(dateofs-2, 0);
  display.print(charmapfreelevel());
  /**/
}

#endif


//