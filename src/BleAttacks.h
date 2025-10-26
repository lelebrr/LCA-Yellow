#ifndef BLEATTACKS_H
#define BLEATTACKS_H

#include <Arduino.h>

class BleAttacks {
public:
    BleAttacks();

    void bleSpamFlood();
    void sourAppleAttack();
    void swiftPairSpam();
    void airTagSpoofing();
    void bleBeaconFlood();
    void connectionSpam();
    void serviceDiscoveryDoS();
    void notificationFlood();
    void flipperZeroSpoof();
    void ccSkimmerDetect();
    void batteryDrainAttack();
    void uuidFlood();
    void advertisingIntervalDoS();
    void legacyBleFlood();
    void extendedAdvFlood();
    void manufacturerSpam();
    void rssiManipulation();
    void periodicAdvFlood();
    void gattWriteFlood();
    void readRequestFlood();
    void disconnectFlood();
    void mtuNegotiationDoS();
    void securityManagerDoS();
    void l2capEchoFlood();
    void scanRequestFlood();
    void deviceNameSpoof();
    void appearanceSpoof();
    void txPowerSpoof();
    void channelMapDoS();
    void leCodedPhyFlood();
};

#endif // BLEATTACKS_H
