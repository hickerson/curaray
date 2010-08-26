#include "Box.hh"
#include "MonteCarlo.hh"

InteractionEvent* Box::interact(Pathlet* pathlet, double start_time, double stop_time) const
{
	return NULL;
}

InteractionEvent* Box::selfinteract(Pathlet* pathlet, double start_time, double stop_time) const
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

void Box::writeMathematicaGraphics(ofstream & of) 
{
	// XXX
	// TODO
	abort();
}

void Box::writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop)
{
	// XXX
	// TODO
	abort();
}
