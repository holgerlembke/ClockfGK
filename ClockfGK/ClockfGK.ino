/*
     Clock for Generation Click

     // ..\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\3.1.2\cores\esp8266

    ++ ESP8266 <-> Arduino-Konfiguration
       
       Ziemlich egal, Flash Size 1 MB sollte klappen, auch wenn 4 MB drauf sind.

    ++ Konfiguration

        Zuerst started der ESP8266 beim Anstecken der Stromversorgung als Accesspoint 
        mit einem Webserver. Dort wartet er für 30 Sekunden, ob sich ein Client verbindet. Wenn nicht,
        bootet er erneut in einen Modus ohne Accesspoint.

        Wenn sich ein Client verbindet bekommt der eine Webseite mit der IP 192.168.1.1, URL egal.

        Das Formular zeigt *keine* gespeicherten Daten an. Sicherheit und piepapoundso.

        Nach dem Speichern wird gebootet ind den Modus ohne Accesspoint.

    ++ display

    optionale Elemente:

    ++ uselcdledcontrol
        Kontrolliert die Helligkeit des LC-Displays.

        Standard ist das LiquidCrystal_I2C-Verfahren mit .backlight();

        Hier zusätzlich kann ein PWM auf die LCD-Leitung gelegt werden. Die notwendige Software wird über
        define uselcdledcontrol bereitgestellt.

        Hardware-setup
        
        Weg 1: ohne Eingriff 
          - Kabel geht von GPIO15 zum links oberen Pin des LED-Jumpers auf dem
            PCF8574-Board. Wenn man den anderen Pin nimmt, stirbt wohl der IO-Port,
            weil da liegen 5V...
          - Leider maximal etwas dunkeler, weil Vgpio=Vcc vom ESP8266 nur 3V3 statt 5V mit dem Jumper.

        Weg 2: mit Eingriff
          Wir bauen einen Spannungsteiler an die Basis des Transistors 8050. Weil die Basis wird via 4k7 nach Vcc des
          LCD 5V hochgezogen. Würden wir da direkt rangehen, stürbe der ESP8266 GPIO (kann bis 3V6). Also Spannungsteiler 
          auf ungefähr 3V3. Geht mit 10k (3V4) bzw. 9K (3V3).

                              oDK
                            /
          ----o      3      R7  C1
          ----o    =8050=   R7  C1
                    1  2    R7  C1

          - direkt am R7 geht oben nach rechts eine sehr kurze Leiterbahn zu einer Durchkontaktierung.
          - die Leiterbahn trennen
          - dann an den Widerstand R7 oben einen Widerstand 10k (besser: 9k) nach Ground legen.
            (Wenn man einen bedrahteten Widerstand nimmt, kann man ihn zum IC legen, Ground ist rechts oben.)
          - Kabel an R7-Widerstand anlöten
          - PRÜFEN!!! Liegt nun am Kabel eine Spannung um 3V3 an? Ja: Gut. Nein: Panik!
          - anderes Ende des Kabels geht (wie oben) an GPIO15.
*/

//< < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < <
//< < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < <
//< < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < < <
// Welchen Displaytyp?
#define LCD2004 1
#define Clock303 2
#define LCD12864 3

// LCD2004   com 4
// LCD12864  com 5
// Clock303  com 5

//#define displaymode LCD2004
#define displaymode Clock303
//#define displaymode LCD12864

#define uselcdledcontrol
#if displaymode == Clock303
#undef uselcdledcontrol
#endif
#if displaymode == LCD12864
#undef uselcdledcontrol
#endif

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <TZ.h>
#include <sntp.h>             // nonos-sdk
#include <SolarCalculator.h>  // https://github.com/jpb10/SolarCalculator

#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <DNSServer.h>

#if displaymode == LCD12864
#include <st7567sfGK.h>
st7567sfGK display;
#endif

#if displaymode == LCD2004
#include <LiquidCrystal_I2C.h>  // https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
const byte LCDI2CAddr = 0x27;   // !! different LCD adapter have different I2C Addrs!
LiquidCrystal_I2C display(LCDI2CAddr, 20, 4);
#endif

struct geolocation_t {  // Braunschweig.
  double latitude = 52.2646577;
  double longitude = 10.5236066;
} geolocation;

String timezone = "";  // das wird darein kopiert bzw. geladen und genutzt!

struct accesspointdata_t {
  IPAddress ip = IPAddress(192, 168, 1, 1);
  IPAddress gateway = IPAddress(192, 168, 1, 1);  // same as ip!
  IPAddress subnet = IPAddress(255, 255, 255, 0);
  String ssid = "ClockfGK";
  const String password = "";
} accesspoint;


#if displaymode == LCD2004
const byte PinSDA = 4;
const byte PinSCL = 5;
#endif
#if displaymode == Clock303
const byte PinSDA = 13;
const byte PinSCL = 12;
#endif
#if displaymode == LCD12864
const byte PinSDA = 4;
const byte PinSCL = 5;
#endif

const byte PinBlinkLED = 2;
const int EEPromMaxSize = 512;

//********************************************************************************************************************************
ESP8266WiFiMulti wifiMulti;

enum runmode_t { undefined,
                 runasstation,
                 runasaccesspoint };
runmode_t runmode = undefined;

//********************************************************************************************************************************
void setup() {
  delay(5000);
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  delay(5000);

  Serial.print(F("\n\nClock for Generation Klick "));
  Serial.print(__DATE__);
  Serial.print(F(" "));
  Serial.print(__TIME__);
#if (displaymode == LCD2004)
  Serial.print(F(" LCD2004 Mode"));
#endif
#if (displaymode == Clock303)
  Serial.print(F(" Clock303 Mode"));
#endif
#if (displaymode == LCD12864)
  Serial.print(F(" st7567s 128x64 Mode"));
#endif
  Serial.println();

  // Serial.setDebugOutput(true);

  pinMode(PinBlinkLED, OUTPUT);
  digitalWrite(PinBlinkLED, HIGH);

  // i2c Bus bzw. die Geräte in einen definierten Zustand versetzen
  I2C_ClearBus(PinSDA, PinSCL);

  // i2c
  Wire.begin(PinSDA, PinSCL, 400000);
  // Aufruf des Displayverteilers
  setupDisplay();

  timezone = String(FPSTR(TZ_Europe_Berlin));

  EEPROM.begin(EEPromMaxSize);
  LadeKonfiguationAusEEPROM();

  // install a callback that is called when sntp sets the clock via a ntp call to pool.ntp.org
  settimeofday_cb(time_is_set);
  // alles, um das mit der uhrzeit zu tun
  configTime(timezone.c_str(), "pool.ntp.org");

  //ESP8266WiFiMulti int count() { return _APlist.size(); }

  Serial.print("known Accesspoints: ");
  Serial.print(wifiMulti.count());
  Serial.println();

  // hier die Startup-Logik
  startuplogik();
}

//********************************************************************************************************************************
void startuplogik() {  // teil 1, anderer teil ist in loopAsAccesspoint()
  enum rst_reason {
    REASON_DEFAULT_RST = 0,      /* normal startup by power on */
    REASON_WDT_RST = 1,          /* hardware watch dog reset */
    REASON_EXCEPTION_RST = 2,    /* exception reset, GPIO status won’t change */
    REASON_SOFT_WDT_RST = 3,     /* software watch dog reset, GPIO status won’t change */
    REASON_SOFT_RESTART = 4,     /* software restart ,system_restart , GPIO status won’t change */
    REASON_DEEP_SLEEP_AWAKE = 5, /* wake up from deep-sleep */
    REASON_EXT_SYS_RST = 6       /* external system reset */
  };

  const rst_info *resetInfo = ESP.getResetInfoPtr();  // Resetgrund einlesen
  /*
      Nach flash: 6
      nach ESP.restart(): 4

  */
  /**/
  Serial.print("Resetreason: ");
  Serial.print(resetInfo->reason);
  Serial.println();
  /**/

  byte startmode = 0;
  ESP.rtcUserMemoryRead(0, (uint32_t *)&startmode, sizeof(startmode));

  // wir haben keinen Accesspoint in der Konfiguration, also sinnlos zu versuchen als Station zu starten
  if (wifiMulti.count() == 0) {
    Serial.println("No acccespoints in config. Can not start as station. Force AP-Mode.");
    startmode = 12;
  }

  Serial.print("Startmode: ");
  Serial.println(startmode);
  delay(500);
  displaystartupmode(startmode);

  /*
     startmode 
        1   Station
        x   Acccesspoint
  */


  if (startmode != 1) {
    runmode = runasaccesspoint;
    setupwifiAccesspoint();
    displayIP(startmode);
  } else {
    displayapwaitmessage(-3);
    runmode = runasstation;
    setupwifiStation();
    // hier gibt es noch keine IP
    // displayIP(startmode);

    /**/
    // für den nächsten Reset vorbereiten, irgendwas ungleich 1
    startmode = 32;
    ESP.rtcUserMemoryWrite(0, (uint32_t *)&startmode, sizeof(startmode));
    /**/
  }
}

//********************************************************************************************************************************
bool gotsntptime = false;
void time_is_set(bool from_sntp) {
  if (from_sntp) {
    /** /  // for debug 
    gotsntptime = true;
    /**/
    Serial.println("Timeset from sntp");
  } else {
    Serial.println("Timeset from elsewhere");
  }
}

//********************************************************************************************************************************
bool usewifi = false;
void WiFiManagement(bool turnon) {
  static WiFiMode current = (WiFiMode)15;  // because there is no undef value...

  if ((turnon) && (current != WIFI_STA)) {
    WiFi.mode(WIFI_STA);
    current = WIFI_STA;
    Serial.println("Wifi: on");
  } else {
    if ((!turnon) && (current != WIFI_OFF)) {
      WiFi.mode(WIFI_OFF);
      current = WIFI_OFF;
      Serial.println("Wifi: off");
    }
  }

  usewifi = turnon;
}

//********************************************************************************************************************************
void ZeitManagement() {
  // für den Ticker...
  static uint32_t clockticker = 0;
  const uint32_t clocktime = 15000;

  // Taskmgr.
  if (millis() - clockticker < clocktime) {
    return;
  }
  clockticker = millis();

  static byte stunde = 255;
  static byte minute = 0;
  static bool wifiswitch = false;
  const byte hourmodul = 3;
  const byte hourdelta = 0;  // wifi-check is at 0, hourmodul, hourmodul*2, ... + hourdelta
  static int hourcheck = -1;

  time_t now = time(nullptr);
  tm *lt = localtime(&now);

  // Zeit-Daten via Netz erhalten?
  if (lt->tm_year < 100) {
    WiFiManagement(true);
    //displayError();
    return;
  } else {
    // ja
    stunde = lt->tm_hour;
    minute = lt->tm_min;

    //State-Engines sind die Lösung aller Probleme
    enum wifistate_t { fetch,
                       wait4sntptime1,
                       wait4nextsync };
    static wifistate_t wifistate = fetch;

    /** /
    Serial.print("gotsntptime: ");
    Serial.print(gotsntptime);
    Serial.print(" wifistate: ");
    Serial.print(wifistate);
    Serial.println();
    /**/

    switch (wifistate) {
      case fetch:
        {
          WiFiManagement(true);
          wifistate = wait4sntptime1;
          break;
        }
      case wait4sntptime1:
        {
          if (gotsntptime) {
            WiFiManagement(false);
            hourcheck = stunde;
            wifistate = wait4nextsync;
            gotsntptime = false;
          }
          break;
        }
      case wait4nextsync:
        {
          if ((stunde % hourmodul == hourdelta) && (hourcheck != stunde)) {
            wifistate = fetch;
          }
          break;
        }
    }
  }

  // Aufruf des Zeitanzeigeverteilers
  displayTime(now);
}

//********************************************************************************************************************************
void FlashLed() {
  static uint32_t ledticker = 0;
  const int flashon = 50;
  const uint32_t flashtime = 1000l * 10l;
  static int flash = flashon;

  if (millis() - ledticker > flash) {
    ledticker = millis();
    if (!digitalRead(PinBlinkLED)) {
      flash = flashtime - flashon;
    } else {
      flash = flashon;
    }
    digitalWrite(PinBlinkLED, !digitalRead(PinBlinkLED));
  }
}

//********************************************************************************************************************************
void WifiMonitor() {
  // Wifi-Verbindung
  static uint32_t wifiticker = 0;
  const uint32_t connectTimeoutMs = 5000;

  //--------------------------
  if (millis() - wifiticker > 1000) {
    wifiticker = millis();
    if (usewifi) {
      if (WiFi.status() != WL_CONNECTED) {
        if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) {
          Serial.print("WiFi connected: ");
          Serial.print(WiFi.SSID());
          Serial.print(" ");
          Serial.println(WiFi.localIP());
        } else {
          Serial.println("WiFi not connected!");
        }
      }
    }
  }
}

//********************************************************************************************************************************
void loop() {
  if (runmode == runasstation) {
    loopAsStation();
  }
  if (runmode == runasaccesspoint) {
    loopAsAccesspoint();
  }
  // fancy, fancy, bling bling
  FlashLed();
  // Lets wait some time...
  delay(1);
}

//