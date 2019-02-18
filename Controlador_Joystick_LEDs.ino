/*
GND - GND
Vcc - 5v
VRx - A0
VRy - A1
SW -  D9
*/
 

const int pinLEDGreen1 = 2;
const int pinLEDGreen2 = 3;
const int pinLEDGreen3 = 4;
const int pinLEDGreen4 = 5;
const int pinJoyX = A0;
const int pinJoyY = A1;
const int pinJoyButton = 9;
 
void setup() {
   pinMode(pinLEDGreen1, OUTPUT);
   pinMode(pinLEDGreen2, OUTPUT);
   pinMode(pinLEDGreen3, OUTPUT);
   pinMode(pinLEDGreen4, OUTPUT);
   pinMode(pinJoyButton , INPUT_PULLUP);   //activar resistencia pull up 
   Serial.begin(9600);
}
 
void loop() {
   int Xvalue = 0;
   int Yvalue = 0;
   bool buttonValue = false;
 
   //leer valores
   Xvalue = analogRead(pinJoyX);
   delay(100);                 //es necesaria una pequeña pausa entre lecturas analógicas
   Yvalue = analogRead(pinJoyY);
   buttonValue = digitalRead(pinJoyButton);
 
   //mostrar valores por serial
   Serial.print("X:" );
   Serial.print(Xvalue);
   Serial.print(" | Y: ");
   Serial.print(Yvalue);
   Serial.print(" | Pulsador: ");
   Serial.println(buttonValue);
   if (Xvalue < 450){
      digitalWrite(pinLEDGreen1, HIGH);
      digitalWrite (pinLEDGreen2, LOW);
      digitalWrite (pinLEDGreen3, LOW);
      digitalWrite (pinLEDGreen4, LOW);
   }else if (Xvalue > 550){
      digitalWrite(pinLEDGreen3, HIGH);
      digitalWrite (pinLEDGreen1, LOW);
      digitalWrite (pinLEDGreen2, LOW);
      digitalWrite (pinLEDGreen4, LOW);
   }else if (Yvalue < 450){
      digitalWrite(pinLEDGreen2, HIGH);
      digitalWrite (pinLEDGreen1, LOW);
      digitalWrite (pinLEDGreen3, LOW);
      digitalWrite (pinLEDGreen4, LOW);
   }else if (Yvalue > 550){
      digitalWrite(pinLEDGreen4, HIGH);
      digitalWrite (pinLEDGreen1, LOW);
      digitalWrite (pinLEDGreen2, LOW);
      digitalWrite (pinLEDGreen3, LOW);
   }
   delay(200);
}
