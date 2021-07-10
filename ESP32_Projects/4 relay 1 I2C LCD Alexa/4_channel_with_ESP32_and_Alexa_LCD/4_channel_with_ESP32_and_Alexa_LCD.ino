/*
   This is a basic example on how to use Espalexa and its device declaration methods.

   This code is edited for controlling 16 Appliances and 4 LCDs with same addresses by
   Cleveland White 
   for Building From Scratch YouTube channel 

   You can visit the channel to see
   complete tutorial on making this project
   by yoursleves

   YouTube Channel :- https://www.youtube.com/channel/UCOGIb90EIX9c0AdaNbF_yjA


          techiesms
   explore | learn | share
*/

#include <Wire.h>
#include <WiFi.h>
#include <Espalexa.h>
// start of settings for LCD1602 with I2C
#include <LiquidCrystal_I2C.h>


// setting the name for each sepperate LCD channel
LiquidCrystal_I2C lcd1(0x27, 20, 4);

// Forward declaration of our print routine
//void displayLCD(int channel, LiquidCrystal_I2C &LCD);




// Define your 16 relays names with their GPIO number Do not use GPIO 22 or 23 incase you wish to use any I2C devices
#define RelayPin1 32 //ADC0
#define RelayPin2 5 //ADC3
#define RelayPin3 17 //ADC6
#define RelayPin4 16 //ADC7

// prototypes
boolean connectWifi();

//callback functions for each relay or pin output
void device1Changed(uint8_t brightness);
void device2Changed(uint8_t brightness);
void device3Changed(uint8_t brightness);
void device4Changed(uint8_t brightness);
// Change this!!

// WiFi Credentials
const char* ssid = "whitehouse";
const char* password = "shadow57";

// device names for each device that Alexa will see
String Device_1_Name = "Lounge Lights";
String Device_2_Name = "Kitchen Lights";
String Device_3_Name = "Half Bath Lights";
String Device_4_Name = "Full Bath Lights";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  // Initialise the LCD 1
  lcd1.begin();
  lcd1.clear();
  lcd1.noCursor();
  lcd1.backlight();
  lcd1.setCursor(0,0);
  lcd1.print("LCD 1 Ready ");  

// start of settings for LCD1602 with I2C
  lcd1.begin();  
  lcd1.backlight();
  lcd1.clear();
  //lcd.autoscroll();
  lcd1.setCursor(0,0);
  lcd1.print("Pontoon Houseboat");
  lcd1.setCursor(0,1);
  lcd1.print("  Automation");  
  lcd1.setCursor(0,2);
  lcd1.print("    System"); 
  delay(2000); 
 

// This tells the processor the these pins are output pins "Triger Pins"
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

// This will set all output pin to off on reboot or reset
      lcd1.setCursor(0,0);
      lcd1.print("Lounge Lights OFF ");
      digitalWrite(RelayPin1, HIGH);

      lcd1.setCursor(0,1);
      lcd1.print("Kitchen Lights OFF");
      digitalWrite(RelayPin2, HIGH);

      lcd1.setCursor(0,2);
      lcd1.print("Half Bath Lights OFF");
      digitalWrite(RelayPin3, HIGH);

      lcd1.setCursor(0,3);
      lcd1.print("Full Bath Lights OFF");
      digitalWrite(RelayPin4, HIGH);
  delay(2000);
  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {

    // Define your devices here.
    // This links the device names you gave alexa with a LightChange call back function
    espalexa.addDevice(Device_1_Name, device1Changed);
    espalexa.addDevice(Device_2_Name, device2Changed);
    espalexa.addDevice(Device_3_Name, device3Changed);
    espalexa.addDevice(Device_4_Name, device4Changed);
 
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
  delay(5);
 }



//our callback functions
//This links the relay name with the LightChange function to turn the relay on or off
void device1Changed(uint8_t brightness){

  //Control the device
  if (brightness == 255)
    {
//     digitalWrite(RelayPin1, LOW); \\is used if you use a pin on your chip
      digitalWrite(RelayPin1, LOW);
      lcd1.setCursor(0,0);
      lcd1.print("Lounge Lights ON ");  
      Serial.println("Lounge Lights ON");
    }
  else if (brightness == 0)
  {
//     digitalWrite(RelayPin1, HIGH); \\is used if you use a pin on your chip
    digitalWrite(RelayPin1, HIGH);
      lcd1.setCursor(0,0);
      lcd1.print("Lounge Lights OFF");  
Serial.println("Lounge Lights OFF");
  }
}

void device2Changed(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin2, LOW);
      lcd1.setCursor(0,1);
      lcd1.print("Kitchen Lights ON ");  
      Serial.println("Kitchen Lights ON");
    }
  else
  {
    digitalWrite(RelayPin2, HIGH);
      lcd1.setCursor(0,1);
      lcd1.print("Kitchen Lights OFF");  
    Serial.println("Kitchen Lights OFF");
  }
}

void device3Changed(uint8_t brightness)
{
  //Control the device  
  if (brightness == 255)
    {
      digitalWrite(RelayPin3, LOW);
      lcd1.setCursor(0,2);
      lcd1.print("Half Bath Lights ON ");  
      Serial.println("Half Bath Lights ON");
    }
  else
  {
    digitalWrite(RelayPin3, HIGH);
      lcd1.setCursor(0,2);
      lcd1.print("Half Bath Lights OFF");  
    Serial.println("Half Bath Lights OFF");
  }
}

void device4Changed(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin4, LOW);
      lcd1.setCursor(0,3);
      lcd1.print("Full Bath Lights ON ");  
      Serial.println("Full Bath Lights ON");
    }
  else
  {
    digitalWrite(RelayPin4, HIGH);
      lcd1.setCursor(0,3);
      lcd1.print("Full Bath Lights OFF");  
    Serial.println("Full Bath Lights OFF");
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
