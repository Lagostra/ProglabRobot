#include <MusicPlayer.h>

const int songLength = 28;

float notes[songLength] = {E5, 0, E5, E5, E5, D5, E5, 0, E5, 0, E5, 
                          E5, E5, D5, E5, 0, E5, 0, G5, E5, D5, 
                          D5, C5, A4, A4, B4, C5, A4};


float toneLengths[songLength] = {1, 1, 0.5, 0.25, 0.25, 0.25, 0.5, 0.25, 1, 1, 0.5, 
                                0.25, 0.25, 0.25, 0.5, 0.25, 1, 0.5, 1, 1, 0.5, 
                                0.5, 1, 0.5, 0.5, 0.5, 0.5, 0.5};

MusicPlayer mp(6, 100, 1/4, notes, toneLengths, songLength);

int lastLoop = millis();

void setup() {}

void loop() {
  int curLoop = millis();
  mp.tick(curLoop - lastLoop);
  lastLoop = curLoop;
}
