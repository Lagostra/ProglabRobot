#include <PLab_ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <NewPing.h>
#include <MusicPlayer.h>

//Constants for the sonar
const int echoPin = 1;
const int triggerPin = 3;
const int resetPin = 0;
const int maxDistance = 50;

const int dirSelectPin = 4;

unsigned int sensorValues[6];

long lastSonarTrigger = -5000;
boolean isRunning = false;
boolean dirRight = true;

ZumoMotors zMotors;
Pushbutton zButton(ZUMO_BUTTON);
ZumoReflectanceSensorArray rSensors;
NewPing sonar(triggerPin, echoPin, maxDistance);


//Song
const int songLength = 73;
float notes[songLength] = {0, G4, G4, G4, Eb4, Bb4, G4, Eb4, Bb4, G4, D5, D5, 
                              D5, Eb5, Bb4, Gb4, Eb4, Bb4, G4, G5, 0, G5, 
                              Gb5, F5, E5, Eb5, E5, 0, 0, Ab4, Db5, C5, 
                              B4, Bb4, A4, Bb4, 0, 0, Eb4, G4, Eb4, G4,
                              Bb4, G4, Bb4, D5, G5, 0, G5, Gb5, F5, E5, 
                              Eb5, E5, 0, 0, Ab4, Db5, C5, B4, Bb4, A4, 
                              Bb4, 0, 0, Eb4, G4, Eb4, Bb4, G4, Eb4, Bb4, G4};
float toneLengths[songLength] = {2, 1, 1, 1, 0.75, 0.25, 1, 0.75, 0.25, 2, 1, 1, 
                                    1, 0.75, 0.25, 1, 0.75, 0.25, 2, 1, 1, 1, 
                                    0.75, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5, 1, 0.75, 
                                    0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5, 1, 0.75, 0.25, 
                                    1, 0.75, 0.25, 2, 1, 1, 1, 0.75, 0.25, 0.25, 
                                    0.25, 0.25, 0.25, 0.5, 0.5, 1, 0.75, 0.25, 0.25, 0.25, 
                                    0.25, 0.25, 0.5, 0.5, 1, 0.75, 0.25, 1, 0.75, 0.25, 2};
//Song end

long lastLoop = millis();
MusicPlayer mp(6, 104, 1/8, notes, toneLengths, songLength);
long reverseTimer = 0;

void setup() {
  pinMode(dirSelectPin, INPUT_PULLUP);
  rSensors.init(QTR_NO_EMITTER_PIN);
  pinMode(resetPin, OUTPUT);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  
  zButton.waitForButton(); //Wait for the user to push button on zumo-robot

  //Do initialization here (e.g. sensor calibration
  delay(500);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      zMotors.setSpeeds(-200, 200);
    else
      zMotors.setSpeeds(200, -200);
      
    rSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  zMotors.setSpeeds(0,0);
  zButton.waitForButton();
  dirRight = digitalRead(dirSelectPin);
  if(dirRight) {
    zMotors.setSpeeds(10000, -10000);
  } else {
    zMotors.setSpeeds(-10000, 10000);
  }
  delay(150);

  isRunning = true;
}

void loop() {
  if(!isRunning) //Don't run code when isRunning is false
    return;

  int curLoop = millis();
  mp.tick(curLoop - lastLoop);
  lastLoop = curLoop;


  unsigned int linePos = rSensors.readLine(sensorValues, QTR_EMITTERS_ON, true);

  if(linePos > 0 && linePos < 5000) {
    reverseTimer = millis();
  } else if(reverseTimer == 0) { //Drive forward until line is hit for the first time
    zMotors.setSpeeds(10000, 10000);
    return;
  }
  if(millis() - reverseTimer < 200) {
    zMotors.setSpeeds(-10000, -10000);
    return;
  }

  //Find distance to object in front of robot
  int distance = sonar.ping_cm();
  if(distance != 0)
    lastSonarTrigger = millis();

  //Check if there is an object in front of robot
  if(millis() - lastSonarTrigger < 200)
    zMotors.setSpeeds(10000, 10000); //Forward
  else {
    if(dirRight)
      zMotors.setSpeeds(300, -300);
    else
      zMotors.setSpeeds(-300, 300);  
  }

  if(millis() - lastSonarTrigger > 3000) {
    digitalWrite(resetPin, HIGH);
    delay(100);
    digitalWrite(resetPin, LOW);
  }
}
