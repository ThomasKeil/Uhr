#include <stdio.h>
#include <Time.h>

#include "datecalculations.h"

struct datum getNow() {
  struct datum now = {day(), month(), year(), hour()};
  return now;
}
