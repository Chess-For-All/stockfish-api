#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define VIBE_PIN 4

ESP8266WiFiMulti WiFiMulti;

String data = "a2a1";
int coords[4];
int promo;
String oldData = "a2a1";

void vibrate(int delayTime){
  digitalWrite(VIBE_PIN, HIGH);
  delay(delayTime);
  digitalWrite(VIBE_PIN, LOW);
  delay(delayTime);
}


void start(){
  coords[0] = data[0] - ('`');
  coords[1] = data[1] - '0';
  coords[2] = data[2] - ('`');
  coords[3] = data[3] - '0';
  switch(data[4]){
    case ' ': case 0:
        promo = 0;
        break;
    case 'q':
        promo = 1;
        break;
    case 'n':
        promo = 2;
        break;
    case 'r':
        promo = 3;
        break;
    case 'b':
        promo = 4;
        break;
  }
  
  for(int c = 0; c < 4; c++) {
    for(int j = 0; j < coords[c]; j++){
      vibrate(300);
    }
    delay(600);
  }
  if(promo != 0){
    delay(1000);
    vibrate(1000);
    for(int k = 0; k < promo; k++){
      vibrate(300);
    }
  }
  delay(1000);
}


void check(){
  if(data != oldData){
      start();
    oldData = data;
  }
}


IPAddress local_IP(192,168,4,3);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

void setup()
{
  Serial.begin(9600);
  pinMode(VIBE_PIN, OUTPUT);
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  Serial.println(WiFi.softAP("ESP_stockfish", "stockfish") ? "Ready" : "Failed!");
}


void loop()
{
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED || 1)) {
    WiFiClient client;
    HTTPClient http;
    if (http.begin(client, "http://192.168.4.102:8080/bestmove")) {  // HTTP
      int httpCode = http.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          data = http.getString();
          Serial.println(data);
        }
      }
      http.end();
    }
  }
  check();
  delay(100);
}