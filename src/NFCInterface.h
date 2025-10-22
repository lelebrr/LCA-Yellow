#ifndef NFCINTERFACE_H
#define NFCINTERFACE_H

#include "configs.h"

#ifdef HAS_NFC
  #include <Wire.h>
  #include <PN532_I2C.h>
  #include <PN532.h>
  #include <NfcAdapter.h>

  class NFCInterface {
    public:
      NFCInterface();
      void init();
      void scan();
      void emulate();
      void main();

    private:
      PN532_I2C pn532_i2c;
      NfcAdapter nfc;
  };
#endif

#endif