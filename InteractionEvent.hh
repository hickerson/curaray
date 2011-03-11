#ifndef __class_InteractionEvent_hh__
#define __class_InteractionEvent_hh__

#include <string>
#include <iostream>
#include "ContinuityEvent.hh"
//#include "ParticleEvent.hh"
//#include "Geometry.hh"
//#include "Path.hh"
//#include "Surface.hh"


using namespace std;

class Geometry;
class Pathlet;

/**
 * InteractionEvent
 *
 * Author: Kevin Peter Hickerson
 */
//class InteractionEvent : public ParticleEvent
class InteractionEvent 
	: public ContinuityEvent
{
	const Geometry* geometry;
	double normal[3];
	//const Surface*  surface;
	
public:
	InteractionEvent(double t, const Geometry* g, const double n[3], 
					 Pathlet* path_in, Pathlet* path_out) 
		: ContinuityEvent(t)
		//: geometry(g), before(path_in), after(path_out), order(0)
	{
		time = t;
		geometry = g;
		before = path_in;
		after = path_out;
		order = 0;
		assert(before);
		before->getPosition(t, position);
		before->getVelocity(t, in);
    	double ni = dot(n,in);
    	for (unsigned k = 0; k < 3; k++)
		{
    		out[k] = in[k] - 2*ni*n[k];
			normal[k] = n[k];
		}
	}

	~InteractionEvent() {};

/*
	void set_normal(const double n[3]) 
	{
		for (int i = 0; i < 3; i++)
			normal[i] = n[i];
	}
*/
	
private:
/*
	void reflect_velocity()
	{ 
    	double vn = dot(in, normal);
    	for (unsigned i = 0; i < 3; i++)
    		out[i] -= 2*vn*normal[i];
	}
*/
	//virtual void writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time);
};
#endif
