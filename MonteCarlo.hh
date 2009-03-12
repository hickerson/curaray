#ifndef __MONTE_CARLO_H__
#define __MONTE_CARLO_H__

double randomInterval();
double randomRange(double a, double b);
double randomPowerLaw(double max, double power);

void randomDiskVector(double disk[3], double r);
void randomBallVector(double p[3], double r);
void randomCylinderVector(double disk[3], double r, double normal[3], double h);
void randomSphereVector(double sphere[3], double r);
void randomHemiSphereVector(const double dir[3], double sphere[3], double r);

#endif //__MONTE_CARLO_H__
