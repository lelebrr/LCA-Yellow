#include "GestureInterface.h"
#include <Wire.h>

#ifdef HAS_PAJ7620_GESTURE

GestureInterface::GestureInterface() {
  currentGesture = GES_NONE;
}

void GestureInterface::begin() {
  if (!paj7620.begin()) {
    Serial.println("Erro: Falha ao inicializar o sensor de gestos PAJ7620.");
  } else {
    Serial.println("Sensor de gestos PAJ7620 inicializado com sucesso.");
  }
}

void GestureInterface::main() {
  Gesture gesture = getGesture();
  // A lógica principal pode ser adicionada aqui se precisarmos de atualizações contínuas
}

Gesture GestureInterface::getGesture() {
  Gesture gesture_code = paj7620.readGesture();
  currentGesture = GES_NONE;

  switch (gesture_code) {
    case GES_UP:
      currentGesture = GES_UP;
      break;
    case GES_DOWN:
      currentGesture = GES_DOWN;
      break;
    case GES_LEFT:
      currentGesture = GES_LEFT;
      break;
    case GES_RIGHT:
      currentGesture = GES_RIGHT;
      break;
    case GES_FORWARD:
      currentGesture = GES_FORWARD;
      break;
    case GES_BACKWARD:
      currentGesture = GES_BACKWARD;
      break;
    case GES_CLOCKWISE:
      currentGesture = GES_CLOCKWISE;
      break;
    case GES_ANTICLOCKWISE:
      currentGesture = GES_ANTICLOCKWISE;
      break;
    case GES_WAVE:
      currentGesture = GES_WAVE;
      break;
    default:
      break;
  }
  return currentGesture;
}

String GestureInterface::gestureToString(Gesture gesture) {
    switch (gesture) {
        case GES_UP: return "Cima";
        case GES_DOWN: return "Baixo";
        case GES_LEFT: return "Esquerda";
        case GES_RIGHT: return "Direita";
        case GES_FORWARD: return "Frente";
        case GES_BACKWARD: return "Tras";
        case GES_CLOCKWISE: return "Horario";
        case GES_ANTICLOCKWISE: return "Anti-horario";
        case GES_WAVE: return "Onda";
        default: return "";
    }
}

#endif
