//ThatsEngineering
//Sending Data from Arduino to NodeMCU Via Serial Communication
//Arduino code

//DHT11 Lib
#include <dht11.h>
#define DHT11PIN 4
//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
dht11 DHT11;
//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);

//Initialisation of DHT11 Sensor
float temp;
float hum;

void setup() {
  Serial.begin(9600);

  
  nodemcu.begin(9600);
  delay(1000);

  Serial.println("Program started");
}

void loop() {
  int chk = DHT11.read(DHT11PIN);
   Serial.print("Nem (%): ");
   
  Serial.println((float)DHT11.humidity, 4);

  Serial.print("Sicaklik (Celcius): ");
  
  Serial.println((float)DHT11.temperature,4);


  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  //Obtain Temp and Hum data
  dht11_func();


  //Assign collected data to JSON Object
  data["humidity"] = 20;
  data["temperature"] = temp; 

  //Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();

  delay(2000);
}

void dht11_func() {

  hum=((float)DHT11.humidity);
  temp = ((float)DHT11.temperature);
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);

}