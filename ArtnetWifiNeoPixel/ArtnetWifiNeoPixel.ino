/*
This example will receive multiple universes via Artnet and control a strip of ws2811 leds via 
Adafruit's NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel
This example may be copied under the terms of the MIT license, see the LICENSE file for details
*/

#if defined(ARDUINO_ARCH_ESP32)
#include "ScrollingText.h"
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include "RenderEngine.h"
#include "ScrollingText.h"
#include "RandomPoint.h"
#include <Ticker.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WiFiManager.h> 

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

// Neopixel settings
const int numLeds = 420; // change for your setup
const int numberOfChannels = numLeds * 3; // Total number of channels you want to receive (1 led = 3 channels)
const byte dataPin = 3;
//Adafruit_NeoPixel leds = Adafruit_NeoPixel(numLeds, dataPin, NEO_GRB + NEO_KHZ800);

// Neomatrix settings
Adafruit_NeoMatrix ledMatrix = Adafruit_NeoMatrix(30, 14, dataPin,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

//RenderObjects
const int tickerMs = 40;
Ticker frameTicker;
RenderEngine renderEngine(&ledMatrix);
ScrollingText scrollingText(&ledMatrix);
ScrollingText scrollingTextLine2(&ledMatrix);
ScrollingText middleTextMiddle(&ledMatrix);
RandomPoint randomPoint(&ledMatrix);

// connect to wifi – returns true if successful or false if not
boolean ConnectWifi(void)
{
  WiFiManager wifiManager;
  wifiManager.autoConnect();
  Serial.println("connected...yeey :)");
  scrollingTextLine2.SetText(WiFi.localIP().toString());
  return true;
}

//void initTest()
//{
//  for (int i = 0 ; i < numLeds ; i++)
//    leds.setPixelColor(i, 127, 0, 0);
//  leds.show();
//  delay(500);
//  for (int i = 0 ; i < numLeds ; i++)
//    leds.setPixelColor(i, 0, 127, 0);
//  leds.show();
//  delay(500);
//  for (int i = 0 ; i < numLeds ; i++)
//    leds.setPixelColor(i, 0, 0, 127);
//  leds.show();
//  delay(500);
//  for (int i = 0 ; i < numLeds ; i++)
//    leds.setPixelColor(i, 0, 0, 0);
//  leds.show();
//  Serial.println("initTest. Done.");
//}

void initTest2()
{
  showText("initTest2");
  Serial.println("initTest2. Done.");
}

void showText(String text){
  ledMatrix.setBrightness(40);
  ledMatrix.fillScreen(ledMatrix.Color(0, 0, 0));
  ledMatrix.setTextColor(ledMatrix.Color(0, 255, 0));
  ledMatrix.setCursor(0, 0);
  ledMatrix.setTextWrap(true);
  ledMatrix.print(text);
  ledMatrix.show();
}

void setupHttpUpdate()
{
  httpUpdater.setup(&httpServer);
  httpServer.on("/", HTTP_GET, handleRoot);
  httpServer.on("/command", HTTP_POST, handleCommand);
  httpServer.begin();  
  Serial.println("setupHttpUpdate. Done.");
}

static const char updateTextHtml[] PROGMEM =
        R"(<html><body><form method='POST' action='command' enctype='multipart/form-data'>
                  <input type='text' name='scrolltext' placeholder='Scrolling text'>
                  <br/>
			      <input type='text' name='middletext' placeholder='Middle text'>
                  <br/>
				  <input type='text' name='scrolltext2' placeholder='Scrolling text line 2'>
                  <br/>
                  <input type='submit' value='Send'>
               </form>
         </body></html>)";

void handleRoot() {
  httpServer.send(200, "text/html", updateTextHtml);
}

void handleCommand() {
  String argScrollText = httpServer.arg("scrolltext");
  String argMiddleText = httpServer.arg("middletext");
  String argScrollText2 = httpServer.arg("scrolltext2");

  scrollingText.SetText(argScrollText);
  middleTextMiddle.SetText(argMiddleText);
  scrollingTextLine2.SetText(argScrollText2);

  httpServer.send(200, "text/html", updateTextHtml);
}

void frameUpdate() {
	renderEngine.FrameUpdate(tickerMs);
}

void setup()
{
  Serial.begin(115200);
  ledMatrix.begin();
  showText("Wifi...");
  ConnectWifi();
  //initTest();
  initTest2();
  setupHttpUpdate();
  
  scrollingText.SetText("scrolling test text");

  scrollingTextLine2.TargetSpeedMs = 40;
  scrollingTextLine2.PositionY = 7;
  scrollingTextLine2.TextColor = ledMatrix.Color(0, 255, 255);

  middleTextMiddle.SetText("Static");
  middleTextMiddle.TargetSpeedMs = 0;
  middleTextMiddle.PositionX = 0;
  middleTextMiddle.PositionY = 3;
  middleTextMiddle.TextColor = ledMatrix.Color(255, 255, 0);

  renderEngine.AddObject(&scrollingText);
  renderEngine.AddObject(&scrollingTextLine2);
  renderEngine.AddObject(&middleTextMiddle);
  renderEngine.AddObject(&randomPoint);

  frameTicker.attach_ms(tickerMs, frameUpdate);

  showText("Hello");
}

void loop()
{
  httpServer.handleClient();
}
