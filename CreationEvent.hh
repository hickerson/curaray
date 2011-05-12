#ifndef __class_CreationEvent_hh__
#define __class_CreationEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
#include "Geometry.hh"
//#include "Path.hh"


using namespace std;
class Pathlet;
class Source;

/**
 * CreationEvent
 *
 * Author: Kevin Peter Hickerson
 */
class CreationEvent : public ParticleEvent
{
  public:
    //const Source* _source;
    const Geometry* geometry;
	//Pathlet* after;
	//double out[3];
	
  public:
	CreationEvent(double t, double x[3], double v[3], const Geometry* _geometry)
	: ParticleEvent(t,x,v), geometry(_geometry)
	{
		//set_position(x);
		//set_velocity(v);
	}
	//~CreationEvent();

/*
	double get_velocity(int i)
	{
		return out[i];
	}

	void set_velocity(double v[3])
	{
		for (int i=0; i<3; i++)
			out[i] = v[i];
	}
*/
};

#endif
