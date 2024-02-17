// minimaler TM1650 driver...
// some of this stuff is (more or less) copied from https://github.com/arkhipenko/TM1650

const byte TM1650_DISPLAY_BASE = 0x34;  // Address of the left-most digit
const byte TM1650_DCTRL_BASE = 0x24;    // Address of the control register of the left-most digit
const byte DPdigit = 1;                 // we are zero based...

//********************************************************************************************************************************
void displayinit() {
  Wire.beginTransmission(TM1650_DISPLAY_BASE);

  if ((Wire.endTransmission() != 0)) {
    // This fail state will be ignored.
    Serial.println("Panic: Fail to init TM1650");
  }

  displayclear();
  displayMode(true, 3);
}

//********************************************************************************************************************************
void displayclear() {
  // must I send every item that way? or all together?
  for (int i = 0; i < 4; i++) {
    Wire.beginTransmission(TM1650_DISPLAY_BASE + i);
    Wire.write(0);
    Wire.endTransmission();
  }
}

//********************************************************************************************************************************
void displayMode(bool on, byte brightness)  // 0..7
{
  brightness = (brightness & 0x7) << 4;

  for (int i = 0; i < 4; i++) {
    Wire.beginTransmission(TM1650_DCTRL_BASE + i);
    if (on) {
      Wire.write(brightness | 1);
    } else {
      Wire.write(brightness | 0);
    }
    Wire.endTransmission();
  }
}

//********************************************************************************************************************************
byte digits[10] = {
  /*
      A
     F B
      G
     E C 
      D P
  */
  //BFAEDCGP
  0b11111100,  // 0
  0b10000100,  // 1
  0b10111010,  // 2
  0b10101110,  // 3
  0b11000110,  // 4
  0b01101110,  // 5
  0b01111110,  // 6
  0b10100100,  // 7
  0b11111110,  // 8
  0b11101110   // 9
};


//********************************************************************************************************************************
void displaystring(String s) {
  for (int i = 0; i < 4; i++) {
    char c = s[i] - '0';  // https://www.youtube.com/watch?v=ZmnS2IOZ91Y

    Wire.beginTransmission(TM1650_DISPLAY_BASE + i);
    Wire.write(digits[c] + (i == DPdigit));  // (i == DPdigit ? 1 : 0), siehe Kommentar vorher.
    Wire.endTransmission();
  }
}

//********************************************************************************************************************************
void displayError() {
  displayclear();

  Wire.beginTransmission(TM1650_DISPLAY_BASE + 3);
  Wire.write(0b01111010);
  Wire.endTransmission();
}

//********************************************************************************************************************************
void displaytest() {
  static int i = 0;
  static uint32_t ticker = 0;

  if (millis() - ticker > 5000) {
    ticker = millis();

    Serial.println(i);
    Wire.beginTransmission(TM1650_DISPLAY_BASE);
    Wire.write(digits[i]);
    Wire.endTransmission();

    i = (i == 9) ? 0 : i + 1;
  }
}

//
