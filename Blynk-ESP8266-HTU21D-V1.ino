
/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * Note: This requires ESP8266 support package:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <Wire.h>
#include "Adafruit_HTU21DF.h"

SimpleTimer timer;

Adafruit_HTU21DF htu = Adafruit_HTU21DF();

float temperatur = 10;
float humidity = 12;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxxxxx";
char pass[] = "xxxxxx";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  } 
  // Setup function to be called each 1000 milliseconds
  timer.setInterval(1000, sendUptime);
  timer.setInterval(5000, temp);
  
}

void temp()
{
  //Serial.print("Temp: "); Serial.print(htu.readTemperature());
  //Serial.print("\t\tHum: "); Serial.println(htu.readHumidity());
  temperatur = htu.readTemperature();
  humidity = htu.readHumidity();
  Blynk.virtualWrite(1, temperatur);
  Blynk.virtualWrite(2, humidity);
  
}

void sendUptime()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(5, millis()/1000);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
