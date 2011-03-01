#ifndef __class_CreationEvent_hh__
#define __class_CreationEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
#include "Path.hh"


using namespace std;

/**
 * CreationEvent
 *
 * Author: Kevin Peter Hickerson
 */
class CreationEvent : public ParticleEvent
{
private:
	Pathlet* after;
	
public:
	CreationEvent(double t, double x[3], double v[3])
	: ParticleEvent(t)
	{
		set_position(x);
		set_velocity(v);
	}

	~CreationEvent();
};

#endif
