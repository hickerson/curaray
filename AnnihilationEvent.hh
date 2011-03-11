#ifndef __class_AnnihilationEvent_hh__
#define __class_AnnihilationEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
//#include "Path.hh"


using namespace std;
class Pathlet;

/**
 * AnnihilationEvent
 *
 * Author: Kevin Peter Hickerson
 */
class AnnihilationEvent : public ParticleEvent
{
	Pathlet* before;
	double in[3];
	
public:
	//AnnihilationEvent();
	

	//~AnnihilationEvent();
};

#endif
