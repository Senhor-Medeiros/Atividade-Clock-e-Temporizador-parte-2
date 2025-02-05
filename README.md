# Projeto 6-B: Temporizador de Disparo com Raspberry Pi Pico
EMBARCATECH - UNIDADE 04

## Desenvolvedor
Desenvolvido pelo aluno Eduardo Medeiros Magalhães

## Links:
- Vídeo no YouTube da execução no simulador Wokwi integrado ao VSCode: https://youtu.be/Nw4VQusfNOM
- Vídeo no Youtube da execução na placa Bidoglab: 

## Descrição do Projeto
Este projeto implementa um sistema de temporização para o acionamento de LEDs no Raspberry Pi Pico W. A ativação ocorre através de um botão (pushbutton), e os LEDs desligam sequencialmente com um atraso de 3 segundos entre cada estado.

## Funcionalidades
- **Pressionamento do botão**: Todos os LEDs acendem.
- **Sequência de desligamento**:
  - O LED verde apaga após 3 segundos.
  - O LED azul apaga após mais 3 segundos.
  - O LED vermelho apaga após mais 3 segundos.
- **Bloqueio do botão**: Enquanto a sequência está em andamento, novos acionamentos não são permitidos.
- **Mensagens na porta serial**: O estado dos LEDs é exibido a cada alteração.

## Hardware Utilizado
- **Raspberry Pi Pico W**
- **3 LEDs**:
  - LED vermelho conectado ao GPIO 13
  - LED azul conectado ao GPIO 12
  - LED verde conectado ao GPIO 11
- **1 botão (Pushbutton) conectado ao GPIO 5**
- **3 resistores de 330Ω**
- **Conexões ao GND**: Todos os LEDs conectados ao pino GND do Raspberry Pi Pico.

## Esquema de Ligações
### Configuração dos LEDs:
- **GPIO 13** → Resistor → LED Vermelho → GND
- **GPIO 12** → Resistor → LED Azul → GND
- **GPIO 11** → Resistor → LED Verde → GND
- **GPIO 5** → Botão → GND

## Pré-requisitos
### 1. Ferramentas Necessárias:
- Ambiente de desenvolvimento **VS Code** configurado com o **Pico SDK**.
- Ferramenta para monitorar a porta serial (ex: Terminal Serial no VS Code).

### 2. Configuração do VS Code:
- Certifique-se de que o **Pico SDK** está corretamente configurado.
- O **CMake** e o **compilador ARM GCC** devem estar instalados.

## Instruções para Compilação e Execução
1. Clone ou copie este repositório para o seu ambiente de desenvolvimento.
2. Navegue até a pasta do projeto.
3. Configure o build com o CMake:
   ```sh
   mkdir build && cd build
   cmake ..
   ```
4. Compile o programa:
   ```sh
   make
   ```
5. Carregue o binário gerado no Raspberry Pi Pico W.
6. Abra um terminal serial para monitorar as mensagens enviadas pelo programa.

## Resultados Esperados
### 1. Quando o sistema é iniciado:
- O terminal exibe a mensagem: **"Sistema de temporização de LEDs iniciado."**
- O sistema aguarda a pressão do botão.

### 2. Durante a execução:
- Quando o botão é pressionado, os três LEDs acendem simultaneamente.
- Após 3 segundos, o LED verde desliga.
- Após mais 3 segundos, o LED azul desliga.
- Após mais 3 segundos, o LED vermelho desliga.
- O terminal exibe mensagens indicando cada transição de estado.

## Simulação no BitDogLab
O projeto pode ser testado no **BitDogLab**, onde:
- **LED vermelho**: GPIO 13.
- **LED azul**: GPIO 12.
- **LED verde**: GPIO 11.
- **Botão**: GPIO 5.

### Observações:
- Certifique-se de que os LEDs estão corretamente configurados com resistores de 330Ω.
- A execução na **BitDogLab** pode apresentar diferenças visuais devido à representação das cores dos LEDs.

---
**Desenvolvido por:** Eduardo Medeiros Magalhães

