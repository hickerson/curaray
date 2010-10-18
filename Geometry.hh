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
class InteractionEvent;

/**
 * Geometry
 *
 * Author: Kevin Peter Hickerson
 * Modified: Aug 24, 2010
 */
//template <dimension k>
class Geometry
{
public: 
	virtual InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const {}
	virtual InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const {}
	
	virtual void writeMathematicaGraphics(ofstream & of) = 0;
	virtual void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop) = 0;

	//virtual double* get_random_point(double time) const = 0;
	virtual double* get_random_point() const = 0;
	//virtual Point<>* get_random_point() const = 0;
};

#endif
