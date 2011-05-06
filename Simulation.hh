#ifndef __class_Simulation_hh__
#define __class_Simulation_hh__

#include <string>
#include <iostream>
#include <fstream>
//#include "Octree.hh"
//#include "ParticleEvent.hh"
//#include "CreationEvent.hh"
#include "InteractionEvent.hh"
//#include "Volume.hh"
//#include "Solid.hh"
#include "Source.hh"
#include "Field.hh"
#include "Path.hh"
#include "Vertex.hh"
//#include "CellularComplex.hh"

using namespace std;

//typedef vector<VectorField*> VectorFieldTable;
//typedef vector<Surface*> SurfaceTable;
//typedef CellularComplex<3> Solid;

/**
 * Simulation
 *
 * Author: Kevin Peter Hickerson
 */
class Simulation
{
	double 				earliest_time; 	/// the earliest time boundary of the simulation
	double 				latest_time;  	/// the latest time boundary of the simulation
    const Geometry*  	volume;         /// the geometry on which the simulation is valid

	vector<Field*> 		fields;     	/// fields that interact with particles
	vector<Geometry*> 	geometries; 	/// geometries that interact with particles
	vector<Source*> 	sources;    	/// sources of point-like particles
	vector<Path*>   	paths;			/// the paths of simulated particles
	
public:
	//Simulation();
	Simulation(const Geometry *_volume);
	Simulation(const Geometry *_volume, double _start_time, double _stop_time);
	~Simulation();
	
	void addField(Field *field);
	void addGeometry(Geometry *geometry);
	void addSource(Source *source);
	// TODO void setVolume(Geometry *geometry);
	// TODO void addSink(...);	
	// TODO void addVisulization(...);	

	//void addSurface(Surface * _surface);
	//void addVolume(Surface * _surface);
	//void addSurface(STLSurface * stl_surface); // TODO UCNSimulation only
	//void add(STLSurface * stl_surface); 

public:
	// void run(const Particle & particle, double start_time, double stop_time);
	//Path* run(double start_time, double stop_time);
	bool run(double start_time, double stop_time);
	//void run(double start_time, double stop_time, int particle_count, Path**);
	int run(double start_time, double stop_time, int particle_count);
	
public: // i/o
	void writeMathematicaGraphics(ofstream & of);
	void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop);

private:
	//Pathlet* solve_pathlet(ContinuityEvent *event); // generate the next pathlet from the event
	Pathlet* solve_pathlet(Vertex *vertex); // generate the next pathlet from the event
};

#endif
