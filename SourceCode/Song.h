//Song Class
//Jaiden Gerig
//4/14/14
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "BASS/bass.h"//audio library
#include "BASS_FX/bass_fx.h"
#include <vector>
#include <string>
using namespace std;

class Song{
private:
	HSTREAM stream;
	string name;
	string location;

public:
	Song(){
		stream = NULL;
		name = "NULL";
	}
	Song(string tempLoc){
		stream = BASS_StreamCreateFile(FALSE, tempLoc.c_str(), 0, 0, 0);
		location = tempLoc;
		name = tempLoc;//.substr(tempLoc.find_last_of("\\/"), tempLoc.size()-1);
	}
	Song(string tempLoc, HSTREAM tempStream){
		stream = tempStream;
		location = tempLoc;
		name = tempLoc;//.substr(tempLoc.find_last_of("\\/"), tempLoc.size()-1);
	}
	void play(){BASS_ChannelPlay(stream, FALSE); }//Play song
	void stop(){//stop song entirely
		BASS_ChannelStop(stream);
		BASS_ChannelSetPosition(stream, BASS_POS_OGG, 0);
	}
	void pause(){//Pause song
		if (BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING){
			BASS_ChannelPause(stream);
		}
	}
	void setName(string tempName){ name = tempName; }
	void setStream(HSTREAM tempStream){ stream = tempStream; }
	HSTREAM getStream(){ return stream; }
	string getName(){ return name; }
	string getLoc(){ return location; }
	bool isActive(){
		if (BASS_ChannelIsActive(stream) == BASS_ACTIVE_PAUSED || BASS_ChannelIsActive(stream) == BASS_ACTIVE_STOPPED)
			return false;
		else
			return true;
	}
	bool isOver(){//tests if stream is over
		if (BASS_ChannelGetPosition(stream, BASS_POS_BYTE) == BASS_ChannelGetLength(stream, BASS_POS_BYTE))
			return true;
		else
			return false;
	}



};