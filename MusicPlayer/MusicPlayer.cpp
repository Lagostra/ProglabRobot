/*
	MusicPlayer.cpp - Library for playing a song given by an ordered arrays
	of the notes to be played, and a corresponding array of the note lengths.
	Created by Eivind Lie Andreassen, 2016
*/

#include "Arduino.h"
#include "MusicPlayer.h"

/*
	Creates a new MusicPlayer object.
		pin: the pin number used to output melody.
		tempo: the tempo the song is to be played in, in BPM (Beats Per Minute)
		pauseLength: The amount of silence between each played note, in fraction of a quarter note.
		song: 	The array of frequencies to be played. Can use the constants provided in MusicPlayer.h to make
				it easier to write and interpret.
		toneLengths: 	The array of lengths of each played note. In fraction of a quarter note. (i.e. half note = 2,
						quarter note = 1, eigth note = 1/2)
		songLength: The amount of notes in the song. Corresponds to the lengths of song and toneLengths.
*/
MusicPlayer::MusicPlayer(int pin, int tempo, float pauseLength, float* song, float* toneLengths, int songLength) {
	_pin = pin;
	_quarterNote = 60000/tempo;
	_pauseLength = pauseLength;
	pinMode(pin, OUTPUT);
	
	_song = song;
	_toneLengths = toneLengths;
	_songLength = songLength;
	_currentNote = 0;
	_lastNoteTime = 0;
	_playPause = false;
}

/*
	Advances the counter, and plays notes at correct time. Must be called in a loop.
		deltaTime: The amount of time, in milliseconds, since last call.
*/
void MusicPlayer::tick(int deltaTime) {
	_lastNoteTime += deltaTime;
	if(_playPause) {
		if(_lastNoteTime >= (_toneLengths[_currentNote] - _pauseLength) * _quarterNote) {
			_lastNoteTime = 0;
			noTone(_pin);
			_playPause = false;
		}
		return;
	}
	if(_lastNoteTime >= _pauseLength * _quarterNote) {
		_currentNote++;
		_lastNoteTime = 0;
		if(_currentNote >= _songLength) {
			_currentNote = 0;
		}
		
		_playPause = true;
		tone(_pin, _song[_currentNote], (_toneLengths[_currentNote] - _pauseLength) * _quarterNote);
	}
}

/*
	Returns the currently played note.
*/
float MusicPlayer::getCurrentNote() {
	return _song[_currentNote];
}