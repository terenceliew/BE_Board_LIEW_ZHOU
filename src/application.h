#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>

#define FORCELIM 88


using namespace std;

class Door {
private:


	int cmdAngle;
	int cmdBuzzer;
	char msgIndoor[100];
	char msgOutdoor[100];

public:
	Door();
	int get_cmdAngle();
	int get_cmdBuzzer();
	char* get_msgIndoor();
	char* get_msgOutdoor();
	void set_cmdAngle(int a);
	void set_cmdBuzzer(int b);
	void open();
	void close();

	void ringBuzzer();
	void alarmBuzzer();
	void muteBuzzer();
	void screenIndoor();
	void screenOutdoor();
	void run(int cmdBA,int cmdIndoor,int cmdOutdoor, int cmdFp, int val_butSetfp, int cmdRFID);
};

class FingerprintSystem{
private:
	int match;
public:
	FingerprintSystem();
	int getMatch();
	void verifyFingerprint(int loadfpval);
	void setFingerprint(int buttonFp, int val_fp);
	void run(int val_butSetfp,int val_fp);
};


class RFIDSystem{
private:
	int match;
public:
	RFIDSystem();
	int getMatch();
	void verifyRFID(int loadrfidval);
};


class BurglarAlertSystem{
private:
	int alert;
public:
	BurglarAlertSystem();
	int getAlert();
	void run(int forceval);
};

#endif