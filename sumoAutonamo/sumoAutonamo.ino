#define DECODE_SONY
#include <IRremote.hpp>

// --- Pinos para o Driver DRV8833 ---
// Motor A (Direito)
#define AIN1 10
#define AIN2 9
// Motor B (Esquerdo)
#define BIN1 6
#define BIN2 5

// --- Pinos para os Sensores Ultrassônicos HC-SR04 ---
#define TRIG_E 2 // Trigger do sensor Esquerdo
#define ECHO_E 3 // Echo do sensor Esquerdo
#define TRIG_C 4 // Trigger do sensor Central
#define ECHO_C 7 // Echo do sensor Central
#define TRIG_D A0 // Trigger do sensor Direito
#define ECHO_D A1 // Echo do sensor Direito

// --- Configurações ---
#define VELOCIDADE 255
#define DISTANCIA_MAXIMA 40 // Distância em cm para considerar um oponente. Ajuste conforme necessário.

enum RobotStates
{
  standby,
  ready,
  fight,
};

RobotStates robotState = standby;

unsigned long blinkTimer;
bool ledOn;

void setup() {
  pinMode(13, OUTPUT); // LED on-board
  Serial.begin(9600);
  IrReceiver.begin(12); // Pino do receptor IR

  // Configura todos os pinos do motor como saída
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // --- Configura os pinos dos sensores ultrassônicos ---
  pinMode(TRIG_E, OUTPUT);
  pinMode(ECHO_E, INPUT);
  pinMode(TRIG_C, OUTPUT);
  pinMode(ECHO_C, INPUT);
  pinMode(TRIG_D, OUTPUT);
  pinMode(ECHO_D, INPUT);

  delay(1000);
  Serial.println("Robo inicializado. Aguardando comando...");
}

void loop() {
  IrReceive();
  Blink();
  Fight();
  Stop();
}

// --- Função para ler a distância de um sensor HC-SR04 ---
long lerDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.0343 / 2;
}


// --- Funções de Movimento Finais e Corrigidas ---

void Frente() {
  // Motor Direito (A) para frente
  analogWrite(AIN1, VELOCIDADE);
  digitalWrite(AIN2, LOW);
  // Motor Esquerdo (B) para frente (LÓGICA INVERTIDA)
  digitalWrite(BIN1, LOW);
  analogWrite(BIN2, VELOCIDADE);
}

void Tras() {
  // Motor Direito (A) para trás
  digitalWrite(AIN1, LOW);
  analogWrite(AIN2, VELOCIDADE);
  // Motor Esquerdo (B) para trás (LÓGICA INVERTIDA)
  analogWrite(BIN1, VELOCIDADE);
  digitalWrite(BIN2, LOW);
}

void Esquerda() { // Gira para a ESQUERDA (Motor Direito p/ Frente, Esquerdo p/ Trás)
  // Motor Direito (A) para frente
  analogWrite(AIN1, VELOCIDADE);
  digitalWrite(AIN2, LOW);
  // Motor Esquerdo (B) para trás (LÓGICA INVERTIDA)
  analogWrite(BIN1, VELOCIDADE);
  digitalWrite(BIN2, LOW);
}

void Direita() { // Gira para a DIREITA (Motor Esquerdo p/ Frente, Direito p/ Trás)
  // Motor Direito (A) para trás
  digitalWrite(AIN1, LOW);
  analogWrite(AIN2, VELOCIDADE);
  // Motor Esquerdo (B) para frente (LÓGICA INVERTIDA)
  digitalWrite(BIN1, LOW);
  analogWrite(BIN2, VELOCIDADE);
}

void PararMotores() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}


// --- Funções de Estado do Robô ---

void IrReceive()
{
  if (IrReceiver.decode())
  {
    IrReceiver.resume();
    switch (IrReceiver.decodedIRData.command)
    {
      case 0x0: // Exemplo de código IR para READY
        if (robotState == standby)
        {
          Serial.println("READY");
          robotState = ready;
        }
        break;
      case 0x1: // Exemplo de código IR para FIGHT
        if (robotState == ready)
        {
          Serial.println("FIGHT!");
          robotState = fight;
        }
        break;
      case 0x2: // Exemplo de código IR para STANDBY
        Serial.println("STANDBY");
        robotState = standby;
        break;
    }
  }
}

void Blink()
{
  if (robotState == ready)
  {
    PararMotores(); // Garante que o robô fique parado
    if (millis() / 250 > blinkTimer) // Pisca a cada 250ms
    {
      ledOn = !ledOn;
      digitalWrite(13, ledOn);
      blinkTimer = (millis() / 250);
    }
  }
}

void Fight()
{
  if (robotState == fight)
  {
    digitalWrite(13, HIGH); // LED aceso durante a luta

    long distE = lerDistancia(TRIG_E, ECHO_E);
    long distC = lerDistancia(TRIG_C, ECHO_C);
    long distD = lerDistancia(TRIG_D, ECHO_D);

    Serial.print("E: "); Serial.print(distE);
    Serial.print(" | C: "); Serial.print(distC);
    Serial.print(" | D: "); Serial.println(distD);

    if (distC > 0 && distC <= DISTANCIA_MAXIMA) {
      Serial.println("Oponente no CENTRO! ATACAR!");
      Frente();
    }
    else if (distE > 0 && distE <= DISTANCIA_MAXIMA) {
      Serial.println("Oponente a ESQUERDA! Virando...");
      Esquerda();
    }
    else if (distD > 0 && distD <= DISTANCIA_MAXIMA) {
      Serial.println("Oponente a DIREITA! Virando...");
      Direita();
    }
    else {
      Serial.println("Nenhum oponente a vista. Parado.");
      PararMotores();
    }
  }
}

void Stop()
{
  if (robotState == standby)
  {
    digitalWrite(13, LOW);
    PararMotores();
  }
}