#include "HX711.h"
#include "math.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Ip for Weight Sensor ESP: 172.20.10.8

const char* ssid1 = "-_-";
const char* password = "its8characters";

#define EAP_IDENTITY "anand.jasti@student.csulb.edu" //if connecting from another corporation, use identity@organisation.domain in Eduroam 
#define EAP_USERNAME "anand.jasti@student.csulb.edu" //oftentimes just a repeat of the identity
#define EAP_PASSWORD "s<uw$uNkHsCZ4;a" //your Eduroam password
const char* ssid = "eduroam"; // Eduroam SSID
int counter = 0;

WebServer server(8888);

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
}


#define calibration_factor -48100 //This value is obtained using the SparkFun_HX711_Calibration sketch


#define LOADCELL_DOUT_PIN  17
#define LOADCELL_SCK_PIN  16
int A = 1;
// float B = 0;
float C = 100;
float D = 0;
int drinks = 0;


HX711 scale;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

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

  server.on("/drinksLeft", [](){
    server.send(200, "text/plain", String(drinks));
  });

  // server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0


  Serial.println("Readings:");


}


void loop() {
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid1);
  }
  while (WiFi.status() != WL_CONNECTED) { //during lost connection, print dots
    delay(500);
    Serial.print(".");
  }
  server.handleClient();
  
  drinks = round(scale.get_units()/0.8);
  D = (scale.get_units());
  if(drinks == 0 && C != drinks) {
    Serial.print("0"); //scale.get_units() returns a float
    Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
    Serial.println();
    Serial.print("No drinks, refill needed");
    Serial.println();
    A = 0;
    C = 0;
  }
  else if(drinks >= 1 && C != drinks)
  {
    Serial.println();
    Serial.print(D);
    Serial.print(" lbs");
    Serial.println();
    Serial.print(drinks);
    if(drinks==1){
      Serial.print(" drink");
    }
    else{
      Serial.print(" drinks");
    }    
    Serial.println();
    C = drinks;
  }
  delay(5000);
}


