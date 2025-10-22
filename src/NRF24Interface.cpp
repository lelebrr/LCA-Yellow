#include "NRF24Interface.h"

#ifdef HAS_NRF24

#include "Display.h"
extern Display display_obj;

NRF24Interface::NRF24Interface() : radio(NRF24_CE_PIN, NRF24_CSN_PIN) {
}

void NRF24Interface::init() {
  if (radio.begin()) {
    display_obj.tft.println("NRF24L01+ inicializado com sucesso.");
  } else {
    display_obj.tft.println("Falha ao inicializar NRF24L01+.");
  }
  radio.stopListening();
}

void NRF24Interface::scan() {
  display_obj.tft.println("Escaneando com NRF24L01+...");
  // Lógica de escaneamento aqui
  delay(2000);
  display_obj.tft.println("Escaneamento NRF concluído.");
}

void NRF24Interface::attack() {
  display_obj.tft.println("Atacando com NRF24L01+...");
  // Lógica de ataque aqui
  const byte address[6] = "00001";
  radio.openWritingPipe(address);
  char text[] = "Ataque NRF24";
  radio.write(&text, sizeof(text));
  display_obj.tft.println("Ataque NRF concluído.");
}

void NRF24Interface::main() {
  // Funções de loop para o NRF24, se necessário
}

#endif