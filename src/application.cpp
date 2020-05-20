#include "application.h"


Door::Door(){
	cmdAngle=0;
}

int Door::get_cmdAngle(){
	return cmdAngle;
}

/*open*/
void Door::open(){
	cmdAngle=100;;
}

/*close*/
void Door::close(){
	cmdAngle=0;
}

void Door::detectIndoor(int val_button){
	if(val_button){
		open();
	}
	else{
		close();
	}
}