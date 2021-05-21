/*
 * This was created starting with the basic example from the ESPAlexa libriary and modified to turn relays on and off.
 * You an add upto 10 relays using this code for eather the Wemos D1 Mini or Wemos D1 R2 or R1.
 *I don't suggest doing more that 4 relays for the mini as there has been a problem that if you have more than 5 device on
 the Wemos D1 Mini, Alexa will not see any of them, and if you have 5 devices, the 5th one will not opperate reliably. */ 
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

// prototypes
boolean connectWifi();

//callback functions
//you cane rename these if you wish, but I suggest only change the word before "LightChanged(uint8_t brightness)"
//if you wish to add upto 6 more devices, just copy one and past it and give it a unique name before the
//"LightChanged(uint8_t brightness)"
void lightoneLightChanged(uint8_t brightness);
void lighttwoLightChanged(uint8_t brightness);
void lightthreeLightChanged(uint8_t brightness);
void lightfourLightChanged(uint8_t brightness);


// Define the name of the relays and their GPIO number
// Again if you add devices, you will need to add relayPin's and give them the GPIO# you want them to use

#define relayPin1 2
#define relayPin2 12
#define relayPin3 14
#define relayPin4 13


// Change this!!
const char* ssid = "YOUR SSID's NAME";
const char* password = "YOUR SSID PASSWORD";

boolean wifiConnected = false;

Espalexa espalexa;


void setup()
{
  Serial.begin(115200);

// This tells the program that these relay pins are outputs

  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Define your devices here. 
    // These are the device names that Alexa will find and add to your Alexa App
    // Copy a line to add up to 6  more devices
    espalexa.addDevice("Light One", lightoneLightChanged);
    espalexa.addDevice("Light Two", lighttwoLightChanged);
    espalexa.addDevice("Light Three", lightthreeLightChanged); 
    espalexa.addDevice("Light Four", lightfourLightChanged);
   
    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
   espalexa.loop();
   delay(1);
}

//our callback functions
// You can have up to 10 devices
// To add a device, copy from HERE
void lightoneLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(relayPin1, LOW);
      Serial.println("Light One ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(relayPin1, HIGH);
    Serial.println("Light One OFF");
  }
}
// TO HERE and past it after the last one
// You will need to change the name listed after where it say void the the name you are assigning to that relay
// you will also have to change the relayPin number

void lighttwoLightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(relayPin2, LOW);
      Serial.println("Light Two ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(relayPin2, HIGH);
    Serial.println("Light Two OFF");
  }
}

void lightthreeLightChanged(uint8_t brightness)
{


  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(relayPin3, LOW);
      Serial.println("Light Three ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(relayPin3, HIGH);
    Serial.println("Light Three OFF");
  }
}

void lightfourLightChanged(uint8_t brightness)
{


  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(relayPin4, LOW);
      Serial.println("Light Four ON");
    }
    Serial.print("ON, brightness ");
  }
  else
  {
    digitalWrite(relayPin4, HIGH);
    Serial.println("Light Four OFF");
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
