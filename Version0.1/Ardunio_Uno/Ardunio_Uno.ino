//ThatsEngineering
//Sending Data from Arduino to NodeMCU Via Serial Communication
//Arduino code

//DHT11 Lib
#include <dht11.h>
int dhtPin = 4;
dht11 dht_sensor;
//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
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
   int  chk = dht_sensor.read(dhtPin);
  Serial.print("NEM ORANI: ");
  Serial.println((float)dht_sensor.humidity,2);

  Serial.print("SICAKLIK ORANI: ");
  Serial.println((float)dht_sensor.temperature,2);

  hum=dht_sensor.humidity;
  temp = dht_sensor.temperature;


  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  //Obtain Temp and Hum data
  //dht11_func();


  //Assign collected data to JSON Object
  data["humidity"] = hum;
  data["temperature"] = temp; 

  //Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();

  delay(2000);
}

void dht11_func() {

  hum=((float)dht_sensor.humidity,2);
  temp = ((float)dht_sensor.temperature,2);
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);

}