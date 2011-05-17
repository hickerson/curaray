#ifndef __class_ContinuityEvent_hh__
#define __class_ContinuityEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
//#include "AnnihilationEvent.hh"
//#include "CreationEvent.hh"
#include "Path.hh"


using namespace std;
//class Pathlet;

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
/*
public:
	Pathlet* before;
	Pathlet* after;
	double in[3];
	double out[3];
	unsigned order;
*/
	
public:
	ContinuityEvent(double t)
		: ParticleEvent(t)
	{
        // order... ?
	}

	ContinuityEvent(double t, const double x[3])
		: ParticleEvent(t,x)
	{
        // order... ?
	}
/*
	ContinuityEvent(double t, Pathlet* path_in, Pathlet* path_out) 
		: ParticleEvent(t, path_in, path_out)
	{
		order = 2;
		if (order > 0)
    		for (unsigned k = 0; k < 3; k++)
    			out[k] = in[k];
	}

	ContinuityEvent(double t)
		: ParticleEvent(t)
	{ 
		//before = 0;
		//after = 0; 
		order = 2;
		for (int i = 0; i < 3; i++)
		{
			in[i] = v[i];
			out[i] = v[i];
		}
	}	
*/

/*
	double get_in(int i)
	{
		return in[i];
	}

	double get_out(int i)
	{
		return out[i];
	}
*/
	//~ContinuityEvent();
	virtual void writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time);
};

#endif
