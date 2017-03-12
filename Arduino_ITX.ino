#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;                  // variable to store the servo position.
int ledblue = 13;            //variable to store the position of the blue led.
int ledgreen = 7;           //variable to store the position of the green led.
int ledorange = 6;                //variable to store the position of the yellow led.
int ledred = 5;                  // variable to store the position of the red led.
int sensorPin = A0;             // varaible to select the input pin position of the ldr.
int sensorValue = 0;           // variable to store the value coming from the sensor.
int buttonPin = 2;            // the position of the pushbutton pin.
int buttonState = 0;         // variable for reading the pushbutton status.
int buzzer = 11;             // the position of the piezo pin.
int laser1 = 10;            // the position of the laser1 pin.
int laser2 = 12;            // the position of the laser2 pin.
int detector1 = A1;         // the position of the detector1 pin.
int detector1Value;         // variable to store the values received by the detector1.
int detector2 = 8;          // the position of the detector2 pin.
int detector2Value;         // variable to store the values received by the detector2.


void setup() {
  Serial.begin(9600);       // port 9600 openned
  myservo.attach(9);        // attaches the servo on pin 9 to the servo object.

  pinMode(ledblue, OUTPUT);         // initialize blue led as an output.
  pinMode(ledgreen, OUTPUT);        // initialize green led as an output.
  pinMode(ledorange, OUTPUT);       // initialize yellow led as an output.
  pinMode(ledred, OUTPUT);          // initialize red led as an output.
  pinMode(buttonPin, INPUT);        // initialize the pushbutton pin as an input:
  pinMode(buzzer, OUTPUT);          // set buzzer as an output.
  pinMode(laser1, OUTPUT);          // set laser1 as an output.
  pinMode(laser2, OUTPUT);          // set laser2 as an output.
  pinMode(detector1, INPUT);        // set detector1 as an input.
  pinMode(detector2, INPUT);        // set detector2 as an input.
  
}


void laser() {
  digitalWrite(laser1, HIGH);       // turns the laser1 on.
  digitalWrite(laser2, HIGH);       // turns the laser2 on.
}

void adultcase() {
  if (sensorValue < 30) {           //setting a threshold for the ldr
    digitalWrite(ledblue, HIGH);    // turns the blue led on.
  } //turns led ON
  else {digitalWrite(ledblue, LOW);}    // turns the blue led off.
  digitalWrite(ledgreen, HIGH);             // turns the green led on.
  myservo.attach(9);                        // attaches the servo on pin 9 to the servo object.
  for (pos = 0; pos <= 90; pos += 1) {    // goes from 0 degrees to 90 degrees in steps of 1 degree.
    myservo.write(pos);                   // tell servo to go to position in variable 'pos'.
    delay(15);                            // waits 15ms for the servo to reach the position.
  }
  delay(5000);            // waits 5s after the servo has reached the position.
  for (pos = 90; pos >= 0; pos -= 1) {      // goes from 90 degrees to 0 degrees.
    myservo.write(pos);                     // tell servo to go to position in variable 'pos'.
    delay(15);                          // waits 15ms for the servo to reach the position.
  }
  delay(5000);            // waits 5s after the servo has reached the position.
  digitalWrite(ledgreen, LOW);          // turns the green led off.
}

void childcase() {
  if (sensorValue < 30) {             //setting a threshold for the ldr
    digitalWrite(ledblue, HIGH);      //turns blue led ON
  } 
  else {digitalWrite(ledblue, LOW);}    //turns blue led OFF
  digitalWrite(ledred, HIGH);           //turns red led ON
  for (int i = 0; i <= 10; i++) {
    tone(buzzer, 1000, 500);              //send 1KHz and 500Hz sound signal...
    delay(1000);                      // wait for 1 sec
  }    
  delay(2000);                        // waits 2s after the piezo has sounded.
  digitalWrite(ledred, LOW);          // turns the red led off.
}



void unknown() {
  if (sensorValue < 30) {           //setting a threshold for the ldr
    digitalWrite(ledblue, HIGH);    //turns blue led ON
  } 
  else {digitalWrite(ledblue, LOW);}    //turns blue led OFF
  digitalWrite(ledorange, HIGH);         //turns yellow led ON
  for (int i = 0; i < 7; i++) {
    tone(buzzer, 1000, 500);            //send 1KHz and 500Hz sound signal....
    delay(1000);                        //for 1 sec
  }
  digitalWrite(ledorange, LOW);          //turns yellow led OFF
}

void mycase() {

  if ((detector1Value <= 800) && (detector2Value == 0)) {     // checks if detector1 and detector2 are not receiving values
    adultcase();                                              // initialize adultcase 
  } else if ((detector1Value > 800 ) && (detector2Value == 0)) {      // checks if detector1 is receiving value and also detector 2 is not recieving value
    childcase();                                                // initialize childcase
  } else{unknown();}                                            // initialize unknown case
}

void loop() {
 
  buttonState = digitalRead(buttonPin);                         // read the state of the pushbutton value
  if (buttonState == HIGH) {                                    // checks the buttonState
    laser();                                                    // initialize the lasers

    sensorValue = analogRead(sensorPin);                        // reads the value from the sensor
    Serial.println(sensorValue);                                // prints the values coming from the sensor on the screen
    detector1Value = analogRead(detector1);                     // reads the value from detector1
    Serial.println(detectorValue);                              // prints the values coming from the detector1 on the screen
    detector2Value = digitalRead(detector2);                    // reads the value from detector2
    Serial.println(detector2Value);                             // prints the values coming from the detector2 on the screen
   
    mycase();                                                   // mycase is initialized
    
  }
}


