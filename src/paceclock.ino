/*!
 * arduino-paceclock
 */

/**
 * ATmega pins.
 */

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

/**
 * Digits of the paceclock.
 *
 * 00:00
 */

int m1 = 0;
int m2 = 0;
int s1 = 0;
int s2 = 0;

/**
 * Number of seconds to count down, must be <= 9.
 */

int countDownFrom = 9;

/**
 * On/off state of shift register registers (segments) for all digits in a
 * common-anode LED array.
 *
 *   0
 * 5   1
 *   6
 * 4   2
 *   3
 */

int digits[11] = {
  0b00000011, // 0
  0b10011111, // 1
  0b00100101, // 2
  0b00001101, // 3
  0b10011001, // 4
  0b01001001, // 5
  0b01000001, // 6
  0b00011111, // 7
  0b00000001, // 8
  0b00001001, // 9
  0b11111111, // blank
};

/**
 * Arduino setup function that is run once, at power-on.  The clock is cleared,
 * displays 88:88 to show that all segments work, is cleared again, then counts
 * down to 00:00.
 *
 * @api public
 */

void setup() {

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // show that all segments work

  display(8, 8, 8, 8);
  delay(1000);

  // clear the clock

  display(10, 10, 10, 10);
  delay(1000);

  // count down to 00:00

  for (int i = countDownFrom; i >= 0; i--) {
    display(0, 0, 0, i);
    delay(1000);
  }

}

/**
 * Arduino loop function that is run over and over.  This function counts from
 * 00:00 to 59:59 (then back to 00:00) and displays the digits.
 *
 * @api public
 */

void loop() {

  // count from 00:00 to 59:59

  if (s2 == 9) {
    if (s1 == 5) {
      if (m2 == 9) {
        if (m1 == 5) {
          m1 = 0;
        } else {
          m1 += 1;
        }
        m2 = 0;
      } else {
        m2 += 1;
      }
      s1 = 0;
    } else {
      s1 += 1;
    }
    s2 = 0;
  } else {
    s2 += 1;
  }

  // display the digits

  display(m1, m2, s1, s2);
  delay(1000);

}

/**
 * Display the digits by changing the states of the shift register registers
 * (for the segments).
 *
 * @api public
 */

void display(int minute1, int minute2, int second1, int second2) {

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, digits[minute1]);
  shiftOut(dataPin, clockPin, LSBFIRST, digits[minute2]);
  shiftOut(dataPin, clockPin, LSBFIRST, digits[second1]);
  shiftOut(dataPin, clockPin, LSBFIRST, digits[second2]);
  digitalWrite(latchPin, HIGH);

}
