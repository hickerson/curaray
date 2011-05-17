#ifndef __class_ParticleEvent_hh__
#define __class_ParticleEvent_hh__

#include <string>
#include <iostream>
#include "Event.hh"
#include "Particle.hh"
#include "Path.hh"
#include "Vertex.hh"

//using namespace std;
//class Pathlet;
//class Vertex;

/**
 * ParticleEvent
 *
 * Author: Kevin Peter Hickerson
 * Date:   March 3, 2009
 */
class ParticleEvent : public Event
{
	double position[3];
	//Pathlet* before;
	//Pathlet* after;
	//double in[3];
	//double out[3];
	//unsigned order;
	
	//bool out_of_bounds; // TODO clean up
	// Particle* particle; // reference particle type for scattering calculations

public:
	ParticleEvent(double t);
	ParticleEvent(double t, const double x[3]);
	ParticleEvent(double t, const Pathlet* pathlet);
    /* taken over in Vertex...
	ParticleEvent(double t, const double x[3], const double v[3]);
	ParticleEvent(double t, Pathlet* path_in, Pathlet* path_out);
    */
public:
/*
	ParticleEvent(double t);
	ParticleEvent(double t, double x[3]);
	~ParticleEvent();

	// XXX this copies the particle around for no reason
	//     most simulations have identical particles 
	//     so store somewhere else like the particle source

	double get_velocity(int i)
	void set_velocity(double v[3])

	void reflect_velocity(const double normal[3]); // TODO move to SurfaceMap?
*/	
	double get_position(int i);
	void set_position(double x[3]);
	void set_position(const Pathlet* pathlet);
    virtual void redirect_vertex(Vertex* vertex);

	virtual void writeJSON(ostream &out, double start_write_time, double stop_write_time);
	virtual void writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time) = 0;
};

#endif
