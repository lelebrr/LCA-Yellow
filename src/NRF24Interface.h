#ifndef NRF24INTERFACE_H
#define NRF24INTERFACE_H

#include "configs.h"

#ifdef HAS_NRF24
  #include <SPI.h>
  #include <RF24.h>

  class NRF24Interface {
    public:
      NRF24Interface();
      void init();
      void scan();
      void attack();
      void main();

    private:
      RF24 radio;
  };
#endif

#endif