#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Ip for Motors ESP: 172.20.10.7

const char* ssid1 = "AnandJ01";
const char* password = "midzooduncan";

#define EAP_IDENTITY "anand.jasti@student.csulb.edu" //if connecting from another corporation, use identity@organisation.domain in Eduroam 
#define EAP_USERNAME "anand.jasti@student.csulb.edu" //oftentimes just a repeat of the identity
#define EAP_PASSWORD "s<uw$uNkHsCZ4;a" //your Eduroam password
const char* ssid = "eduroam"; // Eduroam SSID
int counter = 0;

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp32!");
}

void handleNotFound() {
  // digitalWrite(led, 1);
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
  // digitalWrite(led, 0);
}

// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14;


int motor2Pin3 = 25;
int motor2Pin4 = 33;
int enable2Pin = 32;

// Setting PWM properties
const int freq = 1000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 90;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel);
  // digitalWrite(enable1Pin, HIGH);
  // digitalWrite(enable2Pin, HIGH);

  Serial.begin(115200);

  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  
  // Example1 (most common): a cert-file-free eduroam with PEAP (or TTLS)
  // WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_IDENTITY, EAP_USERNAME, EAP_PASSWORD);  

  WiFi.begin(ssid1,password);  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address set: "); 
  Serial.println(WiFi.localIP()); //print LAN IP

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/forward", [](){
    go_forward();
    server.send(200,"text/plain", "0");
  });

  server.on("/backward", [](){
    go_backward();
    server.send(200,"text/plain", "0");
  });

  server.on("/turnRight", [](){
    turnRight();
    server.send(200,"text/plain", "0");
  });

  server.on("/turnLeft", [](){
    turnLeft();
    server.send(200,"text/plain", "0");
  });

  server.on("/stop", [](){
    stop();
    server.send(200,"text/plain", "0");
  });

  // server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  // testing
  Serial.print("Testing DC Motor...");
  
  ledcWrite(pwmChannel, dutyCycle); 
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid1);
  }
  counter = 0;
  while (WiFi.status() != WL_CONNECTED) { //during lost connection, print dots
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //30 seconds timeout - reset board
    ESP.restart();
    }
  }
  server.handleClient();
}

void go_forward(){
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);   
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH); 
  // delay(5000);
}

void go_backward(){
  // // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW);
  // delay(5000);
}

void turnRight(){
  // //Right Turn
  Serial.println("Right Turn");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW); 

  // delay(5000);
}

void turnLeft(){
  // //Left Turn
  Serial.println("Left Turn");
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH); 
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  // delay(5000);
}

void stop(){
  // // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  // delay(3000);
}