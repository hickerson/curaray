#include "MonteCarlo.hh"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

#define dot(u,v)  (u[0]*v[0]+u[1]*v[1]+u[2]*v[2])

double randomInterval()
{
    return (double)rand()/RAND_MAX;
}

double randomRange(double a, double b)
{
    return (b-a)*(double)rand()/RAND_MAX + a;
}

double randomPowerLaw(double max, double p)
{
    return max*pow((double)rand()/RAND_MAX,1/p);
}

void randomDiskVector(double disk[3], double r) 
{
    double norm = 2;
    while (norm > 1.0)
    { // this fails half the time exactly. Ummm... try 1-pi/4!
        for (unsigned i = 0; i < 2; i++)
	    disk[i] = 2*randomInterval() - 1;
	norm = sqrt(disk[0] * disk[0]
	  	  + disk[1] * disk[1]);
    }
    for (unsigned i = 0; i < 2; i++)
		disk[i] *= r;
    disk[2] = 0;
}

void randomBallVector(double p[3], double r) 
{
	double norm = 2;
    while (norm > 1)
    {
        for (unsigned i = 0; i < 3; i++)
	    	p[i] = 2*randomInterval() - 1;
		
		norm = sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
    }
    for (unsigned i = 0; i < 3; i++)
		p[i] *= r;
}

void randomCylinderVector(double disk[3], double r, double normal[3], double h) 
{
    double norm = 2;
    while (norm > 1)
    { 
        for (unsigned i = 0; i < 3; i++)
	    disk[i] = 2*randomInterval() - 1;
	norm = sqrt(disk[0] * disk[0]
	  	  + disk[1] * disk[1]
                  + disk[2] * disk[2]);
    }
    for (unsigned i = 0; i < 3; i++)
	disk[i] *= r;
    // TODO double inner = dot(normal,disk) / norm;
    for (unsigned i = 0; i < 3; i++)
        disk[2] -= 1; // TODO fix this before using!!!
}

void randomSphereVector(double sphere[3], double r) 
{
    double norm = 0;
    while (norm < 0.355874565098000916394497394364 || norm > 1.0)
    { // this fails half the time exactly.
        for (unsigned i = 0; i < 3; i++)
	    sphere[i] = 2*randomInterval() - 1;
	norm = sqrt(sphere[0] * sphere[0]
	  	  + sphere[1] * sphere[1]
	  	  + sphere[2] * sphere[2]);
    }
    double mag = r / norm;
    for (unsigned i = 0; i < 3; i++)
	sphere[i] *= mag;
}

void randomHemiSphereVector(const double dir[3], double sphere[3], double r) 
{
	randomSphereVector(sphere, r);
	if ( dot(dir, sphere) > 0 )
		for (int i = 0; i < 3; i++)
			sphere[i] = -sphere[i];
}
