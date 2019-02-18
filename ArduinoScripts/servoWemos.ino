#include <ESP8266WiFi.h>
#include <Servo.h>
Servo myservo;

#define PIN   D5
#define LED_NUM 7
int Motor_state = 2;

//const char* ssid = "MiFibra-E620";
//const char* password = "gVJpwhs5";
const char* ssid = "AndroidAP";
const char* password = "tgrj9296";

WiFiServer server(80); //objeto servidor que inicializaremos en el puerto 80
 
void setup() {
  Serial.begin(115200);
  myservo.attach(14);
  // Poner el módulo WiFi en modo station y desconectar de cualquier red a la que pudiese estar previamente conectado
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);

  //pinMode(PIN, OUTPUT);
  
  //Conectar a la red WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado, la IP del dispositivo es: "); 
  Serial.println(WiFi.localIP());
  
  //Iniciar server
  server.begin();
  Serial.println("Servidor iniciado");
}
 
void loop() {
  //chequeamos si se ha conectado un cliente, en caso contrario terminar (se reiniciaría)
  WiFiClient client = server.available();
  if (!client)
    return;
 
  //Esperar hasta que el cliente envíe algún dato
  while(!client.available())
    yield();
 
  //Lee la request del cliente
  String request = client.readStringUntil('\r');
  client.flush(); //vacía por seguridad
  
  //Request en un objeto String que contiene la URL compelta, incluyendo parámetros. Buscamos si contien la cadena "/RELE=ON"

  if (request.indexOf("/LEFT") != -1){
    myservo.write(180);
    Motor_state=0;
    Serial.println("Left");
  }

  if (request.indexOf("/RIGHT") != -1){
    myservo.write(0);
    Motor_state=1;
    Serial.println("Right");
  }

  //ROJO
  if (request.indexOf("/CENTER") != -1){
    myservo.write(90);
    Motor_state=2;
    Serial.println("MoveCenter");
  }
  
     
  //Parte "response" del servidor hacia el cliente, una página Web
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //requerido
  client.println("<!DOCTYPE HTML>");
  client.println("<meta name='viewport' content='width=device-width, user-scalable=no'>");
  client.println("<html>");
 
  if(Motor_state == 0)
    client.print("Moved left</p><br>");
  else{
   if(Motor_state == 1)
    client.print("Moved right</p><br>"); 
   else
    client.print("Moved center</p><br>");
  }


  client.println("<a href=\"/LEFT\"><button style='width:100%;height:50px;background:#0000FF;'>Move left</button></a>");
  client.println("<a href=\"/RIGHT\"><button style='width:100%;height:50px;background:#000080;'>Move right</button></a><br />");
  client.println("<a href=\"/CENTER\"><button style='width:100%;height:50px;background:#FF0000;'>Move center</button></a>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Cliente desconectado");
  Serial.println(""); 
}
