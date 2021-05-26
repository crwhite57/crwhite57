/*
   This is a basic example on how to use Espalexa and its device declaration methods.

   This code is edited for controlling 4 Appliances by
   Sachin Soni 
   for techiesms YouTube channel 

   You can visit the channel to see
   complete tutorial on making this project
   by yoursleves

   YouTube Channel :- https://www.youtube.com/techiesms


          techiesms
   explore | learn | share
*/

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

// Define your 16 relays names with their GPIO number Do not use GPIO 22 or 23 incase you wish to use any I2C devices
#define R1 11
#define R2 10
#define R3 9
#define R4 13
#define R5 12
#define R6 14
#define R7 27
#define R8 26
#define R9 25
#define R10 33
#define R11 32
#define R12 6
#define R13 7
#define R14 8
#define R15 15
#define R16 2
// The way I have the GPIO leaves 4 A pins and 6 more triger pins or some OLED displays 

// prototypes
boolean connectWifi();

//callback functions for each relay or pin output
void light1LightChanged(uint8_t brightness);
void light2LightChanged(uint8_t brightness);
void light3LightChanged(uint8_t brightness);
void light4LightChanged(uint8_t brightness);
void light5LightChanged(uint8_t brightness);
void light6LightChanged(uint8_t brightness);
void light7LightChanged(uint8_t brightness);
void light8LightChanged(uint8_t brightness);
void light9LightChanged(uint8_t brightness);
void light10LightChanged(uint8_t brightness);
void light11LightChanged(uint8_t brightness);
void light12LightChanged(uint8_t brightness);
void light13LightChanged(uint8_t brightness);
void light14LightChanged(uint8_t brightness);
void light15LightChanged(uint8_t brightness);
void light16LightChanged(uint8_t brightness);

// Change this!!

// WiFi Credentials
const char* ssid = "whitehouse";
const char* password = "shadow57";

// device names for each device that Alexa will see
String Device_1_Name = "Light One";
String Device_2_Name = "Light One";
String Device_3_Name = "Light Three";
String Device_4_Name = "Light Four";
String Device_5_Name = "Light Five";
String Device_6_Name = "Light Six";
String Device_7_Name = "Light Seven";
String Device_8_Name = "Light Eight";
String Device_9_Name = "Light Nine";
String Device_10_Name = "Light Ten";
String Device_11_Name = "Light Eleven";
String Device_12_Name = "Light Twelve";
String Device_13_Name = "Light Thirteen";
String Device_14_Name = "Light Fourteen";
String Device_15_Name = "Light Fifteen";
String Device_16_Name = "Light Sixteen";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

// This tells the processor the these pins are output pins "Triger Pins"
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(R9, OUTPUT);
  pinMode(R10, OUTPUT);
  pinMode(R11, OUTPUT);
  pinMode(R12, OUTPUT);
  pinMode(R13, OUTPUT);
  pinMode(R14, OUTPUT);
  pinMode(R15, OUTPUT);
  pinMode(R16, OUTPUT);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {

    // Define your devices here.
    // This links the device names you gave alexa with a LightChange call back function
    espalexa.addDevice(Device_1_Name, light1LightChanged);
    espalexa.addDevice(Device_2_Name, light2LightChanged);
    espalexa.addDevice(Device_3_Name, light3LightChanged);
    espalexa.addDevice(Device_4_Name, light4LightChanged);
    espalexa.addDevice(Device_5_Name, light5LightChanged);
    espalexa.addDevice(Device_6_Name, light6LightChanged);
    espalexa.addDevice(Device_7_Name, light7LightChanged);
    espalexa.addDevice(Device_8_Name, light8LightChanged);
    espalexa.addDevice(Device_9_Name, light9LightChanged);
    espalexa.addDevice(Device_10_Name, light10LightChanged);
    espalexa.addDevice(Device_11_Name, light11LightChanged);
    espalexa.addDevice(Device_12_Name, light12LightChanged);
    espalexa.addDevice(Device_13_Name, light13LightChanged);
    espalexa.addDevice(Device_14_Name, light14LightChanged);
    espalexa.addDevice(Device_15_Name, light15LightChanged);
    espalexa.addDevice(Device_16_Name, light16LightChanged);

    espalexa.begin();

  }

  else
  {
    while (1)
    {
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
//This links the relay name with the LightChange function to turn the relay on or off
void light1LightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R1, HIGH);
      Serial.println("Light 1 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R1, LOW);
    Serial.println("Light 1 OFF");
  }
}

void light2LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R2, HIGH);
      Serial.println("Light 2 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R2, LOW);
    Serial.println("Light 2 OFF");
  }
}

void light3LightChanged(uint8_t brightness)
{


  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R3, HIGH);
      Serial.println("Light 3 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R3, LOW);
    Serial.println("Light 3 OFF");
  }
}

void light4LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R4, HIGH);
      Serial.println("Light 4 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R4, LOW);
    Serial.println("Light 4 OFF");
  }
}

void light5LightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R5, HIGH);
      Serial.println("Light 5 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R5, LOW);
    Serial.println("Light 5 OFF");
  }
}

void light6LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R6, HIGH);
      Serial.println("Light 6 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R6, LOW);
    Serial.println("Light 6 OFF");
  }
}

void light7LightChanged(uint8_t brightness)
{

  //Control the device  
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R7, HIGH);
      Serial.println("Light 7 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R7, LOW);
    Serial.println("Light 7 OFF");
  }
}

void light8LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R8, HIGH);
      Serial.println("Light 8 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R8, LOW);
    Serial.println("Light 8 OFF");
  }
}

void light9LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R9, HIGH);
      Serial.println("Light 9 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R9, LOW);
    Serial.println("Light 9 OFF");
  }
}

void light10LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R10, HIGH);
      Serial.println("Light 10 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R10, LOW);
    Serial.println("Light 10 OFF");
  }
}

void light11LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R11, HIGH);
      Serial.println("Light 11 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R11, LOW);
    Serial.println("Light 11 OFF");
  }
}

void light12LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R12, HIGH);
      Serial.println("Light 12 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R12, LOW);
    Serial.println("Light 12 OFF");
  }
}

void light13LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R13, HIGH);
      Serial.println("Light 13 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R13, LOW);
    Serial.println("Light 13 OFF");
  }
}

void light14LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R14, HIGH);
      Serial.println("Light 14 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R14, LOW);
    Serial.println("Light 14 OFF");
  }
}

void light15LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R15, HIGH);
      Serial.println("Light 15 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R15, LOW);
    Serial.println("Light 15 OFF");
  }
}

void light16LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R16, HIGH);
      Serial.println("Light 16 ON");
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R16, LOW);
    Serial.println("Light 16 OFF");
  }
}


// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
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
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
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
