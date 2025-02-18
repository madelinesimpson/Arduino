const int pinIRd = 8;
const int pinIRa = A0;
const int pinLED = 2;
const int pinBuzzer = 3;
const int pinButton = 4; // Button to reset alarm

int IRvalueA = 0;
int IRvalueD = 0;
int lastIRvalueD = 0;
bool alarmActive = false;

void setup() {
  Serial.begin(9600);
  pinMode(pinIRd, INPUT);
  pinMode(pinIRa, INPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  lastIRvalueD = digitalRead(pinIRd);
}

void loop() {
  IRvalueA = analogRead(pinIRa);
  IRvalueD = digitalRead(pinIRd);

  //Serial.print("Analog Reading=");
  //Serial.print(IRvalueA);
  //Serial.print("\t Digital Reading=");
  //Serial.println(IRvalueD);

  if (IRvalueD != lastIRvalueD) {
    alarmActive = true; // Activate alarm
  }
  lastIRvalueD = IRvalueD; // Store last IR value

  if (alarmActive) {
    digitalWrite(pinLED, HIGH);
    tone(pinBuzzer, 80);
    delay(200);
    digitalWrite(pinLED, LOW);
    noTone(pinBuzzer);
    delay(200);
    Serial.print("INTRUDER!!!!!!!!!!!!");

    if (digitalRead(pinButton) == LOW) { 
      delay(50);
      if (digitalRead(pinButton) == LOW) {
        alarmActive = false;
        digitalWrite(pinLED, LOW);
        noTone(pinBuzzer);
        Serial.print("Alarm disarmed.")
      }
    }
  }

  delay(100);
}
