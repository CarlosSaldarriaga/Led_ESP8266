#include <ESP8266WiFi.h>

const char* ssid = "PAU2024";
const char* password = "Yeyo88p24";

WiFiServer server(80);

int pinLed = 16; //led azul interno
int pinLed2 = 20; //
int estado = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  digitalWrite(pinLed, LOW);
  digitalWrite(pinLed2, LOW);
  Serial.println("Inicio");
  WiFi.begin(ssid, password);
  Serial.printf("\n\nConectando a la red: %s\n", WiFi.SSID().c_str());
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectada");

  server.begin();
  Serial.println("Servidor inicializada");

  Serial.printf("\n\nUtiliza esta URL para conectar: http://%s/\n", WiFi.localIP().toString().c_str());


  
}

void loop() {
  // put your main code here, to run repeatedly:
WiFiClient client = server.available();
if(!client){
  return;
}

Serial.println("Nuevo cliente");
while(!client.available()){
  delay(1);
}

String peticion = client.readStringUntil('\r');
Serial.println(peticion);
client.flush();

if (peticion.indexOf('/LED=ON') != -1) 
  {estado = LOW;} 
  if (peticion.indexOf('/LED=OFF') != -1)
  {estado = HIGH;}
 
  digitalWrite(pinLed, estado);
  digitalWrite(pinLed2, estado);
 

  client.println("HTTP/1.1 200 OK");
  client.println("");                         
  client.println("");
  client.println("");
  client.println("");

  client.print("<h1 align=center>CONTROL LED ");
 
 if(estado == HIGH) 
 {client.print("<input type='image' src='https://i.imgur.com/00i0BdB.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/LED=ON'>");}
 else 
 {client.print("<input type='image' src='https://i.imgur.com/uQxhFE5.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/LED=OFF'>");}
 
 client.println("</html>");
 delay(1);
 Serial.println("Peticion finalizada"); // Se finaliza la petición al cliente. Se inicializa la espera de una nueva petición.
 Serial.println("");

}
