#include "Field.hh"

#define a_tolerance 0.0001 // TODO calculate tolerances corectly

double CentralForceField::get_acceleration(const Vertex* vertex, unsigned axis)
{
	assert(false);
}

CentralForceField::CentralForceField(const double *center,
		                         double mass) 
{
    _mass = mass;
    for(int i = 0; i < 3; i++)
        _center[i] = center[i];
}

bool CentralForceField::should_subdivide(const double *center,
			                   double size)
{
    // dir = (center - position)
    double dir[3];
    for(int i = 0; i < 3; i++)
	dir[i] = _center[i] - center[i];
    double norm = sqrt(dir[0] * dir[0] 
	             + dir[1] * dir[1] 
		     + dir[2] * dir[2]);
    double d = norm - size / 2;
    if ( d < 0 )
	return true;
    if ( a_tolerance < _mass * (1/(d*d) - 1/(norm*norm)) )
	return true;
    return false;
}

void CentralForceField::compute_field(const double *position,
			                double *field_out)
{
    // dir = (center - position)
    // a = (center - position) M / |center - position|^3
    double dir[3];
    for(int i = 0; i < 3; i++)
	dir[i] = _center[i] - position[i];
    double norm = sqrt(dir[0] * dir[0] 
	             + dir[1] * dir[1] 
		     + dir[2] * dir[2]);
    double denominator = norm * norm * norm;
    for(int i = 0; i < 3; i++)
    	field_out[i] = _mass * dir[i] / denominator;
}

void CentralForceField::get_force (const Particle *particle,
			const double *field_value,
			double       *force_out)
{
    // f = m * a
    for(int i = 0; i < 3; i++)
    	force_out[i] = particle->mass * field_value[i];
}

// ConstantForceField
ConstantForceField::ConstantForceField(const double *gravity)
{
    for(int i = 0; i < 3; i++)
        _gravity[i] = gravity[i];
}

// ConstantForceField
ConstantForceField::ConstantForceField(double gravity, int axis)	                         
{
	// TODO throw error if out of bounds?
    _gravity[ axis   %3] = gravity;
	_gravity[(axis+1)%3] = 0;
	_gravity[(axis+2)%3] = 0;
	//cout << "_gravity =("<<_gravity[0] <<","<< _gravity[1] <<","<< _gravity[2] <<")" <<endl;
	//exit(0);
}

bool ConstantForceField::should_subdivide(const double *center,
			                              double size)
{
    return false;
}

void ConstantForceField::compute_field(const double *position,
			                double *field_out)
{
    for(int i = 0; i < 3; i++)
    	field_out[i] = _gravity[i];
}

void ConstantForceField::get_force (const Particle *particle,
			const double *field_value,
			double       *force_out)
{
    // f = m * a
    for(int i = 0; i < 3; i++)
    	force_out[i] = particle->mass * field_value[i];
}

int ConstantForceField::get_degree(unsigned axis) 
{
	if (_gravity[axis] == 0)
		return 0;
	else 
		return 2;
}

// TODO to require vertex time and particle properties
double ConstantForceField::get_acceleration(const Vertex* vertex, unsigned axis)
{
	//cout << "_gravity[axis]" << _gravity[axis] <<endl;
	return _gravity[axis];
}
