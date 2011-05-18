#include "Path.hh"
#include "Vertex.hh"

/*
Vertex::Vertex(double _time, const double x[3], const double v[3])
{
    //time = _time;
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
*/

Vertex::Vertex(Event* _event, const double x[3], const double v[3])
{
    event = _event;
    before = 0;
    after = 0;
    order = 0;
    for (unsigned k = 0; k < 3; k++)
    {
        position[k] = x[k];
        in[k] = v[k];
        out[k] = v[k];
    }
}

//Vertex::Vertex(Event* _event , Pathlet* _before, Pathlet* _after) 
Vertex::Vertex(Event* _event , Pathlet* _before) 
{
    event = _event;
    before = _before;
    after = 0;
    order = 0;
    if (before)
    {
        double time = event->time;
        before->get_position(time, position);
        before->get_velocity(time, in);
        before->get_velocity(time, out);
        //event->set_position(in);
    }
}

double Vertex::get_time()
{
    assert(event);
    return event->time;
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
    //time = event->time;
}

Event* Vertex::get_event()
{
    assert(event);
    return event;
}

void Vertex::set_before(Pathlet* _before) 
{
    assert(event);
    before = _before;
    if (before)
    {
        before->get_position(event->time, position);
        before->get_velocity(event->time, in);
    }
}

void Vertex::set_after(Pathlet* _after) 
{
    after = _after;
    if (after)
    {
        after->get_position(event->time, position);
        after->get_velocity(event->time, in);
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


void Vertex::writeJSON(ostream &out, double start_write_time, double stop_write_time)
{
    assert(event);
    out << "\"event\" : ";
    event->writeJSON(out, start_write_time, stop_write_time);
}

void Vertex::writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time)
{
    assert(event);
    event->writeMathematicaGraphics(out, start_write_time, stop_write_time);
}

