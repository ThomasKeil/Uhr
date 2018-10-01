#!/bin/bash
clear;
g++ -DDC_DEBUG -I~/.platformio/lib/Time_ID44/ ../src/datecalculations.cpp ../src/schnapszahlen.cpp main.cpp -o date_test && ./date_test
