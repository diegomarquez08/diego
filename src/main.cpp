

#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"


const char* ssid = "MARCELA";
const char* password = "Sadiju40";

AsyncWebServer server(80);
int tiempomilisegundos=2000;




const int output26 = 26;
const int output27 = 27;

const int ledPin = 2;
String ledState;
String output26State ;
String output27State ;



String processor(const String& var){
  Serial.println(var);
  if(var == "ESTADO"){
    if(digitalRead(ledPin)){
      ledState = "PUERTA ABIERTA";
    }
    else{
      ledState = "PUERTA CERRADA";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(output26, OUTPUT); 
  pinMode(output27, OUTPUT);
  
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/body.html");
  });

  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css", "text/css");
  });

  // Route to load main.js file
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/main.js");
  });
  
  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    
    

     digitalWrite(output27, LOW);   
     digitalWrite(ledPin, HIGH);  
      digitalWrite(output26, HIGH);   
      delay(tiempomilisegundos);
    
        digitalWrite(output26, LOW);
    request->send(SPIFFS, "/body.html", String(), false, processor);
  });

  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);  
        digitalWrite(output26, LOW);   
     digitalWrite(output27, HIGH);   
      delay(tiempomilisegundos);

      digitalWrite(output27, LOW); 

    request->send(SPIFFS, "/body.html", String(), false, processor);
   
  });


  

  server.begin();
}

void loop() {



  // put your main code here, to run repeatedly:
}