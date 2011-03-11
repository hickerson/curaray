#ifndef __class_ContinuityEvent_hh__
#define __class_ContinuityEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
//#include "AnnihilationEvent.hh"
//#include "CreationEvent.hh"
//#include "Path.hh"

using namespace std;
class Pathlet;

/**
 * ContinuityEvent
 *
 * Author: Kevin Peter Hickerson
 */
class ContinuityEvent 
	: public ParticleEvent
//	: public CreationEvent,
//	  public AnnihilationEvent
{
public:
	Pathlet* before;
	Pathlet* after;
	double in[3];
	double out[3];
	unsigned order;
	
public:
	ContinuityEvent(double t, Pathlet* path_in, Pathlet* path_out) 
		: ParticleEvent(t)
	{
		time = t;
		before = path_in;
		after = path_out;
		order = 2;
		if (before)
		{
			before->getPosition(t, position);
			before->getVelocity(t, in);
		}
    	for (unsigned k = 0; k < 3; k++)
		{
    		out[k] = in[k];
		}
	}

	ContinuityEvent(double t, double x[3], double v[3])
		: ParticleEvent(t,x)
	{ 
		before = 0;
		after = 0; 
		order = 2;
		for (int i = 0; i < 3; i++)
		{
			in[i] = v[i];
			out[i] = v[i];
		}
	}	

	//~ContinuityEvent();
	//virtual void writeMathematicaGraphics(ofstream &, double start_write_time, double stop_write_time);
};

#endif
