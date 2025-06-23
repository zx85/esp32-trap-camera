/*
    ESP-NOW Broadcast Slave
    Lucas Saavedra Vaz - 2024

    This sketch demonstrates how to receive broadcast messages from a master device using the ESP-NOW protocol.

    The master device will broadcast a message every 5 seconds to all devices within the network.

    The slave devices will receive the broadcasted messages. If they are not from a known master, they will be registered as a new master
    using a callback function.
*/

#include <esp_now.h>
#include <WiFi.h>
#define CHANNEL 1

#include <SPIFFS.h>
// #include <telegram_functions.h>
#include <esp_now_functions.h>
#include <wifi_functions.h>

int currentTransmitCurrentPosition = 0;
int currentTransmitTotalPackages = 0;
byte showImage = 0;
byte awaitImage = 1;

// Telegram setup
WiFiClientSecure clientTCP;
UniversalTelegramBot bot(BOTtoken, clientTCP);


void setup() {
  Serial.begin(115200);
  Serial.println("ESPNow/Basic/Secondary Example");

 if (!SPIFFS.begin())
  {
    Serial.println(F("ERROR: File System Mount Failed!"));
  }
  else
  {
    Serial.println(F("success init spifss"));
  }


}

void loop() {
  // if waiting for an image
  if (awaitImage)
    {
    awaitImage = 0;
    //Set device in AP mode to begin with
    InitESPNow();
    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info.
    esp_now_register_recv_cb(OnDataRecv);
    }

  // if show image flag
  if (showImage)
  {
    showImage = 0;
    unsigned long start = millis();
    InitWifi();
    delay(5000);
    Serial.printf("Time used: %lu\n", millis() - start);
    awaitImage = 1;
  }
}



// callback when data is recv from Master
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {

  switch (*data++)
  {
    case 0x01:
      Serial.println("Start of new file transmit");
      currentTransmitCurrentPosition = 0;
      currentTransmitTotalPackages = (*data++) << 8 | *data;
      Serial.println("currentTransmitTotalPackages = " + String(currentTransmitTotalPackages));
      SPIFFS.remove("/pic.jpg");
      break;
    case 0x02:
      //Serial.println("chunk of file transmit");
      currentTransmitCurrentPosition = (*data++) << 8 | *data++;
      //Serial.println("chunk NUMBER = " + String(currentTransmitCurrentPosition));
      File file = SPIFFS.open("/pic.jpg",FILE_APPEND);
      if (!file)
        Serial.println("Error opening file ...");
        
      for (int i=0; i < (data_len-3); i++)
      {
        //byte dat = *data++;
        //Serial.println(dat);
        file.write(*data++);
      }
      file.close();

      if (currentTransmitCurrentPosition == currentTransmitTotalPackages)
      {
        showImage = 1;
        Serial.println("done file transfer");
        File file = SPIFFS.open("/pic.jpg");
        Serial.println(file.size());
        file.close();
      }
      
      break;
  } //end case 
} //end 




