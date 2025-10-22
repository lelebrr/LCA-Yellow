#include "FeedbackInterface.h"
#include <Arduino.h>

#define BUZZER_CHANNEL 0 // Canal LEDC para o buzzer

FeedbackInterface::FeedbackInterface() {}

void FeedbackInterface::begin() {
  #ifdef HAS_BUZZER_LED
    ledcSetup(BUZZER_CHANNEL, 5000, 8); // Configura o canal LEDC
    pinMode(BUZZER_LED_PIN, OUTPUT);
    Serial.println("Interface de Feedback (Buzzer/LED) inicializada.");
  #endif

  #ifdef HAS_SPEAKER
    pinMode(SPEAKER_PIN, OUTPUT);
    Serial.println("Interface de Feedback (Speaker) inicializada.");
  #endif
}

#ifdef HAS_BUZZER_LED
void FeedbackInterface::buzz(int frequency, int duration) {
  ledcAttachPin(BUZZER_LED_PIN, BUZZER_CHANNEL);
  ledcWriteTone(BUZZER_CHANNEL, frequency);
  delay(duration);
  ledcDetachPin(BUZZER_LED_PIN);
  digitalWrite(BUZZER_LED_PIN, LOW);
}

void FeedbackInterface::ledOn() {
  digitalWrite(BUZZER_LED_PIN, HIGH);
}

void FeedbackInterface::ledOff() {
  digitalWrite(BUZZER_LED_PIN, LOW);
}
#endif

#ifdef HAS_SPEAKER
void FeedbackInterface::playTone(int frequency, int duration) {
    // Implementação simples usando DAC. Para áudio complexo, precisaríamos de mais.
    // Esta é uma aproximação de tom, não uma onda senoidal perfeita.
    const int sampleRate = 8000;
    int numSamples = duration * sampleRate / 1000;
    for (int i = 0; i < numSamples; i++) {
        dacWrite(SPEAKER_PIN, 128 + 127 * sin(2 * PI * frequency * i / sampleRate));
        delayMicroseconds(1000000 / sampleRate);
    }
    dacWrite(SPEAKER_PIN, 0); // Desliga o DAC
}
#endif
