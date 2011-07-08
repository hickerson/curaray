#ifndef __class_Path_hh__
#define __class_Path_hh__

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "assert.h"

#include "polynomial.hh"
#include "Event.hh"

#define MAX_ORDER 4

using namespace std;

class Vertex;

/**
 * Pathlet
 *
 * Author: Kevin Peter Hickerson
 */
class Pathlet
{
  public: 
    friend class Path;

  private:
    Vertex* start;
    Vertex* stop;
	polynomial curve[3];

	const double scale; // for now always 1
    //unsigned dim; // for now dim = 3
    //unsigned order; 

  public:
    Pathlet();
    Pathlet(const Pathlet &);
	//Pathlet(polynomial p[3], Vertex* _start); 
	Pathlet(polynomial p[3], Vertex* _start, Vertex* _stop); 
	
  public:
    void get_moment(double time, double position[3]) const ;
    void get_position(double time, double position[3]) const ;
    void get_velocity(double time, double velocity[3]) const ;
    void getStartPosition(double position[3]) const ;
    void getStopPosition(double position[3]) const ;
    double getMaximum(double start, double stop, const double direction[3]) const ;
    void reflect(double normal[3]);
    void noreflect();
	void set(int axis, const polynomial &p);
	double get_stable_time(int axis); // TODO replace with numerical stability calculation
	double get_stable_time();
	double get_start_time();
	double get_stop_time();
	void set_start_vertex(Vertex*);
	void set_stop_vertex(Vertex*);
	Vertex* get_start_vertex();
	Vertex* get_stop_vertex();
    const polynomial& get_curve(int i) const;
	void writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time);
	void writeJSON(ostream &out, double start_write_time, double stop_write_time);
};


class Path
{
  private:
    //unsigned count; 
    vector<Pathlet*> 	pathlets;
	vector<Vertex*>  	verticies;
	Vertex* 			start;
	Vertex* 			stop;

    bool 		        _visable;
    unsigned 	        _reflections;

  public:
    //Path();
    ~Path();
    Path(const Path &);
	Path(Vertex* vertex); 

    void get_position(double time, double position[3]);
    void get_velocity(double time, double velocity[3]);
    double get_position(double start, double stop, double position[3]);
    double get_maximum(double start, double stop, const double direction[3]);

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
	void writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time);
	void writeJSON(ostream &out, double start_write_time, double stop_write_time);

  private:
    int compare_vectors(const double a[3], const double b[3], double c);
};


#endif
