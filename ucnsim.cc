#include "loadSTL.hh"
#include "GNUPlot.hh"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fields.hh"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "MonteCarlo.hh"
#include "Visualization.hh"
using namespace std;

// TODO make MathematicaStream
// TODO make ParticleSource

#define MULTIPLE_MATHEMATICA_FILES 0

int main(int argc, char **argv)
{
#if 1 
// only once
    // Load the STL file
    STLfile *stl_file;
    assert (argv[1]);
    string stl_filename = argv[1];
    string base_filename = stl_filename;
    stl_file = STLfile::readSTLfile(argv[1]);
    assert(stl_file);
#endif

// setup the simulation environment
    unsigned max_depth = 1;
    unsigned fields_count = 1;
    Octree octree(-1, 4,
		  -1, 4,
		  -1, 4,
		  fields_count,
		  max_depth);

    double gravity[3] = {0,-9.8,0}; // m/s^2
    //double gravity[3] = {0,0,0}; // m/s^2
    VectorField *field = new ConstantGravityField(gravity);
    octree.setup_vector_fields(&field);
    octree.walls = stl_file;

    // TODO will be part of the Simulation class
    const unsigned neutron_count = 100;
    const unsigned segment_count = 3;
    const unsigned buffer_size = 1024;
    const double start_time = 0;
    const double stop_time = 3;

    // TODO will be part of the Visulation class
    const unsigned frame_count = 10;
    const double frame_start_time = 0;
    const double frame_stop_time = 3;
    ofstream math_file; 

    // TODO make ParticleSource
    // make all the neutrons
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

     // compute paths
     ParticlePath ucn_path[neutron_count];
     for (unsigned i = 0; i < neutron_count; i++)
     {
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
     }

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
    math_file << "graphics = Show[" << endl;
 
    // write the stl file first
    stl_file->writeMathematicaGraphics(math_file);
    // TODO math_file << stl_file; XXX no endl at the end
    math_file << "," << endl;

    // prep for drawing the paths
    math_file << "Graphics3D[{" << endl << "RGBColor[0,0,0]";

#if 0
     for (unsigned i = 0; i < neutron_count; i++)
     {
        cout << "ploting path " << i << "...";
        // start path segments
        double last_time = start_time;
        if (ucn_path[i].visable())
        {
        for (int frame = 0; frame < frame_count; frame++)
        {
    	    const double frame_start_time = (stop_time - start_time) * (double)frame / (double)frame_count + start_time;
    	    const double frame_stop_time = (stop_time - start_time) * ((double)frame + 1) / (double)frame_count + start_time;
            math_file << "," << endl 
                      << setiosflags(ios::fixed) 
                      << setprecision(8)
                      << "Line[{";
            // TODO write first point
            bool first_time = true;
    	    for (double segment = 0; segment < segment_count; segment += 1.0)
    	    {
    	        const double time = (stop_time - start_time)
                                  * (frame + segment / (segment_count - 1)) 
                                  / frame_count 
                                  + start_time;
                while (last_time < time or first_time)
                {
                    double p[3];
	    	    if (first_time)
                    {
       		        ucn_path[i].getPosition(time, p);
                        last_time = time;
                    }
                    else
                    {
            	        math_file[frame] << "," << endl;
       		        last_time = ucn_path[i].getPosition(last_time, time, p);
                    }
			
       		    math_file[frame] << "{" << p[0] << ", " << p[2] << ", " << p[1] << "}";
                    first_time = false;
                }
	    }
            math_file[frame] << "}]";
        }
        }
        cout << "done." << endl;
     }
#endif

    // close Mathematica files
    math_file << " }], PlotRange -> {{-1, 6}, {0,1}, {-0.5, 3.5}}];" << endl;
    // TODO add range to Visulisation class
    //math_file << " }], PlotRange -> {{-.1, 4}, {0,1}, {-0.1, 3.1}}];" << endl;
    //math_file << " }], PlotRange -> {{4, 6}, {0,1}, {-0.5, 3.5}}];" << endl;
    math_file << "Export[\"" << base_filename << ".eps" << "\", graphics, "
              << "ImageSize->600, ImageResolution->75]" << endl;
    math_file << "Exit[]" << endl;
    math_file << "Quit[]" << endl;

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
