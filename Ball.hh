#ifndef __class_Ball_hh__
#define __class_Ball_hh__

#include <iostream>
#include "CellularComplex.hh"
using namespace std;

/**
 * Ball
 *
 * Author: Kevin Peter Hickerson
 */
template <dimension k, codimension n> 
class Ball : public CellularComplex<k,n>
{
	double radius;
	double center[k];
	
public:
	Ball() // unit sphere
	: radius(1)
	{
		for (int i = 0; i < k; i++)
			center[i] = 0;
	}
	
	Ball(double _radius) 
	: radius(_radius)
	{
		for (int i = 0; i < k; i++)
			center[i] = 0;
	}

	Ball(double _center[k], double _radius) 
	: radius(_radius)
	{
		for (int i = 0; i < k; i++)
			center[i] = _center[i];
	}
	
	~Ball();

	double* get_random_point(double time) const;
	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const;
	InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const;
	void writeMathematicaGraphics(ofstream & of);
	void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop);
};

template <dimension k, codimension n>
double* Ball<k,n>::get_random_point(double time) const 
{
	double* p = new double[k];
	// randomBallVector(p, radius);  // TODO make multidimensional 
	for (int i = 0; i < k; i++)
		p[i] += center[i];
	return p;
}

template <dimension k, codimension n>
void Ball<k,n>::writeMathematicaGraphics(ofstream & math_file) 
{
	math_file << "Graphics3D[ {Red, Opacity[0.3], "
			  << "Ball [{" << center[0] << ", " << center[1] << ", " << center[2] << "}, "  << radius << "]";
	math_file << "}]";
}

template <dimension k, codimension n>
void Ball<k,n>::writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop)
{
	writeMathematicaGraphics(math_file);
}
#endif
