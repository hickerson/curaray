#ifndef __class_InteractionEvent_hh__
#define __class_InteractionEvent_hh__

#include <string>
#include <iostream>
#include "ContinuityEvent.hh"
//#include "ParticleEvent.hh"
//#include "Geometry.hh"
#include "Path.hh"
//#include "Surface.hh"


using namespace std;

class Geometry;
//class Pathlet;

/**
 * InteractionEvent
 *
 * Author: Kevin Peter Hickerson
 */
class InteractionEvent 
	: public ContinuityEvent
//	: public ParticleEvent
{
	const Geometry* geometry;
	double normal[3];
	//const Surface*  surface;
	
public:
	InteractionEvent(double t, const Geometry* _geometry, const double _normal[3])
		: ContinuityEvent(t), geometry(_geometry)
	{
        for (int i =0; i < 3; i++)
            normal[i] = _normal[i];

		//before->getPosition(t, position);
		//before->getVelocity(t, in);
        /*
		if (before)
		{
    		double n_i = dot(n,in);
    		for (unsigned k = 0; k < 3; k++)
			{
    			out[k] = in[k] - 2*n_i*n[k];
				normal[k] = n[k];
			}
		}
		else
			abort();
        */
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
	virtual void writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time);
};
#endif
