#ifndef __class_InteractionEvent_hh__
#define __class_InteractionEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
#include "Geometry.hh"
#include "Path.hh"
//#include "Surface.hh"


using namespace std;

class Geometry;

/**
 * InteractionEvent
 *
 * Author: Kevin Peter Hickerson
 */
class InteractionEvent : public ParticleEvent
{
	const Geometry* geometry;
	const Pathlet*  before;

public:
	double normal[3];
	//const Surface*  surface;
	
public:
	InteractionEvent(double t, const Geometry* g) 
	: ParticleEvent(t), geometry(g), before(0) {}

	InteractionEvent(double t, const Geometry* g, const double n[3]) 
	: ParticleEvent(t), geometry(g), before(0) 
	{
		set_normal(n);
	}

	~InteractionEvent() {};

	void set_normal(const double n[3]) 
	{
		for (int i = 0; i < 3; i++)
			normal[i] = n[i];
	}
};
#endif
