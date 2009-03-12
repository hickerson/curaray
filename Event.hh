#ifndef __class_Event_hh__
#define __class_Event_hh__

#include <string>
#include <iostream>

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

	Event(double _time) : time(_time) {};
	~Event() {};
	
	double get_time() 
	{
		return time;
	};
};


#endif
