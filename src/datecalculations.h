struct datum {
  int tag, monat, jahr, stunde;
};

struct periode {
  int stunden, tage, monate, jahre, monate_gesamt, tage_gesamt;
};

struct periode calculatePeriode(struct datum datum1, struct datum datum2);
