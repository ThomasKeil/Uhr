#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>


// #include "Utils.h"
#include "Time.h"
#include "config.h"

#define NTPSERVER "ptbtime2.ptb.de"

// ernie wlan/ntp
#if WIFI
  bool wifi_wlan = true;
  bool wlanreset = false;
  #include <TimeLib.h>
  #include <NtpClientLib.h>
  #include <ESP8266WiFi.h>
  #include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
  #include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
  #include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
  #include <ESP8266mDNS.h>


  #define ONBOARDLED 2 // Built in LED on ESP-12/ESP-07

  WiFiManager wifiManager;

  int8_t timeZone = 1;
  int8_t minutesTimeZone = 0;
  bool wifiFirstConnected = false;
  #if WEBSERVER
    ESP8266WebServer server(80);
  #endif
#else
  bool wifi_wlan = false;
#endif

#include "clockutils.h"
#include "schnapszahlen.h"
#include "datecalculations.h"
#include "displayinfos.h"
#include "handleinput.h"

time_t time;
unsigned int next_update = millis();
int time_is_present = 0;

struct datum hochzeitstag;

char wifiip[16] = "keine ip";
int seconds = 0;


SoftwareSerial ESPserial(GPS_PIN_RX, GPS_PIN_TX); // RX | TX
TinyGPSPlus gps;

const char *clckst[] {
  [CLOCK_STRING_YEAR_SINGLULAR] = "Jahr",
  [CLOCK_STRING_YEAR_PLURAL] = "Jahre",
  [CLOCK_STRING_MONTH_SINGLULAR] = "Monat",
  [CLOCK_STRING_MONTH_PLURAL] = "Monate",
  [CLOCK_STRING_DAY_SINGLULAR] = "Tag",
  [CLOCK_STRING_DAY_PLURAL] = "Tage",
  [CLOCK_STRING_HOUR_SINGULAR] = "Stunde",
  [CLOCK_STRING_HOUR_PLURAL] = "Stunden"
};

#if WIFI
  #if WEBSERVER
   void handleRoot() {
      server.send(200, "text/html", "<h2>Hochzeitsuhr</h2><br><a href=\"/action?ip=1\">ip anzeigen</a><br>\
        <a href=\"action?cleardisplay=1\">Display l&ouml;schen</a><br>\
        <a href=\"action?drawverheiratetseit=1\">Verheiratet seit auf Display</a><br>\
        <a href=\"action?currenttime=1\">Aktuelle Zeit</a><br>\
        ");
    }

   void handleAction() {
      static char message[512];
      String test = server.argName(0);
        test.toCharArray(message,test.length()+1);
        handleInput_auswertung(message);
        server.send(200, "text/plain", "hello from esp8266! argv = "+ test);
    }
  #endif

  void onSTAConnected (WiFiEventStationModeConnected ipInfo) {
      Serial.printf ("Connected to %s\r\n", ipInfo.ssid.c_str ());
  }

  // Start NTP only after IP network is connected
  void onSTAGotIP (WiFiEventStationModeGotIP ipInfo) {
      Serial.printf ("Got IP: %s\r\n", ipInfo.ip.toString ().c_str ());
      Serial.printf ("Connected: %s\r\n", WiFi.status () == WL_CONNECTED ? "yes" : "no");
      digitalWrite (ONBOARDLED, HIGH); // Turn off LED
      wifiFirstConnected = true;
  }

  // Manage network disconnection
  void onSTADisconnected (WiFiEventStationModeDisconnected event_info) {
      Serial.printf ("Disconnected from SSID: %s\n", event_info.ssid.c_str ());
      Serial.printf ("Reason: %d\n", event_info.reason);
      digitalWrite (ONBOARDLED, LOW); // Turn on LED
      //NTP.stop(); // NTP sync can be disabled to avoid sync errors
  }

  void processSyncEvent (NTPSyncEvent_t ntpEvent) {
      if (ntpEvent) {
          Serial.print ("Time Sync error: ");
          if (ntpEvent == noResponse)
              Serial.println ("NTP server not reachable");
          else if (ntpEvent == invalidAddress)
              Serial.println ("Invalid NTP server address");
      } else {
          Serial.print ("Got NTP time: ");
          Serial.println (NTP.getTimeDateString (NTP.getLastNTPSync ()));
          time_is_present = 1;
      }
  }

  void configModeCallbackWifiManager (WiFiManager *myWiFiManager) {
    char apname[40];
    myWiFiManager->getConfigPortalSSID().toCharArray(apname,myWiFiManager->getConfigPortalSSID().length()+1);
    char ip[20];
    WiFi.softAPIP().toString().toCharArray(ip,WiFi.softAPIP().toString().length()+1);
    screenCaptivePortal(apname,ip);
  }

  boolean syncEventTriggered = false; // True if a time even has been triggered
  NTPSyncEvent_t ntpEvent; // Last triggered event
#endif // wifi ende

// Send a byte array of UBX protocol to the GPS
void sendUBX(uint8_t *MSG, uint8_t len) {
  for(int i=0; i<len; i++) {
    ESPserial.write(MSG[i]);
  }
}

void setupGPSpower() {
  //Set GPS ot Power Save Mode
  uint8_t setPSM[] = { 0xB5, 0x62, 0x06, 0x11, 0x02, 0x00, 0x08, 0x01, 0x22, 0x92 }; // Setup for Power Save Mode (Default Cyclic 1s)
  sendUBX(setPSM, sizeof(setPSM)/sizeof(uint8_t));
}

void setup(void) {
  Serial.begin(9600);
  ESPserial.begin(9600);
  u8g2.begin();

  hochzeitstag = HOCHZEITSTAG;
#if WIFI
//      WiFi.mode (WIFI_STA);
      wifiManager.setAPCallback(configModeCallbackWifiManager);
//      wifiManager.setTimeout(15);
      wifiManager.autoConnect("Hochzeitsuhr");
      static WiFiEventHandler e1, e2, e3;
      Serial.println("Local IP");
      Serial.println(WiFi.localIP());
      IPAddress ip = WiFi.localIP();
      sprintf(wifiip, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

      screenIPAddress(wifiip);

      pinMode (ONBOARDLED, OUTPUT); // Onboard LED
      digitalWrite (ONBOARDLED, LOW); // Switch on LED

      digitalWrite (ONBOARDLED, HIGH); // Turn off LED
      wifiFirstConnected = true;

      if (MDNS.begin("Hochzeitsuhr")) {
        Serial.println("MDNS responder started");
       }

 #if WEBSERVER
      server.on("/action", handleAction);
      server.on("/", handleRoot);

      server.begin();
 #endif

      NTP.onNTPSyncEvent ([](NTPSyncEvent_t event) {
          ntpEvent = event;
          syncEventTriggered = true;
      });

      e1 = WiFi.onStationModeGotIP (onSTAGotIP);// As soon WiFi is connected, start NTP Client
      e2 = WiFi.onStationModeDisconnected (onSTADisconnected);
      e3 = WiFi.onStationModeConnected (onSTAConnected);

#endif
}

/* draw something on the display with the `firstPage()`/`nextPage()` loop*/
void loop(void) {
#if WIFI

    if (wifiFirstConnected) {
        wifiFirstConnected = false;
        NTP.begin (NTPSERVER, timeZone, true, minutesTimeZone);
        NTP.setInterval (63);
    }

    if (syncEventTriggered) {
        processSyncEvent (ntpEvent);
        syncEventTriggered = false;
    }


    #if WEBSERVER
      server.handleClient();
    #endif
/*
    static int i = 0;
    static int last = 0;

    if ((millis () - last) > 5100) {
        //Serial.println(millis() - last);
        last = millis ();
        Serial.print (i); Serial.print (" ");
        Serial.print (NTP.getTimeDateString ()); Serial.print (" ");
        Serial.print (NTP.isSummerTime () ? "Summer Time. " : "Winter Time. ");
        Serial.print ("WiFi is ");
        Serial.print (WiFi.isConnected () ? "connected" : "not connected"); Serial.print (". ");
        Serial.print ("Uptime: ");
        Serial.print (NTP.getUptimeString ()); Serial.print (" since ");
        Serial.println (NTP.getTimeDateString (NTP.getFirstSync ()).c_str ());
        i++;
    }
*/
#else // wifi ende
  // time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available

  while (ESPserial.available() > 0) {
    gps.encode(ESPserial.read());
  }

  if (seconds != gps.time.second() && gps.time.isValid() && gps.date.isValid()) {
    seconds = gps.time.second();
    // Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
    // Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
    // Serial.print("ALT=");  Serial.println(gps.altitude.meters());

  //  Serial.print("TIME="); Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32)
    // Serial.print("HOUR="); Serial.println(gps.time.hour()); // Hour (0-23) (u8)
    // Serial.print("MINUTE="); Serial.println(gps.time.minute()); // Minute (0-59) (u8)
    // Serial.print("SECOND="); Serial.println(gps.time.second()); // Second (0-59) (u8)
    //
    if (!time_is_present && seconds > 0) {
      time_is_present = 1;
      setTime(gps.time.hour() + 2, gps.time.minute(),gps.time.second(),gps.date.day(),gps.date.month(),gps.date.year());
      setupGPSpower(); // Lower power consumption
    }
  }
#endif // else ende von wifi

  if (millis() > next_update) {
#if WIFI
    if (wlanreset) {
//      WiFi.disconnect(true);
      wifiManager.resetSettings();
      Serial.println("wlan gelöscht mache ein reset !!!");
      delay(1000);
      ESP.restart();
      delay(1000);
      Serial.println("Reset");
    }
#endif
    if (time_is_present) {
      struct datum today = getNow();
      struct datum next = getNextWeddingDayDate(today, hochzeitstag);
      int count = next.jahr - hochzeitstag.jahr;

      Serial.printf("Next: %i.%i.%i, der %i.\n", next.tag, next.monat, next.jahr, count);

      Serial.printf("Berechne Vergangenes\n");
      struct periode elapsed = calculatePeriode(hochzeitstag, today);

      if (!elapsed.valid) {
        Serial.printf("ERROR: elapsed not valid.\n");
        next_update += REFRESH_OBTAINING_INFO;
        time_is_present = 0;
        return;
      }

      Serial.printf("Berechne kommenden Hochzeitstag.\n");
      struct periode to_come = calculatePeriode(today, next);
      /* if (!to_come.valid) {
        Serial.printf("ERROR: to_come not valid.\n");
        next_update += REFRESH_OBTAINING_INFO;
        return;
      } */

      Serial.printf("Berechnet.\n");
      char description[40];
      char text[40];

      if (day() == hochzeitstag.tag && month() == hochzeitstag.monat)  // Ist gerade Hochzeitstag?
      {
        if (count > 0) {
          Serial.printf("Hochzeitstag %i wird gezeigt.\n", count);
          screenHochzeitstaginfo(count);
        }
      }
      else if(isSpecial(elapsed.stunden_gesamt, 3, 1, description))  // Ist eine Stunden "Schnapszahl" für vergangene Zeit?
      {
        Serial.printf("Schnapszahl vergangene Stunden %i wird gezeigt.\n", elapsed.stunden_gesamt);
        sprintf(text, "Verheiratet %i Stunden.", elapsed.stunden_gesamt);
        screenSchnapszahl(elapsed, text, description);
      }
      else if(to_come.valid && isSpecial(to_come.stunden_gesamt, 3, 1, description)) // Ist eine Stunde "Schnapszahl" für den kommenden Hochzeitstag?
      {
        Serial.printf("Schnapszahl Stunden %i kommender HT wird gezeigt\n", to_come.stunden_gesamt);
        Serial.println(description);
        sprintf(text, "Hochzeitstag in %i Stunden.", to_come.stunden_gesamt);
        screenSchnapszahl(elapsed, text, description);
      }
      else if(to_come.valid && to_come.tage_gesamt <= 7) // Ist der kommende Hochzeitstag innerhalb von 7 Tagen?
      {
        Serial.printf("Nächster Hochzeitstag: der %i.\n",count);
        if (count > 0) { // Am Tag der Hochzeit selbst zeigen wir nicht, das Hochzeitstag ist
          screenUpcomingWeddingDay(elapsed, next, count);
        }
      }
      else if (isSpecial(elapsed.tage_gesamt, 2, 1, description)) // Haben wir eine Schnapszahl mit Tagen der vergangene Zeit?
      {
        Serial.printf("Schnapszahl vergangene Tage %i wird gezeigt.\n", elapsed.tage_gesamt);
        sprintf(text, "Verheiratet %i Tagen.", elapsed.tage_gesamt);
        screenSchnapszahl(elapsed, text, description);
      }
      else if (to_come.valid && isSpecial(to_come.tage_gesamt, 2, 1, description)) // haben wir eine Schnapszahl mit Tagen für den kommenden Hochzeitstag?
      {
        Serial.printf("Schnapszahl Tage %i kommender HT wird gezeigt", to_come.tage_gesamt);
        sprintf(text, "Hochzeitstag in %i Tagen.", to_come.tage_gesamt);
        screenSchnapszahl(elapsed, text, description);
      }
      else // Trifft alles nicht zu, daher default zeigen.
      {
        Serial.printf("Verheitetet seit zeigen\n");
        screenVerheiratetSeit(elapsed);
      }
      next_update += REFRESH_REGULAR;
    } else {
      u8g2.firstPage();
      u8g2.setPowerSave(0); // before drawing, enable charge pump (req. 300ms)
      do {
        drawObtainingTime();
      } while ( u8g2.nextPage() );
      u8g2.setPowerSave(1); // disable charge pump

      next_update += REFRESH_OBTAINING_INFO;
    }

  }

  handleInput();
  //delay(10);

}
