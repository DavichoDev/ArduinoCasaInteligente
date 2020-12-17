#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid = "Total_Play105";
const char* password = "WiFiMarieta105@";
 
void setup () {
 
  Serial.begin(115200);

 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
 
}
 
void loop() {

    StaticJsonDocument<256> doc;
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("https://adminpro-backend-angular.herokuapp.com/api/arduino/5fdaab168851f82f74cae53d");  //Specify request destination
    int httpCode = http.GET();                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload

      DeserializationError err = deserializeJson(doc, payload);

      if(err){
        Serial.print("Error: ");
        Serial.println(err.c_str());
        return; 
      }

     String dispositivo = doc["dispositivo"];
     int sala = doc["dispositivo"]["sala"];
     int patio = doc["dispositivo"]["patio"];
     int puerta = doc["dispositivo"]["puerta"];
      
     Serial.print("Patio: ");
     Serial.print(patio);
     Serial.println();
     Serial.print("Sala: ");
     Serial.print(sala);
     Serial.println();
     Serial.print("Puerta: ");
     Serial.print(puerta);
     Serial.println();
    }
 
    http.end();   //Close connection
 
  }
 
  delay(1000);    //Send a request every 5 seconds
}
