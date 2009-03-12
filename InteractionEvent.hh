#ifndef __class_InteractionEvent_hh__
#define __class_InteractionEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
#include "Geometry.hh"
#include "Path.hh"

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
	InteractionEvent(double t, const Geometry* g) 
	: ParticleEvent(t), geometry(g), before(0) {};
	~InteractionEvent() {};
};

#endif
