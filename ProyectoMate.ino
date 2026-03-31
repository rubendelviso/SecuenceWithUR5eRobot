#define RELAY_PIN 5 //Señal Brazo Robot IN2
#define BUTTON_PIN 23
#define TRIG_PIN 18
#define ECHO_PIN 19

#define LUZ_R 27 //Señal Brazo Robot 
#define LUZ_B 26 //Señal Brazo Robot
#define LUZ_G 25 //Señal Brazo Robot
// VARIABLE PARA REGULAR LA ALTURA (en centímetros)
int distanciaLimite = 20; 
int timerSecuencia = 7500; //6320 es la primera medicion de tiempo. Siendo este todo lo que tarda en agarrar la pieza
bool procesoActivo = false;
unsigned long tiempoInicio = 0;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  // pinMode(LUZ_LED, OUTPUT);
  pinMode(LUZ_R, OUTPUT);
  pinMode(LUZ_G, OUTPUT);
  pinMode(LUZ_B, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  digitalWrite(RELAY_PIN, LOW); //Señal para brazo Robot
  digitalWrite(LUZ_R, LOW);
  digitalWrite(LUZ_G, LOW);
  digitalWrite(LUZ_B, LOW);
  Serial.begin(115200); // Para que puedas ver la distancia en el monitor serie
}
// void PrenderLedIntermitente(){
//   Serial.println("Prendiendo TiraLed");
//   digitalWrite(LUZ_LED,LOW);
//   delay(1500);
//   digitalWrite(LUZ_LED,HIGH);
//   delay(1500);
// }
void pruebaTiraled(){
  delay(1000);
  digitalWrite(LUZ_R,HIGH);
  delay(3000);
  digitalWrite(LUZ_R,LOW);
  delay(1000);
  
  digitalWrite(LUZ_G,HIGH);
  delay(3000);
  digitalWrite(LUZ_G,LOW);
  




}
void PrenderLuzLed(int estadoLed){
  digitalWrite(LUZ_R, LOW);
  digitalWrite(LUZ_G, LOW);
  digitalWrite(LUZ_B, LOW);
  
  digitalWrite(estadoLed,HIGH);

  
  //if (digitalRead(BUTTON_PIN)==HIGH) digitalWrite(estadoLed,HIGH); 
  
}
void loop() {
  long duracion;
  int distancia;
  // digitalWrite(LUZ_LED,HIGH);
  // --- LÓGICA DEL SENSOR ULTRASONIDO ---
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  //Apago Todos los leds, vuelvo a evaluar
  // digitalWrite(LUZ_B,LOW);
  // digitalWrite(LUZ_R,LOW);
  // digitalWrite(LUZ_G,LOW);
  
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
  
  if (!procesoActivo && digitalRead(BUTTON_PIN) == LOW && distancia < distanciaLimite && distancia > 0) {
    procesoActivo = true;
    tiempoInicio = millis();
    //PrenderLedIntermitente();
    //pruebaTiraled(); //SimplePrueba
    
    digitalWrite(RELAY_PIN, HIGH);
    
     
    // delay(timerSecuencia);
    //digitalWrite(RELAY_PIN, LOW);//Sugerido por el chat
    //procesoActivo = false;
  } 
  if (procesoActivo) {
    PrenderLuzLed(LUZ_G); // verde durante proceso

    // 👉 ¿ya pasó el tiempo?
    if (millis() - tiempoInicio >= timerSecuencia) {
      
      digitalWrite(RELAY_PIN, LOW);
      procesoActivo = false; // termina el proceso
    }
  }

  // 🔹 CUANDO NO ESTÁ ACTIVO
  if (!procesoActivo) {
    PrenderLuzLed(LUZ_R); // rojo en reposo
  }

  delay(100);
}