all: sim
clean: 
	rm *.o *~ core sim

CFLAGS = -g
CXXFLAGS = -g
CC = g++
OBJECTS = Plane.o Box.o Path.o InteractionEvent.o CreationEvent.o AnnihilationEvent.o ContinuityEvent.o ParticleEvent.o Field.o loadSTL.o MonteCarlo.o Particle.o Source.o Graphics.o Volume.o Sphere.o Event.o Simulation.o Surface.o Geometry.o polynomial.o

sim: sim.o $(OBJECTS) 
	$(CC) -g -lm -Wall -lgsl -lgslcblas -o $@ $^
