#include <Servo.h>
Servo cdReflector;

int pos = 90;
int eastSerial = A0;
int westSerial = A5;

void setup() {
  cdReflector.attach(9);
  Serial.begin(9600);
}

void loop() {
  int east = analogRead(eastSerial);
  int west = analogRead(westSerial);

  if (abs(east - west) < 50) {
    pos = 86;
  } else if (east > west) {
    pos = min(pos + 5, 116);
  } else {
    pos = max(pos - 5, 56);
  }

  cdReflector.write(pos);
  Serial.println("East: " + String(east) + ", West: " + String(west));

  delay(50);

}
