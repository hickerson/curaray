#pragma once 
#ifndef __class_Geometry_hh__
#define __class_Geometry_hh__

#include <string>
#include <iostream>
#include "InteractionEvent.hh" 
#include "Path.hh"
using namespace std;

typedef int dimension;
typedef int codimension;
template <dimension n> class Point;

/**
 * Geometry
 *
 * Author: Kevin Peter Hickerson
 * Modified: Aug 24, 2010
 */
//template <dimension n, codimension m = 0> TODO turn this into a template class?
class Geometry
{
public: 
	virtual InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	virtual InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	
	virtual void writeMathematicaGraphics(ostream &out) = 0;
	virtual void writeMathematicaGraphics(ostream &out, double start_time, double stop_stop) = 0;

	//virtual double* get_random_point(double time) const = 0;
	virtual double* get_random_point() const = 0;
	//virtual Point<>* get_random_point() const = 0;
};

#endif
