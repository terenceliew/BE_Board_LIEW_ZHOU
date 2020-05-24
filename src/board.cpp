#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;

  // achat des senseurs et actionneurs
  // les boutons est paramétrés avec les fichier qui les commande
  Button butIndoor(DELAY,"indoor.txt"); 
  Button setFp (DELAY, "setFp.txt");
  Button butOutdoor (DELAY, "outdoor.txt");
  Servo servm(DELAY); 
  BiometricSensor fp(DELAY);
  Buzzer buz(DELAY);
  RFIDSensor rfid(DELAY);
  ForceSensor fsensor(DELAY);
  I2CActuatorScreen screenIndoor;
  I2CActuatorScreen screenOutdoor;
  
  
  // branchement des capteurs actionneurs
  esp8266.pin(2,servm);
  esp8266.pin(3,butIndoor);
  esp8266.pin(4,fp);
  esp8266.pin(5,buz);
  esp8266.pin(6,butOutdoor);
  esp8266.pin(7,rfid);
  esp8266.pin(8,setFp);
  esp8266.pin(9,fsensor);

  // branchement des ecrans
  esp8266.i2c(1,screenIndoor);
  esp8266.i2c(2,screenOutdoor);
  
  // allumage de la carte
  esp8266.run();
  return 0;
}


