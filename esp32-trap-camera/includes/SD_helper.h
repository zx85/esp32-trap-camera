#pragma once
#include "FS.h"
#include "SD_MMC.h"


// SD card


#define SD_MMC_CMD 38 //Please do not modify it.
#define SD_MMC_CLK 39 //Please do not modify it.
#define SD_MMC_D0 40 //Please do not modify it.

// SD card
#pragma once
#include "FS.h"
#include "SD_MMC.h"

// Initialize SD_MMC in 1-bit or 4-bit mode
inline bool initSDMMC(bool mode1bit = true, const char* mountpoint = "/sdcard") {
    Serial.println("[SD_MMC] Initializing...");

    // Configure pins (needed if you’re freeing GPIOs in 1-bit mode)
    if (!SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0)) {
        Serial.println("Failed to set SD_MMC pins!");
        return false;
    }

    // Mount the card
    if (!SD_MMC.begin(mountpoint, mode1bit)) {
        Serial.println("SD Card Mount Failed");
        return false;
    }

    // Detect card type
    uint8_t cardType = SD_MMC.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("No SD Card attached");
        return false;
    }

    Serial.print("SD_MMC Card Type: ");
    if (cardType == CARD_MMC) {
        Serial.println("MMC");
    } else if (cardType == CARD_SD) {
        Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    // Report card size
    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);

    return true;
}
