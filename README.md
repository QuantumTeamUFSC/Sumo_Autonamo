# 🤖 Projeto Kami - Robô de Sumô Autônomo | QuantumTeamUFSC

Código-fonte do robô de sumô autônomo "Kami", desenvolvido pela equipe **Quantum Team** da UFSC para competições de robótica. O projeto utiliza uma placa Arduino para controlar dois motores DC e utiliza três sensores ultrassônicos para detectar e atacar o oponente de forma autônoma.

## 📝 Índice

- [Funcionalidades](#-funcionalidades)
- [Hardware Utilizado](#-hardware-utilizado)
- [Mapeamento de Pinos](#-mapeamento-de-pinos)
- [Como Usar](#-como-usar)
  - [Pré-requisitos](#pré-requisitos)
  - [Instalação](#instalação)
- [Modo de Operação](#-modo-de-operação)
- [Autores](#-autores)

## ✨ Funcionalidades

- **Controle por Estados:** O robô opera com uma máquina de estados simples (`standby`, `ready`, `fight`) para segurança e controle.
- **Detecção de Oponentes:** Utiliza três sensores ultrassônicos (Esquerda, Centro e Direita) para mapear a posição do oponente.
- **Lógica de Combate Autônoma:**
  - Se o oponente está à frente, o robô avança para atacar.
  - Se o oponente está em uma das laterais, o robô gira em sua direção.
  - Se nenhum oponente é detectado, o robô permanece parado, aguardando.
- **Controle Remoto IR:** Um controle infravermelho (protocolo SONY) é usado para iniciar e parar o robô durante a competição, alternando entre os estados.

## 🔌 Hardware Utilizado

- 1x Placa Arduino (Uno, Nano, ou similar)
- 1x Driver de Motor Duplo H-Bridge **DRV8833**
- 2x Motores DC com rodas
- 3x Sensores Ultrassônicos **HC-SR04**
- 1x Receptor Infravermelho (IR)
- 1x Bateria para alimentar o sistema

## 🗺️ Mapeamento de Pinos

A tabela abaixo descreve a conexão de cada componente aos pinos do Arduino, conforme definido no código.

| Componente                | Pino no Robô | Pino no Arduino |
| ------------------------- | ------------ | --------------- |
| **Driver DRV8833** |              |                 |
| Motor Direito (A)         | `AIN1`       | `10`            |
|                           | `AIN2`       | `9`             |
| Motor Esquerdo (B)        | `BIN1`       | `6`             |
|                           | `BIN2`       | `5`             |
| **Sensores HC-SR04** |              |                 |
| Sensor Esquerdo           | `TRIG_E`     | `2`             |
|                           | `ECHO_E`     | `3`             |
| Sensor Central            | `TRIG_C`     | `4`             |
|                           | `ECHO_C`     | `7`             |
| Sensor Direito            | `TRIG_D`     | `A0`            |
|                           | `ECHO_D`     | `A1`            |
| **Outros** |              |                 |
| Receptor IR               | `DATA`       | `12`            |
| LED On-board              | `LED_BUILTIN`| `13`            |

## 🚀 Como Usar

### Pré-requisitos

- [Arduino IDE](https://www.arduino.cc/en/software) instalado.
- Conhecimento básico de como carregar um código para uma placa Arduino.

### Instalação

1.  **Clone o repositório:**
    ```bash
    git clone [https://github.com/QuantumTeamUFSC/Sumo_Autonamo.git](https://github.com/QuantumTeamUFSC/Sumo_Autonamo.git)
    ```

2.  **Instale a Biblioteca Necessária:**
    Este projeto requer a biblioteca `IRremote`. Para instalá-la:
    - Abra a Arduino IDE.
    - Vá em `Tools` > `Manage Libraries...`.
    - Na barra de pesquisa, digite `IRremote`.
    - Procure pela biblioteca de **shirriff** ou **ArminJo** e clique em "Install".

3.  **Montagem e Upload:**
    - Monte o hardware seguindo o [Mapeamento de Pinos](#-mapeamento-de-pinos).
    - Conecte a placa Arduino ao seu computador.
    - Abra o arquivo do projeto na Arduino IDE.
    - Selecione a sua placa e a porta COM correta em `Tools`.
    - Clique no botão "Upload" para carregar o código.

## ⚙️ Modo de Operação

Após carregar o código, o robô iniciará no estado `standby`. Utilize um controle remoto infravermelho (padrão SONY) com os seguintes comandos para operar o robô:

| Comando no Controle | Código Hexadecimal | Ação do Robô                      | Estado Resultante |
| ------------------- | ------------------ | --------------------------------- | ----------------- |
| (Botão 1 - Exemplo) | `0x0`              | Prepara o robô para o combate     | `ready`           |
| (Botão 2 - Exemplo) | `0x1`              | Inicia o modo de luta autônoma    | `fight`           |
| (Botão 3 - Exemplo) | `0x2`              | Para o robô e volta ao modo inicial | `standby`         |

*No estado `ready`, o LED on-board piscará, indicando que aguarda o comando de início.*
*No estado `fight`, o LED on-board ficará aceso continuamente.*

## 👨‍💻 Autores

Este projeto foi desenvolvido pela equipe **Quantum Team** da Universidade Federal de Santa Catarina (UFSC).

---
> Sinta-se à vontade para abrir uma *Issue* caso encontre algum problema ou tenha sugestões de melhoria.
