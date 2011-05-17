#ifndef __class_AnnihilationEvent_hh__
#define __class_AnnihilationEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
//#include "Path.hh"


using namespace std;
class Pathlet;

/**
 * AnnihilationEvent
 *
 * Author: Kevin Peter Hickerson
 */
class AnnihilationEvent : public ParticleEvent
{
	//Pathlet* before;
	//double in[3];
	
public:
	AnnihilationEvent(double t)
	: ParticleEvent(t)
	{
		//set_position(x);
		//set_velocity(v);
	}
	

	//~AnnihilationEvent();
	virtual void writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time);
};

#endif
