#include <Arduino.h>
#include <U8g2lib.h>

#include "schnapszahlen.h"
#include "datecalculations.h"

#include "displayinfos.h"
#include "dateinfo.h"

#include "Time.h"

#include "Images/caro_und_sven.xbm" // 250x34
#include "Images/Stefanie_und_Patrick_ccw.xbm" // 45x128
#include "Images/GPS.xbm" // 110x110

U8G2_IL3820_V2_296X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ D5, /* data=*/ D7, /* cs=*/ D2, /* dc=*/ D1, /* reset=*/ D3);

extern struct datum hochzeitstag;

void mehrzahl(char* result, int zahl, const char *einzahl, const char *mehrzahl) {
  switch (zahl) {
    case 0:
      strcpy(result, "");
      break;

    case 1:
      sprintf(result, "%i %s", zahl, einzahl);
      break;

    default:
      sprintf(result, "%i %s", zahl, mehrzahl);
      break;
  }
}

int getHochzeitstagTitel(int index, char *titel) {
    for (int i=0; i < hochzeitstage_count; i++) {
      struct hochzeitstag ht = hochzeitstage[i];
      if (ht.period == index) {
        strcpy(titel, ht.name);
        return true;
      }
    }
    return false;
}

void clearDisplay() {
  u8g2.firstPage();
  u8g2.setPowerSave(0);	// before drawing, enable charge pump (req. 300ms)
  do {
    u8g2.clearDisplay();
  } while ( u8g2.nextPage() );
  u8g2.setPowerSave(1);	// disable charge pump
}

u8g2_uint_t get_x_for_centered_text(char *text, const uint8_t *font) {
  u8g2_uint_t text_width, display_width;
  u8g2.setFont(font);
  text_width = u8g2.getStrWidth(text);
  display_width = u8g2.getDisplayWidth();
  // Serial.print("Display width: "); Serial.println(display_width);
  return (display_width / 2) - (text_width / 2);
}

void drawHeaderLarge() {
  char text[] = "Verheiratet seit";
  const uint8_t *font = u8g2_font_helvR12_tf;

  // graphic commands to redraw the complete screen should be placed here
  u8g2.drawXBMP(23, 0, caro_und_sven_width, caro_und_sven_height, caro_und_sven_bits);
  u8g2.setFont(font);

  u8g2.drawStr(get_x_for_centered_text(text, font), 54, text);
}

void drawHeaderccw() {
  u8g2.drawXBMP(0, 0, Stefanie_und_Patrick_ccw_width, Stefanie_und_Patrick_ccw_height, Stefanie_und_Patrick_ccw_bits);

}

void drawObtainingTime() {
  char text[] = "Empfange Zeit...";
  const uint8_t *font = u8g2_font_helvR12_tf;
  // graphic commands to redraw the complete screen should be placed here
  u8g2.drawXBMP(14, 14, GPS_width, GPS_height, GPS_bits);
  u8g2.setFont(font);

  u8g2.drawStr(140, 54, text);

  sprintf(text, "%02i:%02i:%02i", hour(), minute(), second());
  u8g2.drawStr(140, 84, text);


}

void drawVerheiratetSeit(struct periode result) {
      printf("%i Jahre, %i Monate, %i Tage, %i Monate gesamt, %i Tage gesamt, %i Stunden\n", result.jahre, result.monate, result.tage, result.monate_gesamt, result.tage_gesamt, result.stunden);
      char text[40] = "";
      char jahre_text[6]; // "Jahre" + \0
      char monate_text[7];
      char tage_text[5];
      char stunden_text[8];

      const uint8_t *font = u8g2_font_helvR12_tf;
      u8g2.setFont(font);

      if (result.jahre > 0) {
        mehrzahl(jahre_text, result.jahre, clckst[CLOCK_STRING_YEAR_SINGLULAR], clckst[CLOCK_STRING_YEAR_PLURAL]);
        strcat(text, jahre_text);

        if (result.monate > 0) {
          strcat(text, ", ");
          mehrzahl(monate_text, result.monate, clckst[CLOCK_STRING_MONTH_SINGLULAR], clckst[CLOCK_STRING_MONTH_PLURAL]);
          strcat(text, monate_text);
        }

        if (result.tage > 0) {
          strcat(text, ", ");
          mehrzahl(tage_text, result.tage, clckst[CLOCK_STRING_DAY_SINGLULAR], clckst[CLOCK_STRING_DAY_PLURAL]);
          strcat(text, tage_text);
        }
      } else if (result.monate > 0) {
        mehrzahl(monate_text, result.monate, clckst[CLOCK_STRING_MONTH_SINGLULAR], clckst[CLOCK_STRING_MONTH_PLURAL]);
        strcat(text,monate_text);

        if (result.tage > 0) {
          strcat(text, ", ");
          mehrzahl(tage_text, result.tage, clckst[CLOCK_STRING_DAY_SINGLULAR], clckst[CLOCK_STRING_DAY_PLURAL]);
          strcat(text, tage_text);
        }

        if (result.stunden > 0) {
          strcat(text, ", ");
          mehrzahl(stunden_text, result.stunden, clckst[CLOCK_STRING_HOUR_SINGULAR], clckst[CLOCK_STRING_HOUR_PLURAL]);
          strcat(text, stunden_text);
        }

      } else if (result.tage > 0) {
        mehrzahl(tage_text, result.tage, clckst[CLOCK_STRING_DAY_SINGLULAR], clckst[CLOCK_STRING_DAY_PLURAL]);
        strcat(text, tage_text);

        if (result.stunden > 0) {
          strcat(text, ", ");
          mehrzahl(stunden_text, result.stunden, clckst[CLOCK_STRING_HOUR_SINGULAR], clckst[CLOCK_STRING_HOUR_PLURAL]);
          strcat(text, stunden_text);
        }

      } else {
        mehrzahl(stunden_text, result.stunden, clckst[CLOCK_STRING_HOUR_SINGULAR], clckst[CLOCK_STRING_HOUR_PLURAL]);
        strcat(text, stunden_text);
      }

      u8g2.drawStr(get_x_for_centered_text(text, font), 80, text);
      char zusatztext[80] = "";
      sprintf(zusatztext,"Stunden: %i, Tage: %i, Monate: %i\n", result.stunden_gesamt, result.tage_gesamt, result.monate_gesamt);
      const uint8_t *font2 = u8g2_font_helvR08_tf;
      u8g2.setFont(font2);
      u8g2.drawStr(get_x_for_centered_text(zusatztext, font2), 100, zusatztext);
      char uhrzeit[40] = "";
      sprintf(uhrzeit, "%02i.%02i.%04i %02i:%02i:%02i", day(), month(), year(), hour(), minute(), second());
      u8g2.drawStr(get_x_for_centered_text(uhrzeit, font2), 120, uhrzeit);
      Serial.printf("Ausgabe : %s\n", text);
      Serial.printf("Zusatz: Stunden gesamt: %i, Tage gesamt: %i, Monate gesamt: %i\n", result.stunden_gesamt, result.tage_gesamt, result.monate_gesamt);

}

void drawSchnapszahl(struct periode result) {

}

void drawHochzeitstagInfo(int tag_index) {
  const uint8_t *large_font = u8g2_font_9x18B_tf;
  u8g2.setFont(large_font);
  u8g2.drawStr(55, 10, hochzeitstage[tag_index].name);


  const uint8_t *font = u8g2_font_lucasfont_alternate_tf;
  u8g2.setFont(font);

  char delimiter[] = " ";
  char *ptr;

  char text[800];
  strcpy(text, hochzeitstage[tag_index].text);

  // initialisieren und ersten Abschnitt erstellen, den werfen wir gleich weg
  ptr = strtok(text, delimiter);

  // Serial.println(ptr);

  int x = 55; int y = 25;
  int width = 0;

  while(ptr != NULL) {
    // Serial.print(ptr); Serial.print(" ");
    width = u8g2.getStrWidth(ptr);
    if (width > u8g2.getDisplayWidth() - x) {
      x = 55;
      y += 10;
    }
    u8g2.drawStr(x, y, ptr);
    x += width + 4;

    ptr = strtok(NULL, delimiter);

  }


}

void drawNextWeddingDay(struct datum date, int count) {
  const uint8_t *font = u8g2_font_helvR12_tf;
  u8g2.setFont(font);

  char text[40] = "";
  sprintf(text, "Am %02i.%02i.%i ist der %i. Hochzeitstag", date.tag, date.monat, date.jahr, count);
  u8g2.drawStr(get_x_for_centered_text(text, font), 105, text);

  char titel[25] = "";
  if (getHochzeitstagTitel(count, titel)) {
    u8g2.drawStr(get_x_for_centered_text(titel, font), 130, titel);    
  }
}

void screenVerheiratetSeit(struct periode elapsed) {
  u8g2.firstPage();
  u8g2.setPowerSave(0);	// before drawing, enable charge pump (req. 300ms)
  do {
    drawHeaderLarge();
    drawVerheiratetSeit(elapsed);
  } while ( u8g2.nextPage() );
  u8g2.setPowerSave(1);	// disable charge pump
}

void screenHochzeitstaginfo(int tag_index) {
  u8g2.firstPage();
  u8g2.setPowerSave(0);	// before drawing, enable charge pump (req. 300ms)
  do {
    drawHeaderccw();
    drawHochzeitstagInfo(tag_index);
  } while ( u8g2.nextPage() );
  u8g2.setPowerSave(1);	// disable charge pump

}
void screenUpcomingWeddingDay(struct periode elapsed, struct datum next_wedding_day, int count) {
  u8g2.firstPage();
  u8g2.setPowerSave(0);	// before drawing, enable charge pump (req. 300ms)
  do {
    drawHeaderLarge();
    drawVerheiratetSeit(elapsed);
    drawNextWeddingDay(next_wedding_day, count);
  } while ( u8g2.nextPage() );
  u8g2.setPowerSave(1);	// disable charge pump

}
