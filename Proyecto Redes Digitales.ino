#include <ESP8266WiFi.h> //conexión NodeMcu a la red wifi local
#include <WiFiClient.h>  //Configurar NodeMCU cliente
#include <ESP8266HTTPClient.h> //Funciones enviar request POST o GET
#include <DHT.h> //librería sensor de temperatura

const char* ssid = "INFINITUMXZGA_2.4"; //Remplazar con el nombre wifi
const char* pass = "AbTm5RMfx7";    //Remplaza con la constraseña

//Pagina PHP
String serverName="http://jesusjarillo.000webhostapp.com/Proyecto/tablero/index3.php";
//http para solicitar cambios desde un dispositivo
String variable1="contra1";
String variable2="sensor";
String message="";

#define DHTPIN 10          //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);

void setup() {
  pinMode(10, INPUT);
  Serial.begin(115200);
  delay(10);
  dht.begin();
  conectarwifi();
}

void loop() {

  float t= dht.readTemperature();
  String con2="con2";
  enviardato(con2, t); //funcion local para enviar datos a PHP
      
  delay(10000);
}


void conectarwifi(){
  
  Serial.print("Conectando a ");
  Serial.print(ssid);
  WiFi.begin(ssid, pass);
  //Realiza conexión a la red

  while (WiFi.status() !=WL_CONNECTED)
  
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println(""); //Espacio de un eneter
  Serial.println("WiFi conectado");

}

void enviardato(String dato1, int dato2){

     if(WiFi.status()== WL_CONNECTED) //revisa el status del wifi
     {
      HTTPClient http; //crea un objeto de tipo HTTPCLIENT
      message=serverName+"?"+variable1+"="+String(dato1)+"&"+variable2+"="+String(dato2);
      http.begin(message.c_str()); //Crea el request HTTP

      Serial.print("HTTP Request Data: ");
      Serial.println(message);
      
      int httpResponseCode=http.GET();
      //Realiza el metodo POST que lo envia al nombre del server
      
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();//Cerrar conexión con el server
      Serial.println("");    
    }
    
    else 
    {
      Serial.println("WiFi Desconectado"); 
      //Si la red esta desconectada
    }
}
