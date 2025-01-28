CC	= gcc -O3 -pg -Wall -Wextra
INCLUDE = -I/usr/include/mpich-3.2-x86_64/
LIBS 	= -lm

OBJECTS	= AccumProps.o AllocArrays.o ApplyBoundaryCond.o Close.o    \
	  ComputeForcesCells.o EvalProps.o Init.o LeapfrogStep.o   BrownianStep.o  \
  	  main.o PrintSummary.o SetupJob.o Trajectory.o 	    \
	  EvalSpacetimeCorr.o EvalVacf.o AccumVacf.o InitVacf.o     \
	  ZeroVacf.o PrintVacf.o Integrate.o DumpState.o EvalRdf.o PrintVrms.o ComputeBondForce.o \
	  DumpBonds.o VelocityVerletStep.o ApplyForce.o	ApplyDrivingForce.o\
	  ApplyShear.o ApplyLeesEdwardsBoundaryCond.o PrintStress.o ComputePairForce.o PrintMomentum.o \
	  DisplaceAtoms.o DumpRestart.o Halt.o EvalCom.o PrintCom.o EvalVrms.o
	  


main	: $(OBJECTS) 
	$(CC) -o main $(OBJECTS) $(LIBS) $(INCLUDE)

$(OBJECTS) : global.h globalExtern.h

.PHONY : clean

clean :
	rm -rf main $(OBJECTS)

