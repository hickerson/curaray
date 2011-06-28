#ifndef __class_Vertex_hh__
#define __class_Vertex_hh__

#include <string>
#include <iostream>
#include "Event.hh"

class Pathlet;

/**
 * Vertex
 * 
 * Author: Kevin Peter Hickerson
 * Date: May 6, 2011
 * Note: Code moved to this file on creation date. Class written earlier. Used to be in Path.[hh,cc]
 */
class Vertex 
{
	double position[3];
	double in[3];
	double out[3];
	Pathlet* before;
	Pathlet* after;
	unsigned order;
	Event* event;

    enum vertexType {
        continuous,
        begining,
        end,
        branch,
        reflection,
        interacting
    };

	
public:
	//Vertex(double _time, const double x[3], const double v[3]);
	Vertex(Event* _event, const double x[3], const double v[3]);
	//Vertex(Event* _event , Pathlet* _before, Pathlet* _after);
	Vertex(Event* _event , Pathlet* _before);

    double get_time();
	double get_position(int i);
	void get_position(double x[3]);
	void set_position(const double x[3]);
	double get_in(int i);
	double get_out(int i);
	void get_in(double p[3]);
	void get_out(double p[3]);
	void set_in(const double p[3]);
	void set_out(const double p[3]);
	void set_event(Event* _event);
	Event* get_event();
	void set_before(Pathlet* _before);
	void set_after(Pathlet* _after);
	//void set_all(Event* _event, Pathlet* _before, Pathlet* _after);

	void writeJSON(ostream &math_file, double start_write_time, double stop_write_time);
	void writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time);
};
#endif
