#include "Particle.hh"
#include <stdio.h>
#include <assert.h>
#include <iostream>

using namespace std;


Particle::Particle(
    double _position[3],
    double _velocity[3],
    double _time,
    double _mass,
    double _charge,
    double _magnetic_dipole)
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = _position[i];
    for(unsigned i = 0; i < 3; i++)
        velocity[i] = _velocity[i];
    time = _time;
    mass = _mass;
    charge = _charge;
    magnetic_dipole = _magnetic_dipole;
}

Particle::Particle(
    double _position[3],
    double _velocity[3],
    double _time,
    double _mass)
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = _position[i];
    for(unsigned i = 0; i < 3; i++)
        velocity[i] = _velocity[i];
    time = _time;
    mass = _mass;
    charge = 0;
    magnetic_dipole = 0;
}

Particle::Particle()
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = 0;
    for(unsigned i = 0; i < 3; i++)
        velocity[i] = 0;
    time = 0;
    mass = 0;
    charge = 0;
    magnetic_dipole = 0;
}

Particle::Particle(const Particle &copy)
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = copy.position[i];
    for(unsigned i = 0; i < 3; i++)
        velocity[i] = copy.velocity[i];
    time = copy.time;
    mass = copy.mass;
    charge = copy.charge;
    magnetic_dipole = copy.magnetic_dipole;
}

// ignore Particles position and velocity
Particle::Particle(const Particle & copy, 
                   const double _position[3],
                   const double _velocity[3])
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = _position[i];
    for(unsigned i = 0; i < 3; i++)
        velocity[i] = _velocity[i];

    time = copy.time;
    mass = copy.mass;
    charge = copy.charge;
    magnetic_dipole = copy.magnetic_dipole;
}

Particle::Particle(const Particle & copy, 
                   const double _position[3],
                   const double _velocity[3],
                   const double _time)
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = _position[i];
    for(unsigned i = 0; i < 3; i++)
        velocity[i] = _velocity[i];
    time = _time;

    // the rest is copied
    mass = copy.mass;
    charge = copy.charge;
    magnetic_dipole = copy.magnetic_dipole;
}

void Particle::print() {
	printf("t = %.6f; position = (%.6f, %.6f, %.6f); velocity = (%.6f, %.6f, %.6f);\n",
		time, 
		position[0], position[1], position[2],
		velocity[0], velocity[1], velocity[2]);
}

// Advance particle.
void Particle::advance(double accel[3], double t_step)
    {
	double dvelo[3], dposition[3];
	for (unsigned i = 0; i < 3; i++)
	{
	    dvelo[i] = t_step * accel[i];
	    dposition[i] = t_step * (0.5 * dvelo[i] + velocity[i]);
	    position[i] += dposition[i];
	    velocity[i] += dvelo[i];
	}
	time += t_step;
    }

// Reflect particle.
void Particle::reflect(double normal[3])
{ 
    double d = dot(velocity, normal);
    for (unsigned i = 0; i < 3; i++)
    {
    	velocity[i] -= 2*d*normal[i];
    }
}


/*
ParticlePathSample::ParticlePathSample(unsigned _order, double _start_time, double _stop_time)
{
    start_time = _start_time;
    stop_time = _stop_time;
    reflection = false;
    order = _order;
}

ParticlePathSample::~ParticlePathSample()
{
}
*/

ParticlePathSample::ParticlePathSample(const ParticlePathSample &copy)
{
    start_time = copy.start_time;
    stop_time = copy.stop_time;
    reflection = false;
    order = copy.order;
    for (unsigned n = 0; n < order; n++)
        for (unsigned i = 0; i < 3; i++)
            coefficient[n][i] = copy.coefficient[n][i];
}

ParticlePathSample::ParticlePathSample(const Particle & particle, 
                                       const double time, 
				       const double a[3])
{
    start_time = particle.time;
    stop_time = particle.time + time;
    reflection = false;
    order = 3;
    for (int k = 0; k < 3; k++)
	coefficient[0][k] = particle.position[k];
    for (int k = 0; k < 3; k++)
	coefficient[1][k] = particle.velocity[k];
    for (int k = 0; k < 3; k++)
	coefficient[2][k] = a[k] / 2;
}

ParticlePathSample::ParticlePathSample(const Particle & particle, 
                                       const double time, 
				       const double a[3], 
				       const double b[3])
{
    start_time = particle.time;
    stop_time = particle.time + time;
    reflection = false;
    order = 3;
    for (int k = 0; k < 3; k++)
	coefficient[0][k] = particle.position[k];
    for (int k = 0; k < 3; k++)
	coefficient[1][k] = particle.velocity[k];
    for (int k = 0; k < 3; k++)
	coefficient[2][k] = a[k] / 2;
    for (int k = 0; k < 3; k++)
	coefficient[3][k] = b[k] / 6;
}

ParticlePathSample::ParticlePathSample(const Particle & particle, 
                                       const double time,
				       const double a[3], 
				       const double b[3], 
				       const double c[3])
{
	// TODO
	assert(false);
}

// Reflect particle.
void ParticlePathSample::reflect(double normal[3])
{ 
    reflection = true;
/*
    double d = dot(coefficient[1], normal);
    for (unsigned i = 0; i < 3; i++)
    {
    	coefficient[1][i] -= 2*d*normal[i];
    }
 */
}

// Reflect particle.
void ParticlePathSample::noreflect()
{ 
    reflection = false;
}

//const double[3] & ParticlePathiSample::getPosition(double time)
void ParticlePathSample::getPosition(double time, double position[3]) const
{
    assert(time >= start_time);
    assert(time <= stop_time);
    assert(order > 0);

    for (int i = 0; i < 3; i++)
        position[i] = coefficient[0][i];
 
    double t = time - start_time;
    double t_power = t;
    for (int n = 1; n < order; n++)
    {
        for (int i = 0; i < 3; i++)
            position[i] += coefficient[n][i] * t_power;
        t_power *= t;
        //t_power *= t / n; // tayler 
    }
/*
    for (int i = 0; i < 3; i++)
        position[i] = 0;
 
    double time_power = 1;
    for (int n = 0; n < order; n++)
    {
        for (int i = 0; i < 3; i++)
            position[i] += coefficient[n][i] * time_power;
        time_power *= (time - start_time);
    }
*/
}

void ParticlePathSample::getStartPosition(double position[3]) const
{
	getPosition(start_time, position);
}

void ParticlePathSample::getStopPosition(double position[3]) const
{
	getPosition(stop_time, position);
}

double ParticlePathSample::getMaximum(double start, double stop, const double direction[3]) const
{
    assert(start < stop_time);
    assert(stop > start_time);
    assert(start_time < stop_time);
    assert(start < stop);
    
    double a = dot(coefficient[2], direction);
    double b = dot(coefficient[1], direction);
    double c = dot(coefficient[0], direction);
    if (a < 0)
    {
        // first find maximum for this parabola
    	double t = - b / (2*a); // Changed Oct 24, 2007
    	//double t = - b / a;
#if 0
	double time = t + start_time;
	//double tmp_t = t;

        // next clip to the desired range
	if (start < start_time)
	    start = start_time;

	if (stop > stop_time)
	    stop = stop_time;

        // then find the constrained end that has the maximum if not in range
	if (time < start)
	    t = start - start_time;

	if (time > stop)
	    t = stop - start_time;

        //if (t == tmp_t)
	//    cout << "no change in t" << endl;
#endif
	return a*t*t + b*t + c; // Changed Oct 24, 2007 
	//return a*t*t/2 + b*t + c;
    }
    else if (a > 0)
    {
        // TODO compute the opposite case farthest away from the minimum
        assert(false);
    }
    else
    {
        // TODO we have a line
	// TODO look at the end points
        assert(false);
    }
}



/*
ParticlePathIter::ParticlePathIter(const ParticlePath &path) :
    _time(path.start_time),
    _path(path),
    _start_time(path.start_time),
    _stop_time(path.stop_time),
    _step_time(0),
    _segments(true)
{
}

ParticlePathIter::ParticlePathIter(const ParticlePath &path,
                                   double start_time, 
                                   double stop_time) :
    _time(path.start_time),
    _path(path),
    _start_time(path.start_time),
    _stop_time(path.stop_time),
    _step_time(0),
    _segments(true)
{
 //TODO check to path bounds
}

ParticlePathIter::ParticlePathIter(const ParticlePath &path,
                                   double start_time, 
                                   double stop_time,
                                   double step_time) :
    _time(start_time),
    _path(path),
    _start_time(start_time),
    _stop_time(stop_time),
    _step_time(step_time),
    _segments(true)
{
 //TODO check to path bounds
}

void ParticlePathIter::start()
{
    _time = _start_time;
}

void ParticlePathIter::start(double start_time)
{
    if (start_time >= _path.start_time)
        _start_time = start_time;
    else
        _start_time = _path.start_time;
    _time = _start_time;
}

void ParticlePathIter::next()
{
    //if (_time < _stop_time)
}

bool ParticlePathIter::more()
{
    return _time < _stop_time;
}

void ParticlePathIter::ignore_segments()
{
    _segments = false;
}

void ParticlePathIter::stepto_segments()
{
    _segments = true;
}
*/
