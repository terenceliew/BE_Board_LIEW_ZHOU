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
	void open();
	void close();
	void detectIndoor(int val_button);
};





#endif