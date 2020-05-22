
#include <thread>
#include <unistd.h>
#include <string.h>

#include "core_simulation.h"

//#include "application.h"

// class BoardException
int BoardException::get(){return num;}

string BoardException::text(){
  string s;
  switch(num){
  case SPEED : s=string("mauvaise vitesse de la laison terminal");break;
  case INOUT : s=string("mauvaise utilisation du sens de l'entree/sortie"); break;
  case ADDRESS : s=string("mauvaise adresse de la pin"); break;
  case SIZEXC : s=string("taille erronee"); break;
  case EMPTY: s=string("zone vide"); break;
  default: s=string("erreur inconnue");
  }
  return s;
}

// classe terminale
void Terminal::begin(int speed){
  if (speed!=9600){
    cerr << "wrong speed\n";
    throw BoardException(SPEED);
  }
}
void Terminal::println(string s){
  cout <<"Serial: "<< s<<endl;
}

// representatoin du bus I2C
I2C::I2C(){
  for(int i=0;i<MAX_I2C_DEVICES;i++){
    registre[i]=new char[I2C_BUFFER_SIZE];
    vide[i]=true;
  }
}

bool I2C::isEmptyRegister(int addr){
  bool result=true;
  if ((addr>=0)&&(addr<MAX_I2C_DEVICES))
    result=vide[addr];
  else
    throw BoardException(ADDRESS);
  return result;
}

int I2C::write(int addr, char* bytes, int size){
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  if ((size<0)||(size>I2C_BUFFER_SIZE))
    throw BoardException(SIZEXC);
  tabmutex[addr].lock();
  memcpy(registre[addr],bytes,size*sizeof(char));
  vide[addr]=false;
  tabmutex[addr].unlock();
  return size;
}

int I2C::requestFrom(int addr, char* bytes, int size){
  int result =0;
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  if ((size<0)||(size>I2C_BUFFER_SIZE))
    throw BoardException(SIZEXC);
  if (vide[addr]==false){
    tabmutex[addr].lock();
    memcpy(bytes,registre[addr],size*sizeof(char));
    vide[addr]=true;
    tabmutex[addr].unlock();
    result =size;
  }
  return result;
}

char * I2C::getRegistre(int addr){
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  return (registre[addr]);
}

bool* I2C::getVide(int addr){
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  return (&vide[addr]);
}

// classe generique reprenstant un capteur/actionneur
Device::Device(){
  ptrtype=NULL;
  ptrmem=NULL;
  i2caddr=-1;
  i2cbus=NULL;
}

void Device::run(){
  while(1){
    cout << "empty device\n";
    sleep(3);
  }
}

void Device::setPinMem(unsigned short* ptr,enum typeio *c){
  ptrtype=c;
  ptrmem=ptr;
}

void Device::setI2CAddr(int addr, I2C * bus){
  i2caddr=addr;
  i2cbus=bus;
}

// classe representant une carte arduino
void Board::run(){
  try{
    setup();
    while(1) loop();
  }
  catch(BoardException e){
    cout <<"exception: "<<e.get() <<endl;
  }
}

void Board::pin(int p, Device& s){
  s.setPinMem(&io[p], &stateio[p]);
  tabthreadpin[p]=new thread(&Device::run,&s);
  
}

void Board::pinMode(int p,enum typeio t){
  stateio[p]=t;
}

void Board::digitalWrite(int i, int l){
  if (stateio[i]==OUTPUT)
    io[i]=l;
  else
    throw BoardException(INOUT);
}

int Board::digitalRead(int i){
  int   result=0;
  if (stateio[i]==INPUT)
    result= io[i];
  else
    throw BoardException(INOUT);
  return result;
}

void Board::analogWrite(int i, int l){
  if (stateio[i]==OUTPUT)
    io[i]=l;
  else
    throw BoardException(INOUT);
}

int Board::analogRead(int i){
  int   result=0;
  if (stateio[i]==INPUT)
    result= io[i];
  else
    throw BoardException(INOUT);
  return result;
}

void Board::i2c(int addr,Device& dev){
  if ((addr<0)||(addr>=MAX_I2C_DEVICES))
    throw BoardException(ADDRESS);
  dev.setI2CAddr(addr,&bus);
  tabthreadbus[addr]=new thread(&Device::run,&dev);
}

/////////////////////////
Door::Door():cmdAngle(0),cmdBuzzer(0),msgIndoor("Initialising Indoor..."),msgOutdoor("Initialising Outdoor..."){
  
}

int Door::get_cmdAngle(){
  return cmdAngle;
}

void Door::set_cmdAngle(int a){
  cmdAngle = a;
}

int Door::get_cmdBuzzer(){
  return cmdBuzzer;
}

void Door::set_cmdBuzzer(int b){
  cmdBuzzer = b;
}

/*open door*/
void Door::open(){
  cmdAngle=100;;
}

/*close door*/
void Door::close(){
  cmdAngle=0;
}

int Door::detectIndoor(int val_button){
  int open;
  if(val_button){
    open = 1;
  }
  else{
    open = 0;
  }
  return open;
}

int Door::detectOutdoor(int val_button){
  int ring;
  if(val_button){
    ring = 1;
  }
  else{
    ring = 0;
  }
  return ring;
}

void Door::ringBuzzer(){
  cmdBuzzer=80;
}

void Door::alarmBuzzer(){
  cmdBuzzer=100;
}


void Door::muteBuzzer(){
  cmdBuzzer=0;
}

char* Door::get_msgIndoor(){
  return msgIndoor;
}

char* Door::get_msgOutdoor(){
  return msgOutdoor;
}


void Door::screenIndoor(){
  if(!cmdAngle){
    //door is closed
    if(cmdBuzzer>5 && cmdBuzzer<85 ){
      //someone rings the doorbell
      sprintf(msgIndoor," ((Inside)) Someone is at the door!");
    }else if(cmdBuzzer>=85){
      //someone is forcing the door!
      sprintf(msgIndoor," ((Inside)) Burglar Alert!!! Calling Police...");
    }else{    
      sprintf(msgIndoor," ((Inside)) Please press the indoor button!");
    }

  } else{
    //door is open
    sprintf(msgIndoor," Door is open!");
  }


}

void Door::screenOutdoor(){
  if(!cmdAngle){
    //door is closed
    if(cmdBuzzer>=85){
      //someone is forcing the door!
      sprintf(msgOutdoor," ((Outside)) Don't force the door, the police is coming !!!");
    }else{
      sprintf(msgOutdoor," ((Outside)) Please scan your fingerprint or your card! Doorbell is on your left!");
    }
    
  } else{
    //door is open
    sprintf(msgOutdoor," Door is open!");
  }
}

FingerprintSystem::FingerprintSystem():match(0){}

int FingerprintSystem::getMatch(){
  return match;
}

/*verifyFingerprint*/
void FingerprintSystem::verifyFingerprint(int loadfpval){
  string savedfpstring;
  static int savedfpval;
  fstream savedfpfile;

  savedfpfile.open("savedfp.txt");
  while(!savedfpfile.eof()){
    getline(savedfpfile,savedfpstring);
    
  }
  //cout<<"savedstring:"<<savedfpstring<<endl;
  if (!savedfpstring.empty()){
    //cout<<"ho"<<endl;
    savedfpval=stoi(savedfpstring);
  }
  //cout<<"savedvalue:"<<savedfpval<<endl;
  
  if(savedfpval==loadfpval){
    match=1;
  }else{
    match=0;
  }
  //cout<<"match"<<match<<endl;
  savedfpfile.close();
}

/*set new Fingerprint*/
void FingerprintSystem::setFingerprint(int buttonFp,int newFp){
  string savedfpstring;
  //int savedfpval;
  fstream savedfpfile;

  //cout<<"hi"<<newFp<<endl;
  if(buttonFp){
    // cout<<"newfp :"<<to_string(newFp)<<endl;
    
      //cout<<"helllllooooo"<<endl;
    savedfpfile.open("savedfp.txt",ios::out | ios::trunc); //delete content before open

    savedfpfile << to_string(newFp);
    
    
    savedfpfile.close();
      // getline(savedfpfile,savedfpstring);
      // cout<<"saved : "<<savedfpstring<<endl;
      
  }
  
}

RFIDSystem::RFIDSystem():match(0){}

int RFIDSystem::getMatch(){
  return match;
}

/*verifyRFID*/
void RFIDSystem::verifyRFID(int loadrfidval){
  string savedrfidstring;
  int savedrfidval;
  fstream savedrfidfile;

  savedrfidfile.open("savedrfid.txt");
  while(!savedrfidfile.eof()){
    getline(savedrfidfile,savedrfidstring);
    
  }
  
  if (!savedrfidstring.empty()){
    savedrfidval=stoi(savedrfidstring);
  }

  if(savedrfidval==loadrfidval){
    match=1;
  }else{
    match=0;
  }

  savedrfidfile.close();
}

BurglarAlertSystem::BurglarAlertSystem():alert(0){}

int BurglarAlertSystem::getAlert(){
  return alert;
}

/*verifyFingerprint*/
void BurglarAlertSystem::run(int forceval){

  if(forceval>FORCELIM){
    alert=1;
  }else{
    alert=0;
  }
  
}