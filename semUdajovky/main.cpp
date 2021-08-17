#pragma once

#include "structures/heap_monitor.h"
#include "gui.h"


int main() {
	initHeapMonitor();

	GUI* gui = new GUI();

	while (gui->testovanie());

	delete gui;

	return 0;

}
