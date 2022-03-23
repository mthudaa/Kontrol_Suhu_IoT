#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#define PINDHT D1
#define TIPEDHT DHT11

int kipas=D2;
int pintu=D3;
int nilai=0;
float batas=24;

FirebaseData dhanfirebase;
float k;
float c;
float f;

DHT dht(PINDHT, TIPEDHT);

void konekwifi() {
  Serial.println("menyambungkan.....");
  WiFi.begin("leeknow", "h3u1d0a802");
  while (!(WiFi.status() == WL_CONNECTED)) {
    delay(500);
    Serial.println("...");
  }
  Serial.println("tersambung wifi");
}

void setup() {
  Serial.begin(115200);
  pinMode(kipas, OUTPUT);
  pinMode(pintu, OUTPUT);
  dht.begin();
  konekwifi();
  Firebase.begin("url.firebaseio.com", "abcdefghijklmn");
}

void loop() {
  float kelembaban = dht.readHumidity();
  float TC = dht.readTemperature();
  float TF = dht.readTemperature(true);
  nilai = Firebase.getInt("n");
  delay(1000);
  Serial.print("kelembaban udara= ");
  Serial.println(kelembaban);
  Serial.print("suhu celcius= ");
  Serial.println(TC);
  Serial.print("suhu fahrenheit= ");
  Serial.println(TF);
  if (TC>batas) {
    digitalWrite(kipas, LOW);
    delay(1000);
  }
  else {
    digitalWrite(kipas, HIGH);
    delay(1000);
  }
  if (nilai==0) {
    digitalWrite(pintu, HIGH);
  }
  else {
    digitalWrite(pintu, LOW);
    delay(5000);
  }
  Firebase.setInt("n", nilai);
  if (Firebase,failed()) {
    return;
  }
  Firebase.setFloat(dhanfirebase, "kelembaban udara", kelembaban);
  Firebase.setFloat(dhanfirebase, "suhu dalam celcius", TC);
  Firebase.setFloat(dhanfirebase, "suhu dalam fahrenheit", TF);
  Firebase.getFloat(dhanfirebase, "kelembaban udara");
  k = dhanfirebase.floatData();
  Firebase.getFloat(dhanfirebase, "suhu dalam celcius");
  c = dhanfirebase.floatData();
  Firebase.getFloat(dhanfirebase, "suhu dalam fahrenheit");
  f = dhanfirebase.floatData();
  Serial.println(k);
  Serial.println(c);
  Serial.println(f);
}
