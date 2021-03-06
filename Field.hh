#ifndef __FIELD_HH__
#define __FIELD_HH__

//#include "Octree.hh"
#include "Particle.hh"
#include "ParticleEvent.hh"
#include "Path.hh"
#include <assert.h>

class Field 
{
public:
	//virtual int get_degree(const ParticleEvent* event, unsigned axis) = 0;
	virtual int get_degree(unsigned axis) = 0;
	virtual double get_acceleration(const Vertex* vertex, unsigned axis) = 0;
};

/*
class VectorField : public Field
{
};
*/

struct CentralForceField : public Field
{
    double _center[3];
    double _mass;

  public:
    CentralForceField(const double *center,
	                double mass);
    
    virtual bool should_subdivide(const double *center,
	                              double size);
    virtual void compute_field(const double *position,
	                           double *field_out);
    virtual void get_force (const Particle *particle,
			                const double *field_value,
			                double       *force_out);

  	//virtual int get_degree(const ParticleEvent* event, unsigned axis) 
  	virtual int get_degree(unsigned axis) 
  	{ 
		cout << "not supported yet" << endl;
		return 4; // TODO fix this shit! 
	}
	
	virtual double get_acceleration(const Vertex* vertex, unsigned axis);
};

struct ConstantForceField : public Field
{
    double _gravity[3];

  public:
    ConstantForceField(const double gravity[3]);
    ConstantForceField(double gravity, int axis); // force along one axis
	
    virtual bool should_subdivide(const double *center,
	                              double size);
    virtual void compute_field(const double *position,
	                           double *field_out);
    virtual void get_force (const Particle *particle,
			                const double *field_value,
			                double       *force_out);
  	//virtual int get_degree(const ParticleEvent* event, unsigned axis) 
  	virtual int get_degree(unsigned axis);
	
	// TODO to require event time and particle properties
	virtual double get_acceleration(const Vertex* vertex, unsigned axis);
};

#endif
