/*
     303WifiLC01-Clock

     https://github.com/holgerlembke/303WIFILC01Uhr

     Hardwaredetails sind von https://github.com/maarten-pennings/303WIFILC01 DANKE, DANKE, DANKE für die Arbeit!

     // ..\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\3.1.2\cores\esp8266

helligkeitskontrolle tag/nacht

     2023-12-25
       ++ done.


now: 1703523481 Y: 123 Time: 1758
now: 1703523541 Y: 123 Time: 1759
Wifi: on
now: 1703523601 Y: 123 Time: 1800
Timeset from sntp
WiFi connected: xxxxx 192.168.yyyy.yyyy
Wifi: off
now: 1703523662 Y: 123 Time: 1801
now: 1703523722 Y: 123 Time: 1802       

*/
#include <Wire.h>
#include <privatedata.h>  // my credential data, https://github.com/holgerlembke/privatedata
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <TZ.h>
#include <sntp.h>  // nonos-sdk

#define MYTZ TZ_Europe_Berlin

const byte PinSDA = 13;
const byte PinSCL = 12;
const byte PinLED = 2;

ESP8266WiFiMulti wifiMulti;

//********************************************************************************************************************************
void setup() {
  delay(5000);
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  delay(5000);
  Serial.println(F("\n\n"));

  Serial.print(F("\n\n303WifiLC01-Clock "));
  Serial.print(__DATE__);
  Serial.print(F(" "));
  Serial.print(__TIME__);
  Serial.println();

  pinMode(PinLED, OUTPUT);
  digitalWrite(PinLED, HIGH);

  // alles, um das mit der uhrzeit zu tun
  configTime(MYTZ, "pool.ntp.org");

  // wifimulti example copy/paste
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(privatedata_mySSID, privatedata_myWAP2);

  Wire.begin(PinSDA, PinSCL);
  displayinit();

  // install a callback that is called when sntp sets the clock via a ntp call to pool.ntp.org
  settimeofday_cb(time_is_set);
}

//********************************************************************************************************************************
bool gotsntptime = false;
void time_is_set(bool from_sntp) {
  if (from_sntp) {
    gotsntptime = true;
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
  static String lasttime = "";
  static bool wifiswitch = false;
  const byte hourmodul = 3;
  const byte hourdelta = 0;  // wifi-check is at 0, hourmodul, hourmodul*2, ... + hourdelta
  static int hourcheck = -1;

  time_t now = time(nullptr);
  tm* lt = localtime(&now);

  // Zeit-Daten via Netz erhalten?
  if (lt->tm_year < 100) {
    WiFiManagement(true);
    displayError();
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

  String s = "";
  s += (stunde < 10) ? "0" + String(stunde) : String(stunde);
  s += (minute < 10) ? "0" + String(minute) : String(minute);

  if (lasttime != s) {
    /**/
    Serial.print(" now: ");
    Serial.print(now);
    Serial.print(" Y: ");
    Serial.print(lt->tm_year);
    Serial.print(" Time: ");
    Serial.print(s);
    Serial.println();
    /**/

    displaystring(s);
    lasttime = s;
  }
}

//********************************************************************************************************************************
void FlashLed() {
  static uint32_t ledticker = 0;
  const int flashon = 50;
  const uint32_t flashtime = 1000l * 10l;
  static int flash = flashon;

  if (millis() - ledticker > flash) {
    ledticker = millis();
    if (!digitalRead(PinLED)) {
      flash = flashtime - flashon;
    } else {
      flash = flashon;
    }
    digitalWrite(PinLED, !digitalRead(PinLED));
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
  WifiMonitor();
  FlashLed();
  ZeitManagement();
}

//