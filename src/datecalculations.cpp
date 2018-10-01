#include "datecalculations.h"

extern struct datum hochzeitstag;


// Siehe: http://latest-technology-guide.blogspot.com/2013/03/c-language-example-36-find-date.html

struct periode calculatePeriode(struct datum datum1, struct datum datum2) {
  struct periode result;
  result.stunden = 0;
  result.tage = 0;
  result.monate = 0;
  result.jahre = 0;
  result.tage_gesamt = 0;
  result.monate_gesamt = 0;
  result.stunden_gesamt = 0;
  result.valid = 1;

  if (datum2.jahr < datum1.jahr) {
    result.valid = 0;
    return result;
  }

  if (datum1.jahr == datum2.jahr) {
    if (datum2.monat < datum1.monat) {
      result.valid = 0;
      return result;
    }
    if (datum1.monat == datum2.monat) {
      if (datum2.tag < datum1.tag) {
        result.valid = 0;
        return result;
      }
      if ( datum1.tag == datum2.tag) {
        if (datum2.stunde < datum1.stunde) {
          result.valid = 0;
          return result;
        }
      }
    }
  }

  int days_in_month[]={31,28,31,30,31,30,31,31,30,31,30,31};


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
  return days;
}

struct datum getNextWeddingDayDate(struct datum now, struct datum hochzeitstag) {
  struct datum next = {hochzeitstag.tag, hochzeitstag.monat, now.jahr, hochzeitstag.stunde};

  if (isLarger(now, next) || isEqual(now, next)) {
    next.jahr++;
  }
  return next;
}

int datumToInt(struct datum datum) {
  int result = datum.jahr * 1000000 + datum.monat * 10000 + datum.tag * 100 + datum.stunde;
  return result;
}

int isEqual(struct datum datum1, struct datum datum2) {
  int d1 = datumToInt(datum1);
  int d2 = datumToInt(datum2);
  return d1 == d2;
}

int isSmaller(struct datum datum1, struct datum datum2) {
  int d1 = datumToInt(datum1);
  int d2 = datumToInt(datum2);
  return d1 < d2;
}

int isLarger(struct datum datum1, struct datum datum2) {
  int d1 = datumToInt(datum1);
  int d2 = datumToInt(datum2);
  return d1 > d2;
}


int getDaysInMonth(int month, int year) {
  int february = 28;
  if (year%4==0 && (year%100!=0 || year%400==0)) {
    february = 29;
  }

  int days_in_month[]={31,february,31,30,31,30,31,31,30,31,30,31};
  return days_in_month[month - 1];
}

int getTagesnummer(struct datum datum) {
  struct datum cursor = {1,1,datum.jahr,0};
  int tagesnummer = 1;
  while (isSmaller(cursor, datum)) {
    cursor.tag++;
    tagesnummer++;
    if (cursor.tag > getDaysInMonth(cursor.monat, cursor.jahr)) {
      cursor.tag = 1;
      cursor.monat++;
    }
  }
  return tagesnummer;
}
