#pragma once
#ifndef __class_CellularComplex_hh__
#define __class_CellularComplex_hh__

//#include <boost/graph/adjacency_list.hpp>
#include <boost/spirit/core.hpp>

#include <vector>
#include "Geometry.hh"
//#include "Cell.hh"
#include "Point.hh"

using namespace std;

//class InteractionEvent;

//class Point;

/**
 * k-CellularComplex
 *
 * Author: Kevin Peter Hickerson
 * Created: Aug 23, 2010
 */
template <dimension k, codimension n = 0>
class CellularComplex : public Geometry
{
protected:
	// The blob graph is only valid for n > 1
	
	//vector<Ball*> cells;
	//vector<Mates*> mates;
	//CellularComplex<k-1>* boundary;

public:
	CellularComplex() {};
	~CellularComplex() {};

public: 
	//virtual CellularComplex* get_union(CellularComplex* p) = 0;
	//virtual CellularComplex* boundary_and(CellularComplex* p) = 0;

	/**
	 * Get the sub-CellularComplex Component that contains Point p
	 */
	//virtual Point<k>* getRandomPoint(double time) const = 0;
	//virtual CellularComplex<k>* getComponent(CellularComplex<k>* p) = 0;
	//virtual CellularComplex<k>* getComponent(CellularComplex<k>* p) = 0;
	//virtual CellularComplex<k>* getComponent(CellularComplex<k-1>* p) = 0;
	virtual CellularComplex<k-1,n+1>* get_boundary() = 0;
	virtual CellularComplex<1,1>* intersection(CellularComplex<1,k+n-1>* p) = 0;

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

/**
 * (0,n)-CellularComplex
 * 
 * This is a disjoint union of Points in n dimension
template <>
class CellularComplex<0,codimension n> : public Geometry
{
	//...
	virtual (void*) get_boundary() = 0;
	{ 
		return 0;
	}
};
 */

#endif
