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
#if 0 
// only once
    // Load the STL file
    //STLfile *stl_file;
    //assert (argv[1]);
    //string stl_filename = argv[1];
    //string base_filename = stl_filename;
    //stl_file = STLfile::readSTLfile(argv[1]);
    //assert(stl_file);
#endif
	if (!argv[1])
	{
		usage(argv[0]);
    	exit(1);
	}
	string base_filename = argv[1];

	// setup the simulation environment
    // old way ...
	/*unsigned max_depth = 1;
    unsigned fields_count = 1;
    Octree octree(-1, 4,
		  -1, 4,
		  -1, 4,
		  fields_count,
		  max_depth);
	*/
	// new way ...
	//Box* box = new Box(-4, 4, -4, 4, -4, 4);
	double simulation_bounds[] = {-4, 4, -4, 4, -4, 4};
	Interval<3,0>* box = new Interval<3,0>(simulation_bounds); // TODO make 4D
    // TODO will be part of the Simulation class
    const unsigned neutron_count = 100;
    //const unsigned segment_count = 3;
    //const unsigned buffer_size = 1024;
    const double start_time = 0;
    const double stop_time = 4;
	
	Simulation simulation(box, start_time, stop_time);
	
	// add gravity
	// old way ...
    /*
	double gravity[3] = {0,-9.8,0}; // m/s^2
    VectorField *field = new ConstantGravityField(gravity);
    octree.setup_vector_fields(&field);
    octree.walls = stl_file;
	*/
	// new way ...
	//ConstantForceField *gravity = new ConstantForceField(-9.80665,DOWN); // TODO fix 
	// new way ...
	ConstantForceField *gravity = new ConstantForceField(-9.80665,DOWN); // TODO fix 
	simulation.addField(gravity);
	
    // TODO make ParticleSource
    // make all the neutrons
    // old way ...
	/*
	Particle particle[neutron_count];
    for (unsigned i = 0; i < neutron_count; i++)
    {
	double velocity[3];
	double position[3] = {0,0,0};
        randomSphereVector(velocity, randomPowerLaw(7,2));
        //randomSphereVector(velocity, randomRange(6,7));
        //randomSphereVector(velocity, 7);
        //randomDiskVector(position, 0.02);
    	Particle neutron(position, velocity, 0, 1.0);
    	particle[i] = neutron;
     }
	 */
	 
	// new way ...
	double center[3] = {0,0,0};
	double zero[3] = {0,0,0};
	double neutron_mass = 10.454077; //neV s^2/m^2
	double neutron_energy = 250; // neV
	double neutron_momentum = sqrt(2*neutron_mass*neutron_energy);
	//Sphere<2>* position_sphere = new Sphere<2>(center, 0.5);
	Sphere<2>* position_sphere = new Sphere<2>(0.5);
	//Sphere<2>* momentum_sphere = new Sphere<2>(zero, neutron_momentum);
	Sphere<2>* momentum_sphere = new Sphere<2>(neutron_momentum);
	PowerLawSpectrum* spectrum = new PowerLawSpectrum(3/2, 350, 0, 70);
	Particle* neutron = new Particle(neutron_mass, 0, 1/886.3);
	Source* source = new Source(position_sphere, momentum_sphere, spectrum, neutron);
	simulation.addSource(source);
	
	double ground_normal[3] = {0,0,1.0};
	double ground_center[3] = {0,0,-1.0};
	Plane<3>* ground = new Plane<3>(ground_normal, ground_center);
	simulation.addGeometry(ground);
	
     // compute paths
	 // old way...
	 /*
     ParticlePath ucn_path[neutron_count];
     for (unsigned i = 0; i < neutron_count; i++)
     {
     #if 0
        cout << "simulating path " << i << "...";
        cout.flush();

        // start path segments
        double last_time = start_time;
        //ucn_path[i] = ParticlePath(1024, start_time, stop_time);
        ucn_path[i].sample = new ParticlePathSample[buffer_size];
        ucn_path[i].start_time = start_time;
        ucn_path[i].stop_time = stop_time;
        ucn_path[i].count = buffer_size;
        ucn_path[i].show();
        int j = 0;
    	while (last_time < stop_time)
        {
            assert( j < buffer_size - 1);
            // copy over particle information to path
            //ParticlePathSample sample;
            //sample.stop_time = particle[i].time;
            //ucn_path[i].sample[j] = sample; // XXX replace with add
            ucn_path[i].sample[j].order = 3;
            for (int k = 0; k < 3; k++)
            {
                ucn_path[i].sample[j].coefficient[0][k] = particle[i].position[k];
                ucn_path[i].sample[j].coefficient[1][k] = particle[i].velocity[k];
                ucn_path[i].sample[j].coefficient[2][k] = gravity[k] / 2;
            }
            ucn_path[i].sample[j].start_time = last_time;
           
            // step forward
    	    // TODO octree.step_particle(&particle[i], &ucn_path[i], t_start, t_stop);
    	    octree.step_particle(&particle[i]);
            // XXX deal with this condition
            if (not octree.in_bounds(particle[i].position))
            {
       	        cerr << "{" << particle[i].position[0] << ", " 
                            << particle[i].position[2] << ", " 
                            << particle[i].position[1] << "}" << endl;
                ucn_path[i].hide();
            }

            // look for the end of the path sample
            const double next_time = particle[i].time;
            ucn_path[i].sample[j].stop_time = next_time;
            last_time = next_time;
            j++;
	}
        ucn_path[i].count = j;
        if (ucn_path[i].check(0.00000001) > 0)
        {
            cerr << "Detected errors in path " << i << "." << endl
                 << "aborting..." << endl;
            exit(1);
        }
        cout << "done." << endl;
	#endif
     }
	*/
	
	// new way ...
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
              << "ImageSize->600, ImageResolution->75]" << endl;
    math_file << "Exit[]" << endl;

#if 1
    // Execute mathematica file
    cout << "serching in path " << getenv("PATH") << endl;
    cout << "Mathematica:" << endl;
    string s = "math -noprompt -run \"<<" + base_filename + ".math" + "\"";
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
    string s = "math -noprompt -run \"<<" + frame_name[frame]+ ".math" + "\"";
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
