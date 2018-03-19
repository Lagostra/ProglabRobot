/*
	MusicPlayer.h - Library for playing a song given by an ordered arrays
	of the notes to be played, and a corresponding array of the note lengths.
	Created by Eivind Lie Andreassen, 2016
*/

#ifndef MusicPlayer_h
#define MusicPlayer_h

#define C2 65.41
#define Cs2 69.30
#define Db2 69.30
#define D2 73.42
#define Ds2 77.78
#define Eb2 77.78
#define E2 82.41
#define F2 87.31
#define Fs2 92.50
#define Gb2 92.50
#define G2 98.00
#define Gs2 103.83
#define Ab2 103.83
#define A2 110.00
#define As2 116.54
#define Bb2 116.54
#define B2 123.47
#define C3 130.81
#define Cs3 138.59
#define Db3 138.59
#define D3 146.83
#define Ds3 155.56
#define Eb3 155.56
#define E3 164.81
#define F3 174.61
#define Fs3 185.00
#define Gb3 185.00
#define G3 196.00
#define Gs3 207.65
#define Ab3 207.65
#define A3 220.00
#define As3 233.08
#define Bb3 233.08
#define B3 246.94
#define C4 261.63
#define Cs4 277.18
#define Db4 277.18
#define D4 293.66
#define Ds4 311.13
#define Eb4 311.13
#define E4 329.63
#define F4 349.23
#define Fs4 369.99
#define Gb4 369.99
#define G4 392.00
#define Gs4 415.30
#define Ab4 415.30
#define A4 440.00
#define As4 466.16
#define Bb4 466.16
#define B4 493.88
#define C5 523.25
#define Cs5 554.37
#define Db5 554.37
#define D5 587.33
#define Ds5 622.25
#define Eb5 622.25
#define E5 659.25
#define F5 698.46
#define Fs5 739.99
#define Gb5 739.99
#define G5 783.99
#define Gs5 830.61
#define Ab5 830.61
#define A5 880.00
#define As5 932.33
#define Bb5 932.33
#define B5 987.77
#define C6 1047.50


#include "Arduino.h"

class MusicPlayer {
	public:
		MusicPlayer(int pin, int tempo, float pauseLength, float* song, float* toneLengths, int songLength);
		void tick(int deltaTime);
		float getCurrentNote();
	private:
		int _pin;
		float* _song;
		float* _toneLengths;
		bool _playPause;
		float _pauseLength;
		int _songLength;
		int _currentNote;
		int _lastNoteTime;
		float _quarterNote;
};

#endif