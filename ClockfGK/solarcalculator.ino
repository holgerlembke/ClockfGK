#if displaymode == LCD2004

//*********************************************************************************************************************
void hmtoString(double timepnt, int &hr, int &mn) {
  int m = timepnt * 60.0 + 0.5;
  hr = (m / 60) % 24;
  mn = m % 60;
}

//*********************************************************************************************************************
void holeNaechstenSonnenAufgangUntergang(time_t now, byte &hour, byte &minute, bool &istsonnenaufgang) {

  double transitheute, sunriseheute, sunsetheute, transitmorgen, sunrisemorgen, sunsetmorgen;

  // die funktionen zeigen auf einen statischen buffer, also muss der wert vor dem nächsten aufruf gesichtert werden
  tm *gt = gmtime(&now);
  int gth = gt->tm_hour;
  tm *lt = localtime(&now);
  int lth = lt->tm_hour;
  int timezone = (lth - gth);
  if (timezone < 0) {
    timezone += 24;
  }

  // Calculate the times of sunrise, transit, and sunset, in hours (UTC)
  calcSunriseSunset(lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
                    geolocation.latitude, geolocation.longitude,
                    transitheute, sunriseheute, sunsetheute);

  // das ist wahrscheinlich alles viel zu umständlich gemacht....

  int srh, srm, ssh, ssm;
  hmtoString(sunriseheute + timezone, srh, srm);
  hmtoString(sunsetheute + timezone, ssh, ssm);

  int lttp = lt->tm_hour * 60 + lt->tm_min;
  int srtp = srh * 60 + srm;
  int sstp = ssh * 60 + ssm;

  if ((lttp > srtp) && (lttp <= sstp)) {  // zwischen Sonnenaufgang und -untergang: untergang anzeigen
    hour = ssh;
    minute = ssm;
    istsonnenaufgang = false;
  } else {
    // Ok, das kann der Sonnenaufgang von heute sein oder der von morgen...
    if (lttp > sstp) {  // ok, für morgen, berechnen wird den ganzen kram noch mal...
      now += 24 * 60 * 60;
      tm *lt = localtime(&now);
      calcSunriseSunset(lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
                        geolocation.latitude, geolocation.longitude,
                        transitheute, sunriseheute, sunsetheute);
      hmtoString(sunriseheute + timezone, srh, srm);
      hour = srh;
      minute = srm;
    } else {
      hour = srh;
      minute = srm;
    }
    istsonnenaufgang = true;
  }

  /** /
  Serial.print("TZ: ");
  Serial.print(timezone);
  Serial.print(" Srh: ");
  Serial.print(srh);
  Serial.print(" Srm: ");
  Serial.print(srm);
  Serial.print(" Ssh: ");
  Serial.print(ssh);
  Serial.print(" Ssm: ");
  Serial.print(ssm);
  Serial.print(" hour: ");
  Serial.print(hour);
  Serial.print(" minute: ");
  Serial.print(minute);
  Serial.print(" istsonnenaufgang: ");
  Serial.print(istsonnenaufgang);
  Serial.println();
  /**/
}

#endif