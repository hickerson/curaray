#include "Source.hh"
#include "MonteCarlo.hh"
#include "Path.hh"

double PowerLawSpectrum::get_random_momentum()
{
    return randomPowerLaw(high, power) + offset;
}

//CreationEvent* Source::create(double start, double stop) const
//ContinuityEvent* Source::create(double start, double stop) const
Vertex* Source::create_vertex(double start, double stop) const
{
    //double p[3];
    //double q[3];

    // TODO hack to assume uniform in time
    double t = randomRange(start, stop);
    //geometry->get_random_point(p, t);
    //momentum->get_randim_ponit(q, t);
    //double* x = geometry->get_random_point(t);
    double* x = geometry->get_random_point();
    //double* v = momentum->get_random_point(t);
    double* v = momentum->get_random_point();
    cout << "Random range returned time "<<t<<" in create."<<endl;

    for(int i=0; i<3; i++) // TODO support dimension
        v[i] /= particle->mass;

    CreationEvent *ce = new CreationEvent(t,geometry);
    assert(ce);
    return new Vertex(ce, x, v);
}

double Source::get_strength(double start_time, double stop_time)
{
    return 1;
}
