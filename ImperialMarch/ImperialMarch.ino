#include <MusicPlayer.h>

const int songLength = 73;

float notes[songLength] = {0, G3, G3, G3, Eb3, Bb3, G3, Eb3, Bb3, G3, D4, D4, 
                              D4, Eb4, Bb3, Gb3, Eb3, Bb3, G3, G4, 0, G4, 
                              Gb4, F4, E4, Eb4, E4, 0, 0, Ab3, Db4, C4, 
                              B3, Bb3, A3, Bb3, 0, 0, Eb3, G3, Eb3, G3,
                              Bb3, G3, Bb3, D4, G4, 0, G4, Gb4, F4, E4, 
                              Eb4, E4, 0, 0, Ab3, Db4, C4, B3, Bb3, A3, 
                              Bb3, 0, 0, Eb3, G3, Eb3, Bb3, G3, Eb3, Bb3, G3};

float toneLengths[songLength] = {2, 1, 1, 1, 0.75, 0.25, 1, 0.75, 0.25, 2, 1, 1, 
                                    1, 0.75, 0.25, 1, 0.75, 0.25, 2, 1, 1, 1, 
                                    0.75, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5, 1, 0.75, 
                                    0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5, 1, 0.75, 0.25, 
                                    1, 0.75, 0.25, 2, 1, 1, 1, 0.75, 0.25, 0.25, 
                                    0.25, 0.25, 0.25, 0.5, 0.5, 1, 0.75, 0.25, 0.25, 0.25, 
                                    0.25, 0.25, 0.5, 0.5, 1, 0.75, 0.25, 1, 0.75, 0.25, 2};

MusicPlayer mp(6, 104, 1/8, notes, toneLengths, songLength);

int lastLoop = millis();

void setup() {}

void loop() {
  int curLoop = millis();
  mp.tick(curLoop - lastLoop);
  lastLoop = curLoop;
}
