#ifndef __class_Sphere_hh__
#define __class_Sphere_hh__

#include <string>
#include <iostream>
#include "Surface.hh"

using namespace std;

/**
 * Sphere
 *
 * Author: Kevin Peter Hickerson
 */
//class Sphere : Boundary
class Sphere : public Surface
{
	double radius;
	double center[3];
	
public:
	Sphere() // unit sphere
	: radius(1)
	{
		for (int i = 0; i < 3; i++)
			center[i] = 0;
	}
	
	Sphere(double _center[3], double _radius) 
	: radius(_radius)
	{
		for (int i = 0; i < 3; i++)
			center[i] = _center[i];
	}
	
	~Sphere();

	double* get_random_point(double time) const;
	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const;
};

#endif
