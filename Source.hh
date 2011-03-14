#ifndef __SOURCE_HH__
#define __SOURCE_HH__

#include "Particle.hh"
#include "Geometry.hh"
//#include "CreationEvent.hh"
#include "ContinuityEvent.hh"

using namespace std;

//class SourceGeometry
//{
//    virtual void get_new_position(double _position[3]) = 0;
//};

// TODO move to Spectrum.hh
class Spectrum //: public Geometry
{
	//Geometry* geometry; // Geometry in phase

public:
    //virtual void get_random_momentum(double _velocity[3]) = 0;
	virtual double get_random_momentum() = 0;
};

class PowerLawSpectrum : public Spectrum
{
	double power;
	double high;
	double low; // TODO implement low cutoff (ingnored for now)
	double offset;
	
public:
	PowerLawSpectrum(double _power, double _high)
	: power(_power), high(_high), low(0), offset(0) 
	{};
	
	PowerLawSpectrum(double _power, double _high, double _low, double _offset)
	: power(_power), high(_high), low(_low), offset(_offset) 
	{};
	
	PowerLawSpectrum(double _power, double _high, double _offset)
	: power(_power), high(_high), low(0), offset(_offset) 
	{};
		
	double get_random_momentum();
};	

class Source
{
public:
    Geometry *geometry; // the spacial geometry of this source
	Geometry *momentum; // the momentum gemometry in phase space
    Spectrum *spectrum; // the energy spectrum of this source
    Particle *particle; // an example particle
	
public:
	Source(Geometry* _geometry, Geometry* _momentum, Spectrum* _spectrum, Particle* _particle)
	: geometry(_geometry), momentum(_momentum), spectrum(_spectrum), particle(_particle)
	{};
	
    //virtual Particle* get_new_particle() = 0;
	//virtual Particle* get_new_particle(double start_time, double stop_time) = 0;
	virtual double get_strength(double start_time, double stop_time);
	//virtual void get_new_particle(Particle* _particle);
	//Geometry* getGeometry() { return *gemometry };

	//virtual CreationEvent* create(double start, double stop) const;
	virtual ContinuityEvent* create(double start, double stop) const;
};


#endif
