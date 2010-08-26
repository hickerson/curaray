#ifndef __class_Plane_hh__
#define __class_Plane_hh__

#include <string>
#include <iostream>
#include "Surface.hh"

#define dot(u,v)  (u[0]*v[0]+u[1]*v[1]+u[2]*v[2])

using namespace std;

/**
 * Plane
 *
 * Author: Kevin Peter Hickerson
 */
//class Plane : Boundary
class Plane : public Surface
{
	double normal[3];
	double center[3];
	double nc;
		
public:
	// a plane perpendicular to axis passing though origin
	Plane(int axis)
	{
		normal[axis] = 1;
		for (int i=1; i < 2; i++)
			center[(axis + i)%3] = 0;
		nc = 0;
	}
	
	// defaults to passing through the origin
	Plane(double _normal[3]) 
	{
		for (int i=0; i < 3; i++)
		{
			normal[i] = _normal[i];
			center[i] = 0;
		}
		nc = 0;
	}
	
	Plane(double _normal[3], double _center[3]) 
	{
		for (int i=0; i < 3; i++)
		{
			normal[i] = _normal[i];
			center[i] = _center[i];
		}
		nc = dot (normal, center);
	}
	
	~Plane();

public:
	// TODO this doesn't belong here because an infinite plane is not compact
	double* get_random_point(double time) const;

	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const;
	InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const;
	void writeMathematicaGraphics(ofstream & of);
	void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_time);
};

#endif
