//Sending Data from Arduino to NodeMCU Via Serial Communication
//Arduino code

//DHT11 Lib
#include <dht11.h>
//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>



int dhtPin = 4;  //sıcaklık ve nem sensörunun data pini
#define Fan 7    // fan data kontrol pini
#define Pompa 8
dht11 dht_sensor;
SoftwareSerial nodemcu(5, 6);        //Initialise Arduino to NodeMCU (5=Rx & 6=Tx)


//değiskenler alanı
float temp;
float hum;
String fanDurum;
String PompaDurum;




void setup() {
  Serial.begin(9600);
  pinMode(Fan, OUTPUT);
  pinMode(Pompa, OUTPUT);
  
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
  
  if(hum<50)       ///DENEME AMAÇLI HUM KOYULUDU DEĞİŞECEK !!!!!!!!!!!!
  {
    digitalWrite(Fan,HIGH);
    fanDurum = "Fan kapalı";
  }
  else
  {
    digitalWrite(Fan,LOW);
    fanDurum = "Fan açık";

  }
  Serial.print("FAN DURUMU: ");
  Serial.println(fanDurum);

  if(hum<50)       ///DENEME AMAÇLI HUM KOYULUDU DEĞİŞECEK !!!!!!!!!!!!
  {
    digitalWrite(Pompa,HIGH);
    PompaDurum = "Pompa kapalı";
  }
  else
  {
    digitalWrite(Pompa,LOW);
    PompaDurum = "Pompa açık";

  }
  Serial.print("POMPA DURUMU: ");
  Serial.println(PompaDurum);

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();







  //Assign collected data to JSON Object
  data["humidity"] = hum;
  data["temperature"] = temp; 
  data["fanBilgisi"] = fanDurum; 
  data["PompaBilgisi"] = PompaDurum; 


  //Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();
  Serial.println("-----------------------------------------");
  delay(2000);
}
