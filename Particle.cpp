/*
 * Particle.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: mqadri
 */

#include "Particle.h"
#include <stdlib.h>
#include <math.h>
namespace sdlscreen {

Particle::Particle() {
	/*
	m_x = ((2.0 * rand())/RAND_MAX) - 1; // number between -1 and 1
	m_y = ((2.0 * rand())/RAND_MAX) - 1;
	m_xspeed =  0.001*((2.0 * rand())/RAND_MAX - 1);
	m_yspeed =  0.001*((2.0 * rand())/RAND_MAX - 1); */
	init();
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::init() {
	m_x = 0;
	m_y = 0;
	m_direction = 2* M_PI * rand()/RAND_MAX;
	m_speed = (0.04 * rand())/RAND_MAX;

	m_speed *= m_speed;
}

void Particle::update(int interval){
	m_direction += interval * 0.0003;
	double xspeed = m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);

	// amount the particle moves is proportional to the time since last game loop iteration
	m_x += xspeed * interval;
	m_y += yspeed * interval;
	if(m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		init();
	}
	if(rand() < RAND_MAX/100) {
		init();
	}
}

} /* namespace sdlscreen */
