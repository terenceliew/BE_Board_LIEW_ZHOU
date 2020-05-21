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

/*open door*/
void Door::open(){
	cmdAngle=100;;
}

/*close door*/
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
	int ring;
	if(val_button){
		ring = 1;
	}
	else{
		ring = 0;
	}
	return ring;
}

void Door::ringBuzzer(){
	cmdBuzzer=80;
}

void Door::muteBuzzer(){
	cmdBuzzer=0;
}

FingerprintSystem::FingerprintSystem():match(0){}

int FingerprintSystem::getMatch(){
	return match;
}

/*verifyFingerprint*/
void FingerprintSystem::verifyFingerprint(int loadfpval){
	string savedfpstring;
	static int savedfpval;
	fstream savedfpfile;

	savedfpfile.open("savedfp.txt");
	while(!savedfpfile.eof()){
		getline(savedfpfile,savedfpstring);
		
	}
	//cout<<"savedstring:"<<savedfpstring<<endl;
	if (!savedfpstring.empty()){
		//cout<<"ho"<<endl;
		savedfpval=stoi(savedfpstring);
	}
	//cout<<"savedvalue:"<<savedfpval<<endl;
	
	if(savedfpval==loadfpval){
		match=1;
	}else{
		match=0;
	}
	//cout<<"match"<<match<<endl;
	savedfpfile.close();
}

/*set new Fingerprint*/
void FingerprintSystem::setFingerprint(int buttonFp,int newFp){
	string savedfpstring;
	//int savedfpval;
	fstream savedfpfile;

	//cout<<"hi"<<newFp<<endl;
	if(buttonFp){
		// cout<<"newfp :"<<to_string(newFp)<<endl;
		
			//cout<<"helllllooooo"<<endl;
		savedfpfile.open("savedfp.txt"); //delete content before open

		savedfpfile << to_string(newFp);
		
		
		savedfpfile.close();
			// getline(savedfpfile,savedfpstring);
			// cout<<"saved : "<<savedfpstring<<endl;
			
	}
	
}

RFIDSystem::RFIDSystem():match(0){}

int RFIDSystem::getMatch(){
	return match;
}

/*verifyRFID*/
void RFIDSystem::verifyRFID(int loadrfidval){
	string savedrfidstring;
	int savedrfidval;
	fstream savedrfidfile;

	savedrfidfile.open("savedrfid.txt");
	while(!savedrfidfile.eof()){
		getline(savedrfidfile,savedrfidstring);
		
	}
	
	if (!savedrfidstring.empty()){
		savedrfidval=stoi(savedrfidstring);
	}

	if(savedrfidval==loadrfidval){
		match=1;
	}else{
		match=0;
	}

	savedrfidfile.close();
}