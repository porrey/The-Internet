// Copyright © 2017 Daniel Porrey
//
// This file is part of the Internet project
// on hackster.io.
//
// The_Internet.ino is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The_Internet.ino is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with The_Internet.c. If not, see http://www.gnu.org/licenses/.
//

// ***
// *** The pin on which the LED is connected.
// ***
#define LED_PIN 1

// ***
// *** Gamma correction for the LED fading. This
// *** gamma is for an LED with the anode connected
// *** to the pin, so the value should be reversed
// *** (255 - value).
// ***
const uint8_t gamma[] =
{
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

void setup()
{
  digitalWrite(LED_PIN, HIGH);
}

void loop()
{
  // ***
  // *** The first parameter is the number of times
  // *** to repeat. The second paramter is the delay
  // *** between changes; this controls the speed
  // *** of the effect.
  // ***
  breath(random(2, 8) , 10);

  // ***
  // *** The first parameter is the number of times
  // *** to repeat. The second parameter is the delay
  // *** between the on and off. Use a random delay
  // *** between 0.15 and 1.20 seconds.
  // ***
  flash(random(5, 100) , random(150, 1200));

  // ***
  // *** The first parameter is the number of times
  // *** to repeat. The second parameter is the number
  // *** of short pulses while the third parameter
  // *** is the number of long pulses.
  // ***
  signal(random(5, 100) , random(2, 5), random(2, 5));
}

// ***
// *** Fade the LED. Since the LED is wired
// *** with the cathode to the pin, a value
// *** of 255 turns the LED off.
// ***
void breath(uint16_t repeatCount, uint32_t delayTime)
{
  for (uint16_t i = 0; i < repeatCount; i++)
  {
    // ***
    // *** Fade the LED from off to on using
    // *** gamma correction to make it more
    // *** natural.
    // ***
    for (uint8_t j = 255; j > 0; j--)
    {
      analogWrite(LED_PIN, 255 - gamma[j]);
      delay(delayTime);
    }

    // ***
    // *** Fade the LED from on to off using
    // *** gamma correction to make it more
    // *** natural.
    // ***
    for (uint8_t k = 0; k < 255; k++)
    {
      analogWrite(LED_PIN, 255 - gamma[k]);
      delay(delayTime);
    }
  }
}

// ***
// *** Flashes the LED on and off the number
// *** of times specified. The delayTime is
// *** the amount of time between the on and
// *** off event.
// ***
void flash(uint16_t repeatCount, uint32_t delayTime)
{
  // ***
  // *** Make sure the pin is set for output.
  // ***
  pinMode(1, OUTPUT);

  // ***
  // *** Turn the LED on and off the specified
  // *** number of times.
  // ***
  for (uint16_t i = 0; i < repeatCount; i++)
  {
    digitalWrite(LED_PIN, LOW);
    delay(delayTime);
    digitalWrite(LED_PIN, HIGH);
    delay(delayTime);
  }
}

void signal(uint16_t repeatCount, uint8_t shortPulseCount, uint8_t longPulseCount)
{
  // ***
  // *** Turn the LED on and off the specified
  // *** number of times.
  // ***
  for (uint16_t i = 0; i < repeatCount; i++)
  {
    // ***
    // *** Turn the LED on and off the specified
    // *** number of times fast.
    // ***
    for (uint8_t j = 0; j < shortPulseCount; j++)
    {
      digitalWrite(LED_PIN, LOW);
      delay(125);
      digitalWrite(LED_PIN, HIGH);
      delay(125);
    }

    // ***
    // *** Turn the LED on and off the specified
    // *** number of times slow.
    // ***
    for (uint8_t k = 0; k < longPulseCount; k++)
    {
      digitalWrite(LED_PIN, LOW);
      delay(750);
      digitalWrite(LED_PIN, HIGH);
      delay(750);
    }
  }
}