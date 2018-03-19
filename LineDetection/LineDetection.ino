#include <PLab_ZumoMotors.h>
#include <Pushbutton.h>
#include <ZumoReflectanceSensorArray.h>
#include <QTRSensors.h>

Pushbutton button(ZUMO_BUTTON);
ZumoReflectanceSensorArray rSensors;
ZumoMotors zMotors;

unsigned int sensorValues[6];

void setup() {
  rSensors.init(QTR_NO_EMITTER_PIN);
  button.waitForButton();
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
  button.waitForButton();
}

void loop() {
  unsigned int linePos = rSensors.readLine(sensorValues, QTR_EMITTERS_ON, true);

  if(linePos > 0 && linePos <= 2500) {
    zMotors.setSpeeds(-10000, 10000);
    delay(50);
    zMotors.setSpeeds(-10000, -10000);
    delay(500);
  } else if(linePos > 2500 && linePos < 5000) {
    zMotors.setSpeeds(10000, -10000);
    delay(50);
    zMotors.setSpeeds(-10000, -10000);
    delay(500);
  } else {
    zMotors.setSpeeds(10000, 10000);
  }
  /*
  if(linePos > 0 && linePos < 5000) {
    zMotors.setSpeeds(-10000, -10000);
    delay(500);
    return;
  } else {
    zMotors.setSpeeds(10000, 10000);
  }*/
}
