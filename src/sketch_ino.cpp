#include <unistd.h>
#include "core_simulation.h"
#include "application.h"

static Door myDoor;
static FingerprintSystem fpSys;
static RFIDSystem rfidSys;
static BurglarAlertSystem baSys;

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(1,INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);

  for(int i=0;i<10;i++){
    io[i]=0;
  }
  
}

// la boucle de controle arduino
void Board::loop(){
  
  // char buf_temperature[100];
  // char buf_lum[100];
  // char buf_bouton[100];
  // int val_temp;
  // int val_lum;
  // int val_bouton;

  //static int cpt=0;
  //static int bascule=0;
   int val_butIndoor;
   int val_butOutdoor; 
   int val_butSetfp;
   int val_fp;
   int val_rfid;
   int val_fsensor;

   int cmdIndoor;
   int cmdOutdoor;
   int cmdFp;
   int cmdRFID;
   int cmdBA;
   
   char buf_rfid[100];
   char buf_fp[100];
   char buf_force[100];

   char buf_angle[100];
   char buf_buzzer[100];

  //recuperation des valeurs de capteurs
  val_butIndoor = digitalRead(3);
  val_fp = analogRead(4);
  val_butOutdoor = digitalRead(6);
  val_rfid = analogRead(7);
  val_butSetfp = digitalRead(8);
  val_fsensor = analogRead(9);
  
  /*affichage sur terminal les valeurs des capteurs*/
  /*FingerprintSensor*/
  sprintf(buf_fp,"Detected  FingerprintID: %d",val_fp);
  Serial.println(buf_fp);

  /*rfidSensor*/
  sprintf(buf_rfid,"Detected  RFID: %d",val_rfid);
  Serial.println(buf_rfid);

  /*forceSensor*/
  sprintf(buf_force,"Detected  Force: %d",val_fsensor);
  Serial.println(buf_force);

  //appel de software
  /*Indoor*/
  cmdIndoor = myDoor.detectIndoor(val_butIndoor);
  /*Outdoor*/
  cmdOutdoor = myDoor.detectIndoor(val_butOutdoor);

  /*Fingerprint System*/
  fpSys.setFingerprint(val_butSetfp,val_fp);
  fpSys.verifyFingerprint(val_fp);
  cmdFp = fpSys.getMatch();

  /*RFID System*/
  rfidSys.verifyRFID(val_rfid);
  cmdRFID = rfidSys.getMatch();

  /*RFID System*/
  baSys.run(val_fsensor);
  cmdBA = baSys.getAlert();

  /*Choisir la commande*/
  /*Commande d'ouverture de la porte*/
  if(cmdIndoor || cmdFp|| cmdRFID){
    myDoor.open();
  }
  else{
    myDoor.close();
  }
  

  /*Commande de buzzer*/
  if(cmdOutdoor || cmdBA){
    myDoor.ringBuzzer();
  }else{
    myDoor.muteBuzzer();
  }


  //faire la commande
  analogWrite(2,myDoor.get_cmdAngle());
  analogWrite(5,myDoor.get_cmdBuzzer());

  /*Affichage valeur d'actuator*/
  /*Door (Servo)*/
  sprintf(buf_angle,"Angle : %d",Angle);
  Serial.println(buf_angle);

  /*Buzzer*/
  sprintf(buf_buzzer,"Frequence Buzzer : %d MHz",freqBuzzer);
  Serial.println(buf_buzzer);

  Serial.println("-----------------------------------------");


  // if(cpt%5==0){
  //     // tous les 5 fois on affiche sur l ecran la luminosite
  //   sprintf(buf_fp,"%d",val_fp);
  //   bus.write(1,buf_fp,100);
  // }

  sleep(1);
  //mettre a jour les capteurs


  // Serial.println("((Door Open))");
  // Serial.println("((Door Close))");
  // Serial.println("((Buzzer ON))");
  // Serial.println("((Buzzer OFF))");

  //int i=0;

  //for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature
  //   val_temp=analogRead(1);
  //   sprintf(buf_temperature,"temperature %d",val_temp);
  //   Serial.println(buf_temperature);
  //   if(cpt%5==0){
  //       // tous les 5 fois on affiche sur l ecran la temperature
  //     sprintf(buf_temperature,"%d",val_temp);
  //     bus.write(1,buf_temperature,100);
  //   }

  //   // lecture sur la pin 2 : capteur de luminosite
  //   val_lum=analogRead(2);
  //   sprintf(buf_lum,"luminosity %d",val_lum);
  //   Serial.println(buf_lum);
    
  //   if(cpt%5==0){
  //       // tous les 5 fois on affiche sur l ecran la luminosite
  //     sprintf(buf_lum,"%d",val_lum);
  //     bus.write(1,buf_lum,100);
  //   }

  //   // lecture sur la pin 4 : capteur de l'etat du bouton
  //   val_bouton=analogRead(4);
  //   sprintf(buf_bouton,"bouton %d",val_bouton);
  //   Serial.println(buf_bouton);
    
  //   if(cpt%5==0){
  //       // tous les 5 fois on affiche sur l ecran la luminosite
  //     sprintf(buf_bouton,"%d",val_bouton);
  //     bus.write(1,buf_bouton,100);
  //   }

  //   //lire la valeur du bouton
  //   bascule=digitalRead(4);
  
  //   // on eteint et on allume la LED intelligent
  //   if(bascule){
  //     digitalWrite(3,HIGH);
  //   }
  //   else{
  //     digitalWrite(3,LOW);
  //   }

  //   cpt++;
  //   sleep(1);
  // }


  
}


