//Sending Data from Arduino to NodeMCU Via Serial Communication
//Arduino code
//DHT11 Lib
#include <dht11.h>
//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

int istenilenSicaklik;
String istenilenpompa;
int toprakNemPin = A0;
int dhtPin = 4;  //sıcaklık ve nem sensörunun data pini
#define Fan 7    // fan data kontrol pini
#define Pompa 8
#define isitici 3
dht11 dht_sensor;
SoftwareSerial nodemcusend(5, 6);        //Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
//SoftwareSerial nodemcureceive(9, 10); 

//değiskenler alanı
float temp;
float hum;
String fanDurum;
String PompaDurum;
String isiticiDurum;
int toprakNemi;



void setup() {
  Serial.begin(9600);
  nodemcusend.begin(9600);
  //nodemcureceive.begin(9600);
  pinMode(Fan, OUTPUT);
  pinMode(Pompa, OUTPUT);
  pinMode(isitici, OUTPUT);

  delay(1000);

  Serial.println("Program started");
}

void loop() {
//DynamicJsonDocument jsonDoc(200);
// StaticJsonBuffer<1000> jsonBuffer2;
 //JsonObject& data2 = jsonBuffer2.parseObject(nodemcureceive);
// Serial.print("Recieved serasicaklık:     ");
// int seraaa = data2["serasicaklik"];
 //Serial.println(seraaa);

  delay(10000);







  Serial.print("istenilenSicaklik:     ");
  Serial.println(istenilenSicaklik);
  Serial.print("istenilenpompa:     ");
  Serial.println(istenilenpompa);

  int  chk = dht_sensor.read(dhtPin);
  Serial.print("NEM ORANI: ");
  Serial.println((float)dht_sensor.humidity,2);

  Serial.print("SICAKLIK ORANI: ");
  Serial.println((float)dht_sensor.temperature,2);

  hum=dht_sensor.humidity;
  temp = dht_sensor.temperature;
  if(istenilenSicaklik<temp || istenilenSicaklik==temp)       ///DENEME AMAÇLI HUM KOYULUDU DEĞİŞECEK !!!!!!!!!!!!
  {
    digitalWrite(isitici,HIGH);
    isiticiDurum = "kapalı";
  }
  else
  {
    digitalWrite(isitici,LOW);
    isiticiDurum = "açık";

  }
  Serial.print("Isıtıcı DURUMU: ");
  Serial.println(isiticiDurum);
  if(istenilenSicaklik>temp || istenilenSicaklik==temp)       ///DENEME AMAÇLI HUM KOYULUDU DEĞİŞECEK !!!!!!!!!!!!
  {
    digitalWrite(Fan,HIGH);
    fanDurum = "kapalı";
  }
  else
  {
    digitalWrite(Fan,LOW);
    fanDurum = "açık";

  }
  Serial.print("FAN DURUMU: ");
  Serial.println(fanDurum);

  if(istenilenpompa=="false")       ///DENEME AMAÇLI HUM KOYULUDU DEĞİŞECEK !!!!!!!!!!!!
  {
    digitalWrite(Pompa,HIGH);
    PompaDurum = "kapalı";
  }
  else
  {
    digitalWrite(Pompa,LOW);
    PompaDurum = "açık";

  }
  Serial.print("POMPA DURUMU: ");
  Serial.println(PompaDurum);

 

  toprakNemi = analogRead(toprakNemPin);
  Serial.print("Toprak Nemi:   ");
  Serial.println(toprakNemi);   //0-1023 arası   ne kadar küçük o kadar nemli demek


  StaticJsonBuffer<500> jsonBuffer;


  JsonObject& data = jsonBuffer.createObject();
  //Assign collected data to JSON Object
  data["humidity"] = hum;
  data["temperature"] = temp; 
  data["fanBilgisi"] = fanDurum; 
  data["PompaBilgisi"] = PompaDurum; 
  data["toprakNemBilgisi"] = toprakNemi; 
  data["isiticiBilgisi"] = isiticiDurum; 

  //Send data to NodeMCU
  data.printTo(nodemcusend);
  jsonBuffer.clear();
  
  JsonObject& data2 = jsonBuffer.parseObject(nodemcusend);
 

  String seraapompa= data2["serapompa"];
  Serial.print("Recieved serapompa:     ");
  Serial.println(seraapompa);

  Serial.print("Recieved serasicaklik:     ");
  int seraa = data2["serasicaklik"];
  Serial.println(seraa);


  if(seraa!=0){
    istenilenSicaklik = seraa;
    istenilenpompa= seraapompa;
  }
 
  jsonBuffer.clear();

  Serial.println("-----------------------------------------");
  
}
