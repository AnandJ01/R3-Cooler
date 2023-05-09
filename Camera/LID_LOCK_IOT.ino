#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// const char* ssid = "ESP32-Access-Point";
// const char* password = "123456789";

// Ip for Lid lock ESP: 172.20.10.5:8888

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

//Your IP address or domain name with URL path
// change ip
const char* serverNameQR = "http://172.20.10.3:8888/QR_DATA";

String QR;
// define the pin number for the MOSFET gate
#define MOSFET_PIN 13

// define the pin number for the hall effect sensor
#define HALL_SENSOR_PIN 4

bool lidLocked = false;

void setup() {
  
  // initialize the serial port
  Serial.begin(115200);

  // initialize the MOSFET pin as an output
  pinMode(MOSFET_PIN, OUTPUT);

  // initialize the hall effect sensor pin as an input
  pinMode(HALL_SENSOR_PIN, INPUT);

  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  // IPAddress local_IP(10,39,21,192);
  // IPAddress gateway(10,39,0,1);
  // IPAddress subnet(225,225,128,0);
  // IPAddress dns(134,138,19,5);
  // IPAddress dns1(0,0,0,0);
  // if(!WiFi.config(local_IP, gateway, subnet,dns,dns1)){
  //   Serial.println("STA failed");
  // }
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

  server.on("/unlock", [](){
    unLockLid();
    server.send(200,"text/plain", "0");
  });

  server.begin();
  Serial.println("HTTP server started");

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
  
  Serial.println(QR);
  if(WiFi.status()== WL_CONNECTED ){ 
      QR = httpGETRequest(serverNameQR);
  // read the value of the hall effect sensor pin
  int hallValue = digitalRead(HALL_SENSOR_PIN);

  bool code = true; // QR-Code not detected
  if(QR == "0")
  {
    code == true;
  }
  else if(QR == "1")
  {
    code == false;
  }

if (hallValue == 0 && QR == "0") {
    if(!lidLocked){
      digitalWrite(MOSFET_PIN, HIGH);  // Lock the Magnetic Lid Lock
      lidLocked = true;
    }
  } else{
    if(lidLocked){
      digitalWrite(MOSFET_PIN, LOW); // Unlock the Magnetic Lid Lock
      lidLocked = false;
      delay(5000);
    }
  }
  }
  else {
      Serial.println("WiFi Disconnected");
    }
  
  // Read again after 1 second
  delay(500);
}

void unLockLid(){
  if(lidLocked){
    digitalWrite(MOSFET_PIN, LOW); // Unlock the Magnetic Lid Lock
    lidLocked = false;
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