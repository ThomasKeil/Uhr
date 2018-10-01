#ifndef DATECALCULATIONSTRUCTS
#define DATECALCULATIONSTRUCTS

struct datum {
  int tag, monat, jahr, stunde;
};

struct periode {
  int stunden, tage, monate, jahre, monate_gesamt, tage_gesamt, stunden_gesamt, valid;
};

struct periode calculatePeriode(struct datum datum1, struct datum datum2);
int daysInFebruary(int jahr);
int datumToInt(struct datum datum);
int getTagesnummer(struct datum datum);
int isSmaller(struct datum datum1, struct datum datum2);
int isEqual(struct datum datum1, struct datum datum2);
int getDaysInMonth(int month, int year);

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
