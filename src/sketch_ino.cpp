#include <unistd.h>
#include <vector>
#include "core_simulation.h"
#include "mydevices.h"
#include "application.h"



// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte

  pinMode(2,OUTPUT); //servo motor
  pinMode(3,INPUT); //indoor button
  pinMode(4,INPUT); //fingerprint sensor
  pinMode(5,OUTPUT); //buzzer
  pinMode(6,INPUT); //doorbell (outdoor button)
  pinMode(7,INPUT); //RFID sensor
  pinMode(8,INPUT); //set fingerprint button
  pinMode(9,INPUT); //force sensor

  /*Intialisation des valeurs des pins*/
  for(int i=0;i<MAX_IO_PIN;i++){
    io[i]=0;
  }
}

// la boucle de controle arduino
void Board::loop(){

    /*Declaration des variables pour les valeurs des capteurs*/
   int val_butIndoor;
   int val_butOutdoor; 
   int val_butSetfp;
   int val_fp;
   int val_rfid;
   int val_fsensor;
   
   /*buffer permetant d'afficher les valeurs de capteurs et actionneurs*/
   char buf_butIndoor[100];
   char buf_butOutdoor[100];
   char buf_butSetfp[100];
   char buf_rfid[100];
   char buf_fp[100];
   char buf_force[100];

   char buf_angle[100];
   char buf_buzzer[100];

   vector<char*> vecbuf;//utilisation vector de STL pour stocker les buffer

   /*remplir le vecteur de buffer*/
   vecbuf.push_back(buf_butIndoor);
   vecbuf.push_back(buf_butOutdoor);
   vecbuf.push_back(buf_butSetfp);
   vecbuf.push_back(buf_rfid);
   vecbuf.push_back(buf_fp);
   vecbuf.push_back(buf_force);



  /**********recuperation des valeurs de capteurs**********/
    val_butIndoor = digitalRead(3);
    val_butOutdoor = digitalRead(6);
    val_butSetfp = digitalRead(8);

    val_fp = analogRead(4);
    if( val_fp<0 || val_fp>55555 ){
      //exception pour fingerprint sensor
      //rmq important! Cette exception ne detect pas la valeur plus grand que 65535(unsigned short)
      throw BoardException(FPERR);
    }
    
   
    val_rfid = analogRead(7);
    //exception pour rfid sensor
    //rmq important! Cette exception ne detect pas la valeur plus grand que 65535(unsigned short)
    if( val_rfid<0 || val_rfid>44444 ){
      throw BoardException(RFIDERR);
    }
    
    val_fsensor = analogRead(9);
    /*exception si force est plus petite que 0 ou plus grand que 100*/
    //rmq important! Cette exception ne detect pas la valeur plus grand que 65535(unsigned short)
    if( val_fsensor<0 || val_fsensor>100 ){
      throw BoardException(FORCEERR);;
    }

 
  
  /*********affichage sur terminal les valeurs des capteurs*********/
  /*Indoor Button*/
  sprintf(buf_butIndoor,"Indoor button: %d",val_butIndoor);

  /*Outdoor Button*/
  sprintf(buf_butOutdoor,"Outdoor button: %d",val_butOutdoor);

  /*Set fingerprint button*/
  sprintf(buf_butSetfp,"Set fingerprint button: %d",val_butSetfp);

  /*FingerprintSensor*/
  sprintf(buf_fp,"Detected  FingerprintID: %d",val_fp);

  /*rfidSensor*/
  sprintf(buf_rfid,"Detected  RFID: %d",val_rfid);

  /*forceSensor*/
  sprintf(buf_force,"Detected  Force: %d",val_fsensor);

  Serial.println("-----------------------------------------");
  /*affichage des buffers dans le vecteur*/
  for(long unsigned int i=0;i<vecbuf.size();i++){
    Serial.println(vecbuf[i]);
  }

  /*********Appel de software*********/

  /*Fingerprint System*/
  fpSys.run(val_butSetfp,val_fp);

  /*RFID System*/
  rfidSys.verifyRFID(val_rfid);

  /*Burglar alert System*/
  baSys.run(val_fsensor);

  /*Update door command base on all the security systems and sensors*/
  myDoor.run(baSys.getAlert(),val_butIndoor,val_butOutdoor,fpSys.getMatch(),val_butSetfp,rfidSys.getMatch());

  /*********faire la commande*********/
  analogWrite(2,myDoor.get_cmdAngle());
  analogWrite(5,myDoor.get_cmdBuzzer());

  /*********Affichage valeur d'actuator en terminal*********/
  /*Door (Servo)*/
  sprintf(buf_angle,"Door angle : %d",Angle);
  Serial.println(buf_angle);

  /*Buzzer*/
  sprintf(buf_buzzer,"Buzzer Frequency : %d MHz",freqBuzzer);
  Serial.println(buf_buzzer);

  /*********Gestion d'affichage sur ecran*********/
  /*Ecran a l'interieur*/
  bus.write(1,myDoor.get_msgIndoor(),100);
  /*Ecran a l'exerieur*/
  bus.write(2,myDoor.get_msgOutdoor(),100);

  Serial.println("-----------------------------------------");


  sleep(1);


  
}


