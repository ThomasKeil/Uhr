#include <stdio.h>
#include "Time.h"

#include "datecalculations.h"


// Siehe: http://latest-technology-guide.blogspot.com/2013/03/c-language-example-36-find-date.html

struct periode calculatePeriode(struct datum datum1, struct datum datum2) {
  if (datum2.jahr < datum1.jahr) {
    // Error. How?
  }

  if (datum1.jahr == datum1.jahr) {
    if (datum2.monat < datum1.monat) {
      // Error
    }
    if (datum1.monat == datum2.monat) {
      if (datum2.tag < datum1.tag) {
        // error

      }
      if ( datum1.tag == datum2.tag) {
        if (datum2.stunde < datum1.stunde) {
          // error
        }
      }
    }
  }

  int days_in_month[]={31,28,31,30,31,30,31,31,30,31,30,31};

  struct periode result;
  result.stunden = 0;
  result.tage = 0;
  result.monate = 0;
  result.jahre = 0;
  result.tage_gesamt = 0;
  result.monate_gesamt = 0;
  result.stunden_gesamt = 0;

  // Hier starten wir.
  struct datum cursor = datum1;

  days_in_month[1] = daysInFebruary(cursor.jahr);

  while (!isEqual(cursor, datum2)) {
    result.stunden++;
    result.stunden_gesamt++;

    cursor.stunde++;
    if (cursor.stunde == 24) {
      cursor.tag++;
      cursor.stunde = 0;
    }

    if (cursor.tag > days_in_month[cursor.monat -1]) {
        cursor.tag = 1;
        cursor.monat++;
    }

    if (cursor.monat > 12) {
      cursor.monat = 1;
      cursor.jahr++;
      days_in_month[1] = daysInFebruary(cursor.jahr);
    }

    if (cursor.stunde == datum1.stunde) {
      // Ein Tag ist vergangen.
      result.tage_gesamt++;
      result.tage++;
      result.stunden = 0;

      if (cursor.tag == datum1.tag) {
        // Ein Monat ist vergangen
        result.monate_gesamt++;
        result.monate++;
        result.tage = 0;

        if (cursor.monat == datum1.monat) {
          result.monate = 0;
          result.jahre++;
        }
      }
    }

  }

  return result;
}

/*!
  Bestimmt die Anzahl der Tage des Februars für ein bestimmtes Jahr

  \param jahr Das Jahr um die Monate zu bestimmen
  \return Ein int mit 28 oder 29
 */
int daysInFebruary(int jahr) {
  int days = 28;
  if (jahr%4==0 && (jahr%100!=0 || jahr%400==0)) {
    days = 29;
  }
  #ifdef DC_DEBUG
  printf("Der Februar hatte im Jahr %i %i Tage.\n", jahr, days);
  #endif
  return days;
}

int isEqual(struct datum datum1, struct datum datum2) {
  if (datum1.jahr != datum2.jahr) return 0;
  if (datum1.monat != datum2.monat) return 0;
  if (datum1.tag != datum2.tag) return 0;
  if (datum1.stunde != datum2.stunde) return 0;
  return 1;
}

struct datum getNow() {
  struct datum now = {day(), month(), year(), hour()};
  return now;
}

struct datum getNext() {
  // TODO: Provisorium ersetzen
  struct datum now = {day(), month(), year(), hour()};
  return now;
}
