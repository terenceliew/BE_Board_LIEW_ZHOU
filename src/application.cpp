#include "application.h"


Door::Door(int pServo, int pIndoorButton):pinServo(pServo),pinIndoorButton(pIndoorButton){
	analogWrite(pinServo,0);
}

/*open*/
void Door::open(){
	analogWrite(pinServo,100);
}

/*close*/
void Door::close(){
	analogWrite(pinServo,0);
}

void Door::detectIndoor(){
	if(digitalRead(pinIndoorButton)){
		open();
	}
	else{
		close();
	}
}