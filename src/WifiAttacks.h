#ifndef WIFIATTACKS_H
#define WIFIATTACKS_H

#include <Arduino.h>

class WifiAttacks {
public:
    WifiAttacks();

    void deauthenticationFlood();
    void eapolHandshakeCapture();
    void pmkidAttack();
    void evilTwinAP();
    void karmaAttack();
    void channelFlood();
    void disassociationFlood();
    void authenticationFlood();
    void nullDataFrameFlood();
    void probeResponseFlood();
    void ctsRtsFlood();
    void beaconSpam();
    void qosNullFlood();
    void associationFlood();
    void wpsPixieDust();
    void fakeAPDoS();
    void ackFlood();
    void channelSwitchAnnouncement();
    void ssidConfusion();
    void managementFrameDoS();
    void powerSaveAttack();
    void fragmentationAttack();
    void baPSFlood();
    void clientIsolationBypass();
    void wpa3SaeDowngrade();
    void beaconTimingAttack();
    void probeRequestFlood();
    void dtimDoS();
    void countryCodeAttack();
    void vendorSpecificDoS();

    // Ataques WPS
    void wpsBruteForce();
    void wpsLockBypass();
    void onlineWPSAttack();
    void wpsFlood();
    void pinCheckBypass();
    void wpsSessionFlood();
    void wpsDeauthAndPixie();
    void wpsConfigReload();
    void wpsDictionary();
};

#endif // WIFIATTACKS_H
