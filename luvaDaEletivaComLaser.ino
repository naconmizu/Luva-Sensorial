#include <Wire.h>
#include <VL53L0X.h>

// Define pinos do LED e do buzzer
const int vibra = 13;
const int buzzerPin = 12;

// Cria objeto para o sensor VL53L0X
VL53L0X sensor;

void setup() {
  // Configuração dos pinos
  pinMode(vibra, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Inicia comunicação serial
  Serial.begin(9600);
  
  // Inicia o sensor de distância VL53L0X
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
}

void loop() {
  // Mede a distância em MM
  int distancia = sensor.readRangeContinuousMillimeters();
  
  // Exibe distância no monitor serial
  if (sensor.timeoutOccurred()) {
    Serial.println("Timeout");
  } else {
    Serial.print("Distância: ");
    Serial.print(distancia);
    Serial.println(" mm");
  }
  
  // Verificar a distância e acionar LED e buzzer
  if (distancia <= 100) { 
    digitalWrite(vibra, HIGH); // Acende o LED
    tone(buzzerPin, 1000); // Som de 1000 Hz
    delay(50); // Delay intermitente
    noTone(buzzerPin); // Para o som
    delay(50); // Delay intermitente 

    // A linha acima emite um som intermitente (ligado pro um certo tempo e apaga depois) quando a distancia for 10 cm (100 mm); 
    
  } else if (distancia <= 200) { // Entre 10 cm e 20 cm (100 mm e 200 mm)
     // Acende o Led
    noTone(buzzerPin); // Som de 1000 Hz contínuo
  } else if (distancia <= 500) { // Entre 20 cm e 50 cm (200 mm e 500 mm)
    digitalWrite(vibra, HIGH); // Acende o LED
    noTone(buzzerPin); // Som de 500 Hz contínuo
  } else {
    digitalWrite(vibria, LOW); // Apaga o LED
    noTone(buzzerPin); // Desativa o som
  }
ia 
  // Delay para evitar problemas
  delay(100);
}
