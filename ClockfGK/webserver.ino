
// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html

//*********************************************************************************************************************
const byte dataformat = 15;
const byte startidx = 10;
const byte dataformatxor = 0xbe;

//*********************************************************************************************************************
int writestring(int idx, String s) {
  EEPROM.write(idx++, s.length());

  for (int i = 0; i < s.length(); i++) {
    EEPROM.write(idx++, s[i]);
  }

  if (idx >= EEPromMaxSize) {
    Serial.println("Panic: EEPROM idx out of bounds");
  }

  return idx;
}

//*********************************************************************************************************************
String readstring(int& idx) {
  int len = EEPROM.read(idx++);
  String s = "";

  for (int i = 0; i < len; i++) {
    s = s + char(EEPROM.read(idx++));
  }

  if (idx >= EEPromMaxSize) {
    Serial.println("Panic: EEPROM idx out of bounds");
  }

  return s;
}

//*********************************************************************************************************************
bool LadeKonfiguationAusEEPROM() {
  // Versionsnummer prüfen und halbwegs sicherstellen, dass es nicht ein zufälliges EEPROM-Muster ist
  if ((EEPROM.read(0) == dataformat) && (EEPROM.read(1) == (dataformat ^ dataformatxor))) {
    int idx = startidx;

    for (byte i = 0; i < 2; i++) {
      wifiMulti.addAP(readstring(idx).c_str(), readstring(idx).c_str());
    }

    timezone = readstring(idx);
    geolocation.latitude = readstring(idx).toFloat();
    geolocation.longitude = readstring(idx).toFloat();

    Serial.println(timezone);
    Serial.println(geolocation.latitude);
    Serial.println(geolocation.longitude);

    return true;
  } else {
    return false;
  }
}

//*********************************************************************************************************************
//*********************************************************************************************************************
const byte dnsport = 53;

ESP8266WebServer* webserver = NULL;
DNSServer* dnsserver = NULL;

//*********************************************************************************************************************
/*
  webserver->send(200, "text/html",
                  R"==x==(
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>LCDClock Wifi Konfiguration</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta charset="UTF-8">
  </head>
  <body>
        <h1>Welcome to My Website</h1>  
  </body>
</html>
  )==x==");
}
*/

//*********************************************************************************************************************
void formpage() {  // ins Flash!
  webserver->send(200, F("text/html"), webpage);
}

//*********************************************************************************************************************
void timezonehtml() {  // ins Flash!
  webserver->send(200, F("text/html"), webpagetimezone);
}

//*********************************************************************************************************************
void rebootlink() {
  ESP.restart();  // reset() or .restart();
}

//*********************************************************************************************************************
void formularreaktion() {
  if (webserver->method() == HTTP_POST) {
    /** /
    for (uint8_t i = 0; i < webserver->args(); i++) {
      Serial.print("Arg: ");
      Serial.print(webserver->argName(i));
      Serial.print(" Value: ");
      Serial.print(webserver->arg(i));
      Serial.println();
    }
    /**/
    int idx = startidx;
    idx = writestring(idx, webserver->arg("ssid1"));
    idx = writestring(idx, webserver->arg("ssid1pwd"));
    idx = writestring(idx, webserver->arg("ssid2"));
    idx = writestring(idx, webserver->arg("ssid2pwd"));
    idx = writestring(idx, webserver->arg("timezone"));
    idx = writestring(idx, webserver->arg("latitude"));
    idx = writestring(idx, webserver->arg("longitude"));

    EEPROM.write(0, dataformat);
    EEPROM.write(1, dataformat ^ dataformatxor);

    EEPROM.commit();

    webserver->send(200, F("text/plain"), "ok, " + String(idx) + " bytes saved.");
    delay(2000);
    ESP.restart();
  }
}

//*********************************************************************************************************************
void setupServers() {
  dnsserver = new DNSServer();
  dnsserver->setErrorReplyCode(DNSReplyCode::NoError);
  dnsserver->start(dnsport, "*", accesspoint.ip);

  webserver = new ESP8266WebServer(80);
  webserver->onNotFound(formpage);
  webserver->on("/", formpage);
  webserver->on("/reboot.html", rebootlink);
  webserver->on("/timezone.html", timezonehtml);
  webserver->on("/speichern", formularreaktion);

  webserver->begin();
}

//*********************************************************************************************************************
void setupwifiStation() {
  // wifimulti example copy/paste
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  setupServers();
}

//*********************************************************************************************************************
void setupwifiAccesspoint() {
  // Die letzten 4 Stellen der MAC anhängen
  String mac = WiFi.macAddress();
  mac.replace(":", "");
  mac.remove(0,8);
  accesspoint.ssid += mac;


  // https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
  WiFi.mode(WIFI_AP);
  WiFi.persistent(false);
  WiFi.softAP(accesspoint.ssid, accesspoint.password);
  WiFi.softAPConfig(accesspoint.ip, accesspoint.gateway, accesspoint.subnet);

  delay(500);
  Serial.print("AP SSID: ");
  Serial.print(accesspoint.ssid);
  Serial.print(" IP address: ");
  Serial.print(WiFi.softAPIP());
  Serial.println();

  setupServers();
}


//