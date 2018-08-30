#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#include "Utils.h"
#include "Time.h"


#include "schnapszahlen.h"
#include "datecalculations.h"
#include "displayinfos.h"
#include "handleinput.h"

using namespace Utils;

// #define DCF_PIN D1	         // Connection pin to DCF 77 device
// #define DCF_INTERRUPT D1		 // Interrupt number associated with pin

time_t time;
unsigned int next_update = 0;
extern int time_is_present = 0;

int seconds = 0;

SoftwareSerial ESPserial(D6, D1); // RX | TX
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


void setup(void) {
  Serial.begin(9600);
  ESPserial.begin(9600);
  u8g2.begin();
}


/* draw something on the display with the `firstPage()`/`nextPage()` loop*/
void loop(void) {
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


  if (millis() > next_update) {
    if (time_is_present) {
        screenVerheiratetSeit();
        next_update = millis() + 60 * 10 * 1000 ;
    } else {
      u8g2.firstPage();
      u8g2.setPowerSave(0);	// before drawing, enable charge pump (req. 300ms)
      do {
        drawObtainingTime();
//          drawHochzeitstagInfo(2);
      } while ( u8g2.nextPage() );
      u8g2.setPowerSave(1);	// disable charge pump

      // if (DCFtime != 0) {
      //   Serial.println("Time is updated");
      //   setTime(DCFtime);
      //   time_is_present = 1;
      // }
      next_update = millis() + 3 * 1000;

    }

  }
  handleInput();
  delay(10);
}
