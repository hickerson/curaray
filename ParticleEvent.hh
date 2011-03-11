#ifndef __class_ParticleEvent_hh__
#define __class_ParticleEvent_hh__

#include <string>
#include <iostream>
#include "Event.hh"
#include "Particle.hh"

#define dot(u,v)  (u[0]*v[0]+u[1]*v[1]+u[2]*v[2])

using namespace std;
class Pathlet;

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
	//double velocity[3];

	// Particle* particle;

public:
	bool out_of_bounds; // TODO clean up

public:
	ParticleEvent(double t)
		: Event(t) 
	{
	}

	ParticleEvent(double t, double x[3]) 
		: Event(t) 
	{
		for (int i = 0; i < 3; i++)
			position[i] = x[i];
	}
	
	~ParticleEvent() {};

	// XXX this copies the particle around for no reason
	//     most simulations have identical particles 
	//     so store somewhere else like the particle source
/*
	double get_velocity(int i)
	{
		return velocity[i];
	}

	void set_velocity(double v[3])
	{
		for (int i=0; i<3; i++)
			velocity[i] = v[i];
	}

	// TODO move to SurfaceMap?
	void reflect_velocity(const double normal[3])
	{ 
    	double vn = dot(velocity, normal);
    	for (unsigned i = 0; i < 3; i++)
    		velocity[i] -= 2*vn*normal[i];
	}
*/	
	double get_position(int i)
	{
		return position[i];
	}
	
	void set_position(double x[3])
	{
		for (int i=0; i<3; i++)
			position[i] = x[i];
	}

	virtual void writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time);
};

#endif
