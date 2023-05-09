/*******************************************************************************
 * Start of Arduino_GFX setting
 * 
 * Arduino_GFX try to find the settings depends on selected board in Arduino IDE
 * Or you can define the display dev kit not in the board list
 * Defalult pin list for non display dev kit:
 * Arduino Nano, Micro and more: CS:  9, DC:  8, RST:  7, BL:  6, SCK: 13, MOSI: 11, MISO: 12
 * ESP32 various dev board     : CS:  5, DC: 27, RST: 33, BL: 22, SCK: 18, MOSI: 23, MISO: nil
 * ESP32-C3 various dev board  : CS:  7, DC:  2, RST:  1, BL:  3, SCK:  4, MOSI:  6, MISO: nil
 * ESP32-S2 various dev board  : CS: 34, DC: 38, RST: 33, BL: 21, SCK: 36, MOSI: 35, MISO: nil
 * ESP32-S3 various dev board  : CS: 40, DC: 41, RST: 42, BL: 48, SCK: 36, MOSI: 35, MISO: nil
 * ESP8266 various dev board   : CS: 15, DC:  4, RST:  2, BL:  5, SCK: 14, MOSI: 13, MISO: 12
 * Raspberry Pi Pico dev board : CS: 17, DC: 27, RST: 26, BL: 28, SCK: 18, MOSI: 19, MISO: 16
 * RTL8720 BW16 old patch core : CS: 18, DC: 17, RST:  2, BL: 23, SCK: 19, MOSI: 21, MISO: 20
 * RTL8720_BW16 Official core  : CS:  9, DC:  8, RST:  6, BL:  3, SCK: 10, MOSI: 12, MISO: 11
 * RTL8722 dev board           : CS: 18, DC: 17, RST: 22, BL: 23, SCK: 13, MOSI: 11, MISO: 12
 * RTL8722_mini dev board      : CS: 12, DC: 14, RST: 15, BL: 13, SCK: 11, MOSI:  9, MISO: 10
 * Seeeduino XIAO dev board    : CS:  3, DC:  2, RST:  1, BL:  0, SCK:  8, MOSI: 10, MISO:  9
 * Teensy 4.1 dev board        : CS: 39, DC: 41, RST: 40, BL: 22, SCK: 13, MOSI: 11, MISO: 12
 ******************************************************************************/
#include <Arduino_GFX_Library.h>
#include <JPEGDEC.h>
#include <LittleFS.h>
#include "JpegFunc.h"
#include "FreeMono8pt7b.h"
#include "FreeSansBold10pt7b.h"
#include "FreeSerifBoldItalic12pt7b.h"
#include <SD_MMC.h>


#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include <JPEGDecoder.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>


// Ip for LCD ESP: 172.20.10.2

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
}



#define GFX_BL GFX_NOT_DEFINED // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

/* More dev device declaration: https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration */
#if defined(DISPLAY_DEV_KIT)
Arduino_GFX *gfx = create_default_Arduino_GFX();
#else /* !defined(DISPLAY_DEV_KIT) */

// /* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
// Arduino_DataBus *bus = create_default_Arduino_DataBus();

// /* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
// Arduino_GFX *gfx = new Arduino_ILI9341(bus, DF_GFX_RST, 0 /* rotation */, false /* IPS */);

Arduino_DataBus *bus1 = new Arduino_SWSPI(2 /* DC */, -1 /* CS */, 18 /* SCK */, 23 /* MOSI */, GFX_NOT_DEFINED /* MISO */);

Arduino_GFX *gfx1 = new Arduino_ILI9488_18bit(bus1, 4 /* RST */, 1 /* rotation */, false /* IPS */);


// Arduino_DataBus *bus2 = new Arduino_SWSPI(2 /* DC */, 26 /* CS */, 18 /* SCK */, 23 /* MOSI */, GFX_NOT_DEFINED /* MISO */);

// Arduino_GFX *gfx2 = new Arduino_ILI9488_18bit(bus2, 4/* RST */, 1 /* rotation */, false /* IPS */);


// Arduino_DataBus *bus3 = new Arduino_SWSPI(2 /* DC */, 22 /* CS */, 18 /* SCK */, 23 /* MOSI */, GFX_NOT_DEFINED /* MISO */);

// Arduino_GFX *gfx3 = new Arduino_ILI9488_18bit(bus3, 4 /* RST */, 3 /* rotation */, false /* IPS */);


// Arduino_DataBus *bus4 = new Arduino_SWSPI(2 /* DC */, 21 /* CS */, 18 /* SCK */, 23 /* MOSI */, GFX_NOT_DEFINED /* MISO */);

// Arduino_GFX *gfx4 = new Arduino_ILI9488_18bit(bus4, 4/* RST */, 3 /* rotation */, false /* IPS */);

#endif /* !defined(DISPLAY_DEV_KIT) */
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

int FirstScreenCS = 25;
int SecondScreenCS = 26;
int ThirdScreenCS = 22;
int FourthScreenCS = 21;

int h,w;
int pictureWidth, pictureHeight;
File picture;

bool coke = false;
bool drpepper = false;
bool mountaindew = false;
bool pepsi = false;
bool sprite = false;
bool rootbeer = false;

void setup(void)
{
  #ifdef GFX_BL
    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);
  #endif

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

  server.on("/cokeTrue", [](){
    coke = true;
    server.send(200, "text/plain", "0");
  });

  server.on("/cokeFalse", [](){
    coke = false;
    server.send(200, "text/plain", "0");
  });

  server.on("/drpepperTrue", [](){
    drpepper = true;
    server.send(200, "text/plain", "0");
  });

  server.on("/drpepperFalse", [](){
    drpepper = false;
    server.send(200, "text/plain", "0");
  });

  server.on("/mountaindewTrue", [](){
    mountaindew = true;
    server.send(200, "text/plain", "0");
  });

  server.on("/mountaindewFalse", [](){
    mountaindew = false;
    server.send(200, "text/plain", "0");
  });

  server.on("/pepsiTrue", [](){
    pepsi = true;
    server.send(200, "text/plain", "0");
  });

  server.on("/pepsiFalse", [](){
    pepsi = false;
    server.send(200, "text/plain", "0");
  });

  server.on("/rootbeerTrue", [](){
    rootbeer = true;
    server.send(200, "text/plain", "0");
  });

  server.on("/rootbeerFalse", [](){
    rootbeer = false;
    server.send(200, "text/plain", "0");
  });

  server.on("/spriteTrue", [](){
    sprite = true;
    server.send(200, "text/plain", "0");
  });

  server.on("/spriteFalse", [](){
    sprite = false;
    server.send(200, "text/plain", "0");
  });

  // server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  pinMode(FirstScreenCS, OUTPUT);
  pinMode(SecondScreenCS, OUTPUT);
  pinMode(ThirdScreenCS, OUTPUT);
  pinMode(FourthScreenCS, OUTPUT);

  digitalWrite(FirstScreenCS,LOW);
  digitalWrite(SecondScreenCS,LOW);
  digitalWrite(ThirdScreenCS,LOW);
  digitalWrite(FourthScreenCS,LOW);

  gfx1->begin();

  digitalWrite(FirstScreenCS,LOW);
  digitalWrite(SecondScreenCS,HIGH);
  digitalWrite(ThirdScreenCS,HIGH);
  digitalWrite(FourthScreenCS,HIGH);

  gfx1->fillScreen(BLACK);
  gfx1->setRotation(1);
  gfx1->setCursor(0, 0);
  gfx1->setTextSize(3);
  gfx1->println("Hello from Display #1");

  digitalWrite(FirstScreenCS,HIGH);
  digitalWrite(SecondScreenCS,LOW);
  digitalWrite(ThirdScreenCS,HIGH);
  digitalWrite(FourthScreenCS,HIGH);

  gfx1->fillScreen(BLACK);
  gfx1->setRotation(1);
  gfx1->setCursor(0, 0);
  gfx1->setTextSize(3);
  gfx1->println("Hello from Display #2");

  digitalWrite(FirstScreenCS,HIGH);
  digitalWrite(SecondScreenCS,HIGH);
  digitalWrite(ThirdScreenCS,LOW);
  digitalWrite(FourthScreenCS,HIGH);

  gfx1->fillScreen(BLACK);
  gfx1->setRotation(3);
  gfx1->setCursor(0, 0);
  gfx1->setTextSize(3);
  gfx1->println("Hello from Display #3");

  digitalWrite(FirstScreenCS,HIGH);
  digitalWrite(SecondScreenCS,HIGH);
  digitalWrite(ThirdScreenCS,HIGH);
  digitalWrite(FourthScreenCS,LOW);

  gfx1->fillScreen(BLACK);
  gfx1->setRotation(3);
  gfx1->setCursor(0, 0);
  gfx1->setTextSize(3);
  gfx1->println("Hello from Display #4");

  SPIClass *sd_Card = new SPIClass(HSPI);
  sd_Card->begin();
  // sd_Card.begin(33,19,32,5);

  if(!SD.begin(15,*sd_Card)){
    Serial.println("ERROR: File System Mount Failed!");
  }


  // Draw Logo on Screen 1
  digitalWrite(FirstScreenCS,LOW);
  digitalWrite(SecondScreenCS,HIGH);
  digitalWrite(ThirdScreenCS,HIGH);
  digitalWrite(FourthScreenCS,HIGH);
  gfx1->fillScreen(BLACK);
  gfx1->setRotation(1);
  w = gfx1->width();
  h = gfx1->height();

  picture = SD.open("/logo.jpg", FILE_READ);
  JpegDec.decodeSdFile(picture);
  pictureWidth = JpegDec.width;
  pictureHeight = JpegDec.height;

  jpegDraw("/logo.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h/2-pictureHeight/2/* y */, w /* widthLimit */, h /* heightLimit */);

  // Draw Logo on Screen 2
  digitalWrite(FirstScreenCS,HIGH);
  digitalWrite(SecondScreenCS,LOW);
  digitalWrite(ThirdScreenCS,HIGH);
  digitalWrite(FourthScreenCS,HIGH);
  gfx1->fillScreen(BLACK);
  gfx1->setRotation(1);
  w = gfx1->width();
  h = gfx1->height();

  picture = SD.open("/logo.jpg", FILE_READ);
  JpegDec.decodeSdFile(picture);
  pictureWidth = JpegDec.width;
  pictureHeight = JpegDec.height;

  jpegDraw("/logo.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h/2-pictureHeight/2/* y */, w /* widthLimit */, h /* heightLimit */);

  // Draw Logo on Screen 3
  digitalWrite(FirstScreenCS,HIGH);
  digitalWrite(SecondScreenCS,HIGH);
  digitalWrite(ThirdScreenCS,LOW);
  digitalWrite(FourthScreenCS,HIGH);
  gfx1->fillScreen(BLACK);
  gfx1->setRotation(3);
  w = gfx1->width();
  h = gfx1->height();
  
  picture = SD.open("/logo.jpg", FILE_READ);
  JpegDec.decodeSdFile(picture);
  pictureWidth = JpegDec.width;
  pictureHeight = JpegDec.height;

  jpegDraw("/logo.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h/2-pictureHeight/2/* y */, w /* widthLimit */, h /* heightLimit */);

  // Draw Picture on Screen 4
  digitalWrite(FirstScreenCS,HIGH);
  digitalWrite(SecondScreenCS,HIGH);
  digitalWrite(ThirdScreenCS,HIGH);
  digitalWrite(FourthScreenCS,LOW);
  gfx1->fillScreen(BLACK);
  gfx1->setRotation(3);
  w = gfx1->width();
  h = gfx1->height();
  
  picture = SD.open("/logo.jpg", FILE_READ);
  JpegDec.decodeSdFile(picture);
  pictureWidth = JpegDec.width;
  pictureHeight = JpegDec.height;

  jpegDraw("/logo.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h/2-pictureHeight/2/* y */, w /* widthLimit */, h /* heightLimit */);

  // delay(5000);

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

  digitalWrite(FirstScreenCS,HIGH);
  digitalWrite(SecondScreenCS,HIGH);
  digitalWrite(ThirdScreenCS,HIGH);
  digitalWrite(FourthScreenCS,LOW);
  gfx1->fillScreen(BLACK);
  gfx1->setRotation(3);
  gfx1->setCursor(10, 60);
  gfx1->setTextSize(3);
  gfx1->setFont(&FreeSansBold10pt7b);
  gfx1->print("R3 COOLER");

  gfx1->setCursor(10, 170);
  gfx1->setTextSize(2);
  gfx1->print("Temperature");
  gfx1->setCursor(10, 200);
  gfx1->setTextSize(4);
  gfx1->setFont();
  // set temperature here
  gfx1->print("68.42 ");
  // gfx1->print(httpGETRequest("http://172.20.10.5/coolerTemperature"));
  gfx1->setTextSize(2);
  gfx1->print("o");
  gfx1->setTextSize(4);
  gfx1->print("F");


  digitalWrite(FirstScreenCS,HIGH);
  digitalWrite(SecondScreenCS,HIGH);
  digitalWrite(ThirdScreenCS,LOW);
  digitalWrite(FourthScreenCS,HIGH);
  gfx1->fillScreen(BLACK);
  gfx1->setRotation(3);


  gfx1->setCursor(10,40);
  gfx1->setTextSize(2);
  gfx1->setFont(&FreeSansBold10pt7b);
  gfx1->print("Drinks Left");
  gfx1->setCursor(10, 70);
  gfx1->setTextSize(4);
  gfx1->setFont();
  // set drinks left here
  // gfx1->print("12");
  gfx1->print(httpGETRequest("http://6.tcp.ngrok.io:19717/drinksLeft"));

  gfx1->setCursor(240,180);
  gfx1->setTextSize(2);
  gfx1->print("Designed & Built by:");
  gfx1->setCursor(240,200);
  gfx1->print("Emily Marin");
  gfx1->setCursor(240,220);
  gfx1->print("Andres Garcia");
  gfx1->setCursor(240,240);
  gfx1->print("Ethan Dixon");
  gfx1->setCursor(240,260);
  gfx1->print("Abhishek Jasti");
  gfx1->setCursor(240,280);
  gfx1->print("Anand Jasti");

  if(!coke && !drpepper && !mountaindew && !pepsi && !rootbeer && !sprite){

    // Draw Logo on Screen 1
    digitalWrite(FirstScreenCS,LOW);
    digitalWrite(SecondScreenCS,HIGH);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();

    picture = SD.open("/logo.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/logo.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h/2-pictureHeight/2/* y */, w /* widthLimit */, h /* heightLimit */);

    // Draw Logo on Screen 2
    digitalWrite(FirstScreenCS,HIGH);
    digitalWrite(SecondScreenCS,LOW);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();

    picture = SD.open("/logo.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/logo.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h/2-pictureHeight/2/* y */, w /* widthLimit */, h /* heightLimit */);


    server.handleClient();
    delay(10000);
  }

  if(coke){
    // Draw Picture on Screen 1
    digitalWrite(FirstScreenCS,LOW);
    digitalWrite(SecondScreenCS,HIGH);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/Coke1.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/Coke1.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h-pictureHeight/* y */, w /* widthLimit */, h /* heightLimit */);


    // Draw Picture on Screen 2
    digitalWrite(FirstScreenCS,HIGH);
    digitalWrite(SecondScreenCS,LOW);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/Coke2.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/Coke2.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, 0/* y */, w /* widthLimit */, h /* heightLimit */);

    server.handleClient();

    delay(10000);
  }

  if(drpepper){
    // Draw Picture on Screen 1
    digitalWrite(FirstScreenCS,LOW);
    digitalWrite(SecondScreenCS,HIGH);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/DrPepper1.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/DrPepper1.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h-pictureHeight/* y */, w /* widthLimit */, h /* heightLimit */);


    // Draw Picture on Screen 2
    digitalWrite(FirstScreenCS,HIGH);
    digitalWrite(SecondScreenCS,LOW);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/DrPepper2.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/DrPepper2.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, 0/* y */, w /* widthLimit */, h /* heightLimit */);

    server.handleClient();

    delay(10000);
  }

  if(mountaindew){
    // Draw Picture on Screen 1
    digitalWrite(FirstScreenCS,LOW);
    digitalWrite(SecondScreenCS,HIGH);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/MountainDew1.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/MountainDew1.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h-pictureHeight/* y */, w /* widthLimit */, h /* heightLimit */);


    // Draw Picture on Screen 2
    digitalWrite(FirstScreenCS,HIGH);
    digitalWrite(SecondScreenCS,LOW);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/MountainDew2.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/MountainDew2.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, 0/* y */, w /* widthLimit */, h /* heightLimit */);
    
    server.handleClient();

    delay(10000);
  }

  if(pepsi){
    // Draw Picture on Screen 1
    digitalWrite(FirstScreenCS,LOW);
    digitalWrite(SecondScreenCS,HIGH);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/Pepsi1.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/Pepsi1.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h-pictureHeight/* y */, w /* widthLimit */, h /* heightLimit */);


    // Draw Picture on Screen 2
    digitalWrite(FirstScreenCS,HIGH);
    digitalWrite(SecondScreenCS,LOW);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/Pepsi2.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/Pepsi2.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, 0/* y */, w /* widthLimit */, h /* heightLimit */);

    server.handleClient();

    delay(10000);
  }

  if(sprite){
    // Draw Picture on Screen 1
    digitalWrite(FirstScreenCS,LOW);
    digitalWrite(SecondScreenCS,HIGH);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/Sprite1.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/Sprite1.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h-pictureHeight/* y */, w /* widthLimit */, h /* heightLimit */);


    // Draw Picture on Screen 2
    digitalWrite(FirstScreenCS,HIGH);
    digitalWrite(SecondScreenCS,LOW);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/Sprite2.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/Sprite2.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, 0/* y */, w /* widthLimit */, h /* heightLimit */);

    server.handleClient();

    delay(10000);
  }

  if(rootbeer){
    // Draw Picture on Screen 1
    digitalWrite(FirstScreenCS,LOW);
    digitalWrite(SecondScreenCS,HIGH);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/RootBeer1.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/RootBeer1.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, h-pictureHeight/* y */, w /* widthLimit */, h /* heightLimit */);


    // Draw Picture on Screen 2
    digitalWrite(FirstScreenCS,HIGH);
    digitalWrite(SecondScreenCS,LOW);
    digitalWrite(ThirdScreenCS,HIGH);
    digitalWrite(FourthScreenCS,HIGH);
    // gfx1->fillScreen(BLACK);
    gfx1->setRotation(1);
    w = gfx1->width();
    h = gfx1->height();
  
    picture = SD.open("/RootBeer2.jpg", FILE_READ);
    JpegDec.decodeSdFile(picture);
    pictureWidth = JpegDec.width;
    pictureHeight = JpegDec.height;

    jpegDraw("/RootBeer2.jpg", jpegDrawCallback, true /* useBigEndian */, w/2-pictureWidth/2/* x */, 0/* y */, w /* widthLimit */, h /* heightLimit */);

    server.handleClient();
    
    delay(10000);
  }

  

}

 // pixel drawing callback
static int jpegDrawCallback(JPEGDRAW *pDraw)
{
  // Serial.printf("Draw pos = %d,%d. size = %d x %d\n", pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
  gfx1->draw16bitBeRGBBitmap(pDraw->x, pDraw->y, pDraw->pPixels, pDraw->iWidth, pDraw->iHeight);
  return 1;
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


