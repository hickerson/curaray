#ifndef __class_Simulation_hh__
#define __class_Simulation_hh__

#include <string>
#include <iostream>
#include <fstream>
//#include "Octree.hh"
#include "ParticleEvent.hh"
#include "Volume.hh"
#include "Source.hh"
#include "Field.hh"
#include "Path.hh"

using namespace std;

//typedef vector<VectorField*> VectorFieldTable;
//typedef vector<Surface*> SurfaceTable;

/**
 * Simulation
 *
 * Author: Kevin Peter Hickerson
 */
 
 
class Simulation // : Volume
{
	const Volume* 		volume;     // the volume on which the simulation is valid
    //const Volume volume;          // the volume on which the simulation is valid
	//Octree *octree;
	//vector<Surface*> surfaces;   	// surfaces that are not boundaries of volumes
	//vector<Volumes*> volumes;     // volumes with surfaces boundaries 
	vector<Field*> 		fields;     // fields that interact with particles
	vector<Geometry*> 	geometries; // geometries that interact with particles
	vector<Source*> 	sources;    // sorces of particles
	// TODO virtual Source source = 0; um... what?
	vector<Path*>   	paths;		// the paths to render

public:
	//Simulation();
	//Simulation(const BoxVolume &_region, const Octree *_octree);
	//Simulation(const Volume &_volume); // this doesn't work because volume is abstract
	Simulation(Volume *_volume);
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
	Pathlet* advance(ParticleEvent *event); // generate the next pathlet from the event
	
public: // i/o
	void writeMathematicaGraphics(ofstream & of);
};

#endif
