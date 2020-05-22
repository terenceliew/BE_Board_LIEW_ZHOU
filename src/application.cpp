#include "application.h"


Door::Door():cmdAngle(0),cmdBuzzer(0),msgIndoor("Initialising Indoor..."),msgOutdoor("Initialising Outdoor..."){
	
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

void Door::alarmBuzzer(){
	cmdBuzzer=100;
}


void Door::muteBuzzer(){
	cmdBuzzer=0;
}

char* Door::get_msgIndoor(){
	return msgIndoor;
}

char* Door::get_msgOutdoor(){
	return msgOutdoor;
}


void Door::screenIndoor(){
	if(!cmdAngle){
		//door is closed
		sprintf(msgIndoor," ((Inside)) Please press the indoor button!");
	} else{
		//door is open
		sprintf(msgIndoor," Door is open!");
	}

	if(cmdBuzzer>5 && cmdBuzzer<85 ){
		//someone rings the doorbell
		sprintf(msgIndoor + strlen(msgIndoor)," ((Inside)) Someone is at the door!");
	}
	else if(cmdBuzzer>=85){
		//someone is forcing the door!
		sprintf(msgIndoor + strlen(msgIndoor)," ((Inside)) Burglar Alert!!! Calling Police...");
	}
}

void Door::screenOutdoor(){
	if(!cmdAngle){
		//door is closed
		sprintf(msgOutdoor," ((Outside)) Please scan your fingerprint or your card! Doorbell is on your left!");
	} else{
		//door is open
		sprintf(msgOutdoor," Door is open!");
	}
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

BurglarAlertSystem::BurglarAlertSystem():alert(0){}

int BurglarAlertSystem::getAlert(){
	return alert;
}

/*verifyFingerprint*/
void BurglarAlertSystem::run(int forceval){

	if(forceval>FORCELIM){
		alert=1;
	}else{
		alert=0;
	}
	
}