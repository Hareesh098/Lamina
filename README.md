# Lamina: A Molecular Dynamics Package

<p align="center">
  <img src="./figures/LogoLaminaLatex.png" alt="Lamina Logo" width="300"/>
</p>

Welcome to the **Lamina** documentation!

---

## Overview

**Lamina** is a modular 2D molecular dynamics (MD) simulation package designed for simulating hybrid soft solids, including spring networks 
and finite-size discs. Written in C, it models a wide variety of soft and condensed matter systems. It supports robust time evolution integrators 
and a range of thermostats, providing accurate force evaluations for bonded and non-bonded interactions.

Originally developed for 2D bonded systems, **Lamina** now supports broader research goals including active matter, granular solids, and 
complex fluids.

---

## Why "Lamina"?

The word **Lamina** comes from Latin, meaning "a thin layer", "a plate", or "a sheet". In nature and science, laminae often refer to flat, 
two-dimensional structural elements such as leaves, thin metal sheets, or tissue membranes.

This name reflects both the **two-dimensional (2D)** nature of the simulations and the types of materials **Lamina** is built to study: 
**liquids**, **soft solids**, and **networked structures** confined to thin sheets or layers. Just as natural laminae exhibit rich structural and 
dynamic behaviors in simple geometry, this code explores the complexity of emergent phenomena in 2D soft matter systems.

---

## Key Features

### Interaction Potentials
- Yukawa potential (screened Coulomb interactions)
- Lennard-Jones potential (standard 12-6)
- Harmonic bond potential (elastic network models)
- Hookean granular contact potential (for soft granular matter)

### Thermostats and Temperature Control
- Gaussian thermostat
- Nose-Hoover thermostat
- Langevin thermostat
- Configurational temperature evaluation and control

### Time Integration
- Leap-Frog integrator
- Velocity-Verlet integrator
- Langevin (stochastic) integrator
- Brownian (overdamped) integrator

### Physical Observables
- Radial Distribution Function (RDF)
- Velocity Autocorrelation Function (VACF)
- Root-Mean-Square Velocity (VRMS)
- Stress tensor and momentum
- Center-of-mass motion
- Space-time correlation functions

### Output and Utilities
- Output files saved to `../output` folder — ensure this directory exists relative to where you run the code
- Run the simulation with:  
  ```bash
  ./main prefix
  ```
- Structured output files: `.xyz`, `.bond`, `.pair`, `.com`, `.result`
- Restart and resume capability: `.restart` and `.state` files
- Clear separation of source code, unit tests, and output
- Support for Lees–Edwards boundary conditions (sheared systems)
- Configurable halting conditions based on VRMS or custom metrics
- Modular design for easy extension of potentials and features

---

## Project Structure

```plaintext
Lamina/
  |-- source/                  # C source files; avoid placing README.md here to prevent extra pages
  |     |-- main.c             # Main driver
  |     |-- *.c, *.h           # Modular source files
  |-- unittest/                # Unit test suite (planned or implemented)
  |     |-- test_*.c           # Individual test cases
  |-- output/                  # Runtime output files
  |-- prepros/                 # Preprocessing scripts/tools (.sh, .py, etc.)
  |-- postpros/                # Postprocessing scripts/tools (.sh, .py, etc.)
  |-- doxygen/                 # Doxygen configuration and auxiliary files
  |     |-- Doxyfile           # Doxygen config file
  |     |-- header.tex         # Custom LaTeX header for docs
  |     \-- extra_stylesheet.css # Optional CSS for HTML styling
  |-- figures/                 # Figures, logos, icons used in docs/code
  |     \-- LogoLaminaLatex.png # Project logo for documentation
  |-- docs/                    # Generated documentation (HTML, LaTeX, PDFs)
  |     |-- html/              # Doxygen-generated HTML docs
  |     |-- latex/             # Doxygen-generated LaTeX sources
  |     \-- refman.pdf         # Generated PDF manual
  |-- Makefile                 # Build system for manual Make builds
  |-- CMakeLists.txt           # CMake build system configuration
  |-- README.md                # This main documentation file
  \-- .github/                 # GitHub configuration directory
        \-- workflows/         # GitHub Actions workflows for CI/CD
            \-- ci.yml         # CI workflow file
  |--generate-docs.sh          # To genrate the html and latex documents 
```

---

## Installation Instructions

### Prerequisites

1. **GCC Compiler**  
   Install `gcc` to compile C code:

   - Ubuntu/Debian:  
     ```bash
     sudo apt-get install build-essential
     ```
   - Fedora/CentOS:  
     ```bash
     sudo dnf install gcc
     ```
   - macOS (via Homebrew):  
     ```bash
     brew install gcc
     ```CI Build Status

2. **MPICH (MPI Library)**
   Required for parallel computations:

   - Ubuntu/Debian:  
     ```bash
     sudo apt-get install libmpich-dev
     ```
   - Fedora/CentOS:  
     ```bash
     sudo dnf install mpich
     ```
   - macOS:  
     ```bash
    brew install mpich
    ```

3. **OpenMP**
   Required for multi-threaded bond force calculations:

   - Ubuntu/Debian:
     ```bash
     sudo apt-get install libomp-dev
     ```
   - Fedora/CentOS:
     ```bash
     sudo dnf install libgomp
     ```
   - macOS:
     ```bash
     brew install libomp
     ```

4. **CMake (Recommended for modern builds)**
   Install `cmake` to build with the CMake system:

   - Ubuntu/Debian:  
     ```bash
     sudo apt-get install cmake
     ```
   - Fedora/CentOS:  
     ```bash
     sudo dnf install cmake
     ```
   - macOS:  
     ```bash
     brew install cmake
     ```

---

## Building Lamina

You can build Lamina either using the traditional Makefile or the CMake build system.

### Using Makefile

```bash
cd Lamina/source
make clean
make 
```

To build and run unit tests:

```bash
cd ../unittest
make clean
make all
make run
```

---

### Using CMake (Recommended)

This builds the project in a clean isolated directory and manages dependencies automatically.

```bash
cd Lamina
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

To run unit tests (assuming they are built in `unittest` and `mpirun` is used):

```bash
cd ../unittest
make clean
make all
make run
```

---

## Continuous Integration (CI) with GitHub Actions

The project includes a GitHub Actions workflow (`.github/workflows/ci.yml`) that automates building and testing on Ubuntu runners with MPI installed.

The workflow performs the following:

- Checks out the latest code on push or pull requests to the `main` branch.
- Installs build dependencies including `build-essential`, `cmake`, `mpich`, and MPI development libraries.
- Configures and builds Lamina using CMake in the `build` directory.
- Runs the unit tests in parallel using MPI.

You can view the build status and logs on the **Actions** tab of the GitHub repository.


---

## Documentation

- Browse full [HTML documentation](https://hareesh098.github.io/Lamina/)
- Download [Source code PDF manual](https://github.com/Hareesh098/Lamina/blob/main/docs/latex/refman.pdf)
- User manual [Physics PDF manual](https://github.com/Hareesh098/Lamina/blob/main/docs/README.pdf)
- Documentation generated with [Doxygen 1.10.0](https://www.doxygen.nl/)

---

Thank you for your interest in **Lamina**! Contributions and feedback are welcome.  
Please check the repository for the latest updates and contact information.

# Adding a Build Status Badge
[![CI Build Status](https://github.com/Hareesh098/Lamina/actions/workflows/ci.yml/badge.svg)](https://github.com/Hareesh098/Lamina/actions/workflows/ci.yml)

