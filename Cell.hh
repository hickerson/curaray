#ifndef __class_Cell_hh__
#define __class_Cell_hh__

#include <string>
#include <iostream>
#include "InteractionEvent.hh" 
#include "Path.hh"

using namespace std;

class InteractionEvent;

/**
 * Cell
 *
 * Author: Kevin Peter Hickerson
 */
class Cell
{
public:
	Cell() {};
	~Cell() {};

public: 
	virtual InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	virtual InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	
	virtual void writeMathematicaGraphics(ofstream & of) = 0;
	virtual void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop) = 0;

	virtual double* get_random_point(double time) const = 0;
};

#endif
