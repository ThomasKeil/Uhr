#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "schnapszahlen.h"

int isSpecial(signed int zahl, signed int minimal_length, signed int periode, char *description) {
  if (schnapszahl(zahl, periode)) {
    strcpy(description, "Dies ist eine Schnapszahl");
    return 1;
  }
  if (palindrom(zahl, minimal_length)) {
    strcpy(description, "Dies ist ein Palindrom");
    return 1;
  }
  if (upsidedown(zahl, minimal_length)) {
    strcpy(description, "Diese Zahl kann gedreht werden");
    return 1;
  }

  return 0;
}

int schnapszahl(signed int zahl, signed int periode) {
        char input[30];

        sprintf(input, "%i", zahl);

        if (periode >= strlen(input)) return 0;

        char to_try[10];
        strncpy(to_try, input, periode);

        for (int i=0; i<strlen(input); i+=periode) {
                for (int t=0; t<periode; t++) {
                        if (input[i+t] != to_try[t]) return 0;

                }
        }
        return 1;
}

int palindrom(signed int zahl, signed int minimal_length) {
        char input[30];
        sprintf(input, "%i", zahl);
        if (strlen(input) < minimal_length) return 0;

        int offset = strlen(input);
        int middle = offset/2;


        for (int i=0; i <= middle; i++) {
                if (input[i] != input[offset - i -1]) return 0;
        }
        return 1;
}

int upsidedown(signed int zahl, signed int minimal_length) {
        char input[30];
        sprintf(input, "%i", zahl);
        if (strlen(input) < minimal_length) return 0;

        int offset = strlen(input);
        int middle = offset/2;
        int counterpart;

        for (int i=0; i <= middle; i++) {
                counterpart = input[offset -i - 1];
                switch (input[i]) {
                case 0x30:
                        if (counterpart != 0x30) return 0;
                        break;

                case 0x38:
                        if (counterpart != 0x38) return 0;
                        break;

                case 0x39:
                        if (counterpart != 0x36) return 0;
                        break;

                case 0x36:
                        if (counterpart != 0x39) return 0;
                        break;

                default:
                        return 0;
                        break;
                }
        }
        return 1;
}
