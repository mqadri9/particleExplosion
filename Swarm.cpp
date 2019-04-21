/*
 * Swarm.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: mqadri
 */

#include "Swarm.h"

namespace sdlscreen {

Swarm::Swarm(): lastTime(0) {
	// TODO Auto-generated constructor stub
	m_pParticles = new Particle[NPARTICLES];

}

Swarm::~Swarm() {
	// TODO Auto-generated destructor stub
	delete [] m_pParticles;
}

// we suply elapsed and make this runs with the same speed on all computers
void Swarm::update(int elapsed){
	int interval = elapsed - lastTime;
	for(int i=0; i< Swarm::NPARTICLES; i++) {
		m_pParticles[i].update(interval);
	}
	lastTime = elapsed;
}
} /* namespace sdlscreen */
