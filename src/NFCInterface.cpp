#include "NFCInterface.h"

#ifdef HAS_NFC

#include "Display.h"
extern Display display_obj;

NFCInterface::NFCInterface() : pn532_i2c(Wire), nfc(pn532_i2c) {
}

void NFCInterface::init() {
  nfc.begin();
  display_obj.tft.println("Módulo NFC PN532 inicializado.");
}

void NFCInterface::scan() {
  display_obj.tft.println("Escaneando tags NFC...");
  if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    display_obj.tft.print("Tag encontrada: ");
    display_obj.tft.println(tag.getUidString());
  } else {
    display_obj.tft.println("Nenhuma tag NFC encontrada.");
  }
}

void NFCInterface::emulate() {
  display_obj.tft.println("Emulando tag NFC...");
  // Lógica de emulação de tag aqui
}

void NFCInterface::main() {
  // Funções de loop para o NFC, se necessário
}

#endif