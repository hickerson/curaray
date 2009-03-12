#ifndef __class_Path_hh__
#define __class_Path_hh__

#include <string>
#include <iostream>
#include <vector>
//#include "Pathlet.hh"
#include "ParticleEvent.hh"
#include "polynomial.hh"

#define MAX_ORDER 4

using namespace std;

/**
 * Path
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
    double start_time;
    double stop_time;

public:
    Event* start_event;
    Event* stop_event;

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
	Pathlet(polynomial p[3]); 
	
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
    void getStartPosition(double position[3]) const ;
    void getStopPosition(double position[3]) const ;
    double getMaximum(double start, double stop, const double direction[3]) const ;
    void reflect(double normal[3]);
    void noreflect();
	void set(int axis, const polynomial &p);
	double get_relative_max_time() {return 1;} // TODO replace with numerical stability calculation
};

 
struct Path
{
    //unsigned count; 
    vector<Pathlet*> 	pathlets;
	vector<Event*>  	events;
    double 				start_time;
    double 				stop_time;
	Event* 				start_event;
	Event* 				stop_event;

private:
    bool 		_visable;
    unsigned 	_reflections;

public:
    //Path();
    ~Path();
    Path(const Path &);
	Path(Event* event); 
    Path(unsigned _count, double _t_start, double _t_stop);

    void getPosition(double time, double position[3]);
    double getPosition(double start, double stop, double position[3]);
    double getMaximum(double start, double stop, const double direction[3]);

	//void append(Event *event);
	//void append(Pathlet *pathlet);
	void append(Pathlet *pathlet, Event *event);

    int check();
    int check(double epsilon);
    void show();
    void hide();
    bool visable();

    //unsigned add(const Pathlet &_segment);
    unsigned discontinuities();
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
