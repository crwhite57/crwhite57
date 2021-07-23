/*
   This is a basic example on how to use Espalexa, its device declaration and a Multiplexor.

   This code is edited for controlling 16 Appliances and 4 LCDs with same addresses by
   Cleveland White 
   for Building From Scratch YouTube channel 

   You can visit the channel to see
   complete tutorial on making this project
   by yoursleves

   YouTube Channel :- https://youtu.be/8NnFFMyaHkM


          Building From Scratch
   explore | learn | share
*/

#include <Wire.h>
#include <WiFi.h>
#include <Espalexa.h>
// start of settings for LCD1602 with I2C
#include <LiquidCrystal_I2C.h>

// Define the multiplexer's address
#define TCAADDR 0x70

// setting the name for each sepperate LCD channel
LiquidCrystal_I2C lcd1(0x27, 20, 4);
//LiquidCrystal_I2C lcd2(0x27, 20, 4);
//LiquidCrystal_I2C lcd3(0x27, 20, 4);
//LiquidCrystal_I2C lcd4(0x27, 20, 4);

// Forward declaration of our print routine
void displayLCD(int channel, LiquidCrystal_I2C &LCD);

// Adafruit's channel selection function
void tcaselect(uint8_t i)
{
if(i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}


// Define your 16 relays names with their GPIO number Do not use GPIO 22 or 23 incase you wish to use any I2C devices
#define R1 36 //ADC0 Able to Dim Lights with solid state relay
#define R2 39 //ADC3 Able to Dim Lights with solid state relay
#define R3 35
#define R4 32
#define R5 33
#define R6 25
#define R7 26
#define R8 27
#define R9 34 //ADC6 Able to Dim Lights with solid state relay
#define R10 14
#define R11 12
#define R12 13
#define R13 23
#define R14 24
#define R15 25
#define R16 26
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
const char* ssid = "SSID Name";
const char* password = "SSID PASSWORD";

// device names for each device that Alexa will see
String Device_1_Name = "Lounge Lights";
String Device_2_Name = "Kitchen Lights";
String Device_3_Name = "Half Bath Lights";
String Device_4_Name = "Full Bath Lights";
String Device_5_Name = "Hallway Lights";
String Device_6_Name = "Master Bedroom Lights";
String Device_7_Name = "Guest Room 1 Lights";
String Device_8_Name = "Guest Room 2 Lights";
String Device_9_Name = "Gazebo Lights";
String Device_10_Name = "Sun Deck Lights";
String Device_11_Name = "Lower Deck Lights";
String Device_12_Name = "Night Lights";
String Device_13_Name = "Navigation Lights";
String Device_14_Name = "Flood Lights";
String Device_15_Name = "Anchor Lights";
String Device_16_Name = "Docking Lights";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  // Initialise the LCD 1
  tcaselect(0);
  lcd1.begin();
  lcd1.clear();
  lcd1.noCursor();
  lcd1.backlight();
  lcd1.setCursor(0,0);
  lcd1.print("LCD 1 Ready ");  

  // Initialise the LCD 2
  tcaselect(1);
  lcd1.begin();
  lcd1.clear();
  lcd1.noCursor();
  lcd1.backlight();
  lcd1.setCursor(0,0);
  lcd1.print("LCD 2 Ready ");  

  // Initialise the LCD 3
  tcaselect(2);
  lcd1.begin();
  lcd1.clear();
  lcd1.noCursor();
  lcd1.backlight();
  lcd1.setCursor(0,0);
  lcd1.print("LCD 3 Ready ");  

  // Initialise the LCD 4
  tcaselect(3);
  lcd1.begin();
  lcd1.clear();
  lcd1.noCursor();
  lcd1.backlight();
  lcd1.setCursor(0,0);
  lcd1.print("LCD 4 Ready ");  

  //Short pause
  delay(5000);
// start of settings for LCD1602 with I2C
  tcaselect(0);
  lcd1.begin();  
  lcd1.backlight();
  lcd1.clear();
  //lcd.autoscroll();
  lcd1.print("Pontoon Houseboat");
  lcd1.setCursor(0,1);
  lcd1.print("  Automation");  
  lcd1.setCursor(0,2);
  lcd1.print("    System"); 
  delay(2000); 

// This tells the program that these relay pins are outputs
    lcd1.clear();
    lcd1.setCursor(0,2);
    lcd1.println("Initializing");  
delay(2000);

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

  digitalWrite(R1, LOW);
      tcaselect(0);
      lcd1.setCursor(0,0);
      lcd1.print("Lounge Lights OFF");  
      digitalWrite(R2, LOW);
      lcd1.setCursor(0,1);
      lcd1.print("Kitchen Lights OFF");  
      digitalWrite(R3, LOW);
      lcd1.setCursor(0,2);
      lcd1.print("Half Bathroom OFF");  
      digitalWrite(R4, LOW);
      lcd1.setCursor(0,3);
      lcd1.print("Full Bathroom OFF");  
      digitalWrite(R5, LOW);

      tcaselect(1);
      lcd1.setCursor(0,0);
      lcd1.print("Hallway Lights OFF");  
  digitalWrite(R6, LOW);
      lcd1.setCursor(0,1);
      lcd1.print("Master Bedroom OFF");  
  digitalWrite(R7, LOW);
      lcd1.setCursor(0,2);
      lcd1.print("Guest Room 1 OFF");  
  digitalWrite(R8, LOW);
      lcd1.setCursor(0,3);
      lcd1.print("Guest Room 2 OFF");  
  digitalWrite(R9, LOW);
      tcaselect(2);
      lcd1.setCursor(0,0);
      lcd1.print("Gazebo Lights OFF");  
  digitalWrite(R10, LOW);
      lcd1.setCursor(0,1);
      lcd1.print("Sun Deck Lights OFF");  
  digitalWrite(R11, LOW);
      lcd1.setCursor(0,2);
      lcd1.print("Lower Deck Light OFF");  
  digitalWrite(R12, LOW);
      lcd1.setCursor(0,3);
      lcd1.print("Night Lights OFF");  
      tcaselect(3);
  digitalWrite(R13, LOW);
      lcd1.setCursor(0,0);
      lcd1.print("Nav Lights OFF");  
  digitalWrite(R14, LOW);
      lcd1.setCursor(0,1);
      lcd1.print("Flood Lights OFF");  
  digitalWrite(R15, LOW);
      lcd1.setCursor(0,2);
      lcd1.print("Anchor Lights OFF");  
  digitalWrite(R16, LOW);
      lcd1.setCursor(0,3);
      lcd1.print("Docking Lights OFF");  
  delay(2000);
  
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
  delay(5);
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
      digitalWrite(R1, LOW);
      Serial.println("Lounge Lights ON");
      tcaselect(0);
      lcd1.setCursor(0,0);
      lcd1.print("Lounge Lights ON ");  

    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R1, HIGH);
    Serial.println("Lounge Lights OFF");
      tcaselect(0);
      lcd1.setCursor(0,0);
      lcd1.print("Lounge Lights OFF");  
  }
}

void light2LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R2, LOW);
      Serial.println("Kitchen Lights ON");
      tcaselect(0);
      lcd1.setCursor(0,1);
      lcd1.print("Kitchen Lights ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R2, HIGH);
    Serial.println("Kitchen Lights OFF");
      tcaselect(0);
      lcd1.setCursor(0,1);
      lcd1.print("Kitchen Lights OFF ");  
  }
}

void light3LightChanged(uint8_t brightness)
{


  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R3, LOW);
      Serial.println("Half Bathroom ON");
      tcaselect(0);
      lcd1.setCursor(0,2);
      lcd1.print("Half Bathroom ON  ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R3, HIGH);
    Serial.println("Half Bathroom OFF");
      tcaselect(0);
      lcd1.setCursor(0,2);
      lcd1.print("Half Bathroom OFF ");  
  }
}

void light4LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R4, LOW);
      Serial.println("Full Bathroom ON");
      tcaselect(0);
      lcd1.setCursor(0,3);
      lcd1.print("Full Bathroom ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R4, HIGH);
    Serial.println("Full Bathroom OFF");
      tcaselect(0);
      lcd1.setCursor(0,3);
      lcd1.print("Full Bathroom OFF");  
  }
}

void light5LightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R5, LOW);
      Serial.println("Hallway Lights ON");
      tcaselect(1);
      lcd1.setCursor(0,0);
      lcd1.print("Hallway Lights ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R5, HIGH);
    Serial.println("Hallway Lights OFF");
      tcaselect(1);
      lcd1.setCursor(0,0);
      lcd1.print("Hallway Lights OFF ");  
  }
}

void light6LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R6, LOW);
      Serial.println("Master Bedroom ON");
      tcaselect(1);
      lcd1.setCursor(0,1);
      lcd1.print("Master Bedroom ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R6, HIGH);
    Serial.println("Master Bedroom OFF");
      tcaselect(1);
      lcd1.setCursor(0,1);
      lcd1.print("Master Bedroom OFF");  
  }
}

void light7LightChanged(uint8_t brightness)
{

  //Control the device  
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R7, LOW);
      Serial.println("Guest Room 1 ON");
      tcaselect(1);
      lcd1.setCursor(0,2);
      lcd1.print("Guest Room 1 ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R7, HIGH);
    Serial.println("Guest Room 1 OFF");
      tcaselect(1);
      lcd1.setCursor(0,2);
      lcd1.print("Guest Room 1 OFF");  
  }
}

void light8LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R8, LOW);
      Serial.println("Guest Room 2 ON");
      tcaselect(1);
      lcd1.setCursor(0,3);
      lcd1.print("Guest Room 2 ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R8, HIGH);
    Serial.println("Guest Room 2 OFF");
      tcaselect(1);
      lcd1.setCursor(0,3);
      lcd1.print("Guest Room 2 OFF");  
  }
}

void light9LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R9, LOW);
      Serial.println("Gazebo Lights ON");
      tcaselect(2);
      lcd1.setCursor(0,0);
      lcd1.print("Gazebo Lights ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R9, HIGH);
    Serial.println("Gazebo Lights OFF");
      tcaselect(2);
      lcd1.setCursor(0,0);
      lcd1.print("Gazebo Lights OFF");  
  }
}

void light10LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R10, LOW);
      Serial.println("Sun Deck Lights ON");
      tcaselect(2);
      lcd1.setCursor(0,1);
      lcd1.print("Sun Deck Lights ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R10, HIGH);
    Serial.println("Sun Deck Lights OFF");
      tcaselect(2);
      lcd1.setCursor(0,1);
      lcd1.print("Sun Deck Lights OFF");  
  }
}

void light11LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R11, LOW);
      Serial.println("Lower Deck Lights ON");
      tcaselect(2);
      lcd1.setCursor(0,2);
      lcd1.print("Lower Deck Light ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R11, HIGH);
    Serial.println("Lower Deck Lights OFF");
      tcaselect(2);
      lcd1.setCursor(0,2);
      lcd1.print("Lower Deck Light OFF");  
  }
}

void light12LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R12, LOW);
      Serial.println("Night Lights ON");
      tcaselect(2);
      lcd1.setCursor(0,3);
      lcd1.print("Night Lights ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R12, HIGH);
    Serial.println("Night Lights OFF");
      tcaselect(2);
      lcd1.setCursor(0,3);
      lcd1.print("Night Lights OFF");  
  }
}

void light13LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R13, LOW);
      Serial.println("Nav Lights ON");
      tcaselect(3);
      lcd1.setCursor(0,0);
      lcd1.print("Nav Lights ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R13, HIGH);
    Serial.println("Nav Lights OFF");
      tcaselect(3);
    lcd1.setCursor(0,0);
    lcd1.print("Nav Lights OFF");  
  }
}

void light14LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R14, LOW);
      Serial.println("Flood Lights ON");
      tcaselect(3);
      lcd1.setCursor(0,1);
      lcd1.print("Flood Lights ON ");  
}
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R14, HIGH);
    Serial.println("Flood Lights OFF");
      tcaselect(3);
      lcd1.setCursor(0,1);
      lcd1.print("Flood Lights OFF");  
  }
}

void light15LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R15, LOW);
      Serial.println("Anchor Lights ON");
      tcaselect(3);
      lcd1.setCursor(0,2);
      lcd1.print("Anchor Lights ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R15, HIGH);
    Serial.println("Anchor Lights OFF");
      tcaselect(3);
      lcd1.setCursor(0,2);
      lcd1.print("Anchor Lights OFF");  
  }
}

void light16LightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R16, LOW);
      Serial.println("Docking Lights ON");
      tcaselect(3);
      lcd1.setCursor(0,3);
      lcd1.print("Docking Lights ON ");  
    }
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    digitalWrite(R16, HIGH);
    Serial.println("Docking Lights OFF");
      tcaselect(3);
      lcd1.setCursor(0,3);
      lcd1.print("Docking Lights OFF");  
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
