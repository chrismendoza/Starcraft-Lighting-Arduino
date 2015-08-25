/* 
 * Model spacecraft nav and strobe lights 
 * 
 * Provides a quickly customizeable way to set up nav and strobe lights for use in lit models.
 */

/************************************ START CONFIGURATION ZONE *******************************************/

// Starting pin location for the strobe LEDs
const int strobePin0 = 11;

// Number of strobe LEDs attached (you could use a transistor to run more than one instead)
// (Example: if strobePin0 is 11, and strobePinCount is 3 the code assumes strobes exist on 11,12,13).
const int strobePinCount = 2;

// Starting pin location for the nav LEDs
const int navPin0 = 2;

// Number of nav LEDs attached (you could use a transistor to run more than one instead)
// (Example: if navPin0 is 11, and navPinCount is 3 the code assumes nav LEDs exist on 11,12,13).
const int navPinCount = 4;

// interval between strobe sets (in milliseconds)
const long strobeInterval = 1000;

// how long to leave the strobe on (in milliseconds)
const int strobeTime = 100;

// number of times to strobe per set.
const int strobeCount = 2;

// how long to leave the nav LEDs on/off (same time interval for both states).
const long navInterval = 1500;           // interval at which to blink (milliseconds)

/************************************* END CONFIGURATION ZONE ********************************************/

int strobeState = HIGH;
int navState = LOW;

unsigned long strobePreviousMillis = 0;
unsigned long navPreviousMillis = 0;

void setup() {
  // set the digital pin as output:
  for (int idx = 0; idx < strobePinCount; idx++)
  {
    pinMode(strobePin0 + idx, OUTPUT);
  }

  for (int idx = 0; idx < navPinCount; idx++)
  {
    pinMode(navPin0 + idx, OUTPUT);
  }
}

void loop()
{
  calcStrobeState();
  calcNavState();

  for (int idx = 0; idx < strobePinCount; idx++)
  {
    digitalWrite(strobePin0 + idx, strobeState);
  }

  for (int idx = 0; idx < navPinCount; idx++)
  {
    digitalWrite(navPin0 + idx, navState);
  }
}

void calcStrobeState()
{
  unsigned long currentMillis = millis();
 
  if(currentMillis - strobePreviousMillis >= strobeInterval) {
    // save the last time you blinked the LED 
    strobePreviousMillis = currentMillis;   
    strobeState = HIGH;
  }

  unsigned long sinceLast = currentMillis - strobePreviousMillis;

  // the number of times to cycle the strobe on or off based on the count specified by the user.
  int strobeCycles = (strobeCount * 2) - 1;

  for (int idx = 0; idx < strobeCycles; idx++) {
    if (sinceLast >= ((idx + 1) * strobeTime) && sinceLast < (((idx + 2) * strobeTime) - 1))
    {
      // turn the LEDs on if in an even part of the cycle, off if not.
      if ((idx + 1) % 2 == 0) {
        strobeState = HIGH;
      } else {
        strobeState = LOW;
      }
    }
  }
}

void calcNavState()
{
  unsigned long currentMillis = millis();

  if(currentMillis - navPreviousMillis >= navInterval) {
    // save the last time you blinked the LED 
    navPreviousMillis = currentMillis;
    if (digitalRead(navPin0) == HIGH) 
    {
      navState = LOW;
    } else {
      navState = HIGH;
    }
  }
}

