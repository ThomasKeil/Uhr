#include <stdio.h>
#include <assert.h>
#include "../src/schnapszahlen.h"
#include "../src/datecalculations.h"


void print_result(struct periode result) {
  printf("%i Jahre, %i Monate, %i Tage,  %i Stunden  -   Monate gesamt: %i, Tage gesamt: %i, Stunden gesamt: %i\n", result.jahre, result.monate, result.tage, result.stunden, result.monate_gesamt, result.tage_gesamt, result.stunden_gesamt);
}

void print_datum(struct datum datum) {
  printf("%i.%i.%i %i:00 Uhr\n", datum.tag, datum.monat, datum.jahr, datum.stunde);
}

void test_periode(struct datum start, struct datum ende, struct datum assert_datum) {
  print_datum(ende);

  struct periode result = calculatePeriode(start, ende);
  print_result(result);
  assert(result.jahre == assert_datum.jahr);
  assert(result.monate == assert_datum.monat);
  assert(result.tage == assert_datum.tag);
  assert(result.stunden == assert_datum.stunde);
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



  struct datum start = { 15, 9, 2012, 10};
  struct datum ende;
  struct datum assert_datum;

  print_datum(start);
  printf("\n");

  ende = (struct datum ) {16, 9, 2018, 8};
  assert_datum = (struct datum ) {0, 0, 6, 22};
  test_periode(start, ende,assert_datum);

  ende = (struct datum ) {14, 9, 2018, 8};
  assert_datum = (struct datum ) {0, 0, 6, 12};
  test_periode(start, ende,assert_datum);
/*
  ende = (struct datum ) {15, 9, 2013, 15};
  test_periode(start, ende);

  ende = (struct datum ) {4, 9, 2018, 18};
  test_periode(start, ende);
*/


}
