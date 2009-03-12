#ifndef __class_UCNEvent_hh__
#define __class_UCNEvent_hh__

#include <string>
#include <iostream>

#include "UCNeutron.hh"
#include "Event.hh"
#include "Particle.hh"

using namespace std;

/**
 * UCNEvent
 *
 * Author: Kevin Peter Hickerson
 */
class UCNEvent
{
	UCNeutron neutron;
	ParticlePath particle;

    public:
	UCNEvent();
	~UCNEvent();
	
	void run(const Particle & particle, double start_time, double stop_time);
};

#endif
