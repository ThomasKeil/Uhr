#ifndef DISPLAYINFOS
#define DISPLAYINFOS

#include <U8g2lib.h>

#include "datecalculations.h"


extern U8G2_IL3820_V2_296X128_F_4W_SW_SPI u8g2;


void mehrzahl(char* result, int zahl, char *einzahl, char *mehrzahl);
void drawStrCentered(char *text, int y, const uint8_t *font);
void drawHeaderLarge();
void drawObtainingTime();
void drawIPAddress(char *ip);
void drawCaptivePortal(char *apname, char *ip);
void drawVerheiratetSeit(struct periode elapsed);
void drawSchnapszahl(struct periode result);
void drawHochzeitstagInfo(int tag_index);
void drawNextWeddingDay(struct datum date, int count);
void clearDisplay();
void screenVerheiratetSeit(struct periode elapsed);
void screenHochzeitstaginfo(int tag_index);
void screenUpcomingWeddingDay(struct periode elapsed, struct datum next_wedding_day, int count);
void screenSchnapszahl(struct periode elapsed, char *text, char *description);
void screenIPAddress(char *ip);
void screenCaptivePortal(char *apname, char *ip);

#endif
