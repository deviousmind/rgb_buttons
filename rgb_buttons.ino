//pinout won't change - make const
#define BLUE 3
#define GREEN 5
#define RED 6
#define BTN_R 7
#define BTN_GR 8
#define BTN_BL 12
#define BTN_PWR 13

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
  pinMode(BTN_R, INPUT_PULLUP);
  currentRed = digitalRead(BTN_R);

  //start green off
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN, LOW);
  pinMode(BTN_GR, INPUT_PULLUP);
  currentGreen = digitalRead(BTN_GR);

  //start blue off
  pinMode(BLUE, OUTPUT);
  digitalWrite(BLUE, LOW);
  pinMode(BTN_BL, INPUT_PULLUP);
  currentBlue = digitalRead(BTN_BL);

  //get power button state for toggle
  pinMode(BTN_PWR, INPUT_PULLUP);
  currentPower = digitalRead(BTN_PWR);
}

void loop() {
  //check power toggle first
  lastPower = currentPower;
  currentPower = digitalRead(BTN_PWR);
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
    currentRed = digitalRead(BTN_R);
    if(lastRed == LOW && currentRed == HIGH) {
      //red pressed, toggle red led
      redLedState = !redLedState;
    }
  
    lastGreen = currentGreen;
    currentGreen = digitalRead(BTN_GR);
    if(lastGreen == LOW && currentGreen == HIGH) {
      //green pressed, toggle green led
      greenLedState = !greenLedState;
    }
    
    lastBlue = currentBlue;
    currentBlue = digitalRead(BTN_BL);
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
