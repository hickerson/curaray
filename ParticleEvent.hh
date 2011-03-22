#ifndef __class_ParticleEvent_hh__
#define __class_ParticleEvent_hh__

#include <string>
#include <iostream>
#include "Event.hh"
#include "Particle.hh"
#include "Path.hh"

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

public:
	Pathlet* before;
	Pathlet* after;
	double in[3];
	double out[3];
	unsigned order;
	
public:
	bool out_of_bounds; // TODO clean up
	// Particle* particle;

public:
	ParticleEvent(double t, const double x[3], const double v[3])
		: Event(t)
	{
		before = 0;
		after = 0;
		order = 1;
    	for (unsigned k = 0; k < 3; k++)
		{
    		position[k] = x[k];
			in[k] = v[k];
			out[k] = v[k];
		}
	}

	ParticleEvent(double t, Pathlet* path_in, Pathlet* path_out) 
		: Event(t)
	{
		before = path_in;
		after = path_out;
		order = 2;
		if (before)
		{
			before->getPosition(t, position);
			before->getVelocity(t, in);
		}
		if (order > 0)
    		for (unsigned k = 0; k < 3; k++)
    			out[k] = in[k];
	}


public:
/*
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
*/	
	//~ParticleEvent() {};

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
