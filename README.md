# esp32-trap-camera
A project to create a (solar powered) trap camera using ESP-NOW to transfer pictures


## Plan

The vague plan is to create a separate power supply that will provide 3.3v to the ESP32CAM, using a solar charger module and some other ancillaries.

Then I'll configure an ESP32CAM to take pictures as per [this tutorial](https://randomnerdtutorials.com/esp32-cam-pir-motion-detector-photo-capture)

I'll modify this project to send the picture via ESP-NOW to a companion device, using [this project](https://github.com/talofer99/ESP32CAM-Capture-and-send-image-over-esp-now) - and [its associated video](https://www.youtube.com/watch?v=0s4Bm9Ar42U) as a basis.

Finally I'll do something with the ESP-NOW companion device (to make the pictures available on the home WiFi network) - but I've ont got that far yet.

### Part 1: capture the picture using a PIR
Managed to compile the software, but the camera is duff.. new bits are on order


