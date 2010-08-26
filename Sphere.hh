#ifndef __class_Sphere_hh__
#define __class_Sphere_hh__

#include <string>
#include <iostream>
#include "CellularComplex.hh"

using namespace std;

/**
 * k-Sphere
 *
 * Author: Kevin Peter Hickerson
 */
template <dimension k>
class Sphere : public CellularComplex<k> 
{
	double radius;
	double center[k+1];
	
public:
	Sphere() // unit sphere
	: radius(1)
	{
		for (int i = 0; i < 3; i++)
			center[i] = 0;
	}
	
	Sphere(double _center[k+1], double _radius) 
	: radius(_radius)
	{
		for (int i = 0; i < k+1; i++)
			center[i] = _center[i];
	}
	
	~Sphere();

	double* get_random_point(double time) const;
	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const;
	InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const;
	void writeMathematicaGraphics(ofstream & of);
	void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop);
};


template <dimension k>
InteractionEvent* Sphere<k>::interact(Pathlet* pathlet, double start_time, double stop_time) const
{
	return NULL;
}


template <dimension k>
InteractionEvent* Sphere<k>::selfinteract(Pathlet* pathlet, double start_time, double stop_time) const
{
	return NULL;
}

template <dimension k>
double* Sphere<k>::get_random_point(double time) const 
{
	double* p = new double[k+1];
	//randomSphereVector(p, radius);
	for (int i = 0; i < k+1; i++)
		p[i] += center[i];
	return p;
}

template <dimension k>
void Sphere<k>::writeMathematicaGraphics(ofstream & math_file) 
{
	math_file << "Graphics3D[ {Red, Opacity[0.3], "
			  << "Sphere [{" << center[0] << ", " << center[1] << ", " << center[2] << "}, "  << radius << "]";
	math_file << "}]";
}

// TODO StaticGeometry class?
template <dimension k>
void Sphere<k>::writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop)
{
	writeMathematicaGraphics(math_file);
}
#endif
