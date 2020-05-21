#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "core_simulation.h"
#include "mydevices.h"


class Door {
private:
	int cmdAngle;
	int cmdBuzzer;

public:
	Door();
	int get_cmdAngle();
	int get_cmdBuzzer();
	void set_cmdAngle(int a);
	void set_cmdBuzzer(int b);
	void open();
	void close();
	//permet de savoir si bouton est appuye
	int detectIndoor(int val_button);
	int detectOutdoor(int val_button);
	void ringBuzzer();
	void muteBuzzer();
};

class FingerprintSystem{
private:
	int match;
public:
	FingerprintSystem();
	int getMatch();
	void verifyFingerprint(int loadfpval);
	void setFingerprint(int buttonFp, int val_fp);
};


class RFIDSystem{
private:
	int match;
public:
	RFIDSystem();
	int getMatch();
	void verifyRFID(int loadrfidval);
};


#endif