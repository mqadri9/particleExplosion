//============================================================================
// Name        : Particle.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/* This Particle explosion program uses the SDL library.
1- Download the SDL2 for Mingw tar file and extract it. We need the x86-64 directory for 64 bits
2- Copy the content of the lib and include directories to the Mingw compiler lib and include directories respectively
3- Copy bin/SDL2.ddl and bin/sdl2-config to the bin directory of the Mingw compiler

Eclipse setup (linking libraries):
1) Go to project properties, c/c++ build, Mingw c++ linker, libraries and add the following in order
mingw32
SDL2main
SDL2
*/



#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace sdlscreen;

int main(int argc, char* argv[]) {
    // Start SDL2
	srand(time(NULL));
	Screen screen;
	if(screen.init() == false){
		cout << "Error initializing SDL." << endl;
	}

	Swarm swarm;

	// This while loop needs to run as fast as possible for smooth particle transitions
	while(true) {
		// Update particles
		int elapsed = SDL_GetTicks();
		swarm.update(elapsed);
		unsigned char green = (1 + sin(elapsed * 0.0001)) * 128; // multiply by for smoother changes. Unsiged char will map all values to 0-255
		unsigned char red = (1 + sin(elapsed * 0.0002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.0003)) * 128;

		const Particle * const pParticles = swarm.getParticles();

		for(int i=0; i< Swarm::NPARTICLES; i++) {
			// get ms since program started
			Particle particle = pParticles[i];

			// Since width > height, we need the same weight to guarantee a round explosion
			int x = (particle.m_x + 1) * screen.SCREEN_WIDTH / 2;
			int y = particle.m_y * screen.SCREEN_WIDTH / 2 + screen.SCREEN_HEIGHT / 2;
			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

		// Draw particles
		screen.update();

		// Check for messages/events
		if(screen.processEvents() == false) {
			break;
		}
	}
	screen.close();
	return 0;
}


