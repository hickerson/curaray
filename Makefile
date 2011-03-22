all: sim
clean: 
	rm *.o *~ core sim

html:
	doxygen
	sudo cp -r ~/Public/sim /var/www

CFLAGS = -g
CXXFLAGS = -g -std=c++0x -Wall -Wno-deprecated
CC = g++
OBJECTS = InteractionEvent.o CreationEvent.o AnnihilationEvent.o ContinuityEvent.o ParticleEvent.o Field.o loadSTL.o MonteCarlo.o Particle.o Source.o Graphics.o polynomial.o Event.o Simulation.o Geometry.o Interval.o Ball.o Sphere.o Axis.o Plane.o CellularComplex.o Revolution.o Extrusion.o Arc.o SimplicialComplex.o Path.o Knot.o Knot.o Torus.o Point.o MathematicaStream.o MathematicaStream.o

sim: sim.o $(OBJECTS) 
	$(CC) -g -std=c++0x -lm -Wall -lgsl -lgslcblas -o $@ $^ 


