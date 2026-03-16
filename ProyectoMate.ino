#define RELAY_PIN 5
#define BUTTON_PIN 23
#define TRIG_PIN 18
#define ECHO_PIN 19

// VARIABLE PARA REGULAR LA ALTURA (en centímetros)
int distanciaLimite = 20; 

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  digitalWrite(RELAY_PIN, LOW);
  Serial.begin(115200); // Para que puedas ver la distancia en el monitor serie
}

void loop() {
  long duracion;
  int distancia;

  // --- LÓGICA DEL SENSOR ULTRASONIDO ---
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duracion = pulseIn(ECHO_PIN, HIGH);
  distancia = duracion * 0.034 / 2; // Calcula la distancia en cm

  // Monitor serie para que calibres tu "variable de altura"
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // --- CONDICIÓN DOBLE ---
  // El relé se activa SOLO si:
  // 1. El botón está presionado (LOW)
  // 2. La distancia es menor al límite (Objeto detectado)
  
  if (digitalRead(BUTTON_PIN) == LOW && distancia < distanciaLimite && distancia > 0) {
    digitalWrite(RELAY_PIN, HIGH); 
  } else {
    digitalWrite(RELAY_PIN, LOW);  
  }
  
  delay(100); // Un pequeño respiro para el sensor
}