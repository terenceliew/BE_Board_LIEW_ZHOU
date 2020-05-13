#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  // pinMode(4,INPUT);

  //pinMode(0,OUTPUT);
  pinMode(3,OUTPUT);
}

// la boucle de controle arduino
void Board::loop(){
  char buf_temperature[100];
  char buf_lum[100];
  int val_temp;
  int val_lum;

  static int cpt=0;
  static int bascule=0;

  int i=0;

  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature
    val_temp=analogRead(1);
    sprintf(buf_temperature,"temperature %d",val_temp);
    Serial.println(buf_temperature);
    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      sprintf(buf_temperature,"%d",val_temp);
      bus.write(1,buf_temperature,100);
    }

    // lecture sur la pin 2 : capteur de luminosite
    val_lum=analogRead(2);
    sprintf(buf_lum,"luminosity %d",val_lum);
    Serial.println(buf_lum);
    
    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la luminosite
      sprintf(buf_lum,"%d",val_lum);
      bus.write(1,buf_lum,100);
    }

    cpt++;
    sleep(1);
  }
// // on eteint et on allume la LED
//   if(bascule)
//     digitalWrite(0,HIGH);
//   else
//     digitalWrite(0,LOW);
//   bascule=1-bascule;



  // on eteint et on allume la LED
  if(bascule)
    digitalWrite(3,HIGH);
  else
    digitalWrite(3,LOW);
  bascule=1-bascule;


  
}


