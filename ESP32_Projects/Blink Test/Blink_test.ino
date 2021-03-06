/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6 and on the esp32 it is pin 2. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your board
  model, check the Technical Specs of your board.

  modified 26 May 2021
  by Cleveland White

  This example code is in the public domain.


*/
#define LED1 2 
// the setup function runs once when you press reset or power the board
void setup() {
  
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("On");
  delay(1000);                       // wait for a second
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("Off");
  delay(1000);                       // wait for a second
}
