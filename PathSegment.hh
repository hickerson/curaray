#ifndef __PATHSEGMENT_HH__
#define __PATHSEGMENT_HH__

#include "math.h"
#include <vector>
#include "PathVertex.hh"
#include "polynomial.hh"

using namespace std;

#define dot(u,v)  (u[0]*v[0]+u[1]*v[1]+u[2]*v[2])
#define norm(u)  sqrt(u[0]*u[0]+u[1]*u[1]+u[2]*u[2])


struct PathSegment
{
public:
    double start_time;
    double stop_time;

public:
    PathVertex* start_vertex;
    PathVertex* stop_vertex;
    polynomial coefficents[3];
    //unsigned dim; // for now dim = 3
    //bool reflection;
    //bool start_reflection;
    //bool stop_reflection;
    //unsigned order; 
    //double coefficient[MAX_ORDER][3]; // at most 4th order

public:
    PathSegment();
    PathSegment(const PathSegment &);
	
    PathSegment(//const Particle & particle, 
                const double time,
		const polynomial p[3]);
    PathSegment(//const Particle & particle, 
                const double time,
		const double a[3]);
    PathSegment(//const Particle & particle, 
                const double time,
		const double a[3], 
                const double b[3]);
    PathSegment(//const Particle & particle, 
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
//typedef std::vector<PathSegment> array_PathSegment;


/*
/* moved to Path.hh
struct ParticlePath
{
    //array_PathSegment sample;
    vector<PathSegment> segments;
    int count; 
    double start_time;
    double stop_time;

private:
    bool _visable;
    int _reflections;

public:
    ParticlePath();
    ~ParticlePath();
    ParticlePath(const ParticlePath &);
    ParticlePath(int _count, double _t_start, double _t_stop);

    void getPosition(double time, double position[3]);
    double getPosition(double start, double stop, double position[3]);
    double getMaximum(double start, double stop, const double direction[3]);

    int check();
    int check(double epsilon);
    void show();
    void hide();
    bool visable();

    unsigned add(const PathSegment &_segment);
    unsigned discontinuities();
};


struct ParticlePathIter
{
    ParticlePathIter(const ParticlePath &path);
    ParticlePathIter(const ParticlePath &path,
                     double start_time, double stop_time);
    ParticlePathIter(const ParticlePath &path,
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
    const ParticlePath & _path;
    double _start_time;
    double _stop_time;
    double _step_time;
    double _time;
 
    bool _segments;
};
*/

#endif
