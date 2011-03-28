#ifndef __class_Path_hh__
#define __class_Path_hh__

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "polynomial.hh"
//#include "InteractionEvent.hh"
//#include "ContinuityEvent.hh"
#include "Event.hh"

#define MAX_ORDER 4

//class InteractionEvent;
//class ContinuityEvent;
//class ParticleEvent;
//class Event;

using namespace std;

class Vertex;


/**
 * Pathlet
 *
 * Author: Kevin Peter Hickerson
 */
struct Pathlet
{
private:
	// may not need this if we always define as unity
	// for now scale is the endpoint 
	double scale; 
    
public:
	polynomial curve[3];

	// TODO make private
    //double start_time;
    //double stop_time;

public:
    //Event* start_event;
    //Event* stop_event;
    Vertex* start;
    Vertex* stop;

    //unsigned dim; // for now dim = 3
    //bool reflection;
    //bool start_reflection;
    //bool stop_reflection;
    //unsigned order; 
    //double coefficient[MAX_ORDER][3]; // at most 4th order

public:
    Pathlet();
    Pathlet(const Pathlet &);
	//Pathlet(Event* start, polynomial p[3]);
	//Pathlet(Event* start, Event* stop, polynomial p[3]); 
	//Pathlet(polynomial p[3]); 
	Pathlet(polynomial p[3], Vertex* _start); 
	Pathlet(polynomial p[3], Vertex* _start, Vertex* _stop); 
	
/*
    Pathlet(double _start_time,
			double _stop_time,
			const polynomial p[3]);
	Pathlet(//const Particle & particle, 
            const double time,
		    const double a[3]);
    Pathlet(//const Particle & particle,  
            const double time,
		    const double a[3], 
            const double b[3]);
    Pathlet(//const Particle & particle, 
            const double time,
			const double a[3], 
			const double b[3],
			const double c[3]);
	*/

public:
    void getPosition(double time, double position[3]) const ;
    void getVelocity(double time, double velocity[3]) const ;
    void getStartPosition(double position[3]) const ;
    void getStopPosition(double position[3]) const ;
    double getMaximum(double start, double stop, const double direction[3]) const ;
    void reflect(double normal[3]);
    void noreflect();
	void set(int axis, const polynomial &p);
	double get_relative_max_time() {return 1;} // TODO replace with numerical stability calculation
	void writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time);
	double get_start_time();
	double get_stop_time();
};


/**
 * PathEvent
 * 
 * Author: Kevin Peter Hickerson
 */
class Vertex 
{
public:
	double position[3];
	double in[3];
	double out[3];
	Pathlet* before;
	Pathlet* after;
	unsigned order;
	Event* event;
	
public:
	Vertex(Event* _event, const double x[3], const double v[3])
	{
		event = _event;
		before = 0;
		after = 0;
		order = 1;
    	for (unsigned k = 0; k < 3; k++)
		{
    		position[k] = x[k];
			in[k] = v[k];
			out[k] = v[k];
		}
	}

	Vertex(Event* _event , Pathlet* _before, Pathlet* _after) 
	{
		event = _event;
		before = _before;
		after = _after;
		order = 2;
		if (before)
		{
			before->getPosition(event->get_time(), position);
			before->getVelocity(event->get_time(), in);
		}
		if (order > 0)
    		for (unsigned k = 0; k < 3; k++)
    			out[k] = in[k];
	}

	double get_position(int i)
	{
		return position[i];
	}
	
	void set_position(double x[3])
	{
		for (int i=0; i<3; i++)
			position[i] = x[i];
	}

	double get_in(int i)
	{
		return in[i];
	}

	double get_out(int i)
	{
		return out[i];
	}
};
 
struct Path
{
    //unsigned count; 
    vector<Pathlet*> 	pathlets;
	vector<Vertex*>  	verticies;
	//vector<Event*>  	events;
    //double 			start_time;
    //double 			stop_time;
	//Event* 			start_event;
	//Event* 			stop_event;
	Vertex* 			start;
	Vertex* 			stop;

private:
    bool 		_visable;
    unsigned 	_reflections;

public:
    //Path();
    ~Path();
    Path(const Path &);
	//Path(Event* event); 
	Path(Vertex* vertex); 
    Path(unsigned _count, double _t_start, double _t_stop);

    void getPosition(double time, double position[3]);
    void getVelocity(double time, double velocity[3]);
    double getPosition(double start, double stop, double position[3]);
    double getMaximum(double start, double stop, const double direction[3]);

	//void append(Event *event);
	//void append(Pathlet *pathlet);
	//void append(Pathlet *pathlet, Event *event);
	//void append(polynomial p[3], Event *e);
	void append(Pathlet *pathlet, Vertex *v);
	//void append_continuity(Pathlet *pathlet, ContinuityEvent *event);
	//void append_interaction(Pathlet *pathlet, InteractionEvent *event);

    int check();
    int check(double epsilon);
    void show();
    void hide();
    bool visable();

    //unsigned add(const Pathlet &_segment);
    unsigned discontinuities();
	void writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time);
};






/*
struct PathIter
{
    PathIter(const Path &path);
    PathIter(const Path &path,
                     double start_time, double stop_time);
    PathIter(const Path &path,
                     double start_time, 
                     double stop_time,
                     double step_time);

    void start();
    void start(double start_time);
    void next();
    bool more();

    void ignore_segments();
    void stepto_segments();

private:
    const Path & _path;
    double _start_time;
    double _stop_time;
    double _step_time;
    double _time;
 
    bool _segments;
};
*/


#endif
