
#include "mydevices.h"

using namespace std;


/*Initialisation des varibales globales (variables environment)*/
int luminosite_environnement = 200;
int Angle = 0;
int freqBuzzer = 0; //en MHz


//Classe Sensor
Sensor::Sensor(int d):Device(),temps(d){
}
void Sensor::setTemps(int d){
  temps = d;
}
int Sensor::getTemps(){
  return temps;
}

//Classe DigitalSensor
DigitalSensor::DigitalSensor(int d):Sensor(d),state(OFF){
}
void DigitalSensor::setState(int s){
  state = s;
}
int DigitalSensor::getState(){
  return state;
}

//Classe AnalogSensor
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


//Classe Actuator
Actuator::Actuator(int d):Device(),temps(d){
}
void Actuator::setTemps(int d){
  temps = d;
}
int Actuator::getTemps(){
  return temps;
}

//Classe DigitalActuator
DigitalActuator::DigitalActuator(int d):Actuator(d),state(OFF){
}
void DigitalActuator::setState(int s){
  state = s;
}
int DigitalActuator::getState(){
  return state;
}

//Classe AnalogActuator
AnalogActuator::AnalogActuator(int d):Actuator(d),val(0){
}
void AnalogActuator::setVal(int v){
  val = v;
}
int AnalogActuator::getVal(){
  return val;
}

//Class Servo
Servo::Servo(int d):AnalogActuator(d){
  setVal(0);
}
void Servo::run(){
  while(1){
    if(ptrmem!=NULL) setVal(*ptrmem);

    // Convertir la valeur de commande (0-100) à l'angle de la porte en degré (0-180)
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

    // Conversion de la valeur (0-100) au fréquence du buzzer en MHz
    // (0) si le son de buzzer est coupé
    // (400-500) MHz d'autres cas
    if (getVal()){
    	freqBuzzer=400+getVal();
    }else{
    	freqBuzzer = 0;
    }
    
	  //cout<< "Buzzer : "<< getVal()<<endl;

    sleep(getTemps());//avoid conflit 
  }
}

// Classe Button
Button::Button(int d, string nomf):DigitalSensor(d), nomfichier(nomf){
	setState(OFF);
}
void Button::run(){
	while(1){
		// vérification l'existance du fichier 'nomfichier'
		if (ifstream(nomfichier)){
			setState(ON);
		}
		else{
			setState(OFF);
		}

		*ptrmem = getState();
	
		sleep(getTemps());	
	}

	
}

// Classe BiometricSensor (Fingerprint Sensor)
BiometricSensor::BiometricSensor(int d):AnalogSensor(d){
	setVal(0);
}

void BiometricSensor::run(){
	fstream loadfpfile;
	string loadfpstring;
	while(1){

		// ouverture du fichier et obtention de la valeur dans le fichier
		loadfpfile.open("loadfp.txt");
		while(!loadfpfile.eof()){
			getline(loadfpfile,loadfpstring);
			
		}

		//cout<<"Detected FingerprintID : "<<loadfpstring<<endl;
		

		// si la valeur sur le fichier est récupéré avec succès, on la converti en integer
		if(!loadfpstring.empty()){
			setVal(stoi(loadfpstring));
			*ptrmem=getVal(); 
		}
		
		// fermeture du fichier
		loadfpfile.close();

		sleep(getTemps());
	}
}

RFIDSensor::RFIDSensor(int d):AnalogSensor(d){
	setVal(0);
}

void RFIDSensor::run(){
	fstream loadrfidfile;
	string loadrfidstring;
	while(1){

		// ouverture du fichier et obtention de la valeur dans le fichier
		loadrfidfile.open("loadrfid.txt");
		while(!loadrfidfile.eof()){
			getline(loadrfidfile,loadrfidstring);
			
		}
		//cout<<"Detected RFID : "<<loadrfidstring<<endl;

		// si la valeur sur le fichier est récupéré avec succès, on la converti en integer
		if(!loadrfidstring.empty()){
			setVal(stoi(loadrfidstring));
			*ptrmem=getVal(); 
		}
		
		
		// fermeture du fichier
		loadrfidfile.close();

		sleep(getTemps());
	}
}

ForceSensor::ForceSensor(int d):AnalogSensor(d){
	setVal(0);
}

void ForceSensor::run(){
	fstream forcefile;
	string forcestring;
	while(1){

		// ouverture du fichier et obtention de la valeur dans le fichier
		forcefile.open("force.txt");
		while(!forcefile.eof()){
			getline(forcefile,forcestring);
			
		}
		//cout<<"Detected Force : "<<forcestring<<endl;

		// si la valeur sur le fichier est récupéré avec succès, on la converti en integer
		if(!forcestring.empty()){
			setVal(stoi(forcestring)); 
			*ptrmem=getVal();
		}
		
		
		// fermeture du fichier
		forcefile.close();

		sleep(getTemps());
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

///////////////////////////////////////////////////////////////////////////////////////////////////

/**Classes qui n'est pas utilisés dans cette version du projet mais peut-être utilisé dans la**/
/**version future**/

//////////////////////////////////////////////////////////////////////////////////////////////////

//Classe LED
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

// //class Camera
// Camera::Camera(int d):DigitalActuator(d),capture(0){
//   setState(LOW);
// }
// void Camera::run(){
//   while(1){
//     if(ptrmem!=NULL) setState(*ptrmem);
//     if (getState()==LOW){
//       //cout << "((((Camera OFF))))\n";
//     }
//     else{
//     	//cout << "((((Camera ON))))\n"; 
//     if(Force>100) capture=1;   
//     sleep(getTemps());
//     }
//   }
// }

///////////////////////////////////////////////////////////////////////////////////////////////////

/******************Classes qui est écrit pour tester le simulateur au début***********************/

//////////////////////////////////////////////////////////////////////////////////////////////////

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







