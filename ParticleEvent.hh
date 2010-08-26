#ifndef __class_ParticleEvent_hh__
#define __class_ParticleEvent_hh__

#include <string>
#include <iostream>
#include "Event.hh"
#include "Particle.hh"

#define dot(u,v)  (u[0]*v[0]+u[1]*v[1]+u[2]*v[2])

using namespace std;

/**
 * ParticleEvent
 *
 * Author: Kevin Peter Hickerson
 * Date:   March 3, 2009
 */
class ParticleEvent : public Event
{
public:
	double position[3];
	//double momentum[3];
	double velocity[3];
	// Particle* particle;

public:
	bool out_of_bounds; // TODO clean up

public:
	ParticleEvent(double t) 
		//: Event(t), particle(NULL) {}
		: Event(t) {}
	
	~ParticleEvent() {};

	// XXX this copies the particle around for no reason
	//     most simulations have identicle particles 
	//     so store somewhere else like the particle sorce
	double get_velocity(int i)
	{
		return velocity[i];
	}
	
/*	
	double get_momentum(int i)
	{
		return momentum[i];
	}
*/
	double get_position(int i)
	{
		return position[i];
	}
	
	double set_velocity(double v[3])
	{
		for (int i=0; i<3; i++)
			velocity[i] = v[i];
	}
/*		
	double set_momentum(double p[3])
	{
		for (int i=0; i<3; i++)
			momentum[i] = p[i];
	}
*/	
	double set_position(double x[3])
	{
		for (int i=0; i<3; i++)
			position[i] = x[i];
	}

	// TODO move to SurfaceMap?
	void reflect_velocity(const double normal[3])
	{ 
    	double vn = dot(velocity, normal);
    	for (unsigned i = 0; i < 3; i++)
    		velocity[i] -= 2*vn*normal[i];
	}
};

#endif
