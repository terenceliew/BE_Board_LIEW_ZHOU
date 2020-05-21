
#include "mydevices.h"

/*Initialisation des varibales globales (variables environment)*/
int luminosite_environnement = 200;
int Force = 0;
int Angle = 0;
int detectedfreqRFID = 0;
int wrong_pwd = 0;
int wrong_fp = 0;
fstream loadfpfile;
fstream loadrfidfile;

using namespace std;

//Sensor
Sensor::Sensor(int d):Device(),temps(d){
}
void Sensor::setTemps(int d){
  temps = d;
}
int Sensor::getTemps(){
  return temps;
}

//DigitalSensor
DigitalSensor::DigitalSensor(int d):Sensor(d),state(OFF){
}
void DigitalSensor::setState(int s){
  state = s;
}
int DigitalSensor::getState(){
  return state;
}

//AnalogSensor
AnalogSensor::AnalogSensor(int d):Sensor(d),val(0),alea(0){
}
void AnalogSensor::setVal(int v){
  val = v;
}
int AnalogSensor::getVal(){
  return val;
}
void AnalogSensor::setAlea(int a){
	alea = a;
}


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

//class Camera
Camera::Camera(int d):DigitalActuator(d),capture(0){
  setState(LOW);
}
void Camera::run(){
  while(1){
    if(ptrmem!=NULL) setState(*ptrmem);
    if (getState()==LOW){
      //cout << "((((Camera OFF))))\n";
    }
    else{
    	//cout << "((((Camera ON))))\n"; 
    if(Force>100) capture=1;   
    sleep(getTemps());
    }
  }
}

//class LED
LED::LED(int d):DigitalActuator(d){
  setState(LOW);
}
void LED::run(){
  	int last_state = LOW;

  while(1){
    if(ptrmem!=NULL) setState(*ptrmem);
    if (getState()==LOW){
      //cout << "((((eteint))))\n";      
      if (last_state!=getState()){
      	luminosite_environnement -= 50;
      }
    }
    else{
    	//cout << "((((allume))))\n";
    	if (last_state!=getState()){
    		luminosite_environnement += 50;
      }	
    }    
    last_state=getState();
    sleep(getTemps());
    }

}

//Class Servo
Servo::Servo(int d):AnalogActuator(d){
  setVal(0);
}

void Servo::run(){
  while(1){
    if(ptrmem!=NULL) setVal(*ptrmem);
    // if(getVal()>=70){
    //   cout<<"Door OPEN"<<endl;
    // }else if(getVal()<70){
    //   cout<<"Door CLOSE"<<endl;
    // }else{
    //   cout<<"ERREUR Servo"<<endl;
    // }

    Angle = (getVal()/100)*180;
	//cout<< "Angle de la porte : "<< Angle<<endl;

    sleep(getTemps());
  }
}
//Class Buzzer
Buzzer::Buzzer(int d):AnalogActuator(d){
  setVal(0);
}
void Buzzer::run(){
  while(1){
    if(ptrmem!=NULL) setVal(*ptrmem);

	  //cout<< "Buzzer : "<< getVal()<<endl;

    sleep(getTemps());//avoid conflit 
  }
}


IndoorButton::IndoorButton(int d):DigitalSensor(d){
	setState(OFF);
}

void IndoorButton::run(){
	while(1){
		if (ifstream("indoor.txt")){
			setState(ON);
		}
		else{
			setState(OFF);
		}

		*ptrmem = getState();
	
		sleep(getTemps());	
	}

	
}
OutdoorButton::OutdoorButton(int d):DigitalSensor(d){
	setState(OFF);
}

void OutdoorButton::run(){
	while(1){
		if (ifstream("outdoor.txt")){
			setState(ON);
		}
		else{
			setState(OFF);
		}

		*ptrmem = getState();
	
		sleep(getTemps());	
	}

	
}

BiometricSensor::BiometricSensor(int d):AnalogSensor(d){
	setVal(0);
}

void BiometricSensor::run(){
	string loadfpstring;
	while(1){
		loadfpfile.open("loadfp.txt");
		while(!loadfpfile.eof()){
			getline(loadfpfile,loadfpstring);
			
		}
		//cout<<"Detected FingerprintID : "<<loadfpstring<<endl;

		setVal(stoi(loadfpstring)); 
		*ptrmem=getVal();
		
		loadfpfile.close();

		sleep(getTemps());
	}
}
RFIDSensor::RFIDSensor(int d):AnalogSensor(d){
	setVal(0);
}

void RFIDSensor::run(){
	string loadrfidstring;
	while(1){
		loadrfidfile.open("loadrfid.txt");
		while(!loadrfidfile.eof()){
			getline(loadrfidfile,loadrfidstring);
			
		}
		//cout<<"Detected RFID : "<<loadrfidstring<<endl;

		setVal(stoi(loadrfidstring)); 
		*ptrmem=getVal();
		
		loadrfidfile.close();

		sleep(getTemps());
	}
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

		sleep(temps);
	}


	

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





