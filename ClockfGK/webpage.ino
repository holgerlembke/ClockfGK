// eigene seite, weil die ide bei der darstellung so ihre probleme hat...


// so kriegt man einen "raw string literal" in den code block
const char webpagetimezone[] PROGMEM = (R"==x==(
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>LCDClock Wifi Konfiguration</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta charset="UTF-8">
  </head>
  <body>
<table>
<tr><td>GMT0</td><td>Africa/Abidjan, Africa/Accra, Africa/Bamako, Africa/Banjul, Africa/Bissau, Africa/Conakry, Africa/Dakar, Africa/Freetown, Africa/Lome, Africa/Monrovia, Africa/Nouakchott, Africa/Ouagadougou, Africa/Sao_Tome, America/Danmarkshavn, Atlantic/Reykjavik, Atlantic/St_Helena, Etc/GMT, Etc/GMT-0, Etc/GMT0, Etc/GMT+0, Etc/Greenwich</td></tr>
<tr><td>EAT-3</td><td>Africa/Addis_Ababa, Africa/Asmara, Africa/Dar_es_Salaam, Africa/Djibouti, Africa/Kampala, Africa/Mogadishu, Africa/Nairobi, Indian/Antananarivo, Indian/Comoro, Indian/Mayotte</td></tr>
<tr><td>CET-1</td><td>Africa/Algiers, Africa/Tunis</td></tr>
<tr><td>WAT-1</td><td>Africa/Bangui, Africa/Brazzaville, Africa/Douala, Africa/Kinshasa, Africa/Lagos, Africa/Libreville, Africa/Luanda, Africa/Malabo, Africa/Ndjamena, Africa/Niamey, Africa/Porto-Novo</td></tr>
<tr><td>CAT-2</td><td>Africa/Blantyre, Africa/Bujumbura, Africa/Gaborone, Africa/Harare, Africa/Juba, Africa/Khartoum, Africa/Kigali, Africa/Lubumbashi, Africa/Lusaka, Africa/Maputo, Africa/Windhoek</td></tr>
<tr><td>EET-2EEST,M4.5.5/0,M10.5.4/24</td><td>Africa/Cairo</td></tr>
<tr><td><+01>-1</td><td>Africa/Casablanca, Africa/El_Aaiun, Etc/GMT-1</td></tr>
<tr><td>CET-1CEST,M3.5.0,M10.5.0/3</td><td>Africa/Ceuta, Arctic/Longyearbyen, Europe/Amsterdam, Europe/Andorra, Europe/Belgrade, Europe/Berlin, Europe/Bratislava, Europe/Brussels, Europe/Budapest, Europe/Busingen, Europe/Copenhagen, Europe/Gibraltar, Europe/Ljubljana, Europe/Luxembourg, Europe/Madrid, Europe/Malta, Europe/Monaco, Europe/Oslo, Europe/Paris, Europe/Podgorica, Europe/Prague, Europe/Rome, Europe/San_Marino, Europe/Sarajevo, Europe/Skopje, Europe/Stockholm, Europe/Tirane, Europe/Vaduz, Europe/Vatican, Europe/Vienna, Europe/Warsaw, Europe/Zagreb, Europe/Zurich</td></tr>
<tr><td>SAST-2</td><td>Africa/Johannesburg, Africa/Maseru, Africa/Mbabane</td></tr>
<tr><td>EET-2</td><td>Africa/Tripoli, Europe/Kaliningrad</td></tr>
<tr><td>HST10HDT,M3.2.0,M11.1.0</td><td>America/Adak</td></tr>
<tr><td>AKST9AKDT,M3.2.0,M11.1.0</td><td>America/Anchorage, America/Juneau, America/Metlakatla, America/Nome, America/Sitka, America/Yakutat</td></tr>
<tr><td>AST4</td><td>America/Anguilla, America/Antigua, America/Aruba, America/Barbados, America/Blanc-Sablon, America/Curacao, America/Dominica, America/Grenada, America/Guadeloupe, America/Kralendijk, America/Lower_Princes, America/Marigot, America/Martinique, America/Montserrat, America/Port_of_Spain, America/Puerto_Rico, America/Santo_Domingo, America/St_Barthelemy, America/St_Kitts, America/St_Lucia, America/St_Thomas, America/St_Vincent, America/Tortola</td></tr>
<tr><td><-03>3</td><td>America/Araguaina, America/Argentina/Buenos_Aires, America/Argentina/Catamarca, America/Argentina/Cordoba, America/Argentina/Jujuy, America/Argentina/La_Rioja, America/Argentina/Mendoza, America/Argentina/Rio_Gallegos, America/Argentina/Salta, America/Argentina/San_Juan, America/Argentina/San_Luis, America/Argentina/Tucuman, America/Argentina/Ushuaia, America/Bahia, America/Belem, America/Cayenne, America/Fortaleza, America/Maceio, America/Montevideo, America/Paramaribo, America/Punta_Arenas, America/Recife, America/Santarem, America/Sao_Paulo, Antarctica/Palmer, Antarctica/Rothera, Atlantic/Stanley, Etc/GMT+3</td></tr>
<tr><td><-04>4<-03>,M10.1.0/0,M3.4.0/0</td><td>America/Asuncion</td></tr>
<tr><td>EST5</td><td>America/Atikokan, America/Cancun, America/Cayman, America/Jamaica, America/Panama</td></tr>
<tr><td>CST6</td><td>America/Bahia_Banderas, America/Belize, America/Chihuahua, America/Costa_Rica, America/El_Salvador, America/Guatemala, America/Managua, America/Merida, America/Mexico_City, America/Monterrey, America/Regina, America/Swift_Current, America/Tegucigalpa</td></tr>
<tr><td><-04>4</td><td>America/Boa_Vista, America/Campo_Grande, America/Caracas, America/Cuiaba, America/Guyana, America/La_Paz, America/Manaus, America/Porto_Velho, Etc/GMT+4</td></tr>
<tr><td><-05>5</td><td>America/Bogota, America/Eirunepe, America/Guayaquil, America/Lima, America/Rio_Branco, Etc/GMT+5</td></tr>
<tr><td>MST7MDT,M3.2.0,M11.1.0</td><td>America/Boise, America/Cambridge_Bay, America/Denver, America/Edmonton, America/Inuvik, America/Yellowknife</td></tr>
<tr><td>CST6CDT,M3.2.0,M11.1.0</td><td>America/Chicago, America/Indiana/Knox, America/Indiana/Tell_City, America/Matamoros, America/Menominee, America/North_Dakota/Beulah, America/North_Dakota/Center, America/North_Dakota/New_Salem, America/Ojinaga, America/Rainy_River, America/Rankin_Inlet, America/Resolute, America/Winnipeg</td></tr>
<tr><td>MST7</td><td>America/Creston, America/Dawson, America/Dawson_Creek, America/Fort_Nelson, America/Hermosillo, America/Mazatlan, America/Phoenix, America/Whitehorse</td></tr>
<tr><td>EST5EDT,M3.2.0,M11.1.0</td><td>America/Detroit, America/Grand_Turk, America/Indiana/Indianapolis, America/Indiana/Marengo, America/Indiana/Petersburg, America/Indiana/Vevay, America/Indiana/Vincennes, America/Indiana/Winamac, America/Iqaluit, America/Kentucky/Louisville, America/Kentucky/Monticello, America/Montreal, America/Nassau, America/New_York, America/Nipigon, America/Pangnirtung, America/Port-au-Prince, America/Thunder_Bay, America/Toronto</td></tr>
<tr><td>AST4ADT,M3.2.0,M11.1.0</td><td>America/Glace_Bay, America/Goose_Bay, America/Halifax, America/Moncton, America/Thule, Atlantic/Bermuda</td></tr>
<tr><td><-02>2<-01>,M3.5.0/-1,M10.5.0/0</td><td>America/Godthab, America/Nuuk</td></tr>
<tr><td>CST5CDT,M3.2.0/0,M11.1.0/1</td><td>America/Havana</td></tr>
<tr><td>PST8PDT,M3.2.0,M11.1.0</td><td>America/Los_Angeles, America/Tijuana, America/Vancouver</td></tr>
<tr><td><-03>3<-02>,M3.2.0,M11.1.0</td><td>America/Miquelon</td></tr>
<tr><td><-02>2</td><td>America/Noronha, Atlantic/South_Georgia, Etc/GMT+2</td></tr>
<tr><td><-04>4<-03>,M9.1.6/24,M4.1.6/24</td><td>America/Santiago</td></tr>
<tr><td><-01>1<+00>,M3.5.0/0,M10.5.0/1</td><td>America/Scoresbysund, Atlantic/Azores</td></tr>
<tr><td>NST3:30NDT,M3.2.0,M11.1.0</td><td>America/St_Johns</td></tr>
<tr><td><+11>-11</td><td>Antarctica/Casey, Asia/Magadan, Asia/Sakhalin, Asia/Srednekolymsk, Pacific/Bougainville, Pacific/Efate, Pacific/Guadalcanal, Pacific/Kosrae, Pacific/Noumea, Pacific/Pohnpei, Etc/GMT-11</td></tr>
<tr><td><+07>-7</td><td>Antarctica/Davis, Asia/Bangkok, Asia/Barnaul, Asia/Ho_Chi_Minh, Asia/Hovd, Asia/Krasnoyarsk, Asia/Novokuznetsk, Asia/Novosibirsk, Asia/Phnom_Penh, Asia/Tomsk, Asia/Vientiane, Indian/Christmas, Etc/GMT-7</td></tr>
<tr><td><+10>-10</td><td>Antarctica/DumontDUrville, Asia/Ust-Nera, Asia/Vladivostok, Pacific/Chuuk, Pacific/Port_Moresby, Etc/GMT-10</td></tr>
<tr><td>AEST-10AEDT,M10.1.0,M4.1.0/3</td><td>Antarctica/Macquarie, Australia/Currie, Australia/Hobart, Australia/Melbourne, Australia/Sydney</td></tr>
<tr><td><+05>-5</td><td>Antarctica/Mawson, Asia/Aqtau, Asia/Aqtobe, Asia/Ashgabat, Asia/Atyrau, Asia/Dushanbe, Asia/Oral, Asia/Qyzylorda, Asia/Samarkand, Asia/Tashkent, Asia/Yekaterinburg, Indian/Kerguelen, Indian/Maldives, Etc/GMT-5</td></tr>
<tr><td>NZST-12NZDT,M9.5.0,M4.1.0/3</td><td>Antarctica/McMurdo, Pacific/Auckland</td></tr>
<tr><td><+03>-3</td><td>Antarctica/Syowa, Asia/Aden, Asia/Amman, Asia/Baghdad, Asia/Bahrain, Asia/Damascus, Asia/Kuwait, Asia/Qatar, Asia/Riyadh, Europe/Istanbul, Europe/Minsk, Etc/GMT-3</td></tr>
<tr><td><+00>0<+02>-2,M3.5.0/1,M10.5.0/3</td><td>Antarctica/Troll</td></tr>
<tr><td><+06>-6</td><td>Antarctica/Vostok, Asia/Almaty, Asia/Bishkek, Asia/Dhaka, Asia/Omsk, Asia/Thimphu, Asia/Urumqi, Indian/Chagos, Etc/GMT-6</td></tr>
<tr><td><+12>-12</td><td>Asia/Anadyr, Asia/Kamchatka, Pacific/Fiji, Pacific/Funafuti, Pacific/Kwajalein, Pacific/Majuro, Pacific/Nauru, Pacific/Tarawa, Pacific/Wake, Pacific/Wallis, Etc/GMT-12</td></tr>
<tr><td><+04>-4</td><td>Asia/Baku, Asia/Dubai, Asia/Muscat, Asia/Tbilisi, Asia/Yerevan, Europe/Astrakhan, Europe/Samara, Europe/Saratov, Europe/Ulyanovsk, Indian/Mahe, Indian/Mauritius, Indian/Reunion, Etc/GMT-4</td></tr>
<tr><td>EET-2EEST,M3.5.0/0,M10.5.0/0</td><td>Asia/Beirut</td></tr>
<tr><td><+08>-8</td><td>Asia/Brunei, Asia/Choibalsan, Asia/Irkutsk, Asia/Kuala_Lumpur, Asia/Kuching, Asia/Singapore, Asia/Ulaanbaatar, Etc/GMT-8</td></tr>
<tr><td><+09>-9</td><td>Asia/Chita, Asia/Dili, Asia/Khandyga, Asia/Yakutsk, Pacific/Palau, Etc/GMT-9</td></tr>
<tr><td><+0530>-5:30</td><td>Asia/Colombo</td></tr>
<tr><td>EET-2EEST,M3.5.0/3,M10.5.0/4</td><td>Asia/Famagusta, Asia/Nicosia, Europe/Athens, Europe/Bucharest, Europe/Helsinki, Europe/Kiev, Europe/Mariehamn, Europe/Riga, Europe/Sofia, Europe/Tallinn, Europe/Uzhgorod, Europe/Vilnius, Europe/Zaporozhye</td></tr>
<tr><td>EET-2EEST,M3.4.4/50,M10.4.4/50</td><td>Asia/Gaza, Asia/Hebron</td></tr>
<tr><td>HKT-8</td><td>Asia/Hong_Kong</td></tr>
<tr><td>WIB-7</td><td>Asia/Jakarta, Asia/Pontianak</td></tr>
<tr><td>WIT-9</td><td>Asia/Jayapura</td></tr>
<tr><td>IST-2IDT,M3.4.4/26,M10.5.0</td><td>Asia/Jerusalem</td></tr>
<tr><td><+0430>-4:30</td><td>Asia/Kabul</td></tr>
<tr><td>PKT-5</td><td>Asia/Karachi</td></tr>
<tr><td><+0545>-5:45</td><td>Asia/Kathmandu</td></tr>
<tr><td>IST-5:30</td><td>Asia/Kolkata</td></tr>
<tr><td>CST-8</td><td>Asia/Macau, Asia/Shanghai, Asia/Taipei</td></tr>
<tr><td>WITA-8</td><td>Asia/Makassar</td></tr>
<tr><td>PST-8</td><td>Asia/Manila</td></tr>
<tr><td>KST-9</td><td>Asia/Pyongyang, Asia/Seoul</td></tr>
<tr><td><+0330>-3:30</td><td>Asia/Tehran</td></tr>
<tr><td>JST-9</td><td>Asia/Tokyo</td></tr>
<tr><td><+0630>-6:30</td><td>Asia/Yangon, Indian/Cocos</td></tr>
<tr><td>WET0WEST,M3.5.0/1,M10.5.0</td><td>Atlantic/Canary, Atlantic/Faroe, Atlantic/Madeira, Europe/Lisbon</td></tr>
<tr><td><-01>1</td><td>Atlantic/Cape_Verde, Etc/GMT+1</td></tr>
<tr><td>ACST-9:30ACDT,M10.1.0,M4.1.0/3</td><td>Australia/Adelaide, Australia/Broken_Hill</td></tr>
<tr><td>AEST-10</td><td>Australia/Brisbane, Australia/Lindeman</td></tr>
<tr><td>ACST-9:30</td><td>Australia/Darwin</td></tr>
<tr><td><+0845>-8:45</td><td>Australia/Eucla</td></tr>
<tr><td><+1030>-10:30<+11>-11,M10.1.0,M4.1.0</td><td>Australia/Lord_Howe</td></tr>
<tr><td>AWST-8</td><td>Australia/Perth</td></tr>
<tr><td>EET-2EEST,M3.5.0,M10.5.0/3</td><td>Europe/Chisinau</td></tr>
<tr><td>IST-1GMT0,M10.5.0,M3.5.0/1</td><td>Europe/Dublin</td></tr>
<tr><td>GMT0BST,M3.5.0/1,M10.5.0</td><td>Europe/Guernsey, Europe/Isle_of_Man, Europe/Jersey, Europe/London</td></tr>
<tr><td>MSK-3</td><td>Europe/Kirov, Europe/Moscow, Europe/Simferopol, Europe/Volgograd</td></tr>
<tr><td><+13>-13</td><td>Pacific/Apia, Pacific/Enderbury, Pacific/Fakaofo, Pacific/Tongatapu, Etc/GMT-13</td></tr>
<tr><td><+1245>-12:45<+1345>,M9.5.0/2:45,M4.1.0/3:45</td><td>Pacific/Chatham</td></tr>
<tr><td><-06>6<-05>,M9.1.6/22,M4.1.6/22</td><td>Pacific/Easter</td></tr>
<tr><td><-06>6</td><td>Pacific/Galapagos, Etc/GMT+6</td></tr>
<tr><td><-09>9</td><td>Pacific/Gambier, Etc/GMT+9</td></tr>
<tr><td>ChST-10</td><td>Pacific/Guam, Pacific/Saipan</td></tr>
<tr><td>HST10</td><td>Pacific/Honolulu</td></tr>
<tr><td><+14>-14</td><td>Pacific/Kiritimati, Etc/GMT-14</td></tr>
<tr><td><-0930>9:30</td><td>Pacific/Marquesas</td></tr>
<tr><td>SST11</td><td>Pacific/Midway, Pacific/Pago_Pago</td></tr>
<tr><td><-11>11</td><td>Pacific/Niue, Etc/GMT+11</td></tr>
<tr><td><+11>-11<+12>,M10.1.0,M4.1.0/3</td><td>Pacific/Norfolk</td></tr>
<tr><td><-08>8</td><td>Pacific/Pitcairn, Etc/GMT+8</td></tr>
<tr><td><-10>10</td><td>Pacific/Rarotonga, Pacific/Tahiti, Etc/GMT+10</td></tr>
<tr><td><+02>-2</td><td>Etc/GMT-2</td></tr>
<tr><td><-07>7</td><td>Etc/GMT+7</td></tr>
<tr><td><-12>12</td><td>Etc/GMT+12</td></tr>
<tr><td>UTC0</td><td>Etc/UCT, Etc/UTC, Etc/Universal, Etc/Zulu</td></tr>
</table>
  </body>
</html>
  )==x==");


// so kriegt man einen "raw string literal" in den code block
const char webpage[] PROGMEM = (R"==x==(
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>LCDClock Wifi Konfiguration</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta charset="UTF-8">
  </head>
  <body>
    <form action="/speichern" method="post">
      <label for="ssid1">SSID 1:</label><br>
      <input type="text" id="ssid1" name="ssid1"><br>
      <label for="ssid1pwd">Passwort 1:</label><br>
      <input type="text" id="ssid1pwd" name="ssid1pwd"><br>
      <br>
      <label for="ssid2">optional SSID 2:</label><br>
      <input type="text" id="ssid2" name="ssid2"><br>
      <label for="ssid2pwd">Passwort 2:</label><br>
      <input type="text" id="ssid2pwd" name="ssid2pwd"><br>
      <br>
      <label for="timezone">Timezone:</label><br>
      <input type="text" id="timezone" name="timezone"><a href="/timezone.html">Timezone List</a><br>
      <br>
      <label for="latitude">Latitude:</label><br>
      <input type="text" id="latitude" name="latitude"><br>
      <label for="longitude">Longitude:</label><br>
      <input type="text" id="longitude" name="longitude"><br>
      Latitude and Longitude noted as floating point number.<br>
      Like 52.2646577 10.5236066 for Braunschweig.<br>     
      <br>
      <input type="submit" value="Speichern und neu Starten">
    </form> 
    <br>
    <br>
    <a href="/reboot.html">Reboot without change.</a>
  </body>
</html>
  )==x==");


  //