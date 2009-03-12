#include "Particle.hh"
#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;

Particle::Particle(
		double _mass,
        double _charge,
		double _decay)
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = 0;
    for(unsigned i = 0; i < 3; i++)
        momentum[i] = 0;
//    time = _time;
	mass = _mass;
    charge = _charge;
	decay = _decay;
    spin = 0;
    moment = 0;
}

Particle::Particle(
	    double _position[3],
    	double _momentum[3],
//    double _time,
   		double _mass,
        double _charge,
		double _decay,
        double _spin,
        double _moment)
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = _position[i];
    for(unsigned i = 0; i < 3; i++)
        momentum[i] = _momentum[i];
//    time = _time;
    mass = _mass;
    charge = _charge;
	decay = _decay;
    spin = _spin;
    moment = _moment;
}


Particle::Particle(
    double _position[3],
    double _momentum[3])
//    double _time,
//    double _mass)
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = _position[i];
    for(unsigned i = 0; i < 3; i++)
        momentum[i] = _momentum[i];
//    time = _time;
//    mass = _mass;
  	mass = 0;
	charge = 0;
    moment = 0;
}

Particle::Particle()
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = 0;
    for(unsigned i = 0; i < 3; i++)
        momentum[i] = 0;
//    time = 0;
    mass = 0;
    charge = 0;
    moment = 0;
	decay = 0;
}

Particle::Particle(const Particle &copy)
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = copy.position[i];
    for(unsigned i = 0; i < 3; i++)
        momentum[i] = copy.momentum[i];
//    time = copy.time;
    mass = copy.mass;
    charge = copy.charge;
    moment = copy.moment;
	decay = copy.decay;
}

// ignore Particles position and momentum
/*
Particle::Particle(const Particle & copy, 
                   const double _position[3],
                   const double _momentum[3])
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = _position[i];
    for(unsigned i = 0; i < 3; i++)
        momentum[i] = _momentum[i];

    time = copy.time;*/


/*
Particle::Particle(const Particle & copy, 
                   const double _position[3],
                   const double _momentum[3],
)//                   const double _time)
{
    for(unsigned i = 0; i < 3; i++)
    	position[i] = _position[i];
    for(unsigned i = 0; i < 3; i++)
        momentum[i] = _momentum[i];
//    time = _time;

    // the rest is copied
    mass = copy.mass;
    charge = copy.charge;
    magnetic_dipole = copy.magnetic_dipole;
}
*/

// TODO replace this with something more relavent
/*
void Particle::print() {
	printf("t = %.6f; position = (%.6f, %.6f, %.6f); momentum = (%.6f, %.6f, %.6f);\n",
		time, 
		position[0], position[1], position[2],
		momentum[0], momentum[1], momentum[2]);
}
*/

/* This isn't reall how this is done any more
// Advance particle.
void Particle::advance(double accel[3], double t_step)
    {
	double dvelo[3], dposition[3];
	for (unsigned i = 0; i < 3; i++)
	{
	    dvelo[i] = t_step * accel[i];
	    dposition[i] = t_step * (0.5 * dvelo[i] + momentum[i]);
	    position[i] += dposition[i];
	    momentum[i] += dvelo[i];
	}
	time += t_step;
    }
*/

// TODO move to SurfaceMap
// Reflect particle.
/*
void Particle::reflect(double normal[3])
{ 
    double d = dot(momentum, normal);
    for (unsigned i = 0; i < 3; i++)
    {
    	momentum[i] -= 2*d*normal[i];
    }
}
*/

/*
ParticlePath::ParticlePath(unsigned _count, double _start_time, double _stop_time)
{
    count = _count;
    start_time = _start_time;
    stop_time = _stop_time;
    //sample = new ParticlePathSample[count];
    sample.resize
    _visable = true;
}
*/


// Moved to Path.hh
#if 0
ParticlePath::ParticlePath()
{
    count = 0;
    start_time = 0;
    stop_time = 0;

    _visable = false;
    _reflections = 0;
}

ParticlePath::~ParticlePath()
{
    //if (sample)
    //	delete[] sample;
    sample.clear();
}

/*
ParticlePath::ParticlePath(const ParticlePath &copy)
{
    count = copy.count;
    start_time = copy.start_time;
    stop_time = copy.stop_time;
    //sample = new ParticlePathSample[count];
    for(unsigned i = 0; i < count; i++)
    	sample[i] = copy.sample[i];
}
*/

ParticlePathSample::ParticlePathSample()
{
    start_time = 0;
    stop_time = 0;
    reflection = false;
    order = 4;
    for (unsigned n = 0; n < MAX_ORDER; n++)
        for (unsigned i = 0; i < 3; i++)
            coefficient[n][i] = 0;
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
	coefficient[1][k] = particle.momentum[k];
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
	coefficient[1][k] = particle.momentum[k];
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


//const double[3] & ParticlePath::getPosition(double time)
void ParticlePath::getPosition(double time, double position[3])
{
    assert(time >= start_time);
    assert(time < stop_time);

    for (int i = 0; i < count; i++)
    {
        if (time >= sample[i].start_time
        and time <= sample[i].stop_time)
        {
	    sample[i].getPosition(time, position);
            return;
        }
    }
    assert(false);
}

double ParticlePath::getPosition(double start, double stop, double position[3])
{
    assert(start >= start_time);
    assert(start < stop_time);
    assert(stop > start_time);
    assert(stop <= stop_time);
    assert(start_time < stop_time);
    assert(start < stop);
    for (int i = 0; i < count; i++)
    {
        if (start >= sample[i].start_time 
        and start < sample[i].stop_time)
        {
            if (stop > sample[i].stop_time)
                stop = sample[i].stop_time;
	    sample[i].getPosition(stop, position);
            return stop;
        }
    }
    cerr << "ran out of samples." << endl;
    cerr << "start = " << start << " stop = " << stop << endl;
    cerr << "start_time = " << start_time << " stop_time = " << stop_time << endl;
    assert(false);
}

double ParticlePath::getMaximum(double start, double stop, const double direction[3])
{
    //if (start < start_time) 
    if (not (start < stop_time)) 
    {
        cerr << start << " " << stop_time << endl;
	cerr << visable() << endl;
	cerr.flush();
    }
    assert(start >= start_time);
    assert(start < stop_time);
    assert(stop > start_time);
    assert(stop <= stop_time);
    assert(start_time < stop_time);
    assert(start < stop);

    // get first distance 
    double maximum;
    int i = 0;
    while (i < count) {
        if (start >= sample[i].start_time 
        and start < sample[i].stop_time)
        {
	    // the most extreme distance must at least as extreme as this point
            maximum = sample[i].getMaximum(start, stop, direction);
	    break;
	}
	i++;
    }

    // we got the first point, now continue on looking for more extreme points
    i++;
    while (i < count)
    {
        if (stop >= sample[i].start_time)
        {
            // get maximum distance for this segment
	    double max = sample[i].getMaximum(start, stop, direction);

	    // see if this is more extreme than any other point so far
	    if (max > maximum)
	        maximum = max;
        }
	i++;
    }
    return maximum;
}

// tests a particle paths continuity
// reports number of errors
int ParticlePath::check(double epsilon)
{
    int error_count = 0;
    double last_position[3];
    double position[3];
    double last_time;
    for (int i = 0; i < count; i++)
    {
        double start = sample[i].start_time;
	sample[i].getPosition(start, position);
        if (i == 0)
        {
            if (start != start_time)
            {
                error_count++;
                cerr << "The first sample start time "
                     << "does not match the path start time." << endl
                     << "First Sample start time is " << start << " sec and "
                     << "Path start time is " << start_time << " sec." << endl;
            }
        }
        else
        {
            if (start != last_time)
            {
                error_count++;
                cerr << "Sample " << i << " start time "
                     << "does not match the previous samples end time." << endl
                     << "Sample start time is " << start << " sec and "
                     << "previous sample stop time was " 
                     << last_time << " sec." << endl;
            }
            else
            {
                double position_error_count = 0;
                for (int j = 0; j < 3; j++)
                {
                    double d = position[j] - last_position[j];
                    //if (abs(d) > epsilon)
                    if (d > epsilon or -d > epsilon)
                        position_error_count++;
                }
                if (position_error_count)
                {
                    error_count++;
                    cerr << "Sample " << i << " start position did not match "
                         << "previous sample end position." << endl;
                    cerr << "Sample start position is " << "(" 
                         << position[0] << ", "
                         << position[1] << ", "
                         << position[2] << ")." << endl;
                    cerr << "Previous sample end position was " << "(" 
                         << last_position[0] << ", "
                         << last_position[1] << ", "
                         << last_position[2] << ")." << endl;
                    cerr << endl;
                }
            }
        }

        double stop = sample[i].stop_time;
	sample[i].getPosition(stop, last_position);
        if (i == count)
        //if (i == sample.size())
        {
            if (stop != stop_time)
            {
                error_count++;
                cerr << "the last sample stop time "
                     << "does not match the path stop time." << endl
                     << "Last sample stop time is " << stop << " sec and "
                     << "Path stop time is " << stop_time << " sec." << endl;
            }
        }
        last_time = stop;
    }
    if (error_count > 0)
    {
        cerr << "There were " << error_count << " errors with "
             << "the start and stop times." << endl
             << "No point in checking more. "
             << "Fix these first. " << endl;
    }
    return error_count;
}

void ParticlePath::show()
{
    _visable = true;
}

void ParticlePath::hide()
{
    _visable = false;
}

bool ParticlePath::visable()
{
    return _visable;
}

unsigned ParticlePath::add(const ParticlePathSample &_sample)
{
	sample.push_back(_sample);
	count = sample.size();
	if (_sample.reflection)
	{
	    _reflections++;
	    double p[3];
	    double floor_level = 0.000001;
	    _sample.getStopPosition( p );
	    if (p[1] < floor_level) {
	    	hide();
		//cout << "hiding because reflection at ("
		//     << p[0] << ", " << p[1] << ", " << p[2] 
		//     << ") was below " << floor_level << endl;
	    }
	    //else
		//cout << "not hiding because of reflection" << endl;
	}
}

unsigned ParticlePath::discontinuities()
{
	return _reflections;
}
#endif
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
