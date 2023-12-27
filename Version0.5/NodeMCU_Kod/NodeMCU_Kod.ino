#include <Arduino_JSON.h>
#include <iostream>
#include <string>
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
#define WIFI_SSID "AndroidAP0B4F"
#define WIFI_PASSWORD "yecu4807"



FirebaseData db;
FirebaseData sera;
int value;

//D6 = Rx & D5 = Tx
SoftwareSerial arduinoreceive(D6, D5);
//SoftwareSerial arduinosend(D8, D7);



void setup() {


  // Initialize Serial port
  Serial.begin(9600);
  arduinoreceive.begin(9600);
 // arduinosend.begin(9600);
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
  JsonObject& data = jsonBuffer.parseObject(arduinoreceive);

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

  Serial.print("Recieved Pompa Durum:    ");
  String Pompa = data["PompaBilgisi"];
  Serial.println(Pompa);

  Serial.print("Recieved Toprak Nemi:  ");
  int toprak = data["toprakNemBilgisi"];
  Serial.println(toprak);

  Serial.print("Recieved Isıtıcı Durum:  ");
  String isitici = data["isiticiBilgisi"];
  Serial.println(isitici);

  //jsonBuffer.clear();
  Serial.println("-----------------------------------------");

  Firebase.setFloat(db, "/sicaklikValue", temp);
  Firebase.setFloat(db, "/nemValue", hum);
  Firebase.setString(db, "/fanValue", fan);
  Firebase.setString(db, "/PompaValue", Pompa);
  Firebase.setInt(db, "/toprakValue", toprak);
  Firebase.setString(db, "/isiticiValue", isitici);

  
  if(Firebase.getString(sera,  "/serasicaklik")){
    String str=sera.stringData();
    
    str.replace("\"", "");
    str.remove(0,1);
    str.remove(str.length()-1);
    value = str.toInt();
    Serial.println(str);

  }

  //StaticJsonBuffer<1000> jsonBuffer2;
  //JsonObject& data2 = jsonBuffer2.createObject();
  //data2["serasicaklik"]= value;
  //data2.printTo(arduinoreceive);
  //jsonBuffer2.clear();



  delay(2000);
  









}