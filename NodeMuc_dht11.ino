
//Raum_KLima.Mini_WeatherStation
//2024

//Lib
#include "ESP8266WiFi.h"
#include <aREST.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <ArduinoHttpClient.h>

//Def Sensor
#define DHTPIN D4
#define DHTTYPE DHT11
//#define MQ A0

//INIT
DHT dht(DHTPIN, DHTTYPE);

//aREST
aREST rest = aREST();

//WiFI
const char* ssid = "PYUR 82057";
const char* password = "uy46v3N2kkrU";

//Port
#define LISTEN_PORT 80

//Create instance of server
WiFiServer server(LISTEN_PORT);

//Variables API
float humidity, temperature;

void setup(){
  Serial.begin(9600);
  dht.begin();
  String sensorName = "sensor_NodeMCU";
  


//Iinit Variables API
  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);

//Name ID
  rest.set_id("1");
  rest.set_name(sensorName.c_str());

//Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); 
  } 

  Serial.println("");
  Serial.println("WiFi connected!");

//Start Server
server.begin();
Serial.println("Server started!");

//IP
  Serial.println(WiFi.localIP());

}

void loop() {
  //Wait ls
  delay(1000);
  //mq = analogRead(MQ);
  humidity = dht.readHumidity(); //RH %0-100 ()
  temperature = dht.readTemperature(); //0-50 *C

  //Rest Calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay (1);
  } 
  rest.handle(client);
  
}

