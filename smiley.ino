#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;
const int ledPin = 13;
int pitch;

int previousPitch = 0;
int currentPitch = 0;

unsigned long previousMillis = 0;
const long interval = 200;
unsigned long currentMillis;

void setup() {
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  while (millis() < 5000)
  {
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh)
    {
      sensorHigh = sensorValue;
    }

    if (sensorValue < sensorLow)
    {
      sensorLow = sensorValue;
    }

    digitalWrite(ledPin, LOW);
  }
}

void loop() {
  sensorValue = analogRead(A0);

  pitch = map (sensorValue, sensorLow, sensorHigh, 50, 4000);
  tone(8, pitch, 20);
  delay(10);

  currentPitch = pitch;

  currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    lcd.clear();
    if (currentPitch > previousPitch)
    {
      lcd.print(":D");
      previousPitch = currentPitch;
    }

    else if (currentPitch < previousPitch)
    {
      lcd.print(":(");
      previousPitch = currentPitch;
    }

    else
    {
      lcd.print(":|");
      previousPitch = currentPitch;
    }
  }
}
