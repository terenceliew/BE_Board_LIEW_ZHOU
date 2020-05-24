#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "core_simulation.h"

/*Declaration des varibales globales (variables environment)*/
extern int luminosite_environnement;
extern int Angle;
extern int freqBuzzer;

// Classe mère de tous les capteurs
class Sensor : public Device{
  private :
    // temps entre 2 prises de valeurs
    int temps; 
  public : 
    // initialisation du temps de rafraichisement
    Sensor(int d);
    /** les getters et setters**/
    void setTemps(int d);
    int getTemps();
};

// Classe mère de tous les capteurs numériques
class DigitalSensor: public Sensor{
  private :
    //etat du capteur
    int state;
  public :
    // initialisation du temps de rafraichisement
    DigitalSensor(int d);
    /** les getters et setters**/
    void setState(int s);
    int getState();
};

// Classe mère de tous les capteurs analogiques
class AnalogSensor: public Sensor{
  private :
    // valeur du capteur mesuree
    int val;
    // fait osciller la valeur du capteur avec cette valeur
    int alea;
  public :
    // initialisation du temps de rafraichisement
    AnalogSensor(int d);
    /** les getters et setters**/
    void setVal(int val);
    int getVal();
    void setAlea(int a);
};

// Classe mère de tous les actionneurs
class Actuator: public Device{
  private :
    // temps entre 2 prises de valeurs
    int temps;
  public : 
    // initialisation du temps de rafraichisement
    Actuator(int d);
    /** les getters et setters**/
    void setTemps(int d);
    int getTemps();
};

// Classe mère de tous les actionneurs numériques
class DigitalActuator: public Actuator{
  private :
    //etat de l'actionneur
    int state;
  public :
    // initialisation du temps de rafraichisement
    DigitalActuator(int d);
    /** les getters et setters**/
    void setState(int s);
    int getState();
};

// Classe mère de tous les actionneurs analogique
class AnalogActuator:public Actuator{
  private :
    // valeur de la commande de l'actionneur
    int val;
  public :
    // initialisation du temps de rafraichisement
    AnalogActuator(int d);
    /** les getters et setters**/
    void setVal(int v);
    int getVal();
};

//Class Servo permet de simuler une porte
class Servo : public AnalogActuator{
  public :
  // initialisation du temps de rafraichisement
  Servo(int d);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//Class Buzzer permet de simuler un buzzer qui peut faire du son avec une frequence definie
class Buzzer : public AnalogActuator{
  public :
    // initialisation du temps de rafraichisement
    Buzzer(int d);
    // thread representant l'actionneur et permettant de fonctionner independamment de la board
    virtual void run();

};

//Class Button permet de simuler un bouton
class Button : public DigitalSensor{
private:
  string nomfichier;
public:
  // initialisation du temps de rafraichisement et faire savoir le nom du fichier pour detecter l'appui du bouton
  Button(int d,string nomf);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};


//Classe BiometricSensor qui permet de simuler un capteur qui peut scanner de l'empreinte 
class BiometricSensor : public AnalogSensor{
public:
  // initialisation du temps de rafraichisement
  BiometricSensor(int d);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// Classe RFIDSensor qui simule un capteur de RFID permettant de detecter la fréquence de la carte scanné
class RFIDSensor : public AnalogSensor{
  public:
    // initialisation du temps de rafraichisement
    RFIDSensor(int d);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

// Classe ForceSensor qui simule un capteur de force permettant de detecter la force exercé sur la porte
class ForceSensor : public AnalogSensor{
public:
  // initialisation du temps de rafraichisement
  ForceSensor(int d);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];
  
public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};


///////////////////////////////////////////////////////////////////////////////////////////////////

/**Classes qui n'est pas utilisés dans cette version du projet mais peut-être utilisé dans la**/
/**version future**/

//////////////////////////////////////////////////////////////////////////////////////////////////

//Class LED
class LED : public DigitalActuator{
  public :
    // initialisation du temps de rafraichiisement
    LED(int d);
    // thread representant l'actionneur et permettant de fonctionner independamment de la board
    virtual void run();
};



// //Class Camera
// class Camera : public DigitalActuator{
//   private :
//     int capture;
//   public :
//     // initialisation du temps de rafraichiisement
//     Camera(int d);
//     virtual void run();
// };

///////////////////////////////////////////////////////////////////////////////////////////////////

/******************Classes qui est écrit pour tester le simulateur au début***********************/

//////////////////////////////////////////////////////////////////////////////////////////////////

// capteur de bouton externe
class ExternalDigitalSensorButton: public Device {
private:
  // etat du bouton
  int state;
  // temps entre 2 affichage de l etat du bouton
  int temps;
  
public:
    // initialisation du temps de rafraichiisement
  ExternalDigitalSensorButton(int t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// actionneur digital intelligent : une led
class IntelligentDigitalActuatorLED: public Device {
private:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;
  
public:
    // initialisation du temps de rafraichiisement
  IntelligentDigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};


//  capteur luminosite
class AnalogSensorLuminosity: public Device {
private:
  // fait osciller la valeur du cpateur de 1
  int alea;
  // valeur de luminosite mesuree
  int val;
  // temps entre 2 prises de valeurs
  int temps;
  
public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorLuminosity(int d);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// exemple de capteur analogique de temperature, ne pas oublier d'heriter de Device
class AnalogSensorTemperature: public Device {
private:
  // fait osciller la valeur du cpateur de 1
  int alea;
  // valeur de temperature mesuree
  int val;
  // temps entre 2 prises de valeurs
  int temps;
  
public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorTemperature(int d,int  t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Device {
private:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;
  
public:
    // initialisation du temps de rafraichiisement
  DigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};


#endif
