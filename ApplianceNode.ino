/*
 * COPYRIGHT AppArt Software Eric Klassen 2020.
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = {YOUR WIFI NAME HERE};
const char* password = {YOUR WIFI PASSWORD HERE};
const char* userId = {YOUR USER UTILITY ID};//Utility coin user id.

WiFiClient wifiClient;//Create WiFi client

void setup() {
  //start serial connection
  Serial.begin(115200);
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, OUTPUT);

  connectToWifi();

}

void loop() {
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(D2);
  //print out the value of the pushbutton
  //Serial.println(sensorVal);

  if (sensorVal != HIGH) {
    HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://192.168.2.20:3000/api/UpdateConsumption");//ip of hosted blockchain.
   http.addHeader("Content-Type", "application/json");
   http.addHeader("Accept", "application/json");

  //Format json request for updating consumption
  String json = String("{\"$class\":\"org.london.luc.UpdateConsumption\",\"consumption\":5,\"user\":\"") +  userId + "\"}";

   Serial.println(json);
   int httpCode = http.POST(json);//Send the request

   String payload = http.getString();//Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
  }
  delay(200);
  
}

//Method to connect to Wifi
void connectToWifi() {  
   Serial.print("Connecting to ");
    Serial.println(ssid);  
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

}
