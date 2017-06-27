unsigned long time = 0;
byte brgtStep = 10;

byte leds[] = {9, 10, 11};
int brightness[sizeof(leds)];
boolean rising[sizeof(leds)];
boolean enabled[sizeof(leds)];

byte buttons[] = {2, 3, 4};
int timeouts[sizeof(buttons)];
int previousStates[sizeof(buttons)];

void setup() {
  for(int i = 0; i < sizeof(leds); i++) {
    brightness[i] = 0;
    rising[i] = true;
    enabled[i] = true;
  }
  
  for(int i = 0; i < sizeof(buttons); i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    timeouts[i] = millis();
    previousStates[i] = HIGH;
  }  
}

void loop() {
  // Some debounce magic to clean up button input.
  int readings[sizeof(buttons)];
  for(int i = 0; i < sizeof(buttons); i++) {
    readings[i] = digitalRead(buttons[i]);
  }
  
  for(int i = 0; i < sizeof(buttons); i++) {
    if((millis() - timeouts[i]) >= 200 && readings[i] != previousStates[i]) {
      timeouts[i] = millis();
      previousStates[i] = readings[i];
      if(readings[i] == LOW) {
        enabled[i] = !enabled[i];
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
