#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Ip for cooling system ESP: 172.20.10.5

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


// //These are color schemes for the ring meter.
// #define RED2RED 0
// #define GREEN2GREEN 1
// #define BLUE2BLUE 2
// #define BLUE2RED 3
// #define GREEN2RED 4
// #define RED2GREEN 5

// // Bit color for grey (does not exist with TFT)
// #define TFT_GREY  0x2104

//Defining GPIO ports for the 4-channel relay and the temperature sensor
#define RELAY_1     16
#define RELAY_2     17
#define RELAY_3     16 
#define RELAY_4     17
#define SENSOR_PIN  21

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

//Variables for temperature F/C
float tempC;
float tempF;
float prevTemp;

//Temp variables roughly for 45-55 degrees F
int temphigh= 30;
int templow = 27;


//boolean range_error = 0;

TFT_eSPI tft = TFT_eSPI();
void setup() {
  Serial.begin(9600); // initialize serial
  DS18B20.begin();    // initialize the DS18B20 sensor

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

  server.on("/coolerTemperature", [](){
    server.send(200,"text/plain",String(tempF));
  });

  // server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  //Setting the pins for the relay as output pins
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);

  //Draws and positions the label for 'TEMPERATURE'
  tft.init();
  tft.setTextSize(2);
  tft.fillScreen(TFT_BLACK);
  TextPrint("TEMPERATURE", TFT_WHITE, 60, 130, 3);
  
  //Displays the static value of the max temp (55 F)
  TextPrint("MAX", TFT_RED, 30, 400, 2);
  TextPrint("55", TFT_WHITE, 28, 420, 2);
  TextPrint("o", TFT_WHITE, 51, 415, 1);
  TextPrint("F", TFT_WHITE, 57, 420, 2);

  //Displays the static value of the min temp (45 F)
  TextPrint("MIN", TFT_BLUE, 253, 400, 2);
  TextPrint("45", TFT_WHITE, 250, 420, 2);
  TextPrint("o", TFT_WHITE, 273, 415, 1);
  TextPrint("F", TFT_WHITE, 280, 420, 2);

  //Shuts down 4-channel relay when board starts up
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
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

  // Command to grab value from temperature sensor
  DS18B20.requestTemperatures(); 
  tempC = DS18B20.getTempCByIndex(0);

  //Converting Celsius to Fahrenheit 
  tempF = tempC * 9 / 5 + 32;

  prevTemp = 0;

  //Output value of temperature from Celsius to Fahrenheit in terminal
  Serial.print("Temperature: ");
  Serial.print(tempC);   
  Serial.print(" C");
  Serial.print("  ~  ");  
  Serial.print(tempF);   
  Serial.println(" F");

  //This will display temperature (F) on the LCD screen
  if(tempC != prevTemp)
  {
    prevTemp = tempC;
    tft.fillRect(95,180,150,40,TFT_BLACK);
    tft.setTextColor(TFT_WHITE);    // print the temperature in °F
    tft.setTextSize(3);
    tft.setCursor(95, 180);
    tft.print(tempF);
    TextPrint("o", TFT_WHITE, 190, 170, 2);
    TextPrint("F", TFT_WHITE, 205, 180, 3);
  }

  //If temperature is less than 7 C(~45 F) the 2-Channel relay will turn off
  if(tempC < templow)
  {
    digitalWrite(RELAY_1, LOW);
    digitalWrite(RELAY_2, LOW);
    digitalWrite(RELAY_3, LOW);
    digitalWrite(RELAY_4, LOW);
  }

  //if temperature is more than 13 C(~45 F) the 2-Channel relay will turn on
  if(tempC > temphigh)
  {
    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4, HIGH);
   
  }


  

}

//Simple function that allows for easier text output LCD
void TextPrint(char *text, uint16_t color, int x, int y, int size)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.setTextWrap(true);
  tft.print(text);
}
