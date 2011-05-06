#include "Path.hh"
#include "Vertex.hh"

Vertex::Vertex(double _time, const double x[3], const double v[3])
{
    time = _time;
    event = 0;
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

Vertex::Vertex(Event* _event, const double x[3], const double v[3])
{
    event = _event;
    time = event->time;
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

Vertex::Vertex(Event* _event , Pathlet* _before, Pathlet* _after) 
{
    event = _event;
    time = event->time;
    before = _before;
    after = _after;
    order = 2;
    if (before)
    {
        before->getPosition(time, position);
        before->getVelocity(time, in);
    }
    if (order > 0)
        for (unsigned k = 0; k < 3; k++)
            out[k] = in[k];
}

double Vertex::get_position(int i)
{
    return position[i];
}

void Vertex::set_position(double x[3])
{
    for (int i=0; i<3; i++)
        position[i] = x[i];
}

double Vertex::get_in(int i)
{
    return in[i];
}

double Vertex::get_out(int i)
{
    return out[i];
}

void Vertex::get_in(double p[3])
{
    for (int i=0; i<3; i++)
        p[i] = in[i];
}

void Vertex::get_out(double p[3])
{
    for (int i=0; i<3; i++)
        p[i] = out[i];
}

void Vertex::set_in(const double p[3])
{
    for (int i=0; i<3; i++)
        in[i] = p[i];
}

void Vertex::set_out(const double p[3])
{
    for (int i=0; i<3; i++)
        out[i] = p[i];
}


void Vertex::set_event(Event* _event)
{
    assert(_event);
    event = _event;
    time = event->time;
}

void Vertex::set_before(Pathlet* _before) 
{
    before = _before;
    if (before)
    {
        before->getPosition(time, position);
        before->getVelocity(time, in);
    }
}

void Vertex::set_after(Pathlet* _after) 
{
    after = _after;
    if (after)
    {
        after->getPosition(time, position);
        after->getVelocity(time, in);
    }
}

/*
   void Vertex::set_all(Event* _event, Pathlet* _before, Pathlet* _after) 
   {
   assert(_event);
   event = _event;
   time = event->time;
   before = _before;
   after = _after;
   order = 2;
   if (before)
   {
   before->getPosition(time, position);
   before->getVelocity(time, in);
   }
   if (order > 0)
   for (unsigned k = 0; k < 3; k++)
   out[k] = in[k];
   }
 */


void Vertex::writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time)
{
    assert(event);
    event->writeMathematicaGraphics(math_file, start_write_time, stop_write_time);
}

