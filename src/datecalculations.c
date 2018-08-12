#include "datecalculations.h"

// Siehe: http://latest-technology-guide.blogspot.com/2013/03/c-language-example-36-find-date.html

struct periode calculatePeriode(struct datum datum1, struct datum datum2) {
  // int d1,m1,y1,d2,m2,y2,i,temp,sum=0,

  struct datum cursor = datum1;
  int resttage, tage;

  int month[]={31,28,31,30,31,30,31,31,30,31,30,31};

  resttage=datum1.tag;
  tage = month[datum1.monat - 1] - datum1.tag;

  struct periode result;
  result.jahre = 0;
  result.monate = 0;
  result.tage = 0;
  result.stunden = 0;
  result.monate_gesamt = 0;
  result.tage_gesamt = 0;

  for(int i=datum1.monat; i<datum2.monat+(datum2.jahr-cursor.jahr)*12; i++) {
          if(i>12) {
                  i=1;
                  result.jahre++;
                  cursor.jahr++;
                  result.monate -= 12;
          }

          // Tage des Februars bestimmen.
          if(i==2) {
                  month[i-1]=28;
                  // Ist Schaltjahr?
                  if(cursor.jahr%4==0 && (cursor.jahr%100!=0 || cursor.jahr%400==0))
                          month[i-1]=29;

          }

          // Verbleibende Tage, die im ersten Monat der Periode noch vergehen können
          result.tage_gesamt += (month[i-1]-resttage);
          resttage=0; // Resttage auf 0, jeder neue Monat erhöht nun um seine vollen Tage


          result.monate_gesamt++;
          result.monate++;
  }

  result.tage_gesamt += datum2.tag - resttage;
  result.tage = tage + datum2.tag;

  result.stunden = result.tage_gesamt * 24 + (24-datum1.stunde) + datum2.stunde;

  return result;
}
