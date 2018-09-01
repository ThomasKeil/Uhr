#!/bin/bash
clear;
g++ -DDC_DEBUG ../src/datecalculations.cpp ../src/schnapszahlen.cpp main.cpp -o date_test && ./date_test
