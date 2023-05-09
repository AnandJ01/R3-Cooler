#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverNameQR = "http://192.168.4.1/QR_DATA";

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

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
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