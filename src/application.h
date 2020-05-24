#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>

#define FORCELIM 88


using namespace std;

// classe represantant de la porte integré avec les systèmes de sécurité
class Door {
private:

	// commande de la valeur represantant l'angle de la porte (0-100)
	int cmdAngle;
	// commande de la valur represantant la frequence de Buzzer(0-100)
	int cmdBuzzer;
	// message d'affichage a l'ecran de l'interieur
	char msgIndoor[100];
	// message d'affichage a l'ecran de l'exterieur
	char msgOutdoor[100];

public:
	// constructeur
	Door();
	/*les getters et setters des membres de la classe Door */
	int get_cmdAngle();
	int get_cmdBuzzer();
	char* get_msgIndoor();
	char* get_msgOutdoor();
	void set_cmdAngle(int a);
	void set_cmdBuzzer(int b);
	// methode pour commander d'ouverture de la porte 
	void open();
	// methode pour commander la fermeture de la porte
	void close();
	// methode pour commander le buzzer quand la sonnette est appuyee
	void ringBuzzer();
	// methode pour commander le buzzer quand la l'alarme anti-intrusion est declenche
	void alarmBuzzer();
	// methode pour couper le son du buzzer 
	void muteBuzzer();
	// methode pour la gestion d'affichage de l'ecran a l'interieur
	void screenIndoor();
	// methode pour la gestion d'affichage de l'ecran a l'exterieur
	void screenOutdoor();
	// methode permettant de gerer tous les fonctionnalités de la classe Door  
	void run(int cmdBA,int cmdIndoor,int cmdOutdoor, int cmdFp, int val_butSetfp, int cmdRFID);
};

// classe represantant un système d'identification avec empreinte
class FingerprintSystem{
private:
	// variable that shows if the fingerprints match or not
	int match;
public:
	// constructeur
	FingerprintSystem();
	// getter du membre 'match'
	int getMatch();
	// methode pour verifier l'empreint qui est sur 'loadfp.txt'
	void verifyFingerprint(int loadfpval);
	// methode permettant de changer l'empreint installé sur 'savedfp.txt' à celui de 'loadfp.txt'
	void setFingerprint(int buttonFp, int val_fp);
	// methode qui permettant d'executer tous les programmes sur ce système
	void run(int val_butSetfp,int val_fp);
};


// classe representant un système d'identification par RFID
class RFIDSystem{
private:
	// variable that shows if the frequency detected match the one saved
	int match;
public:
	// constructeur
	RFIDSystem();
	// getter pour le membre 'match'
	int getMatch();
	// methode pour verifier le RFID detecté
	void verifyRFID(int loadrfidval);
};


// classe represantant un système d'alarme anti-intrusion
class BurglarAlertSystem{
private:
	// variable qui represent le declenchment de l'alarme
	int alert;
public:
	// constructeur
	BurglarAlertSystem();
	// getter de du membre 'alert'
	int getAlert();
	// methode pour demarrer les système
	void run(int forceval);
};

#endif