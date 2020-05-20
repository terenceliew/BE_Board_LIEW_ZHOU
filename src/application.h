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
	int pinServo;
	int pinIndoorButton;
public:
	Door(int pServo, int pIndoorButton);
	void open();
	void close();
	void detectIndoor();
};





#endif