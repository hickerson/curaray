#ifndef __class_Event_hh__
#define __class_Event_hh__

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * Event
 *
 * Author: Kevin Peter Hickerson
 */
class Event
{
public:
	double time;

	Event(double _time) 
		: time(_time) {};
	~Event() {};
	
	//double get_time();

	//virtual void writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time) = 0;
	virtual void writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time) = 0;
};


#endif
