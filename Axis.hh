#ifndef __class_Axis_hh__
#define __class_Axis_hh__

#include "Geometry.hh"
#include "CellularComplex.hh"

using namespace std;

/**
 * Axis
 *
 * Author: Kevin Peter Hickerson
 */
template <dimension n = 3>
class Axis : public CellularComplex<1,n-1>
{
	bool infinte;
	bool for_contruction;
	//{ Point *point[2]; | CellularComplex<1,n-1>* other_axis; };

public:
	Axis() {};
	~Axis() {};

public: 
/*
	Axis* getComponent(CellularComplex<1>* p) 
	{
		return this;
	}

	virtual InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	virtual InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	virtual void writeMathematicaGraphics(ofstream & of) = 0;
	virtual void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop) = 0;
*/	

	/**
	 * Needs to return a compact project onto the line since the line is infinite
	 */
	double* get_random_point(double time) const 
	{
		// ...
		return 0;
	}
};

#endif
