// move out of stack....
const int maxresults = 500;
String list[maxresults][2];  // adjust as needed
String Tzlist = "";

//***************************************************************************************************************
void tzreverse() {
  Tzlist = Tzlistbase;

  /*
  for (int i = 0; i < 200; i++) {
    Serial.print(Tzlist[i], HEX);
    Serial.print(" ");
    if (i % 16 == 0) {
      Serial.println();
    }
  }

  Serial.println(Tzlist.length());
*/

  //Init.
  for (int i = 0; i < maxresults; i++) {
    for (int j = 0; j < 2; j++) {
      list[i][j] = "";
    }
  }

  int idx = 0;
  int linecount = 0;

  while (Tzlist != "") {
    int i = Tzlist.indexOf('\n');
    if (i >= 0) {
      if (i > 0) {
        String line = Tzlist.substring(0, i);
        linecount++;

        int ii = line.indexOf("\",\"");
        if (ii > 0) {
          String tz = line.substring(1, ii);
          String tzstr = line.substring(ii + 3, line.length() - 1);
          Serial.print("\"");
          Serial.print(tz);
          Serial.print("\",\"");
          Serial.print(tzstr);
          Serial.print("\"");
          Serial.println();

          // Search in Result list
          int r = 0;
          while ((r < maxresults) &&         // klein listenende
                 (list[r][0] != tzstr) &&    // String nicht gefunden
                 (                           //
                   (list[r][1] != "") ||     //
                   (list[r][1].length() > 80)  // Zeile nicht zu lang
                   )                         //
          ) {
            r++;
          }
          Serial.print(r);
          Serial.println();
          list[r][0] = tzstr;
          if (list[r][1] == "") {
            list[r][1] = tz;
          } else {
            list[r][1] = list[r][1] + ", " + tz;
          }
        }
      }
      Tzlist.remove(0, i + 1);

    } else {
      Tzlist = "";
    }
  }

  Serial.println("\n\n\n\n\n<table>");
  // Output result
  for (int i = 0; i < maxresults; i++) {
    if (list[i][0] != "") {
      Serial.print("<tr><td>");
      Serial.print(list[i][0]);
      Serial.print("</td><td>");
      Serial.print(list[i][1]);
      Serial.print("</td></tr>");
      Serial.println();
    }
  }
  Serial.println("</table>\n\n\n\n\n\n\ndone.");
  Serial.println(linecount);
}
