#include "Box.hh"
#include "MonteCarlo.hh"

InteractionEvent* Box::interact(Pathlet* pathlet, double start_time, double stop_time) const
{
	return NULL;
}

double* Box::get_random_point(double time) const 
{
	double* p = new double[3];
	p[0] = randomRange(x_min, x_max);
	p[1] = randomRange(y_min, y_max);
	p[2] = randomRange(z_min, z_max);
	return p;
}
