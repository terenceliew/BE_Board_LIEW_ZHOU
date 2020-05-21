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
	
public:
	Door();
	int get_cmdAngle();
	void set_cmdAngle(int a);
	void open();
	void close();
	//permet de savoir si bouton est appuye
	int detectIndoor(int val_button);
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





#endif