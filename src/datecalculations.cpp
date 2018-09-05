#include <stdio.h>

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

  result.monate_gesamt = (datum2.jahr * 12 + datum2.monat) - (datum1.jahr * 12 + datum1.monat);
  #ifdef DC_DEBUG
  printf("Ermittelte Monate gesamt: %i\n", result.monate_gesamt);
  #endif

  /* Die Anzahl der Monate muss ggfs korrigiert werden, wenn zwischen zwei Zeitpunkten nicht mindestens ein Monat vergangen ist.
     Ein Monat ist vergangen. wenn der Tag im darauffolgenden Monat gleich oder größer des vorgehenden
    Tages ist.

    Beispiele: 14.05.2018 / 17.05.2018  -> kein Monat vergangen
               14.05.2018 / 03.05.2018  -> kein Monat vergangen
               14.05.2018 / 14.06.2018  -> exakt ein Monat vergangen
               14.05.2018 / 15.06.2018  -> ein Monat und ein Tag vergangen
    */


  result.jahre = (int) (result.monate_gesamt / 12);
  result.monate = result.monate_gesamt - result.jahre * 12;
  #ifdef DC_DEBUG
  printf("Ermittelte Monate: %i\n", result.monate);
  #endif

  if (datum1.monat == datum2.monat) {
    // Es ist der gleiche Monat
    result.tage = datum2.tag - datum1.tag;
  } else {
    // Es ist ein späterer Monat
    if (datum2.tag > datum1.tag) {
      result.tage = datum2.tag - datum1.tag;
    } else {
      result.tage = days_in_month[datum1.monat - 1] - datum1.tag + datum2.tag;
      result.monate--;
    }
  }

  // Nun die gesamten Tage zusammenzählen
  result.tage_gesamt = 0;

  // Hier starten wir.
  int cursor_monat = datum1.monat;
  int cursor_jahr = datum1.jahr;

  // Wir beginnen im aktuelle Monat, durchlaufen alle Jahre, und enden im letzen Monat.
  for(int i=0; i<=result.monate_gesamt; i++) {

    // Tage des Februars bestimmen.
    if(cursor_monat==2) {
      // Rücksetzen, falls das vorige Jahr Schaltjahr war.
      days_in_month[1]=28;

      // Ist Schaltjahr?
      if(cursor_jahr%4==0 && (cursor_jahr%100!=0 || cursor_jahr%400==0))
        days_in_month[1]=29;
        #ifdef DC_DEBUG
        printf("Der Februar hatte im Jahr %i %i Tage.\n", cursor_jahr, days_in_month[1]);
        #endif
    }

    // Tage des aktuellen Monats addieren.
    // Die bereits vergangenen und die noch kommenden Tage ziehen wir ggfs. später wieder ab.
    result.tage_gesamt += days_in_month[cursor_monat-1];
    #ifdef DC_DEBUG
    // printf("...Tage für Monat %i im Jahr %i hinzuaddiert: %i, sind jetzt bei %i Tage gesamt\n", cursor_monat, cursor_jahr, days_in_month[cursor_monat-1], result.tage_gesamt);
    #endif

    // Den Cursor einen Monat weiter schieben
    cursor_monat++;
    if(cursor_monat > 12) {
        cursor_monat=1;
        cursor_jahr++;
    }

  }

  #ifdef DC_DEBUG
  printf("Tage gesamt nun %i, beginne Korrektur...\n", result.tage_gesamt);
  #endif

  result.tage_gesamt -= datum1.tag + days_in_month[datum2.monat - 1] - datum2.tag;


  if (datum1.monat != datum2.monat) {
    // Wir sind nicht im gleichen Monat. Da datum2 später sein muss als datum1 können wir davon ausgehen
    // das datum2.tag in einem späteren Monat liegt

    if (datum2.tag <= datum1.tag) {
      result.monate_gesamt--;
    }
  }

  result.stunden = 0;

  // Stunden ermitteln
  if (datum1.tag == datum2.tag) {
    #ifdef DC_DEBUG
    printf("Gleicher Tag\n");
    #endif
    result.stunden = datum2.stunde - datum1.stunde;
  } else {

    if (datum2.stunde > datum1.stunde) {
      #ifdef DC_DEBUG
      printf("Darauffolgender Tag, später als am Tag zuvor\n");
      #endif
      result.stunden = datum2.stunde - datum1.stunde;

    } else if (datum2.stunde < datum1.stunde) {
      #ifdef DC_DEBUG
      printf("Darauffolgender Tag, aber früher als am Tag zuvor\n");
      #endif
      result.stunden = (24-datum1.stunde) + datum2.stunde;
      result.tage_gesamt--;
      result.tage--;

    } else {
      #ifdef DC_DEBUG
      printf("Uhrzeit ist gleich, also nichts unternehmen\n");
      #endif

    }

    // Bei gleiche Stunde tun wir nichts, das passt bereits
  }

  // if (result.stunden > 24) {
  //   result.tage_gesamt++;
  //   result.stunden -= 24;
  // }

  result.stunden_gesamt = result.tage_gesamt * 24 + result.stunden;


  return result;
}

/*!
  \param datum ein Pointer auf ein datum struct, welches vorgezählt wird
  \param stunden int, die Stunden die vorgezählt werden sollten
  \param tage int, die Tage die vorgezählt werden sollten
  \param monate int, die Monate die vorgezählt werden sollen 
*/
void carry(struct datum &datum, int stunden, int tage, int monate) {
  // das kann man bestimmt noch globaler machen
  int days_in_month[]={31,28,31,30,31,30,31,31,30,31,30,31};

  datum.stunde += stunden;
  while (datum.stunde > 23) {
    datum.tag++;
    datum.stunde -= 24;
  }

  datum.tag += tage;
  while (datum.tag > days_in_month[datum.monat - 1]) {
    datum.tag -= days_in_month[datum.monat - 1];
    datum.monat++;
  }

  datum.monat += monate;
  while (datum.monat > 12) {
    datum.jahr++;
    datum.monat -= 12;
  }
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
