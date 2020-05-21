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
	int detectIndoor(int val_button);
	int detectOutdoor(int val_button);
	void openBuzzer();
	void closeBuzzer();
};

class FingerprintSystem{
private:
	int match;
public:
	FingerprintSystem();
	int getMatch();
	void verifyFingerprint(int loadfpval);
};





#endif