#include <stdio.h>

#include "datecalculations.h"


// Siehe: http://latest-technology-guide.blogspot.com/2013/03/c-language-example-36-find-date.html

struct periode calculatePeriode(struct datum datum1, struct datum datum2) {
  struct periode result;
  int days_in_month[]={31,28,31,30,31,30,31,31,30,31,30,31};

  result.monate_gesamt = (datum2.jahr * 12 + datum2.monat) - (datum1.jahr * 12 + datum1.monat);
  result.jahre = (int) (result.monate_gesamt / 12);
  result.monate = result.monate_gesamt - result.jahre * 12;

  if (datum1.monat == datum2.monat) {
    result.tage = datum2.tag - datum1.tag;
  } else {
    if (datum2.tag > datum1.tag) {
      result.tage = datum2.tag - datum1.tag;
    } else {
      result.tage = days_in_month[datum1.monat] - datum1.tag + datum2.tag;
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
    }

    // Tage des aktuellen Monats addieren.
    // Die bereits vergangenen und die noch kommenden Tage ziehen wir ggfs. später wieder ab.
    result.tage_gesamt += days_in_month[cursor_monat-1];


    // Den Cursor einen Monat weiter schieben
    cursor_monat++;
    if(cursor_monat > 12) {
        cursor_monat=1;
        cursor_jahr++;
    }

  }

  result.tage_gesamt -= datum1.tag + (days_in_month[datum2.monat] - datum2.tag) + 2;

  result.stunden = (24-datum1.stunde) + datum2.stunde;
  result.stunden_gesamt = result.tage_gesamt * 24 + result.stunden;
  
  return result;
}
