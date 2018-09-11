#include <stdio.h>
#include "../src/schnapszahlen.h"
#include "../src/datecalculations.h"


void print_result(struct periode result) {
  printf("%i Jahre, %i Monate, %i Tage,  %i Stunden  -   Monate gesamt: %i, Tage gesamt: %i, Stunden gesamt: %i\n", result.jahre, result.monate, result.tage, result.stunden, result.monate_gesamt, result.tage_gesamt, result.stunden_gesamt);
}

void print_datum(struct datum datum) {
  printf("%i.%i.%i %i:00 Uhr\n", datum.tag, datum.monat, datum.jahr, datum.stunde);
}

void test_periode(struct datum start, struct datum ende) {
  print_datum(ende);

  struct periode result = calculatePeriode(start, ende);
  print_result(result);
  printf("\n");
}

int main() {
  // signed int i;
  // signed int t;
  //
  // for (t=1; t<4; t++) {
  //   printf("\n\nWiederholung Periode %i\n", t);
  //   for (i=0; i<= 1000000; i++) {
  //     if (schnapszahl(i,t)) {
  //       printf("%i  ", i);
  //     }
  //   }
  // }
  // printf("\n\nPalindrome\n");
  // for (i=0; i<= 1000000; i++) {
  //   if (palindrom(i, 4)) {
  //     printf("%i ", i);
  //   }
  // }
  // printf("\n\nRotierbar\n");
  // for (i=0; i<= 1000000; i++) {
  //   if (upsidedown(i, 4)) {
  //     printf("%i ", i);
  //   }
  // }
  // printf("\n");



  struct datum start = { 2, 2, 2018, 21};
  struct datum ende;

  print_datum(start);
  printf("\n");

  ende = {2, 2, 2018, 22};
  test_periode(start, ende);

  ende = {3, 2, 2018, 2};
  test_periode(start, ende);

  ende = {3, 2, 2018, 22};
  test_periode(start, ende);

  ende = {4, 2, 2018, 20};
  test_periode(start, ende);

  ende = {1, 3, 2018, 21};
  test_periode(start, ende);

  ende = {2, 3, 2018, 21};
  test_periode(start, ende);

  ende = {3, 3, 2018, 21};
  test_periode(start, ende);

  ende = {1, 9, 2018, 11};
  test_periode(start, ende);

  ende = {2, 2, 2019, 21};
  test_periode(start, ende);

  ende = {3, 2, 2039, 21};
  test_periode(start, ende);


}
