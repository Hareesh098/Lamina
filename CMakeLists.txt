cmake_minimum_required(VERSION 3.10)
project(Lamina C)

# Require C11 standard (adjust if needed)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find MPI package (must be installed on your system)
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Include additional include directories if needed
include_directories(${PROJECT_SOURCE_DIR}/source)

# List all your source files here
set(SOURCES
 source/AccumProps.c
 source/AccumVacf.c
 source/AllocArrays.c
 source/ApplyBoundaryCond.c
 source/ApplyDrivingForce.c
 source/ApplyForce.c
 source/ApplyLeesEdwardsBoundaryCond.c
 source/ApplyShear.c
 source/ApplyViscous.c
 source/BrownianStep.c
 source/Close.c
 source/ComputeBondForce.c
 source/ComputeForcesCells.c
 source/ComputePairForce.c
 source/DisplaceAtoms.c
 source/DumpBonds.c
 source/DumpPairs.c
 source/DumpRestart.c
 source/DumpState.c
 source/EvalCom.c
 source/EvalProps.c
 source/EvalRdf.c
 source/EvalSpacetimeCorr.c
 source/EvalUnwrap.c
 source/EvalVacf.c
 source/EvalVrms.c
 source/Halt.c
 source/Init.c
 source/InitVacf.c
 source/Integrate.c
 source/LeapfrogStep.c
 source/main.c
 source/PrintCom.c
 source/PrintForceSum.c
 source/PrintMomentum.c
 source/PrintStress.c
 source/PrintSummary.c
 source/PrintVacf.c
 source/PrintVrms.c
 source/ReadRestartBinary.c
 source/SetupJob.c
 source/Trajectory.c
 source/VelocityVerletStep.c
 source/WriteRestartBinary.c
 source/ZeroVacf.c
)

# Create executable target
add_executable(lamina ${SOURCES})

# Link MPI libraries
target_link_libraries(lamina ${MPI_LIBRARIES} gsl gslcblas m)

# Add MPI compile definitions and flags
target_compile_definitions(lamina PRIVATE MPI)
target_include_directories(lamina PRIVATE ${MPI_INCLUDE_PATH})
