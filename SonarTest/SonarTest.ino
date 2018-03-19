#include <NewPing.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

const int echoPin = 2;
const int triggerPin = 3;
const int maxDistance = 70;

int lastSonarTrigger = -5000;

ZumoMotors zMotors;
Pushbutton zButton(ZUMO_BUTTON);

NewPing sonar(triggerPin, echoPin, maxDistance);

void setup() {
  //Serial.begin(9600);
  zButton.waitForButton();
}

void loop() {
  int distance = sonar.ping_cm();
  if(distance != 0)
    lastSonarTrigger = millis();
  
  //Serial.println(distance);
  if(millis() - lastSonarTrigger < 200)
    zMotors.setSpeeds(10000, 10000); //Forward
  else
    zMotors.setSpeeds(400, -400);
}
