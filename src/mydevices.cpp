
#include "mydevices.h"

int luminosite_environnement = 200;

using namespace std;
//Actuator
Actuator::Actuator(int d):Device(),temps(d){
}
void Actuator::setTemps(int d){
  temps = d;
}
int Actuator::getTemps(){
  return temps;
}
//DigitalActuator
DigitalActuator::DigitalActuator(int d):Actuator(d),state(OFF){
}
void DigitalActuator::setState(int s){
  state = s;
}
int DigitalActuator::getState(){
  return state;
}
//AnalogActuator
AnalogActuator::AnalogActuator(int d):Actuator(d),val(0){
}
void AnalogActuator::setVal(int v){
  val = v;
}
int AnalogActuator::getVal(){
  return val;
}

//classe ExternalDigitalSensorButton
ExternalDigitalSensorButton::ExternalDigitalSensorButton(int t):Device(),state(OFF),temps(t){
}

void ExternalDigitalSensorButton::run(){
	

	while(1){
		
		if (ifstream("on.txt")){
			state = ON;
		}
		else{
			state = OFF;
		}

		*ptrmem = state;
	}


	sleep(temps);

}

//classe IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void IntelligentDigitalActuatorLED::run(){
	int last_state = LOW;

  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW){
      cout << "((((eteint))))\n";
      
      if (last_state!=state){
      	luminosite_environnement -= 50;
      	// cout << "\nlast_state: " << last_state<< "\nnew state : "<<state;
      	// cout << "\nnew luminosite_environnement: " << luminosite_environnement;
      }
    }
    else{
    	cout << "((((allume))))\n";
    	if (last_state!=state){
    		luminosite_environnement += 50;
    		// cout << "\nlast_state: " << last_state<< "\nnew state : "<<state;
    		// cout << "\nnew luminosite_environnement: " << luminosite_environnement;
    	}
    	
    }
    
    last_state=state;
    sleep(temps);
    }
}

//classe AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(int  d):Device(),val(luminosite_environnement),temps(d){
  //alea=10;
}

void AnalogSensorLuminosity::run(){
  while(1){
    //alea=10-alea;
    if(ptrmem!=NULL){
    	//*ptrmem=val+alea;
    	val=luminosite_environnement;
    	*ptrmem=val;//+alea
    }
    	
    sleep(temps);
  }
}

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Device(),val(t),temps(d){
  alea=1;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(temps);
    }
}

// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}





