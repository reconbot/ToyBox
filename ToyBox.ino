/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

int LEDS[8] = {
  12,
  13,
  27,
  33,
  21,
  26,
  4,
  25
};

int LED_STATES[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void on(int lightNumber) {
  if (LED_STATES[lightNumber] == HIGH) {
    return;
  }

  LED_STATES[lightNumber] = HIGH;
  digitalWrite(LEDS[lightNumber], HIGH);
}

void off(int lightNumber) {
  if (LED_STATES[lightNumber] == LOW) {
    return;
  }
  LED_STATES[lightNumber] = LOW;
  digitalWrite(LEDS[lightNumber], LOW);
}

void flicker(int lightNumber) {
  int previousState = LED_STATES[lightNumber];
  int aroundLights[3];
  int previousStates[3];
  int column = lightNumber % 4;
  int row = lightNumber < 4 ? 0 : 1;
  int numberOfLightsAround = 0;

  // Above or below
  if (lightNumber < 4) {
    aroundLights[numberOfLightsAround] = lightNumber + 4;
  } else {
    aroundLights[numberOfLightsAround] = lightNumber - 4;
  }
  numberOfLightsAround++;

  // left if possible
  if (lightNumber != 0 && lightNumber != 4) {
    aroundLights[numberOfLightsAround] = lightNumber - 1;
    numberOfLightsAround++;
  }

  // right if possible
  if (lightNumber != 3 && lightNumber != 7) {
    aroundLights[numberOfLightsAround] = lightNumber + 1;
    numberOfLightsAround++;
  }

  for (int i = 0; i < numberOfLightsAround; ++i) {
    previousStates[i] = LED_STATES[aroundLights[i]];
  }

  for (int loop = 0; loop <= 1; ++loop) {
    off(lightNumber);
    delay(100);
    for (int i = 0; i < numberOfLightsAround; ++i) {
      on(aroundLights[i]);
    }
    delay(50);
    on(lightNumber);
    delay(100);
    for (int i = 0; i < numberOfLightsAround; ++i) {
      off(aroundLights[i]);
    }
    delay(50);
  }

  // restore states
  for (int i = 0; i < numberOfLightsAround; ++i) {
    if (previousStates[i] == HIGH) {
      on(aroundLights[i]);
    } else {
      off(aroundLights[i]);
    }
  }
  
  if (previousState == HIGH) {
    on(lightNumber);
  } else {
    off(lightNumber);
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  for (int i = 0; i < 8; ++i) {
    pinMode(LEDS[i], OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() {
  for (int i = 0; i < 8; ++i) {
    on(i);
  }

  delay(2000);

  for (int i = 0; i < 8; ++i) {
    off(i);
  }

  for (int i = 0; i < 8; ++i) {
    on(i);
    delay(500);
    flicker(i);
    delay(500);
    off(i);
    delay(500);
  }
}
