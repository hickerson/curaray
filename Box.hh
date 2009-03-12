#ifndef __class_Box_hh__
#define __class_Box_hh__

//#include <string>
//#include <iostream>
#include "Volume.hh"

//using namespace std;

/**
 * Box
 *
 * A Box is just a 3-Interval.
 * In the future this should be replaced with its n-dim analog, the n-Interval
 * 
 * Author: Kevin Peter Hickerson
 * Date:   March 2, 2009
 */
class Box : public Volume
{
	//double x[3][2];
	double x_min, x_max;
	double y_min, y_max;
	double z_min, z_max;

  public:	
	Box(double _x_min, double _x_max,
		double _y_min, double _y_max,
	    double _z_min, double _z_max)
		: x_min(_x_min), x_max(_x_max),
		  y_min(_y_min), y_max(_y_max),
	      z_min(_z_min), z_max(_z_max) {}
	Box(const Box &copy)
		: x_min(copy.x_min), x_max(copy.x_max),
		  y_min(copy.y_min), y_max(copy.y_max),
	      z_min(copy.z_min), z_max(copy.z_max) {}
	~Box() {}
		
	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const;
	double* get_random_point(double time) const;
};

#endif
