#include <ezButton.h>

//pinout won't change - make const
#define BLUE 3
#define GREEN 5
#define RED 6
ezButton redButton(7);
ezButton greenButton(8);
ezButton blueButton(12);
ezButton powerButton(13);

// btn states change - make var
int blueLedState = LOW;
int lastBlue;
int currentBlue;
int greenLedState = LOW;
int lastGreen;
int currentGreen;
int redLedState = LOW;
int lastRed;
int currentRed;
int powerState = LOW;
int lastPower;
int currentPower;
byte incoming;
byte powerMask = 0b1111;
byte redMask = 0b0001;
byte greenMask = 0b0010;
byte blueMask = 0b0100;
byte highMask = 0b0111;
byte resetMask = 0b1000;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  
  //start red off
  pinMode(RED, OUTPUT);
  digitalWrite(RED, LOW);
  redButton.setDebounceTime(50);
  redButton.loop();
  currentRed = redButton.getState();

  //start green off
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN, LOW);
  greenButton.setDebounceTime(50);
  greenButton.loop();
  currentGreen = greenButton.getState();

  //start blue off
  pinMode(BLUE, OUTPUT);
  digitalWrite(BLUE, LOW);
  blueButton.setDebounceTime(50);
  blueButton.loop();
  currentBlue = blueButton.getState();

  //get power button state for toggle
  powerButton.setDebounceTime(50);
  powerButton.loop();
  currentPower = powerButton.getState();
}

void loop() {
  //first check if communication over serial
  if(Serial.available() > 0)
  {
    incoming = Serial.read();
    Serial.print("Incoming data: ");
    Serial.print(incoming, BIN);
    Serial.print("\tRAW: ");
    Serial.print(incoming);
    Serial.print("\tPower data: ");
    Serial.print(powerMask, BIN);
    Serial.print("\tRed data: ");
    Serial.print(redMask, BIN);
    Serial.print("\tGreen data: ");
    Serial.print(greenMask, BIN);
    Serial.print("\tBlue data: ");
    Serial.print(blueMask, BIN);
    Serial.println();
    /* Toggle sequence
     *  0000 power off
     *  0001 red on
     *  0010 green on
     *  0100 blue on
     *  0111 power on (white)
     *  1000 reset
    */
    Serial.print("Compare: ");
    Serial.print("\tPOWER: ");
    byte maskedPower = incoming & powerMask;
    Serial.print(maskedPower, BIN);
    Serial.print("\tRED: ");
    byte maskedRed = incoming & redMask;
    Serial.print(maskedRed, BIN);
    Serial.print("\tGREEN: ");
    byte maskedGreen = incoming & greenMask;
    Serial.print(maskedGreen, BIN);
    Serial.print("\tBLUE: ");
    byte maskedBlue = incoming & blueMask;
    Serial.print(maskedBlue, BIN);
    Serial.println();
    if(maskedPower == 0b0000){
      Serial.println("Power off!");
      //kill power
      lastPower = HIGH;
      currentPower = HIGH;
      powerState = LOW;
          
      lastRed = powerState;
      redLedState = powerState;
    
      lastGreen = powerState;
      greenLedState = powerState;
    
      lastBlue = powerState;
      blueLedState = powerState;
    } else
    if((incoming & highMask) == highMask){
      Serial.println("Power on!");
      //white light, power ON
      lastPower = HIGH;
      currentPower = HIGH;
      powerState = HIGH;
          
      lastRed = powerState;
      redLedState = powerState;
    
      lastGreen = powerState;
      greenLedState = powerState;
    
      lastBlue = powerState;
      blueLedState = powerState;
    }
    else{
      // red control
      if(maskedRed == redMask){
        //switch on red
        Serial.println("Red on!");
        lastRed = HIGH;
        currentRed = HIGH;
        redLedState = HIGH;
      } else {
        //switch off red
        Serial.println("Red off!");
        lastRed = HIGH;
        currentRed = HIGH;
        redLedState = LOW;
      }

      //green control
      if(maskedGreen == greenMask){
        //switch on green
        Serial.println("Green on!");
        lastGreen = HIGH;
        currentGreen = HIGH;
        greenLedState = HIGH;
      } else {
        //switch off 
        Serial.println("Green off!");
        lastGreen = HIGH;
        currentGreen = HIGH;
        greenLedState = LOW;
      }
      
      //blue control
      if(maskedBlue == blueMask){
        //switch on blue
        Serial.println("Blue on!");
        lastBlue = HIGH;
        currentBlue = HIGH;
        blueLedState = HIGH;
      } else {
        //switch off blue
        Serial.println("Blue off!");
        lastBlue = HIGH;
        currentBlue = HIGH;
        blueLedState = LOW;
      }
    }
  }
  else
  {
    //check power toggle first
    lastPower = currentPower;
    powerButton.loop();
    currentPower = powerButton.getState();
    if(lastPower == LOW && currentPower == HIGH){
      //power button has been pressed, toggle power state on all
      Serial.println("Power button pressed!");
      powerState = !powerState;
          
      lastRed = powerState;
      redLedState = powerState;
    
      lastGreen = powerState;
      greenLedState = powerState;
    
      lastBlue = powerState;
      blueLedState = powerState;
    } 
    else {
      //update individual button states
      lastRed = currentRed;
      redButton.loop();
      currentRed = redButton.getState();
      if(lastRed == LOW && currentRed == HIGH) {
        //red pressed, toggle red led
        Serial.println("Red button pressed!");
        redLedState = !redLedState;
      }
    
      lastGreen = currentGreen;
      greenButton.loop();
      currentGreen = greenButton.getState();
      if(lastGreen == LOW && currentGreen == HIGH) {
        //green pressed, toggle green led
        Serial.println("Green button pressed!");
        greenLedState = !greenLedState;
      }
      
      lastBlue = currentBlue;
      blueButton.loop();
      currentBlue = blueButton.getState();
        if(lastBlue == LOW && currentBlue == HIGH) {
        //blue pressed, toggle blue led
        Serial.println("Blue button pressed!");
        blueLedState = !blueLedState;
      }
    }
  }
  
  //update LEDs
  digitalWrite(RED, redLedState);
  digitalWrite(GREEN, greenLedState);
  digitalWrite(BLUE, blueLedState);
}
