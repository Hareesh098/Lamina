cmake_minimum_required(VERSION 3.10)
project(Lamina C)

# Require C11 standard (adjust if needed)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find MPI package (must be installed on your system)
find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Include additional include directories if needed
include_directories(${PROJECT_SOURCE_DIR}/source)

# List all your source files here
set(SOURCES
    source/AccumProps.c
    source/AllocArrays.c
    source/ApplyBoundaryCond.c
    source/Close.c
    source/ComputeForcesCells.c
    source/EvalProps.c
    source/Init.c
    source/LeapfrogStep.c
    source/BrownianStep.c
    source/main.c
    source/PrintSummary.c
    source/SetupJob.c
    source/Trajectory.c
    source/EvalSpacetimeCorr.c
    source/EvalVacf.c
    source/AccumVacf.c
    source/InitVacf.c
    source/ZeroVacf.c
    source/PrintVacf.c
    source/Integrate.c
    source/DumpState.c
    source/EvalRdf.c
    source/PrintVrms.c
    source/ComputeBondForce.c
    source/DumpBonds.c
    source/VelocityVerletStep.c
    source/ApplyForce.c
    source/ApplyDrivingForce.c
    source/ApplyShear.c
    source/ApplyLeesEdwardsBoundaryCond.c
    source/PrintStress.c
    source/ComputePairForce.c
    source/PrintMomentum.c
    source/DisplaceAtoms.c
    source/DumpRestart.c
    source/Halt.c
    source/EvalCom.c
    source/PrintCom.c
    source/EvalVrms.c
    source/EvalUnwrap.c
    source/DumpPairs.c
    source/ApplyViscous.c
)

# Create executable target
add_executable(lamina ${SOURCES})

# Link MPI libraries
target_link_libraries(lamina ${MPI_LIBRARIES} gsl gslcblas m OpenMP::OpenMP_C)

# Add MPI compile definitions and flags
target_compile_definitions(lamina PRIVATE MPI)
target_include_directories(lamina PRIVATE ${MPI_INCLUDE_PATH})
