#ifndef DISPLAYINFOS
#define DISPLAYINFOS

#include <U8g2lib.h>

#include "datecalculations.h"


extern U8G2_IL3820_V2_296X128_F_4W_SW_SPI u8g2;


void mehrzahl(char* result, int zahl, char *einzahl, char *mehrzahl);
void drawHeaderLarge();
void drawObtainingTime();
void drawVerheiratetSeit(struct periode elapsed);
void drawSchnapszahl(struct periode result);
void drawHochzeitstagInfo(int tag_index);
void drawNextWeddingDay(struct datum date, int count);
void clearDisplay();
void screenVerheiratetSeit(struct periode elapsed);
void screenHochzeitstaginfo(int tag_index);
void screenUpcomingWeddingDay(struct periode elapsed, struct datum next_wedding_day, int count);


#endif
