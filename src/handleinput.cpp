#include <Arduino.h>
#include "Time.h"

#include "handleinput.h"
#include "displayinfos.h"


extern struct datum hochzeitstag;


void printCurrentTime() {
  char current_time[40];
  sprintf(current_time, "Bekannte Zeit: %02i.%02i.%04i %02i:%02i:%02i", day(), month(), year(), hour(), minute(), second());
  Serial.println(current_time);
}


void handleInput() {
  const uint16_t inputLength = 512;

  if (Serial.available() > 0) {
    static char input[inputLength];
    static uint16_t i;
    char c = Serial.read();
    Serial.print(c);

    if ( c != '\r' && c != '\n' && i < inputLength - 1) {
      input[i++] = c;
    } else {
      input[i] = '\0';
      i = 0;
      Serial.println();

      if (!strncmp(input, "setdate", 7)) {
        char delimiter[] = " .:";
        char *ptr;

        int dummy = 0, day = 0, month = 0, year = 0;
        // initialisieren und ersten Abschnitt erstellen, den werfen wir gleich weg
        ptr = strtok(input, delimiter);
        Serial.println(ptr);

        ptr = strtok(NULL, delimiter);
        while(ptr != NULL) {
          Serial.println(ptr);
          dummy = atoi(ptr);
          Serial.printf("Found: %i\n", dummy);
          if (day == 0) {
            day = dummy;
          } else if (month == 0) {
            month = dummy;
          } else if (year == 0) {
            year = dummy;
            setTime(hour(),minute(),second(),day,month,year);
            time_is_present = 1;
            Serial.println("Date was set");
          }

          ptr = strtok(NULL, delimiter);

        }
      }

      if (!strncmp(input, "help", 5)) {
        Serial.println("help: Print this help");
        Serial.println("hello: Say hi!");
        Serial.println("currenttime: Prints the currently known time");
        Serial.println("setdate DD.MM.YYYY");
        Serial.println("cleardisplay: Clear the display.");
        Serial.println("drawverheiratetseit: Display the info \"Verheiratet seit\"");
        Serial.println("ht X: Display info about Hochzeitstag 0-25" );
        Serial.println();
      }

      if ( !strncmp(input, "currenttime", 11) ) {
        printCurrentTime();
      }

      if (!strncmp(input, "cleardisplay", 12)) {
        clearDisplay();
      }

      if (!strncmp(input, "drawverheiratetseit", 19)) {
        struct datum today = getNow();
        struct periode elapsed = calculatePeriode(hochzeitstag, today);
        screenVerheiratetSeit(elapsed);
      }

      if ( !strncmp(input, "hello", 5) ) {
        Serial.println("hi");
      }

      if ( !strncmp(input, "ht", 2) ) {
        char delimiter[] = " .:";
        char *ptr;

        int dummy = 0;
        // initialisieren und ersten Abschnitt erstellen, den werfen wir gleich weg
        ptr = strtok(input, delimiter);

        Serial.println(ptr);

        ptr = strtok(NULL, delimiter);
        while(ptr != NULL) {
          Serial.println(ptr);
          dummy = atoi(ptr);
          if (dummy >= 0 && dummy < 26) {
              screenHochzeitstaginfo(dummy);
          }
          ptr = strtok(NULL, delimiter);

        }
      }

      // if ( !strncmp(input, "sa", 2) ) {
      //   Serial.print("  ss= ");
      //   Serial.print(ss);
      //
      //   Serial.print("  bHold= ");
      //   Serial.print(bHold);
      //
      //   Serial.println(" ");
      //   Serial.println("==============================");
      // }
    }
  }
}
