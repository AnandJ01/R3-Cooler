#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
// #include "ESPAsyncWebServer.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Ip for QR Cam ESP: 172.20.10.3:8888

const char* ssid1 = "-_-";
const char* password = "its8characters";

#define EAP_IDENTITY "anand.jasti@student.csulb.edu" //if connecting from another corporation, use identity@organisation.domain in Eduroam 
#define EAP_USERNAME "anand.jasti@student.csulb.edu" //oftentimes just a repeat of the identity
#define EAP_PASSWORD "s<uw$uNkHsCZ4;a" //your Eduroam password
const char* ssid = "eduroam"; // Eduroam SSID
int counter = 0;
const char* VAL = "0";
String content = "";

WebServer server(8888);

SoftwareSerial mySerial(16, 17);

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

int customersIndex = 0;
String customerName;
String customers [] = {"-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1"};
int drinksConsumed [] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int drinksCounter = 0;
bool alreadyInArray = false;

int previousDrinksLeft=0;
int currentDrinksLeft;


void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600); // set the data rate for the SoftwareSerial port

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
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.subnetMask());
  Serial.println(WiFi.dnsIP(0));
  Serial.println(WiFi.dnsIP(1));


  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/QR_DATA", [](){
    server.send_P(200, "text/plain", VAL);
  });

  server.on("/Customer/1",[](){
    server.send(200, "text/plain", customers[0]);
  });

  server.on("/Customer/2",[](){
    server.send(200, "text/plain", customers[1]);
  });

  server.on("/Customer/3",[](){
    server.send(200, "text/plain", customers[2]);
  });

  server.on("/Customer/4",[](){
    server.send(200, "text/plain", customers[3]);
  });

  server.on("/Customer/5",[](){
    server.send(200, "text/plain", customers[4]);
  });

  server.on("/Customer/6",[](){
    server.send(200, "text/plain", customers[5]);
  });

  server.on("/Customer/7",[](){
    server.send(200, "text/plain", customers[6]);
  });

  server.on("/Customer/8",[](){
    server.send(200, "text/plain", customers[7]);
  });

  server.on("/Customer/9",[](){
    server.send(200, "text/plain", customers[8]);
  });

  server.on("/Customer/10",[](){
    server.send(200, "text/plain", customers[9]);
  });

  server.on("/Customer/11",[](){
    server.send(200, "text/plain", customers[10]);
  });

  server.on("/Customer/12",[](){
    server.send(200, "text/plain", customers[11]);
  });

  server.on("/Customer/13",[](){
    server.send(200, "text/plain", customers[12]);
  });

  server.on("/Customer/14",[](){
    server.send(200, "text/plain", customers[13]);
  });

  server.on("/Customer/15",[](){
    server.send(200, "text/plain", customers[14]);
  });

  server.on("/DrinksConsumed/1", [](){
    server.send(200, "text/plain", String(drinksConsumed[0]));
  });

  server.on("/DrinksConsumed/2", [](){
    server.send(200, "text/plain", String(drinksConsumed[1]));
  });

  server.on("/DrinksConsumed/3", [](){
    server.send(200, "text/plain", String(drinksConsumed[2]));
  });

  server.on("/DrinksConsumed/4", [](){
    server.send(200, "text/plain", String(drinksConsumed[3]));
  });

  server.on("/DrinksConsumed/5", [](){
    server.send(200, "text/plain", String(drinksConsumed[4]));
  });

  server.on("/DrinksConsumed/6", [](){
    server.send(200, "text/plain", String(drinksConsumed[5]));
  });

  server.on("/DrinksConsumed/7", [](){
    server.send(200, "text/plain", String(drinksConsumed[6]));
  });

  server.on("/DrinksConsumed/8", [](){
    server.send(200, "text/plain", String(drinksConsumed[7]));
  });

  server.on("/DrinksConsumed/9", [](){
    server.send(200, "text/plain", String(drinksConsumed[8]));
  });

  server.on("/DrinksConsumed/10", [](){
    server.send(200, "text/plain", String(drinksConsumed[9]));
  });

  server.on("/DrinksConsumed/11", [](){
    server.send(200, "text/plain", String(drinksConsumed[10]));
  });

  server.on("/DrinksConsumed/12", [](){
    server.send(200, "text/plain", String(drinksConsumed[11]));
  });

  server.on("/DrinksConsumed/13", [](){
    server.send(200, "text/plain", String(drinksConsumed[12]));
  });

  server.on("/DrinksConsumed/14", [](){
    server.send(200, "text/plain", String(drinksConsumed[13]));
  });

  server.on("/DrinksConsumed/15", [](){
    server.send(200, "text/plain", String(drinksConsumed[14]));
  });



  // server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  // // Setting the ESP as an access point
  // Serial.print("Setting AP (Access Point)…");
  // // Remove the password parameter, if you want the AP (Access Point) to be open
  // WiFi.softAP(ssid, password);




  // IPAddress IP = WiFi.softAPIP();
  // Serial.print("AP IP address: ");
  // Serial.println(IP);
  // server.on("/QR_DATA", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send_P(200, "text/plain",VAL);
  // });
  // server.begin();
}




void loop()
{
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

  if(WiFi.status() == WL_CONNECTED){
    // change ip to get information from weight sensor.
    currentDrinksLeft = httpGETRequest("http://172.20.10.8/drinksLeft").toInt();
    if(currentDrinksLeft > previousDrinksLeft){
      previousDrinksLeft = currentDrinksLeft;
    }
    else if (currentDrinksLeft < previousDrinksLeft) {
      drinksConsumed[drinksCounter] = previousDrinksLeft-currentDrinksLeft;
      previousDrinksLeft = currentDrinksLeft;
    }
  }

  if (mySerial.available()) // Check if there is Incoming Data in the Serial Buffer.
  {
    while (mySerial.available()) // Keep reading Byte by Byte from the Buffer till the Buffer is empty
    {
      char input = mySerial.read(); // Read 1 Byte of data and store it in a character variable
      Serial.print(input); // Print the Byte
      content.concat(input);
      delay(5); // A small delay
    }
    Serial.println();
    int index = content.indexOf(',');
    customerName = content.substring(0,index);
    content = content.substring(index + 1);
    Serial.print(content);
    Serial.println();
    if (content == "Obama"){
      VAL = "1";
      server.handleClient();
      delay(1000);

      alreadyInArray = false;
      for(int i=0;i<15;i=i+1){
        if(customers[i] == customerName){
          alreadyInArray = true;
          drinksCounter = i;
          break;
        }
      }

      if(customersIndex <= 14 && !alreadyInArray){
        customers[customersIndex] = customerName;
        drinksCounter = customersIndex;
        customersIndex = customersIndex + 1;
        alreadyInArray = false;
      }
      content = "";
    }
    else{
      content = "";
    }
  }
  else
  {
    VAL = "0";
    content = "";
  }
}

String httpGETRequest(const char* serverName) {
 WiFiClient client;
 HTTPClient http;
    
 http.begin(client, serverName);
  
 int httpResponseCode = http.GET();
  
 String payload = "--"; 
  
  if (httpResponseCode>0) {
   // Serial.print("HTTP Response code: ");
   // Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
   // Serial.print("Error code: ");
   // Serial.println(httpResponseCode);
  }
 http.end();

 return payload;
}

