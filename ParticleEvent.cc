#include "ParticleEvent.hh"

ParticleEvent::ParticleEvent(double t)
: Event(t)
{
    for (unsigned k = 0; k < 3; k++)
        position[k] = 0;
}

ParticleEvent::ParticleEvent(double t, const double _position[3])
: Event(t)
{
    for (unsigned k = 0; k < 3; k++)
        position[k] = _position[k];
}

ParticleEvent::ParticleEvent(double t, const Pathlet* pathlet)
: Event(t)
{
    if (pathlet)
        pathlet->get_position(t, position);
}

/*
ParticleEvent::ParticleEvent(double t, const double x[3], const double v[3])
: Event(t)
{
    before = 0;
    after = 0;
    order = 1;
    for (unsigned k = 0; k < 3; k++)
    {
        position[k] = x[k];
        in[k] = v[k];
        out[k] = v[k];
    }
}

ParticleEvent::ParticleEvent(double t, Pathlet* path_in, Pathlet* path_out) 
: Event(t)
{
    before = path_in;
    after = path_out;
    order = 2;
    if (before)
    {
        before->get_position(t, position);
        before->get_velocity(t, in);
    }
    if (order > 0)
        for (unsigned k = 0; k < 3; k++)
            out[k] = in[k];
}
*/

void ParticleEvent::redirect_vertex(Vertex* vertex)
{
    double p[3];
    assert(vertex);
    vertex->get_in(p);
    vertex->set_out(p);
    // ...
}

void ParticleEvent::writeJSON(ostream &out, double start_write_time, double stop_write_time)
{
    //if (get_time() >= start_write_time and get_time() < stop_write_time)
    {
        //out << "ParticleEvent : {" << endl
        out << "{" << endl
            << "\"position\" : ["<<get_position(0)<<", "<<get_position(1)<<", "<<get_position(2)<<"]"<< endl
            << "}" << endl;
    }
}

/*
void ParticleEvent::writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time)
{
    //if (get_time() >= start_write_time and get_time() < stop_write_time)
    if (time >= start_write_time and time < stop_write_time)
    {
        out << "Graphics3D[{Yellow, Sphere [{"
            << get_position(0) << ", " << get_position(1) << ", " << get_position(2) << "}, "
            << "0.1]}]"; // TODO radius
    }
}
*/

	//ParticleEvent::~ParticleEvent() {};

	// XXX this copies the particle around for no reason
	//     most simulations have identical particles 
	//     so store somewhere else like the particle source
/*
	double ParticleEvent::get_velocity(int i)
	{
		return velocity[i];
	}

	void ParticleEvent::set_velocity(double v[3])
	{
		for (int i=0; i<3; i++)
			velocity[i] = v[i];
	}

	// TODO move to SurfaceMap?
	void ParticleEvent::reflect_velocity(const double normal[3])
	{ 
    	double vn = dot(velocity, normal);
    	for (unsigned i = 0; i < 3; i++)
    		velocity[i] -= 2*vn*normal[i];
	}
*/

double ParticleEvent::get_position(int i)
{
    return position[i];
}

void ParticleEvent::set_position(double x[3])
{
    for (int i=0; i<3; i++)
        position[i] = x[i];
}

void ParticleEvent::set_position(const Pathlet* pathlet)
{
    if (pathlet)
        pathlet->get_position(time, position);
}
