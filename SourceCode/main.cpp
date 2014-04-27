//Bass audio mp3 player prototype
//Jaiden Gerig


#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "BASS/bass.h"//audio library
#include "BASS_FX/bass_fx.h"
#include <conio.h>//for _kbhit()
#include <vector>
#include <string>
#include "dirent.h"
#include "Song.h"
using namespace std;

vector<Song> searchDirectory(string adr){//looks through directory for mp3 files
	vector<Song> outVec;
	DIR *dir;
	struct dirent *ent;
	//extract all mp3 file names
	if ((dir = opendir(adr.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			string temp = ent->d_name;
			if (temp.size() > 4 && temp.substr(temp.size() - 4) == ".mp3")
				outVec.push_back(Song(temp));
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		throw EXIT_FAILURE;
	}
	return outVec;
}

int main(){
	int device = -1; // Default Sounddevice
	int freq = 44100; // Sample rate (Hz)
	/* Initialize output device */
	BASS_Init(device, freq, 0, 0, NULL);
	string location;
	cout << "Please enter the directory you would like to play music from\n";
	cout << "(Or . for current directory)\n";
	cin >> location;
	vector<Song> songVec = searchDirectory(location);// build vector of Song Objects

	cout << "WELCOME TO MY PROTOTYPE MUSIC PLAYER!\n 0:exit\n 1:next\n 2:prev\n 3:pause\n";

	int control = 4;
	int index = 0;
	bool AUT = false;
	//start playing inital sound file
	songVec[index].play();
	cout << "Current Song: " << songVec[index].getName() << endl;
	if (songVec.size() == 0)//no songs in vector
		control = 0;//end
	while (control != 0){//Main Loop

		//wait for next input or end of song
		while(_kbhit() == 0) {
			if (songVec[index].isOver()){
				songVec[index].stop();
				index = (index + 1) % songVec.size();
				songVec[index].play();
				cout << "Current Song: " << songVec[index].getName() << endl;
				control = 99;
				AUT = true;//bypass waiting for input
			}
		}
		if (!AUT)
			cin >> control;

		if (control == 1){//next song
			songVec[index].stop();
			index = (index + 1) % songVec.size();
			songVec[index].play();
			cout << "Current Song: " << songVec[index].getName() << endl;
		}
		else if (control == 2){//previous song
			songVec[index].stop();
			if (index != 0)
				index = (index - 1) % songVec.size();
			else
				index = songVec.size() - 1;
			songVec[index].play();
			cout << "Current Song: " << songVec[index].getName() << endl;
		}
		else if (control == 3){//Pause current Song
			if (songVec[index].isActive())
				songVec[index].pause();
			else
				songVec[index].play();
	
		}
		AUT = false;
	}
	//free all currently playing streams
	BASS_Free();
	return 0;
}