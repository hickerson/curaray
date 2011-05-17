#include "ContinuityEvent.hh"


void ContinuityEvent::writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time)
{
    //if (get_time() >= start_write_time and get_time() < stop_write_time)
    if (time >= start_write_time and time < stop_write_time)
    {
        out << "Graphics3D[{Grey, Sphere [{"
            << get_position(0) << ", " << get_position(1) << ", " << get_position(2) << "}, "
            << "0.1]}]"; // TODO radius
    }
}
