#include <stdio.h>
#include <Time.h>

#include "datecalculations.h"

struct datum getNow() {
  struct datum now = {day(), month(), year(), hour()};
  return now;
}

struct datum getNextWeddingDayDate(struct datum hochzeitstag) {
  struct datum now = {day(), month(), year(), hour()};
  struct datum next = {hochzeitstag.tag, hochzeitstag.monat, now.jahr, hochzeitstag.stunde};

  int tagesnummer_now = getTagesnummer(now);
  int tagesnummer_next = getTagesnummer(next);

  if (tagesnummer_now > tagesnummer_next) {
    next.jahr++;
  }
  return next;
}
