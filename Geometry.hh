#ifndef __class_Geometry_hh__
#define __class_Geometry_hh__

#include <string>
#include <iostream>
#include "InteractionEvent.hh" 
#include "Path.hh"

using namespace std;

class InteractionEvent;

/**
 * Geometry
 *
 * Author: Kevin Peter Hickerson
 */
class Geometry
{
public:
	Geometry() {};
	~Geometry() {};

public: 
	virtual InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	virtual double* get_random_point(double time) const = 0;
};

#endif
