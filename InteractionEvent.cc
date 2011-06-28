#include "InteractionEvent.hh"

void InteractionEvent::writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time)
{
    if (time >= start_write_time and time < stop_write_time)
    {
        out << "Graphics3D[{Yellow, Sphere [{"
            << get_position(0) << ", " << get_position(1) << ", " << get_position(2) << "}, "
            << "0.1]}]"; // TODO radius
    }
}

void InteractionEvent::redirect_vertex(Vertex* vertex)
{
    double in[3], out[3];
    assert(vertex);
    vertex->get_in(in);
	reflect_velocity(in, out);
    vertex->set_out(out);
    // ...
}
