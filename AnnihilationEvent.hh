#ifndef __class_AnnihilationEvent_hh__
#define __class_AnnihilationEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
#include "Path.hh"


using namespace std;

/**
 * AnnihilationEvent
 *
 * Author: Kevin Peter Hickerson
 */
class AnnihilationEvent : public ParticleEvent
{
	private:
		Pathlet* before;
	
	public:
		// TODO AnnihilationEvent();
		~AnnihilationEvent();
};

#endif
