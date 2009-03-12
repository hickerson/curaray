#ifndef __class_ContinuityEvent_hh__
#define __class_ContinuityEvent_hh__

#include <string>
#include <iostream>
#include "ParticleEvent.hh"
//#include "AnnihilationEvent.hh"
//#include "CreationEvent.hh"
#include "Path.hh"

using namespace std;

/**
 * ContinuityEvent
 *
 * Author: Kevin Peter Hickerson
 */
class ContinuityEvent : public ParticleEvent
//	: public CreationEvent, 
//	  public AnnihilationEvent
{
	private:
		Pathlet* before;
		Pathlet* after;
	
	public:
		unsigned order;
	
	public:
		ContinuityEvent(double t) 
			: ParticleEvent(t), 
			  before(0), after(0), order(0) // TODO
		{}	
		/*
		ContinuityEvent(Pathlet* _before, Pathlet* _after, unsigned _order)
		: before(_before), after(_after), order(_order)
		{}
		*/	
		~ContinuityEvent();
};

#endif
