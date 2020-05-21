#include <unistd.h>
#include "core_simulation.h"
#include "application.h"

static Door myDoor;
static FingerprintSystem fpSys;
static RFIDSystem rfidSys;

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
}

// la boucle de controle arduino
void Board::loop(){

  static int val_but1; 
  static int val_but2;
  static int val_fp;
  static int val_rfid;
  static int cmdIndoor;
  static int cmdOutdoor;
  static int cmdFp;
  static int cmdRFID;
  char buf_rfid[100];
  char buf_fp[100];

  //recuperation des valeurs de capteurs
  val_but1 = digitalRead(3);
  val_fp = analogRead(4);
  val_but2 = digitalRead(6);
  val_rfid = analogRead(7);

  //appel de software
  /*Indoor*/
  cmdIndoor = myDoor.detectIndoor(val_but1);
  cmdOutdoor = myDoor.detectIndoor(val_but2);
  /*Fingerprint System*/
  fpSys.verifyFingerprint(val_fp);
  sprintf(buf_fp,"Detected  FingerprintID: %d",val_fp);
  Serial.println(buf_fp);
  cmdFp = fpSys.getMatch();

  /*RFID System*/
  rfidSys.verifyRFID(val_rfid);
  sprintf(buf_rfid,"Detected  RFID: %d",val_rfid);
  Serial.println(buf_rfid);
  cmdRFID = rfidSys.getMatch();

  /*Buzzer*/
  if(cmdOutdoor){
    myDoor.openBuzzer();
    Serial.println("((Buzzer ON))");
  }else{
    myDoor.closeBuzzer();
    Serial.println("((Buzzer OFF))");
  }

  /*Choisir la commande*/
  if(cmdIndoor || cmdFp || cmdRFID){
    myDoor.open();
    Serial.println("((Door Open))");
  }
  else{
    myDoor.close();
    Serial.println("((Door Close))");
  }

  //faire la commande
  analogWrite(2,myDoor.get_cmdAngle());
  analogWrite(5,myDoor.get_cmdBuzzer());

  //mettre a jour les capteurs



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
     
  // }


  sleep(1);
}


