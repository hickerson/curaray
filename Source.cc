#include "Source.hh"
#include "MonteCarlo.hh"

double PowerLawSpectrum::get_random_momentum()
{
	return randomPowerLaw(high, power) + offset;
}

CreationEvent* Source::create(double start, double stop) const
{
		//double p[3];
		//double q[3];

		// TODO hack to assume uniform in time
	double time = randomRange(start, stop);
		//geometry->get_random_point(p, time);
		//momentum->get_randim_ponit(q, time);
	//double* x = geometry->get_random_point(time);
	double* x = geometry->get_random_point();
	//double* q = momentum->get_random_point(time);
	//double* v = momentum->get_random_point(time);
	double* v = momentum->get_random_point();
	for(int i=0; i<3; i++)
		v[i] /= particle->mass;
	return new CreationEvent(time, x, v);
}

double Source::get_strength(double start_time, double stop_time)
{
	return 1;
}
