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

void setup() {
  Serial.begin(9600);
  
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
  //check power toggle first
  lastPower = currentPower;
  powerButton.loop();
  currentPower = powerButton.getState();
  if(lastPower == LOW && currentPower == HIGH){
    //power button has been pressed, toggle power state on all
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
      redLedState = !redLedState;
    }
  
    lastGreen = currentGreen;
    greenButton.loop();
    currentGreen = greenButton.getState();
    if(lastGreen == LOW && currentGreen == HIGH) {
      //green pressed, toggle green led
      greenLedState = !greenLedState;
    }
    
    lastBlue = currentBlue;
    blueButton.loop();
    currentBlue = blueButton.getState();
      if(lastBlue == LOW && currentBlue == HIGH) {
      //blue pressed, toggle blue led
      blueLedState = !blueLedState;
    }
  }

  //update LEDs
  digitalWrite(RED, redLedState);
  digitalWrite(GREEN, greenLedState);
  digitalWrite(BLUE, blueLedState);
  Serial.println(redLedState);
  Serial.println(greenLedState);
  Serial.println(blueLedState);
  Serial.println(powerState);
}
