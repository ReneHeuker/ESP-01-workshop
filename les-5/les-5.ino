#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>

#include "index.h"
#include "script.h"
#include "styles.h"
#include "therm.h"
#include "slider.h"

const char* ssid = "CaReSoft";
const char* password = "2905196902";
String hostname = "workshop-<<yourname>>";

ESP8266WebServer server(80);

#define PIN_DS18B20 2  // temperature sensor pin
#define PIN_WS2812B 0  // neopixel pin

// Setup a oneWire bus to communicate with ds18B20
double oldTemp = 0;
double newTemp = 0;
OneWire oneWire(PIN_DS18B20);
DallasTemperature ds18B20(&oneWire);

// Setup neopixel leds
#define NROFLEDS 3
uint32_t oldColor = 0;
uint32_t newColor = 0;
uint8_t oldBrightness = 0x80;
uint8_t newBrightness = 0x80;
Adafruit_NeoPixel ws2812B(NROFLEDS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

// Define colors (RGB)
uint8_t const low[3] = {0x0B, 0xF3, 0x1A}; // green
uint8_t const mid[3] = {0xFF, 0xA5, 0x00}; // orange
uint8_t const high[3] = {0xFF, 0x00, 0x00}; // red

void onGetTemperature() {
  setCrossOrigin();
  String value = String(newTemp);
  server.send(200, "application/json", "{\"temperature\": \"" + value + "\"}");
}

void onGetBrightness() {
  setCrossOrigin();
  String value = String(newBrightness);
  server.send(200, "application/json", "{\"brightness\": \"" + value + "\"}");
}

void onSetBrightness() {
  setCrossOrigin();
  if (server.hasArg("plain") == true) {
    JsonDocument doc;
    deserializeJson(doc, server.arg("plain"));
    String value = doc["brightness"];
    newBrightness = value.toInt();
    server.send(200, "application/json", "{\"brightness\": \""+ value + "\"}");
  } else {
    server.send(400);
  }
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

void onIndex() {
  server.send(200, F("text/html"), INDEX_HTML);
}

void onScript() {
  server.send(200, F("text/js"), SCRIPT_JS);
}

void onStyles() {
  server.send(200, F("text/css"), STYLES_CSS);
}

void onTherm() {
  server.send(200, F("text/css"), THERM_CSS);
}

void onSlider() {
  server.send(200, F("text/css"), SLIDER_CSS);
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
  server.on("/", HTTP_GET, onIndex);
  server.on("/script.js", HTTP_GET, onScript);
  server.on("/styles.css", HTTP_GET, onStyles);
  server.on("/therm.css", HTTP_GET, onTherm);
  server.on("/slider.css", HTTP_GET, onSlider);

  server.on(F("/temperature"), HTTP_OPTIONS, onOptions);
  server.on(F("/temperature"), HTTP_GET, onGetTemperature);

  server.on(F("/brightness"), HTTP_OPTIONS, onOptions);
  server.on(F("/brightness"), HTTP_GET, onGetBrightness);
  server.on(F("/brightness"), HTTP_PUT, onSetBrightness);

  server.onNotFound(onNotFound);
}

void setup(void) {

  Serial.begin(9600);

  ds18B20.begin();

  ws2812B.begin();  
  ws2812B.clear();

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

    if (newTemp != oldTemp) {
      // nieuwe kleur berekenen
      if (newTemp < 50) {
        newColor = ws2812B.Color(
          (uint8_t)(round(low[0] + (newTemp / 50) * (mid[0] - low[0]))),
          (uint8_t)(round(low[1] + (newTemp / 50) * (mid[1] - low[1]))),
          (uint8_t)(round(low[2] + (newTemp / 50) * (mid[2] - low[2])))
        );
      } else {
        newColor = ws2812B.Color(
          (uint8_t)(round(mid[0] + ((newTemp - 50) / 50) * (high[0] - mid[0]))),
          (uint8_t)(round(mid[1] + ((newTemp - 50) / 50) * (high[1] - mid[1]))),
          (uint8_t)(round(mid[2] + ((newTemp - 50) / 50) * (high[2] - mid[2])))
        );
      }
    
      oldTemp = newTemp;
    }
  }

  if (newColor != oldColor) {
    ws2812B.setPixelColor(0, newColor);
    ws2812B.setPixelColor(1, newColor);
    ws2812B.setPixelColor(2, newColor);
    ws2812B.show();
    oldColor = newColor;
  }

  if (newBrightness != oldBrightness) {
    ws2812B.setBrightness(newBrightness);
    ws2812B.show();
    oldBrightness = newBrightness;
  }

  cntr++;

  if (cntr>=5000) cntr=0;
}
