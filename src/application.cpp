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
		if(cmdBuzzer>5 && cmdBuzzer<85 ){
			//someone rings the doorbell
			sprintf(msgIndoor," ((Inside)) Someone is at the door!");
		}else if(cmdBuzzer>=85){
			//someone is forcing the door!
			sprintf(msgIndoor," ((Inside)) Burglar Alert!!! Calling Police...");
		}else{		
			sprintf(msgIndoor," ((Inside)) Please press the indoor button!");
		}

	} else{
		//door is open
		sprintf(msgIndoor," Door is open!");
	}


}

void Door::screenOutdoor(){
	if(!cmdAngle){
		//door is closed
		if(cmdBuzzer>=85){
			//someone is forcing the door!
			sprintf(msgOutdoor," ((Outside)) Don't force the door, the police is coming !!!");
		}else{
			sprintf(msgOutdoor," ((Outside)) Please scan your fingerprint or your card! Doorbell is on your left!");
		}
		
	} else{
		//door is open
		sprintf(msgOutdoor," Door is open!");
	}
}


void Door::run(int cmdBA,int val_butIndoor,int val_butOutdoor, int cmdFp, int val_butSetfp, int cmdRFID){
	


	/*Commande d'ouverture de la porte*/
	if(!cmdBA){
	    if(val_butIndoor || (cmdFp && !val_butSetfp) || cmdRFID){
	      open();
	    }
	    else{
	      close();
	    }
	}
	else{
	    close();
	}
	  

	/*Commande de buzzer*/
	if(cmdBA){
	  alarmBuzzer();
    }else if(val_butOutdoor){
	  ringBuzzer();
	}
	else{
	  muteBuzzer();
 	}

 	/*Commande d'affichage*/
 	screenIndoor();
  	screenOutdoor();
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
	
	if (!savedfpstring.empty()){
		
		savedfpval=stoi(savedfpstring);
	}
	
	
	if(savedfpval==loadfpval){
		match=1;
	}else{
		match=0;
	}
	
	savedfpfile.close();
}

/*set new Fingerprint*/
void FingerprintSystem::setFingerprint(int buttonFp,int newFp){
	string savedfpstring;

	fstream savedfpfile;


	if(buttonFp){
	
		savedfpfile.open("savedfp.txt",ios::out | ios::trunc); //delete content before open

		savedfpfile << to_string(newFp);
		
		
		savedfpfile.close();
			
			
	}
	
}

void FingerprintSystem::run(int val_butSetfp,int val_fp){
	setFingerprint(val_butSetfp,val_fp);
    verifyFingerprint(val_fp);
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