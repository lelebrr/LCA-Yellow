# Relatório de Alterações e Pendências - LCA-Yellow

## Data da Última Atualização
21 de Outubro de 2025

## Resumo das Alterações Realizadas

Durante as últimas iterações, foram aplicadas diversas correções e refatorações no projeto LCA-Yellow para resolver erros de compilação e warnings, além de melhorar a compatibilidade e a organização do código. As principais alterações incluem:

*   **Substituição de `LinkedList` por `std::vector`:** Em vários arquivos (`Display.h`, `Display.cpp`, `WiFiScan.h`, `WiFiScan.cpp`, `EvilPortal.h`, `EvilPortal.cpp`, `SDInterface.h`, `SDInterface.cpp`), todas as instâncias da biblioteca `LinkedList` foram substituídas por `std::vector` do C++ Standard Library. Esta mudança visa melhorar a estabilidade, desempenho e compatibilidade do código, além de remover uma dependência externa que estava causando conflitos.
*   **Correção de Erros de Declaração de `calData`:** No arquivo `Display.cpp`, a declaração da variável `calData` foi ajustada para garantir que estivesse visível em todo o escopo da função `RunSetup`, resolvendo um erro de compilação relacionado a `tft.setTouch(calData);`.
*   **Correção de Tipos Conflitantes na Função `minimum`:** No arquivo `Display.cpp`, o erro de tipos conflitantes para a função `minimum` foi resolvido com a adição de `casts` explícitos.
*   **Correção de Warnings de `#ifdef`:** No arquivo `MenuFunctions.cpp`, warnings relacionados a diretivas `#ifdef` mal formatadas foram corrigidos.
*   **Correção de Declaração de Pinos NRF24:** No arquivo `NRF24Interface.cpp`, a declaração dos pinos NRF24 foi corrigida para usar as definições corretas de `configs.h`.
*   **Remoção da Dependência `ivanseidel/LinkedList`:** A dependência `ivanseidel/LinkedList` foi removida do arquivo `platformio.ini` para evitar conflitos com a nova abordagem baseada em `std::vector`.
*   **Correção de Warnings de Conversão de String Literal:** Em `Display.cpp` e `WiFiScan.h`, warnings de conversão de string literal para `char*` foram resolvidos, adicionando `const` para compatibilidade com C++.
*   **Definição de `TOUCH_CS`:** No arquivo `configs.h`, foi adicionada uma definição para `TOUCH_CS` com um pino não utilizado, a fim de suprimir um warning da biblioteca `TFT_eSPI` relacionado à falta de definição do pino de touch.
*   **Correção de Erro `expected declaration before } token`:** No arquivo `WiFiScan.cpp`, um erro de sintaxe relacionado a um `}` extra foi corrigido na função `sendDeauthAttack`.
*   **Substituição de `MARAUDER_VERSION` por `LCA_VERSION`:** No arquivo `WiFiScan.cpp`, todas as ocorrências de `MARAUDER_VERSION` foram substituídas por `LCA_VERSION` para padronização.
*   **Reinstalação da Biblioteca `NimBLE-Arduino`:** A dependência `NimBLE-Arduino` foi removida e reinstalada no `platformio.ini` para garantir o uso da versão mais recente e resolver problemas de assinatura de função com `setAdvertisedDeviceCallbacks`.

## Pendências Conhecidas

1.  **Erros de `NimBLEScan::setAdvertisedDeviceCallbacks`:** Apesar da reinstalação da biblioteca `NimBLE-Arduino`, ainda persistem erros de compilação relacionados a `NimBLEScan::setAdvertisedDeviceCallbacks` em `WiFiScan.cpp`. Isso pode indicar uma mudança na API da biblioteca ou um uso incorreto que precisa ser investigado mais a fundo. É necessário verificar a documentação da versão atual da biblioteca e ajustar as chamadas de função conforme necessário.
2.  **Warning `DynamicJsonDocument` é depreciado:** O warning sobre `DynamicJsonDocument` ser depreciado em favor de `JsonDocument` ainda está presente. Embora não seja um erro crítico, é recomendável atualizar o código para usar a classe `JsonDocument` para manter a compatibilidade futura e seguir as melhores práticas da biblioteca `ArduinoJson`.
3.  **`Display.cpp:6: error: unterminated #ifdef`:** Este erro indica um problema com o balanceamento das diretivas `#ifdef` no arquivo `Display.cpp`. É preciso revisar o arquivo para garantir que todas as diretivas `#ifdef` tenham um `#endif` correspondente e que o aninhamento esteja correto.
4.  **Warnings de Conversão `char*` em `Display.cpp`:** Embora algumas conversões de string literal para `char*` tenham sido corrigidas, ainda existem warnings semelhantes em `Display.cpp`. É importante revisar todas as chamadas `initButton` e outras funções que aceitam `char*` para garantir que `const char*` seja usado ou que os `casts` sejam aplicados corretamente para evitar `warnings` e potenciais `bugs`.

## Próximos Passos

Os próximos passos devem focar na resolução das pendências listadas acima, começando pelos erros de compilação mais críticos e, em seguida, abordando os warnings para garantir um código limpo e funcional. A compilação do projeto deve ser realizada após cada conjunto de correções para verificar a eficácia das mudanças.
