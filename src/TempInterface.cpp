#include "TempInterface.h"
#include <Arduino.h>

TempInterface::TempInterface() {
  currentTempC = -127.0; // Valor inicial para indicar erro ou não lido
}

void TempInterface::begin() {
  #ifdef HAS_DS18B20_TEMP
    oneWire = new OneWire(DS18B20_PIN);
    sensors = new DallasTemperature(oneWire);
    sensors->begin();
    Serial.println("Interface do sensor de temperatura DS18B20 inicializada.");
  #endif
}

void TempInterface::main() {
  #ifdef HAS_DS18B20_TEMP
    // A leitura pode ser demorada, então não a executamos a cada loop.
    // Uma abordagem melhor seria usar um temporizador, mas por enquanto,
    // a leitura pode ser chamada sob demanda ou em intervalos maiores.
    sensors->requestTemperatures();
    currentTempC = sensors->getTempCByIndex(0);
  #endif
}

float TempInterface::getTempC() {
  #ifdef HAS_DS18B20_TEMP
    // Solicita a leitura e a retorna.
    sensors->requestTemperatures();
    currentTempC = sensors->getTempCByIndex(0);
    if (currentTempC == DEVICE_DISCONNECTED_C) {
      Serial.println("Erro: Nao foi possivel ler a temperatura do sensor DS18B20.");
      return -127.0;
    }
    return currentTempC;
  #else
    return -127.0; // Retorna valor de erro se o hardware não estiver ativado
  #endif
}
