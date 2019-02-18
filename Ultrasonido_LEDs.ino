#define MEDIA_VELOCIDAD_SONIDO 0.017175 // Mitad de la velocidad del sonido a 20 °C expresada en cm/µs
#define ESPERA_ENTRE_LECTURAS 1000 // tiempo entre lecturas consecutivas en milisegundos
#define TIMEOUT_PULSO 25000 // la espera máxima de es 30 ms o 30000 µs

const int pinEcho = 6;
const int pinTrigger = 7;
const int pinLEDGreen = 12;

float distancia;
unsigned long tiempo;
unsigned long cronometro;
unsigned long reloj=0;
 
void setup()
{
  Serial.begin(9600);
  pinMode(pinEcho,INPUT);
  pinMode(pinTrigger,OUTPUT);
  pinMode(pinLEDGreen, OUTPUT);
  digitalWrite(pinTrigger,LOW); // Para «limpiar» el pulso del pin trigger del módulo
  delayMicroseconds(2);
}
 
void loop()
{
  //cronometro=millis()-reloj;
  //if(cronometro>ESPERA_ENTRE_LECTURAS)
  //{
    digitalWrite(pinTrigger,HIGH); // Un pulso a nivel alto…
    delayMicroseconds(10); // …durante 10 µs y
    digitalWrite(pinTrigger,LOW); // …volver al nivel bajo
    tiempo=pulseIn(pinEcho,HIGH,TIMEOUT_PULSO); // Medir el tiempo que tarda en llegar un pulso
    distancia=MEDIA_VELOCIDAD_SONIDO*tiempo;
    Serial.print(distancia);
    Serial.println(" cm");
    if (distancia > 20.0){
      digitalWrite(pinLEDGreen, HIGH);
    }else{
      digitalWrite(pinLEDGreen, LOW);
    }
  //  reloj=millis();
  //}
}
