#include "application.h"


Door::Door():cmdAngle(0){
	
}

int Door::get_cmdAngle(){
	return cmdAngle;
}

void Door::set_cmdAngle(int a){
	cmdAngle = a;
}
int Door::get_cmdBuzzer(){
	return cmdBuzzer;
}

void Door::set_cmdBuzzer(int b){
	cmdBuzzer = b;
}

/*open*/
void Door::open(){
	cmdAngle=100;
}

/*close*/
void Door::close(){
	cmdAngle=0;
}

int Door::detectIndoor(int val_button){
	int open;
	if(val_button){
		open = 1;
	}
	else{
		open = 0;
	}
	return open;
}
int Door::detectOutdoor(int val_button){
	int open;
	if(val_button){
		open = 1;
	}
	else{
		open = 0;
	}
	return open;
}
void Door::openBuzzer(){
	cmdBuzzer=80;
}
void Door::closeBuzzer(){
	cmdBuzzer=0;
}

FingerprintSystem::FingerprintSystem():match(0){}

int FingerprintSystem::getMatch(){
	return match;
}

/*verifyFingerprint*/
void FingerprintSystem::verifyFingerprint(int loadfpval){
	string savedfpstring;
	int savedfpval;
	fstream savedfpfile;

	savedfpfile.open("savedfp.txt");
	while(!savedfpfile.eof()){
		getline(savedfpfile,savedfpstring);
		
	}
	
	savedfpval=stoi(savedfpstring);
	
	if(savedfpval==loadfpval){
		match=1;
	}else{
		match=0;
	}

	savedfpfile.close();
}