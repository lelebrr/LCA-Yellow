# LCA Toolkit

<p align="center">
  <img alt="LCA Toolkit logo" src="https://github.com/lelebrr/LCA-Yellow/raw/main/img/lca_logo_ascii.png" width="300">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/version-2.0.0--dev-blue?style=flat" alt="Version Badge" />
  <img src="https://img.shields.io/badge/status-in--development-yellow?style=flat" alt="Status Badge" />
</p>

O objetivo deste projeto é criar uma ferramenta de pentesting poderosa e customizável, baseada no hardware "Cheap Yellow Display" (CYD), com uma interface totalmente gráfica, em português do Brasil, e com suporte extensivo a módulos de hardware adicionais.

---

## 🏴‍☠️ Funcionalidades Atuais 🏴‍☠️

- **Interface Gráfica Completa (GUI):** Interface totalmente redesenhada, com elementos gráficos baseados em ASCII, menus, botões e telas de status.
- **Tradução para Português (pt-BR):** Todos os menus, mensagens e logs estão em português do Brasil.
- **Suporte Extensivo ao Cartão SD:**
    - Armazenamento de logs, configurações e relatórios.
    - Geração de relatórios detalhados de atividades.
    - Gerenciador de arquivos integrado na UI.
- **Alta Customização:**
    - Personalização de cores, fontes e temas (dark/light mode).
    - Configurações salvas no cartão SD para persistência.
- **Foco em Segurança e Ética:**
    - Tela de confirmação com aviso legal antes de iniciar ataques.
    - Logging detalhado de todas as operações.
- **Funcionalidades de Pentest:**
    - Ferramentas de análise e ataque WiFi e Bluetooth.
    - Detecção de Pwnagotchi, Spam BLE, Wardriving e mais.

---

## Módulos de Hardware Suportados

### GPS
A funcionalidade de GPS é suportada através do conector de 4 pinos próximo à porta MicroUSB.

| GPS | -> | CYD |
|-----|:--:|-----|
| VCC | -> | VIN |
| GND | -> | GND |
| TX  | -> | TX  |
| RX  | -> | RX  |

*Nota: Em modelos de 2.4" e 3.5", inverta RX/TX.*

### Módulo NRF24L01+
- **Função:** Adiciona capacidades de sniffing e ataque em redes de 2.4GHz customizadas (ex: mouses/teclados sem fio).
- **Status:** Suporte básico implementado. Funções de scan e ataque disponíveis no menu.

### Módulo NFC PN532
- **Função:** Permite a leitura e emulação de tags NFC (13.56MHz).
- **Status:** Suporte básico implementado. Funções de scan e emulação de tag disponíveis no menu.

---

## Instalação

As instruções de instalação serão fornecidas em uma versão futura. Por enquanto, o desenvolvimento e flash devem ser feitos via PlatformIO ou Arduino IDE.

---

## Compatibilidade

O projeto foi testado com sucesso em diversas variantes do "Cheap Yellow Display". A lista completa será atualizada futuramente.

---

## Agradecimentos

Um agradecimento especial a **JustCallMeKoko** pelo trabalho fundamental no [ESP32Marauder](https://github.com/justcallmekoko/ESP32Marauder) e a todos os contribuidores da comunidade open-source que tornaram este projeto possível.

---

## Aviso Legal

Este projeto destina-se exclusivamente a fins educacionais e profissionais de pentesting. Sempre obtenha autorização por escrito antes de realizar testes em redes que não lhe pertencem ou para as quais você não tem permissão explícita. O uso indevido desta ferramenta é de sua inteira responsabilidade.
