#include <MusicPlayer.h>

const int songLength = 33;

float notes[songLength] = {0, E5, E5, C5, A4, 0, A4, 0, D5, 0, D5, 0, 
                          D5, Fs5, Fs5, G5, A5, G5, G5, G5, D5, 0, 
                          B4, 0, E5, 0, E5, 0, E5, D5, D5, E5, 
                          D5};


float toneLengths[songLength] = {0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
                                0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
                                0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
                                0.5};

MusicPlayer mp(6, 169, 1/4, notes, toneLengths, songLength);

int lastLoop = millis();

void setup() {}

void loop() {
  int curLoop = millis();
  mp.tick(curLoop - lastLoop);
  lastLoop = curLoop;
}
