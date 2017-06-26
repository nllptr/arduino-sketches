unsigned long time = 0;
byte brgtStep = 10;

byte leds[] = {9}; // TODO: Add more leds
int brightness[] = {0};
boolean rising[] = {true};
boolean enabled[] = {true};

byte buttons[] = {2}; // TODO: Add more buttons
int timeouts[] = {0};

void setup() {
  pinMode(buttons[0], INPUT_PULLUP);
  timeouts[0] = millis();
}

void loop() {
  // Some debounce magic to clean up button input.
  for(int i = 0; i < (sizeof(timeouts)/sizeof(int)); i++) {
    if((millis() - timeouts[i]) >= 200) {
      int buttonState = digitalRead(buttons[i]);
        if(buttonState == LOW) {
          enabled[i] = !enabled[i];
          timeouts[i] = millis();
        }
    }
  }
  
  // Update leds
  if(millis() - time >= 50) {
    for(int i = 0; i < sizeof(leds); i++) {
      if(enabled[i]) {
        analogWrite(leds[i], brightness[i]);
        if(rising[i]) {
          brightness[i] = brightness[i] + brgtStep;
          if(brightness[i] > 255) brightness[i] = 255;
        } else {
          brightness[i] = brightness[i] - brgtStep;
          if(brightness[i] < 0) brightness[i] = 0;
        }
        if(brightness[i] == 255 || brightness[i] == 0) {
          rising[i] = !rising[i];
        }
      } else {
        analogWrite(leds[i], 0);
        brightness[i] = 0;
      }
    }
    time = millis();
  }
}
