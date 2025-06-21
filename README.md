# esp32-trap-camera
A project to create a (solar powered) trap camera using ESP-NOW to transfer pictures


## Plan

The vague plan is to create a separate power supply that will provide 3.3v to the ESP32CAM, using a solar charger module and some other ancillaries.

Then I'll configure an ESP32CAM to take pictures as per [this tutorial](https://randomnerdtutorials.com/esp32-cam-pir-motion-detector-photo-capture)

I'll modify this project to send the picture via ESP-NOW to a companion device, using [this project](https://github.com/talofer99/ESP32CAM-Capture-and-send-image-over-esp-now) - and [its associated video](https://www.youtube.com/watch?v=0s4Bm9Ar42U) as a basis.

Finally I'll do something with the ESP-NOW companion device (to make the pictures available on the home WiFi network) - but I've ont got that far yet.



### Part 1: capture the picture using a PIR
Managed to compile the software, but the camera is duff.. new bits are on order

#### ESP32 S3 WROOM - it's pretty cool. 

I've upgraded the hardware to the ESP32 S3 WROOM board.

There's some excellent tutorials on the [Freenove Github page](https://github.com/Freenove/Freenove_ESP32_S3_WROOM_Board) of which I'm following the 'C' tutorial to try and get the new hardware to work.. mainly by removing some bits from the previous tutorial and changing some of the pins. 

#### Arduino IDE setup
 
File - Preferences - Additional Boards Manager URLs - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Boards Manager - look for ESP32 by Espressif Systems - Add (3.2.0)

Library: SDFat by by Bill Greiman (2.3.0)



So far the SD card and the camera are recognised.