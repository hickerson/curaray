//#include "loadSTL.hh"
//#include "GNUPlot.hh"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "MonteCarlo.hh"
//#include "Visualization.hh"
//#include "Volume.hh"
//#include "Solid.hh"
//#include "Box.hh"
#include "Field.hh"
#include "Simulation.hh"
#include "Sphere.hh"
#include "Plane.hh"
#include "Interval.hh"
using namespace std;

// TODO make MathematicaStream
// TODO make ParticleSource

#define MULTIPLE_MATHEMATICA_FILES 	0
#define DOWN 						2
#define DIM							3

void usage(string this_name)
{
	cout << "usage: " << this_name << " <filename>" << endl;
}

int main(int argc, char **argv)
{
	if (!argv[1])
	{
		usage(argv[0]);
    	exit(1);
	}
	string base_filename = argv[1];

	// setup the simulation environment
    // TODO will be part of the Simulation class
    const unsigned neutron_count = 100;
    const double start_time = 0;
    const double stop_time = 4;
	
	double simulation_bounds[] = {-8, 8, -8, 8, -8, 8};
	Interval<3,0>* box = new Interval<3,0>(simulation_bounds); // TODO make 4D
	Simulation simulation(box, start_time, stop_time);
	
	// add sources of neutrons 
	double neutron_mass = 10.454077; //neV s^2/m^2
	double neutron_energy = 250; // neV
	double neutron_momentum = sqrt(2*neutron_mass*neutron_energy);
	Sphere<2>* position_sphere = new Sphere<2>(0.5);
	Sphere<2>* momentum_sphere = new Sphere<2>(neutron_momentum);
	//double center[3] = {0,0,0};
	//double zero[3] = {0,0,0};
	//Sphere<2>* position_sphere = new Sphere<2>(center, 0.5);
	//Sphere<2>* momentum_sphere = new Sphere<2>(zero, neutron_momentum);
	PowerLawSpectrum* spectrum = new PowerLawSpectrum(3/2, 350, 0, 70);
	Particle* neutron = new Particle(neutron_mass, 0, 1/886.3);
	Source* source = new Source(position_sphere, momentum_sphere, spectrum, neutron);
	simulation.addSource(source);
	
	// add geometry
	double ground_normal[3] = {0,0,1.0};
	double ground_center[3] = {0,0,-2.0};
	//Plane<3>* ground = new Plane<3>(ground_normal, ground_center);
	Plane<2>* ground = new Plane<2>(ground_normal, ground_center);
	simulation.addGeometry(ground);

	// add fields
	ConstantForceField* gravity = new ConstantForceField(-9.8,2);
	simulation.addField(gravity);

     // compute paths
	simulation.run(start_time, stop_time, neutron_count);
	// TODO save simulation to file

	// TODO will be part of the Visulation class
    const unsigned frame_count = 10;
    const double frame_start_time = 0;
    const double frame_stop_time = 3;
    ofstream math_file;      
	
	// open the Mathematica file
    string math_filename = base_filename + ".math";
    math_file.open(math_filename.c_str());
    if (not math_file.is_open())
    {
		cerr << "error opening file " << math_filename << endl;
        exit(1);
    }
	
    // write the header
    math_file << "SetOptions[Plot,DisplayFunction->Identity]" << endl;
    math_file << "graphics = " << endl;
	simulation.writeMathematicaGraphics(math_file);
	//math_file << "Export[\"" << base_filename << ".eps" << "\", graphics, "
	math_file << "Export[\"" << base_filename << ".gif" << "\", graphics, "
              << "ImageSize->720, ImageResolution->200]" << endl;
    math_file << "Exit[]" << endl;

#if 1
    // Execute mathematica file
    cout << "serching in path " << getenv("PATH") << endl;
    cout << "Mathematica:" << endl;
    string s = "math -noprompt -run \"<<" + base_filename + ".math" + "\" > mathematica.log";
		cout << "Mathematica returned " << system(s.c_str()) << endl;

    // TODO sys << "math -noprompt -run \"<<" << base_filename << "\"" << execute;
    // TODO if (sys.error())
    // TODO     cerr << "Mathematica returned " << sys.error() << endl;
#else
    // Execute mathematica file
    cout << "serching in path " << getenv("PATH") << endl;
    cout << "Mathematica:" << endl;
    string s = "math -noprompt -run \"<<" + frame_name[frame]+ ".math" + "\"";
    for (int frame = 0; frame < frame_count; frame++)
    {
    string s = "math -noprompt -run \"<<" + frame_name[frame]+ ".math" + "\" > mathematica.log";
    cout << "Mathematica returned " << system(s.c_str()) << endl;
    // TODO sys << "math -noprompt -run \"<<" << math_filename[frame] << "\"" << execute;
    // TODO if (sys.error())
    // TODO     cerr << "Mathematica returned " << sys.error() << endl;
}
#endif

#if 0
for (int frame = 0; frame < frame_count; frame++)
{
    // convert output to ppm
    string s = "pstopnm -portrait -stdout -ysize=900 " + frame_name[frame] + ".eps > " + frame_name[frame] + ".ppm";
    //string s = "pstopnm -portrait -stdout " + frame_name[frame] + ".eps > " + frame_name[frame] + ".ppm";
    cout << "pstopnm returned " << system(s.c_str()) << endl;
    // TODO use system stream as above
}
#endif

#if 0
    // generate mpeg movie
    cout << "ppmtompeg" << endl;
    cout << "ppmtompeg returned " << system("ppmtompeg mpeg_conf") << endl;
#endif

#if 0
for (int frame = 0; frame < frame_count; frame++)
{
    // reduce the number of colors  
    if (frame == 0)
    {
        string str1 = "ppmquant 256 < " + frame_name[frame] + ".ppm > " 
                    + frame_name[frame] + ".pal.ppm"; 
        cout << str1 << endl;
        cout << "ppmquant returned " << system(str1.c_str()) << endl;
    }
    else
    {
        string str1 = "ppmquant -mapfile " 
                    + frame_name[0] + ".pal.ppm < " 
                    + frame_name[frame] + ".ppm > " 
                    + frame_name[frame] + ".pal.ppm"; 
        cout << str1 << endl;
        cout << "ppmquant returned " << system(str1.c_str()) << endl;
    }

    // convert ppm to gif
    string str2 = "ppmtogif < " + frame_name[frame] + ".pal.ppm > " + frame_name[frame] + ".gif";
    cout << str2 << endl;
    cout << "ppmtogif returned " << system(str2.c_str()) << endl;
}

    // generate gif movie
    cout << "gifsicle" << endl;
    string s = "gifsicle --loopcount=forever < ";
    for (int frame = 0; frame < frame_count; frame++)
        s += frame_name[frame] + ".gif ";
    s += "> " + base_filename + ".movie.gif";
    cout << "gifsicle returned " << system(s.c_str()) << endl;
    //cout << system(s.c_str()) << endl;
#endif

    cout << "done" << endl;
	
    return 0;
}
