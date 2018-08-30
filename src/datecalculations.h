#ifndef DATECALCULATIONSTRUCTS
#define DATECALCULATIONSTRUCTS

struct datum {
  int tag, monat, jahr, stunde;
};

struct periode {
  int stunden, tage, monate, jahre, monate_gesamt, tage_gesamt, stunden_gesamt;
};

struct periode calculatePeriode(struct datum datum1, struct datum datum2);

enum string_items {
  CLOCK_STRING_YEAR_SINGLULAR,
  CLOCK_STRING_YEAR_PLURAL,
  CLOCK_STRING_MONTH_SINGLULAR,
  CLOCK_STRING_MONTH_PLURAL,
  CLOCK_STRING_DAY_SINGLULAR,
  CLOCK_STRING_DAY_PLURAL,
  CLOCK_STRING_HOUR_SINGULAR,
  CLOCK_STRING_HOUR_PLURAL
};

extern const char *clckst[];

#endif
