/*
    ESP-NOW Broadcast Receiver
    Lucas Saavedra Vaz - 2024

    This sketch demonstrates how to receive broadcast messages from a master device using the ESP-NOW protocol.

    The sender device will broadcast a message every 5 seconds to all devices within the network.

    The receiver devices will receive the broadcasted messages. If they are not from a known sender, they will be registered as a new sender
    using a callback function.
*/

#define CHANNEL 1
#include <SPIFFS.h>

#include <esp_now_functions.h>
#include <wifi_functions.h>
// #include <telegram_functions.h>

int currentTransmitCurrentPosition = 0;
int currentTransmitTotalPackages = 0;
byte showImage = 0;
byte awaitImage = 1;



void setup() {
  Serial.begin(115200);
  Serial.println("ESPNow/Sender/Receiver Example");

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
    delay(5000);
    Serial.printf("In the first loop");
    // InitESPNow();

    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info.
    // esp_now_register_recv_cb(OnDataRecv);
    }

  // if show image flag
  if (showImage)
  {
    showImage = 0;
    unsigned long start = millis();
    InitWiFi();
    delay(5000);
    Serial.printf("Time used: %lu\n", millis() - start);
    awaitImage = 1;
  }
}



// callback when data is recv from Master
void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *data, int data_len) {
  const uint8_t *mac_addr = recv_info->src_addr;
  
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




