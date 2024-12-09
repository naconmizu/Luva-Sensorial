#include <Wire.h>
#include <VL53L0X.h>

// Definir pinos do LED e buzzer
const int vibra = 13;
const int buzzerPin = 12;

// Criar objeto para o sensor VL53L0X
VL53L0X sensor;

void setup() {
  // Configuração dos pinos
  pinMode(vibra, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Iniciar comunicação serial para monitorar valores
  Serial.begin(9600);
  
  // Iniciar o sensor de distância VL53L0X
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
}

void loop() {
  // Medir a distância em milímetros
  int distance = sensor.readRangeContinuousMillimeters();
  
  // Exibir distância no monitor serial
  if (sensor.timeoutOccurred()) {
    Serial.println("Timeout");
  } else {
    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.println(" mm");
  }
  
  // Verificar a distância e acionar LED e buzzer
  if (distance <= 100) { // Menos de 10 cm (100 mm)
    digitalWrite(vibra, HIGH); // Acende o LED
    tone(buzzerPin, 1000); // Som de 1000 Hz
    delay(50); // Delay intermitente
    noTone(buzzerPin); // Para o som
    delay(50); // Delay intermitente
  } else if (distance <= 200) { // Entre 10 cm e 20 cm (100 mm e 200 mm)
     // Acende o LED
    noTone(buzzerPin); // Som de 1000 Hz contínuo
  } else if (distance <= 500) { // Entre 20 cm e 50 cm (200 mm e 500 mm)
    digitalWrite(vibra, HIGH); // Acende o LED
    noTone(buzzerPin); // Som de 500 Hz contínuo
  } else {
    digitalWrite(vibra, LOW); // Apaga o LED
    noTone(buzzerPin); // Desativa o som
  }
  
  // Pequeno delay antes da próxima medição
  delay(100);
}
