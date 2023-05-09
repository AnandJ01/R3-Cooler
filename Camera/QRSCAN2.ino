#include <Arduino.h>
#include <SoftwareSerial.h>
#include "WiFi.h"
// #include "ESPAsyncWebServer.h"




const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
const char* VAL;
String content = "";




// AsyncWebServer server(80);




SoftwareSerial mySerial(16, 17);


void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600); // set the data rate for the SoftwareSerial port




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
    content = content.substring(index + 1);
    Serial.print(content);
    Serial.println();
    if (content == "Obama"){
    VAL = "1";
    delay(1000);
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
  delay(1000);
}

