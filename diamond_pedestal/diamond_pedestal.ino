byte leds[] = {9}; // TODO: Add more leds
byte brightness[] = {0};
boolean rising[] = {true};

void setup() {
  // TODO: Set up input pins for buttons
}

void loop() {
  // Listen for button presses
  // TODO
  
  // Update leds
  for(int i = 0; i < sizeof(leds); i++) {
    // write
    analogWrite(leds[i], brightness[i]);
    // update brightness
    if(rising[i]) {
      brightness[i]++;
    } else {
      brightness[i]--;
    }
    if(brightness[i] >= 255 || brightness[i] <= 0) {
      rising[i] = !rising[i];
    }
  }
  delay(5);
}
