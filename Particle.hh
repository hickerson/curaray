#ifndef __PARTICLE_HH__
#define __PARTICLE_HH__

#include "math.h"
#include <vector>
//#include "Path.hh"

#define dot(u,v)  (u[0]*v[0]+u[1]*v[1]+u[2]*v[2])
#define norm(u)  sqrt(u[0]*u[0]+u[1]*u[1]+u[2]*u[2])

struct Particle
{
	double position[3]; 
	double momentum[3];
	
    double mass;
	double charge;
	double decay; 
	
	double spin;
    double moment;
 
	Particle(
        double _position[3],
        double _momentum[3],
        double _mass,
        double _charge,
		double _decay,
		double _spin,
        double _moment);

	Particle(
        double _mass,
        double _charge,
		double _decay);
	
    Particle(
        double _position[3],
        double _momentum[3]);

    Particle();
    Particle(const Particle &);
    /*Particle(const Particle &, 
             const double _position[3],
             const double _velocity[3]);
    Particle(const Particle &, 
             const double _position[3],
             const double _velocity[3],
             const double _time);
    */
	//~Particle();

/*
    double get_speed() const {
        // TODO use the above macro
		// TODO or not.
	double rv_squared;
	rv_squared = velocity[0] * velocity[0]
	           + velocity[1] * velocity[1]
	           + velocity[2] * velocity[2];
	return sqrt(rv_squared);
    }
*/
    void print(); // TODO make this use <<
    //void advance(double accel[3], double t_step);
    //void reflect(double normal[3]);
};

#if 0
/*
#define MAX_ORDER 4
struct ParticlePathSample
{
public:
    double start_time;
    double stop_time;

public:
    //ParticlePathVertex* start_vertex;
    //ParticlePathVertex* stop_vertex;
    bool reflection;
    bool start_reflection;
    bool stop_reflection;
    unsigned order; 
    double coefficient[MAX_ORDER][3]; // at most 4th order

public:
    ParticlePathSample();
    ParticlePathSample(const ParticlePathSample &);
    ParticlePathSample(const Particle & particle, 
                       const double time,
		       const double a[3]);
    ParticlePathSample(const Particle & particle, 
                       const double time,
		       const double a[3], 
                       const double b[3]);
    ParticlePathSample(const Particle & particle, 
                       const double time,
		       const double a[3], 
		       const double b[3],
		       const double c[3]);

public:
    void getPosition(double time, double position[3]) const ;
    void getStartPosition(double position[3]) const ;
    void getStopPosition(double position[3]) const ;
    double getMaximum(double start, double stop, const double direction[3]) const ;
    void reflect(double normal[3]);
    void noreflect();
};
typedef std::vector<ParticlePathSample*> ParticlePathSampleTable;
typedef std::vector<ParticlePathSample*> table_ParticlePathSample;
typedef std::vector<ParticlePathSample> array_ParticlePathSample;
*/
#endif

#endif
