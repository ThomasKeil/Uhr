# Hochzeitsuhr

## Hardware
* ESP8266
* [Waveshare 2.9inch 296x128](https://www.waveshare.com/wiki/2.9inch_e-Paper_Module)
* Pollin DCF77 Modul

## Software
Entwickelt mit Atom/Platformio

### Libraries

* Ansteuerung des Waveshare-ePaper Displays:
  [u8g2](https://github.com/olikraus/u8g2) mit [16Bit Mode](https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#16-bit-mode)
* Auslesen der DCF77-Uhr:
  [Arduino DCF77 radio clock receiver – Library](http://thijs.elenbaas.net/2012/04/arduino-dcf77-radio-clock-receiver-library/)
  [Github](https://github.com/thijse/Arduino-DCF77)
