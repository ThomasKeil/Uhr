# Hochzeitsuhr

## Hardware
* ESP8266
* [Waveshare 2.9inch 296x128](https://www.waveshare.com/wiki/2.9inch_e-Paper_Module)
* AZ-Delivery Neo-6M GPS Modul (Clone)

## Software
Entwickelt mit Atom/Platformio

### Libraries

* Ansteuerung des Waveshare-ePaper Displays:
  [u8g2](https://github.com/olikraus/u8g2) mit [16Bit Mode](https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#16-bit-mode)
* Auslesen des GPS-Empfängers:
  [TinyGPS++](http://arduiniana.org/libraries/tinygpsplus/)
  [Github](https://github.com/mikalhart/TinyGPSPlus)
