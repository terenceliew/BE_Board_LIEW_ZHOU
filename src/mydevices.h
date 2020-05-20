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
extern int Force;
extern int Angle;
extern int loadfpfile;
extern int detectedfreqRFID;
extern int wrong_pwd;
extern int wrong_fp;

class Actuator: public Device{
  private :
    int temps;
  public : 
    Actuator(int d);
    void setTemps(int d);
    int getTemps();
};

class DigitalActuator: public Actuator{
  private :
    int state;
  public :
    DigitalActuator(int d);
    void setState(int s);
    int getState();
};

class AnalogActuator:public Actuator{
  private :
    int val;
  public :
    AnalogActuator(int d);
    void setVal(int v);
    int getVal();
};

//Class Camera
class Camera : public DigitalActuator{
  private :
    int capture;
  public :
    // initialisation du temps de rafraichiisement
    Camera(int d);
    virtual void run();
};

//Class LED
class LED : public DigitalActuator{
  public :
    // initialisation du temps de rafraichiisement
    LED(int d);
    virtual void run();
};
//Class Servo
class Servo : public AnalogActuator{
  public :
  Servo(int d);
  virtual void run();
};

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

#endif
