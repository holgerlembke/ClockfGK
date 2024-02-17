/*

    examin clock delta

    esp8266: ca. 5 sekunden/tag


*/

#include <Wire.h>
#include <privatedata.h>  // my credetial data, https://github.com/holgerlembke/privatedata
#include <TZ.h>
#include <sntp.h>  // nonos-sdk
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

const byte PinSDA = 13;
const byte PinSCL = 12;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);


ESP8266WiFiMulti wifiMulti;

//********************************************************************************************************************************
bool gotsntptime = false;
void time_is_set(bool from_sntp) {
  if (from_sntp) {
    gotsntptime = true;
    sntp_stop();
    Serial.println("Timeset from sntp, sntp now stopped.");
  } else {
    Serial.println("Timeset from elsewhere");
  }
}

//********************************************************************************************************************************
void setup() {
  delay(5000);
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  delay(5000);
  Serial.println(F("\n\n"));

  Serial.print(F("\n\nexamin clock delta "));
  Serial.print(__DATE__);
  Serial.print(F(" "));
  Serial.print(__TIME__);
  Serial.println();

  settimeofday_cb(time_is_set);
  configTime(TZ_Etc_GMT, "pool.ntp.org");

  Wire.begin(PinSDA, PinSCL);
  displayinit();

  wifiMulti.addAP(privatedata_mySSID, privatedata_myWAP2);
  timeClient.begin();
}

//********************************************************************************************************************************
void WifiMonitor() {
  // Wifi-Verbindung
  static uint32_t wifiticker = 0;
  const uint32_t connectTimeoutMs = 5000;

  //--------------------------
  if (millis() - wifiticker > 1000) {
    wifiticker = millis();
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

//********************************************************************************************************************************
void loop() {
  WifiMonitor();
  timeClient.update();


  static uint32_t ticker = 0;
  if (millis() - ticker > 1000) {
    time_t now = time(nullptr);

    if (timeClient.isTimeSet()) {
      int delta = timeClient.getEpochTime() - now;
      static int lastdelta = -12;
      if (lastdelta != delta) {
        lastdelta = delta;
        Serial.print(timeClient.getFormattedTime());
        Serial.print(" ");
        Serial.print(delta);
        Serial.println();

        displaystring(String(abs(delta)));
      }
    }
    ticker = millis();
  }
}
