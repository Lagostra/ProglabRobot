#include <ZumoMotors.h>
#include <Pushbutton.h>

ZumoMotors zMotors;
Pushbutton zButton(ZUMO_BUTTON);

void setup() {
  zButton.waitForButton();
}

void loop() {
  zMotors.setSpeeds(400, 400);
  delay(2000);
  zMotors.setSpeeds(-400, -400);
  delay(2000);
}
