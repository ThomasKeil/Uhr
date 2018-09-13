#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>


// #include "Utils.h"
#include "Time.h"
#include "WifiConfig.h"


#define WIFI true

#ifndef WIFI_CONFIG_H
  #define YOUR_WIFI_SSID "YOUR_WIFI_SSID"
  #define YOUR_WIFI_PASSWD "YOUR_WIFI_PASSWD"
#endif // !WIFI_CONFIG_H

#define NTPSERVER "pool.ntp.org"

// ernie wlan/ntp
#if WIFI
  bool wifi_wlan = true;
  #include <TimeLib.h>
  #include <NtpClientLib.h>
  #include <ESP8266WiFi.h>
  #include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
  #include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
  #include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
  #include <ESP8266mDNS.h>


  #define ONBOARDLED 2 // Built in LED on ESP-12/ESP-07

  int8_t timeZone = 1;
  int8_t minutesTimeZone = 0;
  bool wifiFirstConnected = false;

  ESP8266WebServer server(80);

#else
  bool wifi_wlan = false;
#endif

#include "schnapszahlen.h"
#include "datecalculations.h"
#include "displayinfos.h"
#include "handleinput.h"

time_t time;
unsigned int next_update = 0;
extern int time_is_present = 0;

extern char wifiip[16] = "keine ip";

struct datum hochzeitstag;

int seconds = 0;


SoftwareSerial ESPserial(D6, SW_SERIAL_UNUSED_PIN); // RX | TX
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

  boolean syncEventTriggered = false; // True if a time even has been triggered
  NTPSyncEvent_t ntpEvent; // Last triggered event
#endif // wifi ende

void setup(void) {
  Serial.begin(9600);
  ESPserial.begin(9600);
  u8g2.begin();

  hochzeitstag = { 15, 9, 2012, 10};
#if WIFI
      WiFiManager wifiManager;
      WiFi.mode (WIFI_STA);
      wifiManager.setTimeout(15);
      wifiManager.autoConnect("Hochzeitsuhr");
//      wifiManager.resetSettings();
      static WiFiEventHandler e1, e2, e3;
      Serial.println("Local IP");
      Serial.println(WiFi.localIP());
      IPAddress ip = WiFi.localIP();
      sprintf(wifiip, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
      Serial.println ();
//      WiFi.begin (YOUR_WIFI_SSID, YOUR_WIFI_PASSWD);

      pinMode (ONBOARDLED, OUTPUT); // Onboard LED
      digitalWrite (ONBOARDLED, LOW); // Switch on LED

      digitalWrite (ONBOARDLED, HIGH); // Turn off LED
      wifiFirstConnected = true;

      if (MDNS.begin("Hochzeitsuhr")) {
        Serial.println("MDNS responder started");
       }


      server.on("/action", handleAction);
      server.on("/", handleRoot);

      server.begin();


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
      server.handleClient();

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
    delay (0);
#else // wifi ende
  // time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available

  while (ESPserial.available() > 0) {
    gps.encode(ESPserial.read());
  }

  if (seconds != gps.time.second()) {
    // TODO: get fix
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
    }
  }
#endif // else ende von wifi

  if (millis() > next_update) {
    if (time_is_present) {
      struct datum today = getNow();
      struct datum next = getNext(); // TODO

      struct periode elapsed = calculatePeriode(hochzeitstag, today);
      struct periode to_come = calculatePeriode(today, next);

      char description[20];
/*
      if (day() == hochzeitstag.tag && month() == hochzeitstag.monat)  // Ist gerade Hochzeitstag?
      {
        // TODO: Hocheitstag Info
      }
      else if(isSpecial(elapsed.stunden_gesamt, 3, 1, description))  // Ist eine Stunden "Schnapszahl" für vergangene Zeit?
      {
        // TODO: Schnapszahl Info
      }
      else if(isSpecial(to_come.stunden_gesamt, 3, 1, description)) // Ist eine Stunde "Schnapszahl" für den kommenden Hochzeitstag?
      {
        // TODO: Schnapszahl info KOMMENDER Tag
      }
      else if(to_come.tage_gesamt <= 7) // Ist der kommende Hochzeitstag innerhalb von 7 Tagen?
      {
        // TODO: Anstehender Hochzeitstag Info
      }
      else if (isSpecial(elapsed.monate_gesamt, 2, 1, description)) // Haben wir eine Schnapszahl mit Monaten der vergangene Zeit?
      {
        // TODO: Schnapszahl Info
      }
      else if (isSpecial(elapsed.tage_gesamt, 2, 1, description)) // Haben wir eine Schnapszahl mit Tagen der vergangene Zeit?
      {
        // TODO: Schnapszahl Info
      }
      else if (isSpecial(to_come.tage_gesamt, 2, 1, description)) // haben wir eine Schnapszahl mit Tagen für den kommenden Hochzeitstag?
      {
        // TODO: Schnapszahl info KOMMENDER Tag
      }
      else // Trifft alles nicht zu, daher default zeigen.
      {
        screenVerheiratetSeit(elapsed);
      }
*/
      screenVerheiratetSeit(elapsed);

      next_update = millis() + 60 * 10 * 1000 ;
    } else {
      u8g2.firstPage();
      u8g2.setPowerSave(0); // before drawing, enable charge pump (req. 300ms)
      do {
        drawObtainingTime();
//          drawHochzeitstagInfo(2);
      } while ( u8g2.nextPage() );
      u8g2.setPowerSave(1); // disable charge pump

      // if (DCFtime != 0) {
      //   Serial.println("Time is updated");
      //   setTime(DCFtime);
      //   time_is_present = 1;
      // }
      next_update = millis() + 3 * 1000;

    }

  }
  
  handleInput();
  //delay(10);
  
}