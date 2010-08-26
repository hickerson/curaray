#ifndef __class_Simulation_hh__
#define __class_Simulation_hh__

#include <string>
#include <iostream>
#include <fstream>
//#include "Octree.hh"
#include "ParticleEvent.hh"
//#include "Volume.hh"
//#include "Solid.hh"
#include "Source.hh"
#include "Field.hh"
#include "Path.hh"
#include "CellularComplex.hh"

using namespace std;

//typedef vector<VectorField*> VectorFieldTable;
//typedef vector<Surface*> SurfaceTable;
typedef CellularComplex<3> Solid;

/**
 * Simulation
 *
 * Author: Kevin Peter Hickerson
 */
class Simulation // : Volume
{
	double 				earliest_time; 	/// the earliest time boundary of the simulation
	double 				latest_time;  	/// the latest time boundary of the simulation
	//const Volume* 		volume;     	/// the volume on which the simulation is valid
    const Solid* volume;          		/// the volume on which the simulation is valid
	//Octree *octree;
	//vector<Surface*> surfaces;   		/// surfaces that are not boundaries of volumes
	//vector<Volumes*> volumes;     	/// volumes with surfaces boundaries 

	vector<Field*> 		fields;     	/// fields that interact with particles
	vector<Geometry*> 	geometries; 	/// geometries that interact with particles
	vector<Source*> 	sources;    	/// sorces of particles
	vector<Path*>   	paths;			/// the paths of simulated particles
	
public:
	//Simulation();
	//Simulation(const BoxVolume &_region, const Octree *_octree);
	//Simulation(const Volume &_volume); // this doesn't work because volume is abstract
	Simulation(const Solid *_volume);
	Simulation(const Solid *_volume, double _start_time, double _stop_time);
	~Simulation();
	
	void addField(Field *field);
	void addGeometry(Geometry *geometry);
	void addSource(Source *source);
	//void setVolume(Volume *volume);
	
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
	Pathlet* advance(ParticleEvent *event); // generate the next pathlet from the event
};

#endif
