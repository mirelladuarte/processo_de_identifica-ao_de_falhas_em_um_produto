
#include <Servo.h>

// Pinos dos sensores
const int sensorPresenca = 2;
const int sensorFalha = 3;

// Servo motor
Servo atuador;
const int pinoServo = 9;

void setup() {
  pinMode(sensorPresenca, INPUT);
  pinMode(sensorFalha, INPUT);

  atuador.attach(pinoServo);
  atuador.write(0);  // posição inicial

  Serial.begin(9600);
}

void loop() {
  int presenca = digitalRead(sensorPresenca);
  int falha = digitalRead(sensorFalha);

  if (presenca == HIGH) {
    Serial.println("Produto detectado!");

    delay(300); // Pequeno atraso para estabilizar leitura do sensor de falha

    if (falha == HIGH) {
      Serial.println("⚠️ Falha detectada! Ativando atuador.");
      removerProdutoDefeituoso();
    } else {
      Serial.println("✅ Produto OK.");
    }

    delay(1000); // Tempo para o produto sair da zona de leitura
  }
}

void removerProdutoDefeituoso() {
  atuador.write(90); // Gira o braço do servo para empurrar produto
  delay(500);
  atuador.write(0); // Volta para posição inicial
  delay(500);
}
