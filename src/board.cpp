#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  //AnalogSensorTemperature temperature(DELAY,TEMP);
  //AnalogSensorLuminosity luminosity(DELAY);
  //ExternalDigitalSensorButton button(DELAY);
  //DigitalActuatorLED led1(DELAY);
  //IntelligentDigitalActuatorLED led2(DELAY);
  Servo servm(DELAY);
  Button butIndoor(DELAY,"indoor.txt");
  Button setFp (DELAY, "setFp.txt");
  BiometricSensor fp(DELAY);
  Button butOutdoor (DELAY, "outdoor.txt");
  Buzzer buz(DELAY);
  RFIDSensor rfid(DELAY);
  ForceSensor fsensor(DELAY);
  I2CActuatorScreen screen;
  
  // branchement des capteurs actionneurs
  // esp8266.pin(1,temperature);
  // esp8266.pin(2,luminosity);
  //esp8266.pin(4,button);
  esp8266.pin(2,servm);
  esp8266.pin(3,butIndoor);
  esp8266.pin(4,fp);
  esp8266.pin(5,buz);
  esp8266.pin(6,butOutdoor);
  esp8266.pin(7,rfid);
  esp8266.pin(8,setFp);
  esp8266.pin(9,fsensor);
  

  //esp8266.pin(0,led1);
  //esp8266.pin(3,led2);
  esp8266.i2c(1,screen);

  
  // allumage de la carte
  esp8266.run();
  return 0;
}


