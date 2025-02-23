#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "CaReSoft";
const char* password = "2905196902";
String hostname = "workshop-<<yourname>>";

ESP8266WebServer server(80);

#define PIN_DS18B20 2  // temperature sensor pin

// Setup a oneWire bus to communicate with ds18B20
double oldTemp = 0;
double newTemp = 0;
OneWire oneWire(PIN_DS18B20);
DallasTemperature ds18B20(&oneWire);

void onGetTemperature() {
  setCrossOrigin();
  String value = String(newTemp);
  server.send(200, "application/json", "{\"temperature\": \"" + value + "\"}");
}

void setCrossOrigin() {
  server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
  server.sendHeader(F("Access-Control-Max-Age"), F("600"));
  server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
  server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
};

void onOptions() {
  setCrossOrigin();
  server.send(204);
}

void onNotFound() {
  setCrossOrigin();
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

// Define routing
void restServerRouting() {

  server.on(F("/temperature"), HTTP_OPTIONS, onOptions);
  server.on(F("/temperature"), HTTP_GET, onGetTemperature);

  server.onNotFound(onNotFound);
}

void setup(void) {

  Serial.begin(9600);

  ds18B20.begin();

  Serial.print("\nSetup Wifi");
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname.c_str());
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nIP address: ");
  Serial.print(WiFi.localIP());

  // Set server routing
  Serial.print("\nsetup routing");
  restServerRouting();

  // Start server
  Serial.print("\nstarting rest server");
  server.begin();

  Serial.print("\nEsp01 controller started");
  Serial.flush();

}

int cntr=0;

void loop(void) {

  server.handleClient();

  if (cntr==0) {

    // temperatuur uitlezen
    ds18B20.requestTemperatures(); 
    newTemp = ds18B20.getTempCByIndex(0);

    oldTemp = newTemp;
  }

  cntr++;

  if (cntr>=5000) cntr=0;
}
