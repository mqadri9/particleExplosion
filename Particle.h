/*
 * Particle.h
 *
 *  Created on: Apr 20, 2019
 *      Author: mqadri
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <stdlib.h>

namespace sdlscreen {

// by default member variables in a class are private and member variables in structs are private
struct Particle {
double m_x;
double m_y;

//particle speed
double m_speed;

// particle angle
double m_direction;

private:
void init();

public:
	Particle();
	virtual ~Particle();
	void update(int interval);
};

} /* namespace sdlscreen */

#endif /* PARTICLE_H_ */
