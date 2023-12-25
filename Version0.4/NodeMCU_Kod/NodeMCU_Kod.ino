#include <Arduino_JSON.h>

//ThatsEngineering
//Sending Data from Arduino to NodeMCU Via Serial Communication
//NodeMCU code

//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>


#define FIREBASE_HOST "iotprojeuygulama-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "OQqPD4SBmHLjaGil1vrHBkDpigRG1H2GVI14AzR"
#define WIFI_SSID "ERESAZ03"
#define WIFI_PASSWORD "64636634"



FirebaseData db;


//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);


void setup() {


  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Firebase bağlantısını başlat
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 // Firebase.setString("sicaklik", "20");

  while (!Serial) continue;
}

void loop() {
  
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");

  Serial.print("Recieved Humidity:     ");
  float hum = data["humidity"];
  Serial.println(hum);

  Serial.print("Recieved Temperature:  ");
  float temp = data["temperature"];
  Serial.println(temp);

  Serial.print("Recieved Fan Durum:    ");
  String fan = data["fanBilgisi"];
  Serial.println(fan);

  Serial.print("Recieved Fan Durum:    ");
  String Pompa = data["PompaBilgisi"];
  Serial.println(Pompa);

  Serial.print("Recieved Toprak Nemi:  ");
  int toprak = data["toprakNemBilgisi"];
  Serial.println(toprak);

  Serial.println("-----------------------------------------");

  Firebase.setFloat(db, "/sicaklikValue", temp);
  Firebase.setFloat(db, "/nemValue", hum);
  Firebase.setString(db, "/fanValue", fan);
  Firebase.setString(db, "/PompaValue", Pompa);
  Firebase.setInt(db, "/toprakValue", toprak);
  delay(2000);
  









}