#pragma once
#ifndef __class_CellularComplex_hh__
#define __class_CellularComplex_hh__

#include <vector>
#include "Geometry.hh"
//#include "Cell.hh"

using namespace std;

//class InteractionEvent;

class Point;

/**
 * k-CellularComplex
 *
 * Author: Kevin Peter Hickerson
 * Created: Aug 23, 2010
 */
template <dimension k>
class CellularComplex : public Geometry
{
	//vector<Ball*> cells;
	//vector<Mates*> mates;
	//CellularComplex<k-1>* boundary;

public:
	CellularComplex() {};
	~CellularComplex() {};

public: 
	virtual CellularComplex* boolean_and(CellularComplex* p) = 0;
	virtual CellularComplex* boundary_and(CellularComplex* p) = 0;

	/**
	 * Get the sub-CellularComplex Component that contains Point p
	 */
	//virtual Point<k>* getRandomPoint(double time) const = 0;
	//virtual CellularComplex<k>* getComponent(CellularComplex<k>* p) = 0;
	//virtual CellularComplex<k>* getComponent(CellularComplex<k>* p) = 0;
	//virtual CellularComplex<k>* getComponent(CellularComplex<k-1>* p) = 0;
	/*virtual CellularComplex<k-1>* getBoundary() 
	{
		return boundary;
	};*/

	/**
	 * Get the boundary of the sub-CellularComplex Component 
	 * that contains Point p.
	 *
	virtual CellularComplex<k-1>* getBoundary(CellularComplex<k>* p) 
	{
		return getComponent(p)->getBounrdary();
	}
	 */
	/**
	 * Get the boundary of the sub-CellularComplex Component Boundary
	 * that contains Point p
	 *
	virtual CellularComplex<k-1>* getBoundary(CellularComplex<k-1>* p) 
	{
		return getComponent(p)->getBounrdary();
	}
	 */
};

#endif
